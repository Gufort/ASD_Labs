#pragma once

//  Фрагменты для реализации сбалансированных деревьев поиска - заготовка, не рабочая, доделать

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <string>
#include <iterator>
#include <memory>
#include <iomanip>
#include <memory_resource>
#include <initializer_list>
#include <functional>
#include <exception>

template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class AVL_Tree
{
	Compare cmp = Compare();

	class Node
	{
	public:
		Node* parent;
		Node* left;
		Node* right;
		unsigned short height;
		T data;
		Node(T value = T(), Node* p = nullptr, Node* l = nullptr, Node* r = nullptr, unsigned short h = 1) : parent(p), data(value), left(l), right(r), height(h) {}
	};

	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc < Node >;
	AllocType Alc;

	void clone(Node* from, Node* other_dummy)
	{
		if (from == other_dummy)
			return;
		insert(from->data);
		clone(from->right, other_dummy);
		clone(from->left, other_dummy);
	}
public:
	using key_type = T;
	using key_compare = Compare;
	using value_compare = Compare;
	using value_type = typename T;
	using allocator_type = typename AllocType;
	using size_type = typename size_t;
	using difference_type = typename size_t;
	using pointer = typename T*;
	using const_pointer = typename const pointer;
	using reference = value_type&;
	using const_reference = const value_type&;
	class iterator;
	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	Node* dummy;
	size_type tree_size = 0;

	// Создание фиктивной вершины - используется только при создании дерева
	inline Node* make_dummy()
	{
		// Выделяем память по размеру узла без конструирования
		dummy = Alc.allocate(1);

		//  Все поля, являющиеся указателями на узлы (left, right, parent) инициализируем и обнуляем
		std::allocator_traits<AllocType>::construct(Alc, &(dummy->parent));
		dummy->parent = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->left));
		dummy->left = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->right));
		dummy->right = dummy;

		dummy->height = 0;

		//  Возвращаем указатель на созданную вершину
		return dummy;
	}

	// Создание узла дерева 
	template <typename T>
	inline Node* make_node(T&& elem, Node* parent, Node* left, Node* right)
	{
		// Создаём точно так же, как и фиктивную вершину, только для поля данных нужно вызвать конструктор
		Node* new_node = Alc.allocate(1);

		//  Все поля, являющиеся указателями на узлы (left, right, parent) инициализируем и обнуляем
		std::allocator_traits<AllocType>::construct(Alc, &(new_node->parent));
		new_node->parent = parent;

		std::allocator_traits<AllocType>::construct(Alc, &(new_node->left));
		new_node->left = left;

		std::allocator_traits<AllocType>::construct(Alc, &(new_node->right));
		new_node->right = right;

		//  Конструируем поле данных
		std::allocator_traits<AllocType>::construct(Alc, &(new_node->data), std::forward<T>(elem));
		new_node->data = elem;

		updateHeight(new_node);

		//  Возвращаем указатель на созданную вершину
		return new_node;
	}

	// Удаление фиктивной вершины
	inline void delete_dummy(Node* node) {
		std::allocator_traits<AllocType>::destroy(Alc, &(node->parent));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->left));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->right));
		std::allocator_traits<AllocType>::deallocate(Alc, node, 1);
	}

	// Удаление вершины дерева
	inline void delete_node(Node* node) {
		//  Тут удаляем поле данных (вызывается деструктор), а остальное удаляем так же, как и фиктивную
		std::allocator_traits<AllocType>::destroy(Alc, &(node->data));
		delete_dummy(node);
	}

	int getHeight(Node* node) {
		if (node != dummy) return node->height;
		return 0;
	}

	void updateHeight(Node* node) {
		if (node != dummy)
			node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
	}

	int balanceCheck(Node* node) {
		return getHeight(node->left) - getHeight(node->right);
	}

	// Поворот вправо
	Node* rotateRight(Node* node) {
		Node* curr = node->left;

		//В соответсвии со схемой с curr и node делаем правое поддерево curr левым для node
		node->left = curr->right;
		if (curr->right != dummy)
			curr->right->parent = node;

		//Теперь curr родитель для node
		curr->parent = node->parent;
		node->parent = curr;
		curr->right = node;

		//Обновляем значение height в узлах
		updateHeight(node);
		updateHeight(curr);

		return curr;
	}

	//С поворотом влево все обстоит аналогично
	Node* rotateLeft(Node* node) {
		Node* curr = node->right;

		node->right = curr->left;
		if (curr->left != dummy)
			curr->left->parent = node;

		curr->parent = node->parent;
		node->parent = curr;
		curr->left = node;

		updateHeight(curr);
		updateHeight(node);

		return curr;
	}

	Node* rebalance(Node* node) {
		updateHeight(node);

		if (balanceCheck(node) == 2) {
			if (balanceCheck(node->left) < 0) {
				node->left = rotateLeft(node->left);
				node->left->parent = node;
			}
				
			Node* root = rotateRight(node);
			if (root->parent != dummy) {
				if (root->parent->left == node)
					root->parent->left = root;
				else root->parent->right = root;
			}

			return root;
		}

		else if (balanceCheck(node) == -2) {
			if (balanceCheck(node->right) > 0) {
				node->right = rotateRight(node->right);
				node->right->parent = node;
			}

			Node* root = rotateLeft(node);
			if (root->parent != dummy) {
				if (root->parent->left == node)
					root->parent->left = root;
				else root->parent->right = root;
			}

			return root;
		}

		return node;
	}

public:
	class iterator
	{
		friend class Tree;
	public:

		Node* data;
		Node* dummy_node;

		bool isNil() {
			return data == dummy_node;
		}

		Node* Next() const
		{
			if (data == dummy_node) return dummy_node;
			Node* current = data;
			if (current->right != dummy_node)
			{
				current = current->right;
				while (current->left != dummy_node)
					current = current->left;
				return current;
			}
			Node* parent = current->parent;
			while (parent != dummy_node && current == parent->right)
			{
				current = parent; 
				parent = parent->parent;
			}
			return parent;
		}



		Node* Prev() const
		{
			if (data == dummy_node) return dummy_node->right;
			Node* current = data;
			if (current->left != dummy_node)
			{
				current = current->left;
				while (current->right != dummy_node)
					current = current->right;
				return current;
			}
			Node* parent = current->parent;
			while (parent != dummy_node && current == parent->left)
			{
				current = parent;
				parent = parent->parent;
			}
			return parent;
		}

		explicit iterator(Node* _data, Node* _dummy) : data(_data), dummy_node(_dummy) {	}

		Node*& _data()
		{
			return data;
		}

		inline bool isLeaf() const
		{
			return data->left == dummy_node && data->right == dummy_node;
		}

		inline iterator Parent() const noexcept
		{
			return iterator(data->parent, dummy_node);
		}

		inline iterator Left() const noexcept
		{
			return iterator(data->left, dummy_node);
		}

		inline iterator Right() const noexcept
		{
			return iterator(data->right, dummy_node);
		}

		inline bool IsLeft() const noexcept
		{
			return data->parent->left == data;
		}

		inline bool IsRight() const noexcept
		{
			return data->parent->right == data;
		}

		iterator GetMin() {
			iterator current = *this;
			iterator end = iterator(dummy_node, dummy_node);
			while (current.Left() != end)
				current = current.Left();
			return current;
		}

		iterator GetMax() {
			iterator current = *this;
			iterator end = iterator(dummy_node, dummy_node);
			while (current.Right() != end)
				current = current.Right();
			return current;
		}


	public:

		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = AVL_Tree::value_type;
		using difference_type = AVL_Tree::difference_type;
		using pointer = AVL_Tree::pointer;
		using reference = AVL_Tree::reference;


		T& operator*() const
		{
			return data->data;
		}


		iterator& operator++()
		{
			data = Next();
			return *this;
		}

		iterator& operator--()
		{
			data = Prev();
			return *this;
		}

		iterator operator++(int) {
			iterator t = *this;
			++*this;
			return t;
		}

		iterator operator--(int) {
			iterator t = *this;
			--*this;
			return t;
		}

		friend bool operator == (const iterator& it_1, const iterator& it_2)
		{
			return it_1.data == it_2.data;
		}

		friend bool operator != (const iterator& it_1, const iterator& it_2)
		{
			return !(it_1 == it_2);
		}

		const iterator& operator=(const reverse_iterator& it) = delete;
		bool operator==(const reverse_iterator& it) = delete;
		bool operator!=(const reverse_iterator& it) = delete;
		iterator(const reverse_iterator& it) = delete;
	};


	iterator begin() const noexcept { return iterator(dummy->left, dummy); }
	iterator end() const noexcept { return iterator(dummy, dummy); }
	reverse_iterator rbegin() const	noexcept { return reverse_iterator(end()); }
	reverse_iterator rend() const noexcept { return reverse_iterator(begin()); }

	void recursivePrint() {
		infix(dummy->parent);
	}

	void infix(Node* node) {
		if (node == dummy) return;
		infix(node->left);
		std::cout << node->data << " ";
		infix(node->right);
	}

	AVL_Tree(Compare comparator = Compare(), AllocType alloc = AllocType())
		: dummy(make_dummy()), cmp(comparator), Alc(alloc) {}

	AVL_Tree(std::initializer_list<T> il) : dummy(make_dummy())
	{
		for (const auto& x : il)
			insert(x);
	}

	AllocType get_allocator() const noexcept { return Alc; }
	key_compare key_comp() const noexcept { return cmp; }
	value_compare value_comp() const noexcept { return cmp; }

	inline bool empty() const noexcept { return tree_size == 0; }

private:
	template <class RandomIterator>
	void ordered_insert(RandomIterator first, RandomIterator last, iterator position) {
		if (first == last) return;

		RandomIterator center = first;
		std::advance(center, std::distance(first, last) / 2);
		iterator new_pos = insert(position, *center);
		ordered_insert(first, center, position);
		ordered_insert(++center, last, ++position);
	}

public:
	template <class InputIterator>
	AVL_Tree(InputIterator first, InputIterator last, Compare comparator = Compare(), AllocType alloc = AllocType()) : dummy(make_dummy()), cmp(comparator), Alc(alloc)
	{
		//  Проверка - какой вид итераторов нам подали на вход
		if (std::is_same<typename std::iterator_traits<InputIterator>::iterator_category, typename std::random_access_iterator_tag>::value) {
			//  Если итератор произвольного доступа, то есть надежда, что диапазон отсортирован
			//    а даже если и нет - не важно, всё равно попробуем метод деления пополам для вставки
			ordered_insert(first, last, end());
		}
		else
			std::for_each(first, last, [this](T x) { insert(x); });
	}

	AVL_Tree(const AVL_Tree& tree) : dummy(make_dummy())
	{	//  Размер задаём
		tree_size = tree.tree_size;
		if (tree.empty()) return;

		dummy->parent = recur_copy_tree(tree.dummy->parent, tree.dummy);
		dummy->parent->parent = dummy;

		//  Осталось установить min и max
		dummy->left = iterator(dummy->parent, dummy).GetMin()._data();
		dummy->right = iterator(dummy->parent, dummy).GetMax()._data();
	}

private:
	Node* recur_copy_tree(Node* source, const Node* source_dummy)
	{
		//  Сначала создаём дочерние поддеревья
		Node* left_sub_tree;
		if (source->left != source_dummy)
			left_sub_tree = recur_copy_tree(source->left, source_dummy);
		else
			left_sub_tree = dummy;

		Node* right_sub_tree;
		if (source->right != source_dummy)
			right_sub_tree = recur_copy_tree(source->right, source_dummy);
		else
			right_sub_tree = dummy;

		Node* current = make_node(source->data, nullptr, left_sub_tree, right_sub_tree);
		if (source->right != source_dummy)
			current->right->parent = current;
		if (source->left != source_dummy)
			current->left->parent = current;
		return current;
	}

public:
	AVL_Tree(reverse_iterator r_1, reverse_iterator r_2) :dummy(make_dummy()), tree_size(0) {
		for (auto it = r_2.base(); it != r_1.base(); ++it) {
			insert(*it);
		}
	}

	const AVL_Tree& operator=(const AVL_Tree& other)
	{
		if (this == &other) return *this;

		AVL_Tree tmp{ other };
		swap(tmp);

		return *this;
	}

	void swap(AVL_Tree& other) noexcept {
		std::swap(dummy, other.dummy);
		std::swap(tree_size, other.tree_size);
	}

	size_type size() const { return tree_size; }


	std::pair<iterator, bool> insert(const T& value) {
		Node* found = find(value).data;
		if (found != dummy && !cmp(value, found->data) && !cmp(found->data, value)) {
			return std::make_pair(iterator(found, dummy), false);
		}


		dummy->parent = insert(dummy->parent, value);

		while (dummy->parent->parent != dummy) {
			dummy->parent = dummy->parent->parent;
		}

		if (dummy->parent != dummy) {
			dummy->left = iterator(dummy->parent, dummy).GetMin().data;
			dummy->right = iterator(dummy->parent, dummy).GetMax().data;
		}

		Node* inserted = find(value).data;
		return std::make_pair(iterator(inserted, dummy), true);
	}

	// Вспомогательная функция для рекурсивной вставки
	Node* insert(Node* root, const T& value)
	{
		if (root == dummy)
		{
			Node* tmp = make_node(value, dummy, dummy, dummy);
			tree_size++;
			return tmp;
		}

		if (cmp(value, root->data))
		{
			root->left = insert(root->left, value);
			root->left->parent = root;
		}

		else if (cmp(root->data, value))
		{
			root->right = insert(root->right, value);
			root->right->parent = root;
		}

		else
			return root;

		updateHeight(root);
		return rebalance(root);
	}


	iterator insert(const_iterator position, const value_type& x) {
		return insert(x).first;
	}

	//  Не самый лучший вариант.
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last) 
			insert(*first++);
	}

	iterator find(const value_type& value) const {
		iterator current = iterator(dummy->parent, dummy);
		while (current != end()) {
			if (cmp(value, *current)) current = current.Left();
			else if (!cmp(value, *current) && !cmp(*current, value)) break;
			else current = current.Right();
		}
		return current;
	}

	iterator lower_bound(const value_type& key) {
		iterator current(dummy->parent, dummy);
		iterator result = current;
		while (current != end()) {
			if (!cmp(*current, key)) {
				result = current;
				current = current.Left();
			}
			else current = current.Right();
		}
		return result;
	}

	const_iterator lower_bound(const value_type& key) const {
		return const_iterator(const_cast<AVL_Tree*>(this)->lower_bound(key));
	}

	iterator upper_bound(const value_type& key) {
		iterator current(dummy->parent, dummy);
		iterator result = current;
		while (current != end()) {
			if (!cmp(key, *current))
				current = current.Right();
			else
			{
				result = current;
				current = current.Left();
			}
		}
		return result;
	}

	const_iterator upper_bound(const value_type& key) const {
		return const_iterator(const_cast<AVL_Tree*>(this)->upper_bound(key));
	}

	size_type count(const value_type& key) const {
		return find(key) != end() ? 1 : 0;
	}

	std::pair<const_iterator, const_iterator> equal_range(const value_type& key) const {
		return std::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
	}

protected:
	//  Меняет местами текущий узел и максимальный в левом поддереве. Возвращает тот же итератор, но теперь он без правого поддерева
	iterator replace_with_max_left(iterator it)
	{
		auto elem = end();
		if (it.Left() == end()) elem = it.Right().GetMin();
		else elem = it.Left().GetMax();
		swap_iterators(elem, it);
		return it;
	}

public:
	iterator erase(iterator elem) {
		if (elem.data == dummy) return iterator(dummy, dummy);

		Node* node_to_delete = elem.data;
		iterator next = ++elem;

		//Узел является листом
		if (node_to_delete->left == dummy && node_to_delete->right == dummy) {
			if (node_to_delete->parent->left == node_to_delete)
				node_to_delete->parent->left = dummy;
			else node_to_delete->parent->right = dummy;

			if (node_to_delete == dummy->left)
				dummy->left = next.data;
			if (node_to_delete == dummy->right)
				dummy->right = iterator(node_to_delete, dummy).Prev();
		}

		//Узел с одним доченим 
		else if (node_to_delete->left == dummy || node_to_delete->right == dummy) {
			Node* child = (node_to_delete->left != dummy) ? node_to_delete->left : node_to_delete->right;

			if (node_to_delete->parent != dummy) {
				if (node_to_delete->parent->left == node_to_delete)
					node_to_delete->parent->left = child;

				else node_to_delete->parent->right = child;

				child->parent = node_to_delete->parent;
			}
			else {
				node_to_delete->parent->parent = child;
				child->parent = node_to_delete->parent;
			}

			if (node_to_delete == dummy->left)
				dummy->left = next._data();
			if (node_to_delete == dummy->right)
				dummy->right = iterator(node_to_delete, dummy).Prev();

			delete_node(node_to_delete);
		}

		//Узел с двумя дочерними
		else {
			Node* current = node_to_delete->right;
			while (current->left != dummy)
				current = current->left;

			node_to_delete->data = current->data;
			if (current->parent->left == current)
				current->parent->left = current->right;

			else current->parent->right = current->right;


			if (current->right != dummy)
				current->right->parent = current->parent;
			if (current == dummy->left)
				dummy->left = next._data();
			if (current == dummy->right)
				dummy->right = iterator(current, dummy).Prev();

			delete_node(current);
		}

		--tree_size;
		updateHeight(dummy->parent);
		dummy->parent = rebalance(dummy->parent);
		return next;
	}


	size_type erase(const value_type& elem) {
		iterator it = find(elem);
		if (it == end())
			return 0;
		erase(it);
		return 1;
	}

	//  Проверить!!!
	iterator erase(iterator first, iterator last)
	{
		iterator res = end();
		while (first != last)
			res = erase(first++);
		return res;
	}

	//Если передавать по ссылкам, все хорошо. Конструктор копий при нескольких деревьях ломается.
	friend bool operator==(const AVL_Tree<T>& tree_1, const AVL_Tree<T>& tree_2)
	{
		auto i = tree_1.begin(), ii = tree_2.begin();
		for (; (i != tree_1.end()) && (ii != tree_2.end()); ++i, ++ii)
		{
			if (*i != *ii)
				return false;
		}
		return i == tree_1.end() && ii == tree_2.end();
	}

	//  Очистка дерева (без удаления фиктивной вершины)
	void clear() {
		Free_nodes(dummy->parent);
		tree_size = 0;
		dummy->parent = dummy->left = dummy->right = dummy;
	}

	void printTree() const {
		printTree(dummy->parent, 0);
	}


private:
	void printTree(Node* node, int depth) const {
		if (node == dummy) return;
		printTree(node->right, depth + 1);
		std::cout << std::setw(depth * 4) << " " << node->data << std::endl;
		printTree(node->left, depth + 1);
	}

	//  Рекурсивное удаление узлов дерева, не включая фиктивную вершину
	void Free_nodes(Node* node)
	{
		if (node != dummy)
		{
			Free_nodes(node->left);
			Free_nodes(node->right);
			delete_node(node);
		}
	}

	Node* findMin(Node* node) {
		while (node->left != dummy)
			node = node->left;
		return node;
	}

public:
	~AVL_Tree()
	{
		clear(); // рекурсивный деструктор
		delete_dummy(dummy);
	}
};

template <class Key, class Compare, class Allocator>
void swap(AVL_Tree<Key, Compare, Allocator>& x, AVL_Tree<Key, Compare, Allocator>& y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
};


template <class Key, class Compare, class Allocator>
bool operator==(const AVL_Tree<Key, Compare, Allocator>& x, const AVL_Tree<Key, Compare, Allocator>& y) {
	typename AVL_Tree<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	return it1 == x.end() && it2 == y.end();
}

template <class Key, class Compare, class Allocator>
bool operator<(const AVL_Tree<Key, Compare, Allocator>& x, const AVL_Tree<Key, Compare, Allocator>& y) {

	typename AVL_Tree<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	if (it1 == x.end())
		return it2 != y.end();

	return it2 != y.end() && *it1 < *it2;
}

template <class Key, class Compare, class Allocator>
bool operator!=(const AVL_Tree<Key, Compare, Allocator>& x, const AVL_Tree<Key, Compare, Allocator>& y) {
	return !(x == y);
}

template <class Key, class Compare, class Allocator>
bool operator>(const AVL_Tree<Key, Compare, Allocator>& x, const AVL_Tree<Key, Compare, Allocator>& y) {
	return y < x;
}

template <class Key, class Compare, class Allocator>
bool operator>=(const AVL_Tree<Key, Compare, Allocator>& x, const AVL_Tree<Key, Compare, Allocator>& y) {
	return !(x < y);
}

template <class Key, class Compare, class Allocator>
bool operator<=(const AVL_Tree<Key, Compare, Allocator>& x, const AVL_Tree<Key, Compare, Allocator>& y) {
	return   !(y < x);
}
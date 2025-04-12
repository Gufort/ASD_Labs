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
class Binary_Search_Tree
{
	Compare cmp = Compare();

	class Node
	{
	public: 
		Node* parent;
		Node* left;
		Node* right;
		T data;
		Node(T value = T(), Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : parent(p), data(value), left(l), right(r){}
	};

	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc < Node >;
	AllocType Alc;
	
	void clone(Node * from, Node * other_dummy)
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
	using pointer = typename T *;
	using const_pointer = typename const pointer;
	using reference = value_type & ;
	using const_reference = const value_type &;
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

		//  Возвращаем указатель на созданную вершину
		return dummy;
	}

	// Создание узла дерева 
	template <typename T>
	inline Node* make_node(T&& elem, Node * parent, Node* left, Node* right)
	{
		// Создаём точно так же, как и фиктивную вершину, только для поля данных нужно вызвать конструктор
		Node * new_node = Alc.allocate(1);
		
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
	inline void delete_node(Node * node) {
		//  Тут удаляем поле данных (вызывается деструктор), а остальное удаляем так же, как и фиктивную
		std::allocator_traits<AllocType>::destroy(Alc, &(node->data));
		delete_dummy(node);
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
			if (data == dummy_node) return dummy_node->left;

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
		using value_type = Binary_Search_Tree::value_type;
		using difference_type = Binary_Search_Tree::difference_type;
		using pointer = Binary_Search_Tree::pointer;
		using reference = Binary_Search_Tree::reference;


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


	iterator begin() const noexcept { return iterator(dummy->left, dummy);	}
	iterator end() const noexcept { return iterator(dummy, dummy);  }
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

	Binary_Search_Tree(Compare comparator = Compare(), AllocType alloc = AllocType())
		: dummy(make_dummy()), cmp(comparator), Alc(alloc) {}

	Binary_Search_Tree(std::initializer_list<T> il) : dummy(make_dummy())
	{
		for (const auto &x : il)
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
	Binary_Search_Tree(InputIterator first, InputIterator last, Compare comparator = Compare(), AllocType alloc = AllocType()) : dummy(make_dummy()), cmp(comparator), Alc(alloc)
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

	Binary_Search_Tree(const Binary_Search_Tree & tree) : dummy(make_dummy())
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
	Binary_Search_Tree(reverse_iterator r_1, reverse_iterator r_2):dummy(make_dummy()), tree_size(0) {
		for (auto it = r_2.base(); it != r_1.base(); ++it) {
			insert(*it);
		}
	}

	const Binary_Search_Tree& operator=(const Binary_Search_Tree& other)
	{
		if (this == &other) return *this;

		Binary_Search_Tree tmp{ other };
		swap(tmp);

		return *this;
	}

	void swap(Binary_Search_Tree& other) noexcept {
		std::swap(dummy, other.dummy);
		std::swap(tree_size, other.tree_size);
	}

	size_type size() const { return tree_size; }


	std::pair<iterator, bool> insert(const T& value)
	{
		iterator i = end().Parent();

		if (i == i.Parent())
		{
			Node* tmp = make_node(value, dummy, dummy, dummy);
			dummy->left = tmp;
			dummy->right = tmp;
			dummy->parent = tmp;
			tree_size++;
			return std::make_pair(iterator(tmp, dummy), true);
		}

		while (true)
		{
			if (cmp(value, *i))
			{
				if (i.Left() != end())
					i = i.Left();
				else
				{
					Node* tmp = make_node(value, i._data(), dummy, dummy);
					i._data()->left = tmp;
					if (end().Left() == i)
						dummy->left = tmp;
					tree_size++;
					return std::make_pair(iterator(tmp, dummy), true);
				}
			}
			else if (!cmp(value, *i) && !cmp(*i, value))
			{
				return std::make_pair(i, false);
			}

			else
			{
				if (i.Right() != end())
					i = i.Right();
				else
				{
					Node* tmp = make_node(value, i._data(), dummy, dummy);
					i._data()->right = tmp;
					if (end().Right() == i)
						dummy->right = tmp;
					tree_size++;
					return std::make_pair(iterator(tmp, dummy), true);
				}
			}
		}
	}

	iterator insert(const_iterator position, const value_type& x) {
		return insert(x).first;
	}

	//  Не самый лучший вариант.
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last) insert(*first++);
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
		return const_iterator(const_cast<Binary_Search_Tree *>(this)->lower_bound(key));
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
		return const_iterator(const_cast<Binary_Search_Tree*>(this)->upper_bound(key));
	}

	size_type count(const value_type& key) const {
		return find(key) != end() ? 1 : 0;
	}

	std::pair<const_iterator, const_iterator> equal_range(const value_type& key) const {
		return std::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
	}

protected:
	//  Удаление листа дерева. Возвращает количество удалённых элементов
	/*size_type delete_leaf(iterator leaf) {
		Node* parent = leaf.Parent()._data();
		if (leaf.Parent() == end()) {
			dummy->parent = dummy;
			dummy->left = dummy;
			dummy->left = dummy;
		}
		else if (leaf.IsLeft()) {
			leaf.Parent()._data()->left = dummy;
		}
		else {
			parent->right = dummy;
		}
		delete_node(leaf._data());
		--tree_size;
		return 1;
	}*/

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
	//  Удаление элемента, заданного итератором. Возвращает количество удалённых элементов (для set - 0/1)
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

			--tree_size;
			delete_node(node_to_delete);
			return next;
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
	iterator erase(const_iterator first, const_iterator last) {
		while (first != last) {
			iterator next = ++first;
			erase(--first);   
			first = next;
		}
		return last;
	}

	//Если передавать по ссылкам, все хорошо. Конструктор копий при нескольких деревьях ломается.
	friend bool operator==(const Binary_Search_Tree<T> &tree_1, const Binary_Search_Tree<T> & tree_2)
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
	
public:
	~Binary_Search_Tree()
	{
		clear(); // рекурсивный деструктор
		delete_dummy(dummy);
	}
};

template <class Key, class Compare, class Allocator>
void swap(Binary_Search_Tree<Key, Compare, Allocator>& x, Binary_Search_Tree<Key, Compare, Allocator>& y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
};


template <class Key, class Compare, class Allocator>
bool operator==(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	typename Binary_Search_Tree<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	return it1 == x.end() && it2 == y.end();
}

template <class Key, class Compare, class Allocator>
bool operator<(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	
	typename Binary_Search_Tree<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	if (it1 == x.end())
		return it2 != y.end();
	
	return it2 != y.end() && *it1 < *it2;
}

template <class Key, class Compare, class Allocator>
bool operator!=(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	return !(x == y);
}

template <class Key, class Compare, class Allocator>
bool operator>(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	return y < x;
}

template <class Key, class Compare, class Allocator>
bool operator>=(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	return !(x<y);
}

template <class Key, class Compare, class Allocator>
bool operator<=(const Binary_Search_Tree<Key, Compare, Allocator>& x, const Binary_Search_Tree<Key, Compare, Allocator>& y) {
	return   !(y < x);
}




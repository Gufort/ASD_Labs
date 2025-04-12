#ifndef TREE
#define TREE
#include <iostream>
#include <stack>
#include <queue>
#include <functional>

template<typename T>
class Node {
public:
	T Data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
	Node(T data, Node<T>* l, Node<T>* r, Node<T>* p) : Data(data), left(l), right(r), parent(p) {}
	Node(T data) : Data(data), left(nullptr), right(nullptr), parent(nullptr) {}
	~Node() = default;
};

template<typename T, typename Compare = std::less<T>>
class BinaryTree {
public:
	Node<T>* root;
	Node<T>* fict;
	Compare compare;
	size_t tree_size;

	BinaryTree() {
		
		root = fict;
		root->left = fict;
		root->right = fict;
		root->parent = fict;
		tree_size = 0;
	}

	BinaryTree(std::initializer_list<T> il)
	{
		fict = static_cast<Node<T>*>(operator new(sizeof(Node<T>)));
		for (const auto& x : il)
			insert(x);
	}


	using key_type = T;
	using key_compare = Compare;
	using value_compare = Compare;
	using value_type = typename T;
	using size_type = typename size_t;
	using difference_type = typename size_t;
	using pointer = typename T*;
	using const_pointer = typename const pointer;
	using reference = value_type&;
	using const_reference = const value_type&;
	class iterator;
	using iterator = iterator;
	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	class iterator {
	public:
		friend class BinaryTree;
		Node<T>* current;
		BinaryTree<T>& bst;


		iterator(Node<T>* curr, BinaryTree<T> _bst) : current(curr), bst(_bst) {}

		iterator& operator=(const iterator& other) {
			if (this != &other) { // Check for self-assignment
				this->current = other.current; // Copy the current pointer
				this->bst = other.bst; // Copy the reference to the BinaryTree
			}
			return *this; // Return the current instance
		}

		bool operator==(const iterator& other) {
			return current == other.current;
		}

		bool operator!=(const iterator& other) {
			return !(current == other.current);
		}

		pointer operator->() {
			return &current->Data;
		}

		reference operator*() {
			return current->Data;
		}


		iterator& operator++() { 
			if (current == bst.fict) return *this; 
			if (current->right != bst.fict) {
				current = findMin(current->right); 
			}
			else {
				Node<T>* parent = current->parent;
				while (parent != bst.fict && current == parent->right) {
					current = parent; 
					parent = parent->parent;
				}
				current = parent; 
			}
			return *this;
		}

		iterator& operator--() {
			if (current == bst.fict) return *this; 
			if (current->left != bst.fict) {
				current = findMax(current->left); 
			}
			else {
				Node<T>* parent = current->parent;
				while (parent != bst.fict && current == parent->left) {
					current = parent; 
					parent = parent->parent;
				}
				current = parent; 
			}
			return *this;
		}

	private:
		Node<T>* findMin(Node<T>* node) {
			while (node != bst.fict && node->left != bst.fict)
				node = node->left;
			return node;
		}

		Node<T>* findMax(Node<T>* node) {
			while (node != bst.fict && node->right != bst.fict)
				node = node->right;
			return node;
		}
	};

	using reverse_iterator = std::reverse_iterator<iterator>;

	iterator begin() noexcept { return iterator(findMin(root), *this); }
	iterator end() noexcept { return iterator(fict, *this); }
	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
	reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
	size_t size() { return tree_size; }
	bool empty() { return tree_size == 0; }

	bool operator==(BinaryTree& other) {
		return compareTwoTrees(root, other.root);
	}

	std::pair<iterator, bool> insert(const value_type& value) {
		Node<T>* newNode = new Node<T>(value,fict,fict,fict);
		if (root == fict) {
			root = newNode;
			root->parent = fict;
			root->right = fict;
			root->left = fict;
			tree_size++;
			return std::make_pair(iterator(root, *this), true);
		}

		Node<T>* curr = root;
		Node<T>* parent = fict;
		while (curr != fict) {
			parent = curr;
			if (compare(value, curr->Data))
				curr = curr->left;
			else if (compare(curr->Data, value))
				curr = curr->right;
			else {
				delete newNode;
				return std::make_pair(iterator(curr, *this), false);
			}
		}

		newNode->parent = parent;
		if (compare(value, parent->Data))
			parent->left = newNode;
		else if (compare(parent->Data, value))
			parent->right = newNode;
		newNode->left = fict;
		newNode->right = fict;
		tree_size++;
		return std::make_pair(iterator(newNode, *this), true);
	}

	iterator erase(iterator pos) {
		Node<T>* curr = pos.current;

		if (curr == fict) return end();
		Node<T>* parent = curr->parent;

		//1 случай, когда удаляемый элемент не имеет дочерних
		if (curr->left == fict && curr->right == fict) {
			if (parent->left == curr)
				parent->left = fict;
			else parent->right = fict;

			curr->left = fict;
			curr->left = fict;
			curr->parent = fict;

			delete curr;
		}

		//2 случай, когда у удаляемого элемента есть один дочерний элемент
		else if (curr->left == fict || curr->right == fict) {
			Node<T>* child = (curr->left != fict) ? curr->left : curr->right;

			if (parent->left == curr)
				parent->left = child;
			else parent->right = child;
			child->parent = parent;

			curr->left = fict;
			curr->left = fict;
			curr->parent = fict;

			delete curr;
		}

		//3 случай, когда у удаляемого элемента есть два дочерних элемента
		else {
			Node<T>* minInRight = findMin(curr->right);
			if (minInRight != fict) {
				curr->Data = minInRight->Data;
				erase(iterator(minInRight, *this));
			}
		}
		tree_size--;
		return iterator(fict->parent, *this);
	}


	iterator erase(iterator begin, iterator end) {
		while (begin != end)
			begin = erase(begin);
		return end;
	}

	size_t erase(Node<T>* node) {
		if (node == fict) return 0;
		erase(iterator(node, *this));
		return 1;
	}

	Node<T>* find(const T& value) {
		if (root->Data == value) return root;

		Node<T>* curr = root;
		while (curr) {
			if (compare(value, curr->Data))
				curr = curr->left;
			else if (compare(curr->Data, value))
				curr = curr->right;
			else if (curr->Data == value) return curr;
		}
		return fict;
	}

	iterator find_it(const T& value) {
		if (root->Data == value) return iterator(root, *this);

		Node<T>* curr = root;
		while (curr) {
			if (compare(value, curr->Data))
				curr = curr->left;
			else if (compare(curr->Data, value))
				curr = curr->right;
			else if (curr->Data == value) return iterator(curr, *this);
		}
		return iterator(fict, *this);
	}


	Node<T>* findMin(Node<T>* node) {
		while (node != fict && node->left != fict)
			node = node->left;
		return node;
	}

	Node<T>* findMax(Node<T>* node) {
		while (node != fict && node->right != fict)
			node = node->right;
		return node;
	}

	iterator lower_bound(const T& value) {
		Node<T>* curr = root;
		Node<T>* last = fict;

		while (curr != fict) {
			if (!compare(curr->Data, value)) {
				last = curr;
				curr = curr->left;
			}
			else curr = curr->right;
		}

		return iterator(last, *this);
	}

	iterator upper_bound(const T& value) {
		Node<T>* curr = root;
		Node<T>* last = fict;

		while (curr != fict) {
			if (compare(value, curr->Data)) {
				last = curr;
				curr = curr->left;
			}
			else curr = curr->right;
		}

		return iterator(last, *this);
	}

	void recursivePrint() const {
		infix(root);
	}

	void print_stack() const {
		std::stack<Node<T>*> stack;
		Node<T>* curr = root;

		while (!stack.empty() || curr != fict) {
			while (curr != fict){
				stack.push(curr);
				curr = curr->right;
			}
			curr = stack.top();
			stack.pop();
			std::cout << curr->Data << " ";
			curr = curr->left;
		}
		std::cout << std::endl;
	}

	void print_queue() const {
		std::queue<Node<T>*> queue;
		queue.push(root);
		while (!queue.empty()) {
			Node<T>* curr = queue.front();
			queue.pop();
			
			std::cout << curr->Data << " ";

			if (curr->left != fict) queue.push(curr->left);
			if (curr->right != fict) queue.push(curr->right);
		}
		std::cout << std::endl;
	}

	iterator next(iterator pos) {
		Node<T>* curr = pos.current;

		if (curr->right != fict)
			return iterator(findMin(curr->right), *this);

		Node<T>* parent = curr->parent;
		while (parent != fict && curr == parent->right) {
			curr = parent;
			parent = parent->parent;
		}
		return iterator(parent, *this);
	}

	iterator prev(iterator pos) {
		Node<T>* curr = pos.current;

		if (curr->left != fict)
			return iterator(findMin(curr->left), *this);

		Node<T>* parent = curr->parent;
		while (parent != fict && curr == parent->left) {
			curr = parent;
			parent = parent->parent;
		}

		return iterator(parent, *this);
	}


private:
	void infix(Node<T>* node) const {
		if (node == fict) return;
		infix(node->left);
		std::cout << node->Data << " ";
		infix(node->right);
	}

	bool compareTwoTrees(Node<T>* curr_1, Node<T>* curr_2) {
		if (curr_1 == fict && curr_2 == fict) return true;
		if (curr_1 == fict || curr_2 == fict) return false;
		if (curr_1->Data != curr_2->Data) return false;
		return compareTwoTrees(curr_1->left, curr_2->left) &&
			compareTwoTrees(curr_1->right, curr_2->right);
	}
};

#endif // !TREE


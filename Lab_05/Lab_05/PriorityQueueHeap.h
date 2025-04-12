#ifndef PRIORITY_QUEUE_HEAP
#define PRIORITY_QUEUE_HEAP

#include <iostream>
#include <vector>
#include <initializer_list>
#include <queue>
#include <exception>

template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
class Priority_Queue_Heap {
private:
	Container data;
	Compare compare;

	using size_type = typename Container::size_type;

	inline size_t left(size_t i) const { return 2 * i + 1; }
	inline size_t right(size_t i) const { return 2 * i + 2; }
	inline size_t parent(size_t i) const { return (i - 1) / 2; }

	void heapify(size_t i) {
		size_type max_index{ i };
		size_type size{ data.size() };

		if (left(i) < size && !compare(data[left(i)], data[max_index]))
			max_index = left(i);

		if (right(i) < size && !compare(data[right(i)], data[max_index]))
			max_index = right(i);

		if (max_index != i) {
			std::swap(data[i], data[max_index]);
			heapify(max_index);
		}
	}

	void buildHeap() {
		for (int i = parent(data[size - 1]); i > 0; i--)
			heapify(i);
		heapify(0);
	}

public:
	Priority_Queue_Heap() {}

	Priority_Queue_Heap(std::initializer_list<T> list) {
		data = list;
		buildHeap();
	}

	template<class iterator>
	Priority_Queue_Heap(iterator first, iterator last) {
		for (; first != last; first++)
			push(*first);
	}

	const T& top() { return data[0]; }
	size_t size() const { return data.size(); }
	bool empty() const { return size() == 0; }

	void push(const T& value) {
		data.push_back(value);
		size_t i = size() - 1;
		while (i > 0 && compare(data[parent(i)], data[i])) {
			std::swap(data[i], data[parent(i)]);
			i = parent(i);
		}
	}

	void pop() {
		if (empty())
			throw std::runtime_error("pop called on empty priority queue");

		std::swap(data.front(), data.back());
		data.pop_back();

		heapify(0);
	}

	void merge(Priority_Queue_Heap other) {
		while (!other.empty()) {
			push(other.top());
			other.pop();
		}
		buildHeap();
	}

	friend std::ostream& operator<<(std::ostream& os, const Priority_Queue_Heap& pqh) {
		for (auto curr : pqh.data) {
			os << curr << " ";
		}
		return os;
	}
};

#endif // !PRIORITY_QUEUE


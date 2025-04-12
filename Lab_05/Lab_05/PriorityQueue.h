#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <iostream>
#include <vector>
#include <initializer_list>
#include <queue>
#include <exception>

template<typename T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
class Priority_Queue {
private:
	using size_type = typename std::vector<T>::size_type;
	Container data;
	Compare compare;

public:
	Priority_Queue() {};

	Priority_Queue(std::initializer_list<T> list) {
		for (auto curr : list)
			push(curr);
	}

	template<class iterator>
	Priority_Queue(iterator first, iterator last) {
		for (;first != last; ++first)
			push(*first);
	}

	Priority_Queue(const std::vector<T>& vector) {
		for (auto curr : vector)
			push(curr);
	}
	
	void push(const T& value) {
		data.push_back(value);
		//insertionSort(data);
		std::sort(data.begin(), data.end(), compare);
	}

	void pop() { 
		if (empty()) return;
		data.pop_back();
	}

	const T& top() const { return data[0]; }
	size_t size() const { return data.size(); }
	bool empty() const { return size() == 0; }

	void merge(Priority_Queue other) {
		while (!other.empty()) {
			push(other.top());
			other.pop();
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Priority_Queue& pq) {
		for (auto curr : pq.data) {
			os << curr << " ";
		}
		return os;
	}

private:
	void insertionSort(std::vector<T>& data) {
		for (int i = 0; i < data.size(); i++) {
			auto curr = data[i];
			auto j = i - 1;
			while (j >= 0 && data[j] > curr) {
				data[j + 1] = data[j];
				j = j - 1;
			}
			data[j + 1] = curr;
		}
	}
};



#endif

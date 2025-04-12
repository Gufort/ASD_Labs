#pragma once
#include <iostream>
#include <vector>

class elem {
	int value;

public:
	static int count_of_copy;
	static int count_of_comp;

	elem(int v) :value(v) {};
	int get_value() const { return value; }

	elem() {
		value = rand();
	};

	friend std::ostream& operator <<(std::ostream& os, elem& el) {
		os << "Значение - " << el.get_value();
		os << ", кол-во копирований - " << el.count_of_copy << ", кол-во сравнений - " << el.count_of_comp << std::endl;
		return os;
	}

	bool operator<(const elem& other) const {
		++count_of_comp;
		return value < other.value;
	}
	bool operator>(const elem& other) const {
		++count_of_comp;
		return value > other.value;
	}


	const elem& operator=(const elem& other) {
		++count_of_copy;
		value = other.value;
		return *this;
	}

	elem(const elem& other) : value(other.value) {
		++count_of_copy;
	};

	static void reset() {
		count_of_copy = 0;
		count_of_comp = 0;
	}

};

void sort_by_inserts(std::vector<elem>& vect) {
	for (int i = 0; i < vect.size(); i++) {
		elem curr = vect[i];
		int j = i - 1;
		while (j >= 0 && vect[j] > curr) {
			vect[j + 1] = vect[j];
			j--;
		}
		vect[j + 1] = curr;
	}
};



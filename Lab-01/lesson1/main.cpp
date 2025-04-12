#include "elem.h"
#include "methods.h"
#include <iostream>
#include <algorithm>

using namespace std;

int elem::count_of_comp = 0;
int elem::count_of_copy = 0;


int main() {

	setlocale(LC_ALL, "rus");

	//Задание 1
	cout << "===> Задание 1 <===" << endl;
	cout << "Размер вектора: ";
	size_t n;
	cin >> n;
	vector<elem> v1(n), v2(v1);

	cout << "Создан вектор с " << v1.size() << " элементами" << endl;
	cout << "count_of_copy : " << elem::count_of_copy << " count_of_comp : " << elem::count_of_comp << endl;

	elem::reset();
	sort_by_inserts(v1);
	cout << "insert sort: count_of_copy: " << elem::count_of_copy;
	cout << ", count_of_comp: " << elem::count_of_comp;
	cout << endl;
	elem::reset();

	std::sort(v2.begin(),v2.end());

	cout << "Quick sort: count_of_copy: " << elem::count_of_copy;
	cout << ", count_of_comp : " << elem::count_of_comp << endl;
	cout << endl;

	//Количество операций в сортировке вставками гораздо больше, чем в стандартной сортировке
	/*Размер вектора: 12344
	Создан вектор с 12344 элементами
	count_of_copy : 12344 count_of_comp : 0
	insert sort: count_of_copy: 38069174, count_of_comp: 38044480
	Quick sort: count_of_copy: 260837, count_of_comp : 381316*/


	//Задание 2
	cout << "===> Задание 2 <===" << endl;
	for (int i = 1; i <= 10; i++) {
		cout << "Для N = " << i << ": " << countEvenBinaryNumbers(i) << endl;
	}
	cout << endl;


	//Задание 3
	cout << "===> Задание 3 <===" << endl;
	SaveInfoInCSV(); 
	cout << endl;

	//Задание 4
	cout << "===> Задание 4 <===" << endl;
}
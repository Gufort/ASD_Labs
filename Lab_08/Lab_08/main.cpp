#include "myMethods.h"
#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	
	//Задание 3
	cout << "======> Задание 3 <======" << endl;
	vector<int> vect_1{3, 2, 1, 1, 2, 3};
	methodForTask3(vect_1);
	cout << endl;

	//Задание 7
	cout << "======> Задание 7 <======" << endl;
	methodForTask7(50);

	//Задание 16б
	cout << "======> Задание 16б <======" << endl;
	Worker* worker6 = new Worker{ 6, {} };
	Worker* worker5 = new Worker{ 5, {worker6} };
	Worker* worker4 = new Worker{ 4, {worker5} };
	Worker* worker3 = new Worker{ 3, {worker4} };
	Worker* worker2 = new Worker{ 2, {worker3} };
	Worker* director = new Worker{ 1, {worker2} };
	methodForTask16b(director);

	//Задание 29
	cout << "======> Задание 29 <======" << endl;
	int n;
	cin >> n; cin.ignore();
	int s;
	cin >> s; cin.ignore();
	std::vector<int> coins;
	for (int i = 0; i < s; i++) {
		int vi;
		cin >> vi; cin.ignore();
		coins.push_back(vi);
	}

	methodForTask29(n, coins);
}
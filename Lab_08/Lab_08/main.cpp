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
}
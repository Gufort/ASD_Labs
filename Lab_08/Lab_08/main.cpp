#include "myMethods.h"
#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	
	//������� 3
	cout << "======> ������� 3 <======" << endl;
	vector<int> vect_1{3, 2, 1, 1, 2, 3};
	methodForTask3(vect_1);
	cout << endl;

	//������� 7
	cout << "======> ������� 7 <======" << endl;
	methodForTask7(50);

	//������� 16�
	cout << "======> ������� 16� <======" << endl;
	Worker* worker6 = new Worker{ 6, {} };
	Worker* worker5 = new Worker{ 5, {worker6} };
	Worker* worker4 = new Worker{ 4, {worker5} };
	Worker* worker3 = new Worker{ 3, {worker4} };
	Worker* worker2 = new Worker{ 2, {worker3} };
	Worker* director = new Worker{ 1, {worker2} };
	methodForTask16b(director);
}
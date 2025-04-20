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


	//������� 22
	cout << "======> ������� 22 <======" << endl;
	string input = "3 334555556677777777777778888888999999";
	methodForTask22(input);

	//������� 29
	cout << "======> ������� 25 <======" << endl;
	int l;
	cin >> l; cin.ignore();
	int n1;
	cin >> n1; cin.ignore();
	std::vector<std::pair<int, int>> vect;
	for (int i = 0; i < n1; i++) {
		int length;
		int value;
		cin >> length >> value; cin.ignore();
		vect.push_back({ length, value });
	}
	methodForTask25(l, vect);

	//������� 29
	cout << "======> ������� 29 <======" << endl;
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
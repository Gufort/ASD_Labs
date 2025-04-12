#include "elem.h"
#include "methods.h"
#include <iostream>
#include <algorithm>

using namespace std;

int elem::count_of_comp = 0;
int elem::count_of_copy = 0;


int main() {

	setlocale(LC_ALL, "rus");

	//������� 1
	cout << "===> ������� 1 <===" << endl;
	cout << "������ �������: ";
	size_t n;
	cin >> n;
	vector<elem> v1(n), v2(v1);

	cout << "������ ������ � " << v1.size() << " ����������" << endl;
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

	//���������� �������� � ���������� ��������� ������� ������, ��� � ����������� ����������
	/*������ �������: 12344
	������ ������ � 12344 ����������
	count_of_copy : 12344 count_of_comp : 0
	insert sort: count_of_copy: 38069174, count_of_comp: 38044480
	Quick sort: count_of_copy: 260837, count_of_comp : 381316*/


	//������� 2
	cout << "===> ������� 2 <===" << endl;
	for (int i = 1; i <= 10; i++) {
		cout << "��� N = " << i << ": " << countEvenBinaryNumbers(i) << endl;
	}
	cout << endl;


	//������� 3
	cout << "===> ������� 3 <===" << endl;
	SaveInfoInCSV(); 
	cout << endl;

	//������� 4
	cout << "===> ������� 4 <===" << endl;
}
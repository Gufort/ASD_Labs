#include <iostream>
#include <list>
#include <string>
#include <chrono>
#include "my_list.h"

using namespace std;

list<int> randomList(int n) {
	list<int> lst;
	for (int i = 0; i < n; i++)
		lst.push_back(rand() % 100);
	return lst;
}

MyList<int> randomMyList(int n) {
	MyList<int> lst;
	for (int i = 0; i < n; i++)
		lst.push_back(rand() % 100);
	return lst;
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	//1
	MyList<int> list_1{ 1,2,3,4,5,6,-2,52};
	cout << "Кол-во четных элементов в списке: " << list_1.countOfEvenElem() << endl;

	//2
	MyList<int> list_2{ 1,2,2,2,3,3,3,3,3,3,3,2,2,2,1 };
	auto pair = list_2.findMaxElemAndCountItEntry();
	cout << "Максимальный элемент и его кол-во вхождений - " << pair.first << ", " << pair.second << endl;

	//3
	MyList<int> list{ 1,2,3,-1,-2,-3 };
	auto res = list.splitList();

	cout << "Отрицательные элементы: ";
	for (const auto& elem : res.first)
		cout << elem << " ";
	cout << endl;

	cout << "Положительные элементы: ";
	for (const auto& elem : res.second)
		cout << elem << " ";
	cout << endl;

	//4
	MyList<int> list_4{ 1,2,2,-1 };
	cout << "Исходный лист: ";
	for (const auto& curr : list_4)
		cout << curr << " ";
	cout << "Перевернутый лист: ";
	list_4.reverse_custom();
	for (const auto& curr : list_4)
		cout << curr << " ";


	//Сравнение скорости работы различных методов в list и MyList

	for (int i = 0; i < 15; i++) {
		auto lst_1 = randomList(30);
		auto MyLst_1 = randomMyList(30);

		auto start = chrono::high_resolution_clock::now();
		lst_1.push_back(1);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_lst = end - start;
		
		start = chrono::high_resolution_clock::now();
		MyLst_1.push_back(1);
		end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_MyLst = end - start;

		cout << "Для операции push_back:\n" << "Для list - " << time_lst.count() << ", для MyList - " << time_MyLst.count() << endl;
	}

	cout << "____________________" << endl;

	for (int i = 0; i < 15; i++) {
		auto lst_1 = randomList(30);
		auto MyLst_1 = randomMyList(30);

		auto start = chrono::high_resolution_clock::now();
		lst_1.push_front(1);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_lst = end - start;

		start = chrono::high_resolution_clock::now();
		MyLst_1.push_front(1);
		end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_MyLst = end - start;

		cout << "Для операции push_front:\n" << "Для list - " << time_lst.count() << ", для MyList - " << time_MyLst.count() << endl;
	}

	cout << "____________________" << endl;

	for (int i = 0; i < 15; i++) {
		auto lst_1 = randomList(30);
		auto MyLst_1 = randomMyList(30);

		auto start = chrono::high_resolution_clock::now();
		lst_1.pop_front();
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_lst = end - start;

		start = chrono::high_resolution_clock::now();
		MyLst_1.pop_front();
		end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_MyLst = end - start;

		cout << "Для операции pop_front:\n" << "Для list - " << time_lst.count() << ", для MyList - " << time_MyLst.count() << endl;
	}

	cout << "____________________" << endl;

	for (int i = 0; i < 15; i++) {
		auto lst_1 = randomList(30);
		auto MyLst_1 = randomMyList(30);

		auto start = chrono::high_resolution_clock::now();
		lst_1.pop_back();
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_lst = end - start;

		start = chrono::high_resolution_clock::now();
		MyLst_1.pop_back();
		end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_MyLst = end - start;

		cout << "Для операции pop_back:\n" << "Для list - " << time_lst.count() << ", для MyList - " << time_MyLst.count() << endl;
	}

	cout << "____________________" << endl;

	for (int i = 0; i < 15; i++) {
		auto lst_1 = randomList(30);
		auto MyLst_1 = randomMyList(30);

		auto start = chrono::high_resolution_clock::now();
		lst_1.insert(lst_1.begin(), 52);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_lst = end - start;

		start = chrono::high_resolution_clock::now();
		MyLst_1.insert(MyLst_1.begin(), 52);
		end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_MyLst = end - start;

		cout << "Для операции insert:\n" << "Для list - " << time_lst.count() << ", для MyList - " << time_MyLst.count() << endl;
	}

	cout << "____________________" << endl;

	for (int i = 0; i < 15; i++) {
		auto lst_1 = randomList(100);
		auto MyLst_1 = randomMyList(100);

		auto start = chrono::high_resolution_clock::now();
		lst_1.erase(lst_1.begin());
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_lst = end - start;

		start = chrono::high_resolution_clock::now();
		MyLst_1.erase(MyLst_1.begin());
		end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_MyLst = end - start;

		cout << "Для операции erase:\n" << "Для list - " << time_lst.count() << ", для MyList - " << time_MyLst.count() << endl;
	}

	//В Release std::list более быстрый


	//Бонус
	//MyList<int> lst_b;
	//lst_b.push_back(2);
	//lst_b.push_front(3);

	//

	//for (int i : lst_b)
	//	cout << i << " ";
	//cout << endl;

	//auto it = lst_b.begin();
	//++it;
	//lst_b.insert(it, 1);
	//for (int i : lst_b)
	//	cout << i << " ";
	//cout << endl;
	//cout << lst_b.size() << endl;


	//MyList<int> lst_b1 = move(lst_b);
	//lst_b1.push_back(1);
	//for (int i : lst_b1)
	//	cout << i << " ";
	//cout << endl;
}


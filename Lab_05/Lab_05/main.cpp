#include "PriorityQueueHeap.h"
#include "PriorityQueue.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

string trim(const string& s)
{
	string r;
	for (char c : s)
		if (!ispunct(c) || c == '-')
			r += c;
	return r;
}

int main()
{
	setlocale(LC_ALL, "rus");

	/*cout << "======>Тестирование базовой логики<======" << endl;
	Priority_Queue<int> pq;
	for (size_t i = 0; i < 20; i++)
	{
		auto start = chrono::high_resolution_clock::now();
		pq.push(10 + rand() % 90);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time = end - start;
		cout << "Время = " << time.count() << endl;
		cout << pq << endl;
	}

	Priority_Queue_Heap<int> pqh;
	for (size_t i = 0; i < 20; i++)
	{
		auto start = chrono::high_resolution_clock::now();
		pqh.push(10 + rand() % 90);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time = end - start;
		cout << "Время = " << time.count() << endl;
		cout << pqh << endl;
	}

	cout << "Priority queue : \n";
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl; 
	cout << endl;
	
	Priority_Queue<int> pq1{ 213,3,4,5,5,324,4,3,234 };
	Priority_Queue<int> pq2{ 3,5,2,2,1,2,3,4,5,4 };
	cout << pq2 << endl;

	cout << "Слияние с предыдущей очередью: " << endl;
	pq1.merge(pq2);
	cout << pq1 << endl;*/


	cout << "======>Тестирование поиска 20 самых больших слов в тексте<======" << endl;
	string path = "Otcy_and_dety.txt";
	ifstream file(path);
	if (file.fail()) throw std::exception("File not open!");

	auto cmp = [](const string& s1, const string& s2) {return s1.length() < s2.length();};

	Priority_Queue_Heap<string, vector<string>, decltype(cmp)> pq3;

	auto start = chrono::high_resolution_clock::now();
	string line;
	while (file) 
	{
		file >> line;
		pq3.push(trim(line));
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> time = end - start;
	cout << "Время: " << time.count() << ", слова: " << endl;
	for (size_t i = 0; i < 20; i++)
	{
		cout << pq3.top() << endl;
		pq3.pop();
	}

	Priority_Queue<string, vector<string>, decltype(cmp)> pq4;

	string line1;
	start = chrono::high_resolution_clock::now();
	ifstream file1(path);
	while (file1)
	{
		file1 >> line1;
		pq4.push(trim(line1));
	}

	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "Время: " << time.count() << ", слова: " << endl;
	for (size_t i = 0; i < 20; i++)
	{
		cout << pq4.top() << endl;
		pq4.pop();
	}


	std::cout << "\nFinished\n";
}
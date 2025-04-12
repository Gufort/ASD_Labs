#include "treeMethods.h"
#include <chrono>

using namespace std;

int main() {
	//setlocale(LC_ALL, "rus");
	setlocale(LC_ALL, "en");

	string path = "The_Witcher.txt";

	cout << "======>����� ������ 40 ����� ���������� ���� � ������<======" << endl;
	auto start = chrono::high_resolution_clock::now();
	find40MostRepeatedWords(path);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> time = end - start;
	cout << "���� ������� �� ���: " << time.count() << endl;
	cout << "____________________________" << endl;

	cout << "======>����� ���������� 20 ����� ����� ������������� ���� �����������<======" << endl;
	start = chrono::high_resolution_clock::now();
	find20MostRepeatedNames(path);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "���� ������� �� ���: " << time.count() << endl;
	cout << "____________________________" << endl;

	cout << "======>����� ���������� ����� ������� ������ ��������<======" << endl;
	start = chrono::high_resolution_clock::now();
	findMostBigAnagrammGroups(path);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "Time: " << time.count() << endl;
	cout << "____________________________" << endl;

	cout << "======>Tests for find total sales<======" << endl;
	string path1 = "Video_Games.csv";
	start = chrono::high_resolution_clock::now();
	findTotalRevenueByGenre(path1);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "���� ������� �� ���: " << time.count() << endl;
	cout << "____________________________" << endl;

	cout << "======>Tests for find most popular genre for every year======" << endl;
	start = chrono::high_resolution_clock::now();
	findMostBeneficialGenreForEveryYear(path1);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "Time: " << time.count() << endl;
	cout << "____________________________" << endl;

	cout << "======>Tests for find most popular genre for every year======" << endl;
	start = chrono::high_resolution_clock::now();
	findMostBeneficialDevelop(path1);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "Time: " << time.count() << endl;
	cout << "____________________________" << endl;
}
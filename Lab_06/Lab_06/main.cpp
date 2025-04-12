#include "treeMethods.h"
#include <chrono>

using namespace std;

int main() {
	//setlocale(LC_ALL, "rus");
	setlocale(LC_ALL, "en");

	string path = "The_Witcher.txt";

	cout << "======>Тесты поиска 40 самых популярных слов в тексте<======" << endl;
	auto start = chrono::high_resolution_clock::now();
	find40MostRepeatedWords(path);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> time = end - start;
	cout << "Ушло времени на все: " << time.count() << endl;
	cout << "____________________________" << endl;

	cout << "======>Тесты нахождения 20 самых часто повторяющихся имен собственных<======" << endl;
	start = chrono::high_resolution_clock::now();
	find20MostRepeatedNames(path);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "Ушло времени на все: " << time.count() << endl;
	cout << "____________________________" << endl;

	cout << "======>Тесты нахождения самой большой группы анограмм<======" << endl;
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
	cout << "Ушло времени на все: " << time.count() << endl;
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
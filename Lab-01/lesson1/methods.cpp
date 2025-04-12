#include "methods.h"
#include "cmath"
#include <algorithm>
#include <string>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iostream>

//Проверка соответствия условию в двоичной форме
bool checkConditionInBinarySystem(int N) {
	std::string res;
	while (N > 0) {
		res += N % 2 + '0';
		N /= 2;
	}
	std::reverse(res.begin(), res.end());
	return res.find("00") != std::string::npos;
}

//Количество четных двоичных, удовлетворяющих условию
int countEvenBinaryNumbers(int N) {
	int count = 0;
	for (int i = std::pow(2, N - 1); i < std::pow(2, N) - 1; i++) {
		if (i % 2 == 0 && !checkConditionInBinarySystem(i)) count++;
	}
	return count;
}



//Факторизация числа (разбиение на простые множители)
std::vector<long long> Factorization(long long num) {
	int del = 2;
	std::vector<long long> res;
	while (num > 1) {
		if (num % del == 0)
		{
			res.push_back(del);
			num /= del;
		}
		else del++;
	}
	return res;
}

//Целые числа, делители которых не превосходят 7
long long generateSmallDivisorNumber(int N) {
	long long num = 1;
	for (int i = 0; i < N; i++) {
		num *= (rand() % 7 + 1);
	}
	return num;
}

//Рандомное целое число с N знаками
long long generateRandomNumber(int N) {
	return rand() % (long long)std::pow(10, N - 1);
}

//Проверка числа на простоту
bool IsPrimeNumber(int n) {
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) return false;
	return true;
}

//Генерация простого рандомного числа
long long generatePrimeNumber(int N) {
	long long num = 0;
	while (true) {
		num = rand() % (long long)std::pow(10, N - 1);
		if (IsPrimeNumber(num)) return num;
	}
}

//Сохранение в CSV
void SaveInfoInCSV() {
	std::ofstream file("task_3.csv");
	file << "Type,Number,Time(ms)\n";
	int N = 10;
	for (int i = 0; i < N; i++) {
		//Целые числа, делители которых не превосходят 7
		auto number_1 = generateSmallDivisorNumber(N);
		std::cout << "Для числа " << number_1 << " множители: ";
		auto start = std::chrono::high_resolution_clock::now();
		auto div_1 = Factorization(number_1);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = end - start;
		std::cout << "Время работы - " << time.count() << std::endl;
		file << "SmallDivisor," << number_1 << "," << time.count() << "\n";
		for (auto elem : div_1) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		//Рандомное целое число с N знаками
		auto number_2 = generateRandomNumber(N);
		std::cout << "Для числа " << number_2 << " множители: ";
		start = std::chrono::high_resolution_clock::now();
		auto div_2 = Factorization(number_2);
		end = std::chrono::high_resolution_clock::now();
		time = end - start;
		std::cout << "Время работы - " << time.count() << std::endl;
		file << "Random," << number_2 << "," << time.count() << "\n";
		for (auto elem : div_2) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		//Генерация простого рандомного числа
		auto number_3 = generatePrimeNumber(N);
		std::cout << "Для числа " << number_3 << " множители: ";
		start = std::chrono::high_resolution_clock::now();
		auto div_3 = Factorization(number_3);
		end = std::chrono::high_resolution_clock::now();
		time = end - start;
		std::cout << "Время работы - " << time.count() << std::endl;
		file << "Prime," << number_3 << "," << time.count() << "\n";
		for (auto elem : div_3) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		std::cout << "______________________________" << std::endl;
	}
	file.close();
}




////Проверка цифры на простоту
//bool isPrime(char digit) {
//	return digit == '2' || digit == '3' || digit == '5' || digit == '7';
//}
//
////Проверка на наличие двух идущих подряд простых цифр в числе
//bool checkTwoPrimeDigit(const std::string& str) {
//	for (int j = 0; j < str.size() - 1; j++) {
//		if (isPrime(str[j]) && isPrime(str[j + 1])) return true;
//	}
//	return false;
//}
//
////Количество чисел в диапазоне, удовлетворяющих условию
//int countOfEvenNumbersInRangeForRule() {
//	int count = 0;
//	auto begin = std::pow(10, 10);
//	auto end = std::pow(10, 11);
//	for (long long i = begin; i < end; i+=2) {
//		auto curr = std::to_string(i);
//		if (!checkTwoPrimeDigit(curr)) count++;
//	}
//	return count;
//}
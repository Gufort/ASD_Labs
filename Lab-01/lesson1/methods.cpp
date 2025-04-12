#include "methods.h"
#include "cmath"
#include <algorithm>
#include <string>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iostream>

//�������� ������������ ������� � �������� �����
bool checkConditionInBinarySystem(int N) {
	std::string res;
	while (N > 0) {
		res += N % 2 + '0';
		N /= 2;
	}
	std::reverse(res.begin(), res.end());
	return res.find("00") != std::string::npos;
}

//���������� ������ ��������, ��������������� �������
int countEvenBinaryNumbers(int N) {
	int count = 0;
	for (int i = std::pow(2, N - 1); i < std::pow(2, N) - 1; i++) {
		if (i % 2 == 0 && !checkConditionInBinarySystem(i)) count++;
	}
	return count;
}



//������������ ����� (��������� �� ������� ���������)
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

//����� �����, �������� ������� �� ����������� 7
long long generateSmallDivisorNumber(int N) {
	long long num = 1;
	for (int i = 0; i < N; i++) {
		num *= (rand() % 7 + 1);
	}
	return num;
}

//��������� ����� ����� � N �������
long long generateRandomNumber(int N) {
	return rand() % (long long)std::pow(10, N - 1);
}

//�������� ����� �� ��������
bool IsPrimeNumber(int n) {
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) return false;
	return true;
}

//��������� �������� ���������� �����
long long generatePrimeNumber(int N) {
	long long num = 0;
	while (true) {
		num = rand() % (long long)std::pow(10, N - 1);
		if (IsPrimeNumber(num)) return num;
	}
}

//���������� � CSV
void SaveInfoInCSV() {
	std::ofstream file("task_3.csv");
	file << "Type,Number,Time(ms)\n";
	int N = 10;
	for (int i = 0; i < N; i++) {
		//����� �����, �������� ������� �� ����������� 7
		auto number_1 = generateSmallDivisorNumber(N);
		std::cout << "��� ����� " << number_1 << " ���������: ";
		auto start = std::chrono::high_resolution_clock::now();
		auto div_1 = Factorization(number_1);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = end - start;
		std::cout << "����� ������ - " << time.count() << std::endl;
		file << "SmallDivisor," << number_1 << "," << time.count() << "\n";
		for (auto elem : div_1) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		//��������� ����� ����� � N �������
		auto number_2 = generateRandomNumber(N);
		std::cout << "��� ����� " << number_2 << " ���������: ";
		start = std::chrono::high_resolution_clock::now();
		auto div_2 = Factorization(number_2);
		end = std::chrono::high_resolution_clock::now();
		time = end - start;
		std::cout << "����� ������ - " << time.count() << std::endl;
		file << "Random," << number_2 << "," << time.count() << "\n";
		for (auto elem : div_2) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		//��������� �������� ���������� �����
		auto number_3 = generatePrimeNumber(N);
		std::cout << "��� ����� " << number_3 << " ���������: ";
		start = std::chrono::high_resolution_clock::now();
		auto div_3 = Factorization(number_3);
		end = std::chrono::high_resolution_clock::now();
		time = end - start;
		std::cout << "����� ������ - " << time.count() << std::endl;
		file << "Prime," << number_3 << "," << time.count() << "\n";
		for (auto elem : div_3) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		std::cout << "______________________________" << std::endl;
	}
	file.close();
}




////�������� ����� �� ��������
//bool isPrime(char digit) {
//	return digit == '2' || digit == '3' || digit == '5' || digit == '7';
//}
//
////�������� �� ������� ���� ������ ������ ������� ���� � �����
//bool checkTwoPrimeDigit(const std::string& str) {
//	for (int j = 0; j < str.size() - 1; j++) {
//		if (isPrime(str[j]) && isPrime(str[j + 1])) return true;
//	}
//	return false;
//}
//
////���������� ����� � ���������, ��������������� �������
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
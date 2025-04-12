#include <iostream>
#include <set>
#include <chrono>
#include "Tree.h"

using namespace std;

void SieveOfEratosthenesByVector(int n)
{
	vector<bool> prime(n + 1, true);

	for (int p = 2; p * p <= n; p++) {
		if (prime[p] == true) {
			for (int i = p * p; i <= n; i += p)
				prime[i] = false;
		}
	}
	for (int p = 2; p <= n; p++)
		if (prime[p])
			cout << p << " ";
}

void SieveOfEratosthenesByTree(int n)
{
	auto tree = new BinaryTree<int, std::less<int>>();
	for (size_t i = 2; i <= n; i++)
		tree->insert(i);

	auto curr = tree->begin();
	while (curr != tree->end())
	{
		int prime = *curr;
		for (int multiple = prime * prime; multiple <= n; multiple += prime)
		{
			auto res = tree->find_it(multiple);
			if (res != tree->end()) tree->erase(res);
		}
		++curr;
	}


	tree->recursivePrint();
}

int main() {
	setlocale(LC_ALL, "rus");
	
	//Создание дерева
	BinaryTree<int, std::less<int>>  tree;
	tree.insert(4);
	tree.insert(5);
	tree.insert(7);
	tree.insert(1);
	tree.insert(6);
	tree.insert(19);


	auto t = tree.findMin(tree.root);
	cout << t->Data << endl;
	auto t1 = tree.find(5);
	cout << t1->Data << endl;

	//lower_bound and upper_bound
	BinaryTree<int> tree_33{ 1,2,3,4,5,6 };
	auto lower_it = tree.lower_bound(7);
	cout << "lower_bound для 7 - " << *lower_it << endl;
	auto upper_it = tree.upper_bound(10);
	cout << "upper_bound для 10 - " << *upper_it << endl;


	//Различные виды печати
	cout << "Рекурсивная печать (ЛТП): ";
	tree.recursivePrint();
	cout << endl;

	cout << "Печать (ПТЛ) с помощью стека: ";
	tree.print_stack();

	cout << "Печать по слоям с помощью очереди: ";
	tree.print_queue();

	cout << "Печать с помощью цикла по итераторам: ";
	for (auto it = tree.begin(); it != tree.end(); ++it)
		cout << *it << " ";
	cout << endl;

	//Сравнение двух деревьев на равенство
	BinaryTree<int> tree_2;
	tree_2.insert(1);
	tree_2.insert(123);
	tree_2.insert(12);
	auto f = tree == tree_2;
	cout << f << endl;

	//Проверка следующего и предыдущего элемента дерева
	cout << *tree.next(tree.begin()) << endl;
	cout << *tree.prev(tree.next(tree.begin())) << endl;

	//Решето Эратосфена
	auto start = chrono::high_resolution_clock::now();
	SieveOfEratosthenesByVector(10);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> time = end - start;
	cout << "Время работы с вектором: " << time.count() << endl;

	start = chrono::high_resolution_clock::now();
	SieveOfEratosthenesByTree(10);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "Время работы с деревом: " << time.count() << endl;

 }
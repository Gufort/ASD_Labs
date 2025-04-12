#include "BStree.h"
#include <iostream>
#include <chrono>
#include <set>

using namespace std;


void SieveOfEratosthenesByVector(int n)
{
	vector<char> prime(n + 1, true);

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
	auto tree = new Binary_Search_Tree<int, std::less<int>>();
	for (size_t i = 2; i <= n; i++)
		tree->insert(i);

	auto curr = tree->begin();
	while (curr != tree->end())
	{
		int prime = *curr;
		for (int multiple = prime * prime; multiple <= n; multiple += prime)
		{
			auto res = tree->find(multiple);
			if (res != tree->end()) tree->erase(res);
		}
		++curr;
	}


	tree->recursivePrint();
}

int main() {
	setlocale(LC_ALL, "rus");

	cout << "======>Тесты дерева из char<======" << endl;
	Binary_Search_Tree<char> tree_of_char{ 'c','b', 'a', 'e', 'd', 'f' };
	tree_of_char.printTree();
	//cout << (*tree_of_char.erase(tree_of_char.begin()) == 'b') << endl;
	/*tree_of_char.erase('e');
	auto elem = 'e';*/
	cout << tree_of_char.size() << endl;
	cout << tree_of_char.erase('e') << endl;
	cout << tree_of_char.size() << endl;
	cout << endl;
	cout << std::count_if(tree_of_char.begin(), tree_of_char.end(), [](char x) { return x == 'c';}) << endl;
	tree_of_char.printTree();

	cout << "======>Тесты создания и присваивания дерева<======" << endl;
	Binary_Search_Tree<int> tree{ 1,2,3,4,5,6,7,8,9,0 };
	tree.recursivePrint();
	cout << endl;
	auto tree_1(tree);
	tree_1.recursivePrint();
	cout << endl;
	auto flag = tree == tree_1;
	cout << "Равны ли два дерева - " << flag << endl;
	//Binary_Search_Tree<int> tree_2(tree.rend(), tree.rbegin());
	cout << endl;


	cout << "======>Тесты поиска в бинарном дереве<======" << endl;
	Binary_Search_Tree<int> tree_3{ 6,4,5,3,8,1,2};
	cout << "Дерево до удаления 3: " << endl;
	tree_3.printTree();
	tree_3.recursivePrint();
	cout << endl;

	cout << "Дерево после удаления 3: " << endl;
	auto size_before = tree_3.size();
	cout << *tree_3.begin() << endl;
	tree_3.erase(tree_3.find(3));
	tree_3.printTree();
	tree_3.recursivePrint();
	cout << endl;
	cout << "Размер дерева был " << size_before << ", после удаления стал " << tree_3.size() << endl;

	cout << "======>Тесты различных алгоритмов<======" << endl;
	cout << "lower_bound для 3 в Binary_Search_Tree: " << *tree.lower_bound(3) << endl;
	cout << "upper_bound для 3 в Binary_Search_Tree: " << *tree.upper_bound(3) << endl;
	auto range_1 = tree.equal_range(3);
	cout << "equal_range в Binary_Search_Tree: " << *range_1.first << " " << *range_1.second << endl;
	
	set<int> set{ 1,2,3,4,5,6 };
	cout << "lower_bound для 3 в set: " << *set.lower_bound(3) << endl;
	cout << "upper_bound для 3 в set: " << *set.upper_bound(3) << endl;
	auto range_2 = set.equal_range(3);
	cout << "equal_range в set: " << *range_2.first << " " << *range_2.second << endl;
	cout << endl;

	cout << "======>Тесты для решета Эратосфена<======" << endl;
	auto start = chrono::high_resolution_clock::now();
	SieveOfEratosthenesByVector(150);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> time = end - start;
	cout << "Время работы с вектором: " << time.count() << endl;

	start = chrono::high_resolution_clock::now();
	SieveOfEratosthenesByTree(150);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	cout << "Время работы с деревом: " << time.count() << endl;
}
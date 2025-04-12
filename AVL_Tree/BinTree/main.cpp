#include "AVL_Tree.h"
#include <iostream>
#include <chrono>
#include <set>

using namespace std;


void SieveOfEratosthenesByVector(int n)
{
	vector<int> prime(n + 1, true);

	for (int p = 2; p * p <= n; p++) {
		if (prime[p] == true) {
			for (int i = p * p; i <= n; i += p)
				prime[i] = false;
		}
	}
	/*for (int p = 2; p <= n; p++)
		if (prime[p])
			cout << p << " ";*/
}

void SieveOfEratosthenesByTree(int n)
{
	auto tree = new AVL_Tree<int, std::less<int>>();
	for (int i = 2; i <= n; i++)
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

	//tree->recursivePrint();
}

int main() {
	setlocale(LC_ALL, "rus");

	cout << "======>Тесты балансировки<======" << endl;
	AVL_Tree<int> tree1;
	tree1.insert(10);
	tree1.insert(20);
	tree1.insert(30);
	tree1.insert(40);
	tree1.insert(50);
	tree1.insert(25);
	tree1.insert(100);
	tree1.insert(33);

	auto it = tree1.begin();
	while (it != tree1.end()) {
		cout << it.data->data << " = " << it.data->height << endl;
		++it;
	}

	cout << "Сбалансированное дерево: " << endl;
	tree1.printTree();

	cout << "Сбалансированное дерево после удаления элемента: " << endl;
	cout << *tree1.erase(tree1.find(10), tree1.find(25)) << endl;
	
	cout << *++++tree1.begin() << endl;
	tree1.printTree();

	cout << "======>Тесты дерева из char<======" << endl;
	AVL_Tree<char> tree_of_char{ 'c','b', 'a', 'e', 'd', 'f' };
	tree_of_char.printTree();
	//cout << (*tree_of_char.erase(tree_of_char.begin()) == 'b') << endl;
	/*tree_of_char.erase('e');
	auto elem = 'e';*/
	cout << tree_of_char.size() << endl;
	cout << tree_of_char.erase('d') << endl;
	cout << tree_of_char.size() << endl;
	cout << endl;
	cout << std::count_if(tree_of_char.begin(), tree_of_char.end(), [](char x) { return x == 'c';}) << endl;
	tree_of_char.printTree();

	cout << "======>Тесты создания и присваивания дерева<======" << endl;
	AVL_Tree<int> tree{ 1,2,3,4,5,6,7,8,9,0 };
	tree.recursivePrint();
	cout << endl;
	auto tree_1(tree);
	tree_1.recursivePrint();
	cout << endl;
	auto flag = tree == tree_1;
	cout << "Равны ли два дерева - " << flag << endl;
	//AVL_Tree<int> tree_2(tree.rend(), tree.rbegin());
	cout << endl;


	cout << "======>Тесты поиска в бинарном дереве<======" << endl;
	AVL_Tree<int> tree_3{ 6,4,5,3,8,1,2};
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
	cout << "lower_bound для 3 в AVL_Tree: " << *tree.lower_bound(3) << endl;
	cout << "upper_bound для 3 в AVL_Tree: " << *tree.upper_bound(3) << endl;
	auto range_1 = tree.equal_range(3);
	cout << "equal_range в AVL_Tree: " << *range_1.first << " " << *range_1.second << endl;
	
	set<int> set{ 1,2,3,4,5,6 };
	cout << "lower_bound для 3 в set: " << *set.lower_bound(3) << endl;
	cout << "upper_bound для 3 в set: " << *set.upper_bound(3) << endl;
	auto range_2 = set.equal_range(3);
	cout << "equal_range в set: " << *range_2.first << " " << *range_2.second << endl;
	cout << endl;

	double average_vector = 0;
	double average_tree = 0;
	cout << "======>Тесты для решета Эратосфена<======" << endl;
	for (int i = 1; i <= 20; i++) {
		auto start = chrono::high_resolution_clock::now();
		SieveOfEratosthenesByVector(15);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time = end - start;
		average_vector += time.count();

		start = chrono::high_resolution_clock::now();
		SieveOfEratosthenesByTree(15);
		end = chrono::high_resolution_clock::now();
		time = end - start;
		average_tree += time.count();
	}

	cout << average_tree / 20 << " - " << average_vector / 20 << endl;
}
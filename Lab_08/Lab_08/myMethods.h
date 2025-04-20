#ifndef MU_METHODS_H
#define MY_METHODS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <map>

//Структура должностного лица
struct Worker {
	int number;
	std::vector<Worker*> sub;
};

void methodForTask3(const std::vector<int>&);
void methodForTask7(int);
void methodForTask16b(Worker*);
void methodForTask22(const std::string&);
void methodForTask29(int, std::vector<int>);
void methodForTask25(int, const std::vector<std::pair<int, int>>&);


#endif // !MY_METHODS_H


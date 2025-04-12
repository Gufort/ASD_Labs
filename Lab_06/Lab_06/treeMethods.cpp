#include "treeMethods.h"
#include "Games.h"
#include "fstream"
#include <stdexcept>
#include <algorithm>

std::string trim(const std::string& str) {
	std::string res;
	for (char c : str) {
		if (!ispunct(c) || c == '-')
			res += c;
	}
	return res;
}

void find40MostRepeatedWords(const std::string& path) {
	std::fstream file(path);
	if (file.fail()) throw std::runtime_error("File isn't open!");
	std::map<std::string, int> mapOfWords;

	std::string line;
	while (file >> line) {
		mapOfWords[trim(line)]++;
	}


	auto compare = [](const std::pair<std::string, int>& pair_1, const std::pair<std::string, int>& pair_2) {
		return pair_1.second > pair_2.second; };
	std::set<std::pair<std::string, int>, decltype(compare)> setOfWords;

	for (const auto& [word, count] : mapOfWords)
		setOfWords.insert({ word,count });

	int iter = 1;
	for (const auto& curr : setOfWords) {
		if (iter == 40) break;
		std::cout << "Слово " << curr.first << " встречалось " << curr.second << " раз" << std::endl;
		iter++;
	}
}

void find20MostRepeatedNames(const std::string& path) {
	std::fstream file(path);
	if (file.fail()) throw std::runtime_error("File isn't open!");
	std::map<std::string, int> mapOfWords;

	std::string line;
	while (file >> line) {
		auto word = trim(line);
		if(word[0]>='A' && word[0]<='Z')
			mapOfWords[trim(line)]++;
	}


	auto compare = [](const std::pair<std::string, int>& pair_1, const std::pair<std::string, int>& pair_2) {
		return pair_1.second > pair_2.second; };
	std::set<std::pair<std::string, int>, decltype(compare)> setOfWords;

	for (const auto& [word, count] : mapOfWords)
		setOfWords.insert({ word,count });

	int iter = 1;
	for (const auto& curr : setOfWords) {
		if (iter == 40) break;
		std::cout << "Слово " << curr.first << " встречалось " << curr.second << " раз" << std::endl;
		iter++;
	}
}

void findMostBigAnagrammGroups(const std::string& path) {
	std::fstream file(path);
	if (file.fail()) throw std::runtime_error("File isn't open!");

	/*auto compare = [](const std::set<std::string> set_1, std::set<std::string> set_2) {
		return set_1.size() > set_2.size(); };*/
	std::map<std::string, std::set<std::string>> mapOfAnagramms;

	std::string line;
	while (file >> line) {
		std::string word = trim(line);
		auto new_word = std::transform(word.begin(), word.end(), word.begin(), [](char c) { return std::tolower(c); });

		std::string anagram = word;
		std::sort(anagram.begin(), anagram.end());

		mapOfAnagramms[anagram].insert(word);
	}

	int sizeOfMaxGroup = 0;
	for (const auto& curr : mapOfAnagramms)
		if (curr.second.size() > sizeOfMaxGroup)
			sizeOfMaxGroup = curr.second.size();

	std::cout << "Самая большая группа анограмм: " << std::endl;
	for (const auto& curr : mapOfAnagramms) {
		if (curr.second.size() == sizeOfMaxGroup) {
			std::cout << "Анограмма: " << curr.first << ", слова: ";
			for (auto elem : curr.second)
				std::cout << elem << std::endl;
		}
	}
}

void findTotalRevenueByGenre(const std::string& path) {
	std::fstream file(path);
	if (file.fail()) throw std::runtime_error("File isn't open!");

	std::map<std::string, std::map<std::string, double>> mapOfTotalRevenue;

	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		Game game(line);
		if (game.games.size() < 10) continue;
		mapOfTotalRevenue[game[4]][game[3]] += std::stod(game[9]);
	}

	for (const auto& [publisher, game] : mapOfTotalRevenue)
		for (const auto& [genre, global_sales] : game)
			std::cout << "Publicher - " << publisher << ", genre - " << genre << ", sales - " << global_sales << std::endl;
}

void findMostBeneficialGenreForEveryYear(const std::string& path) {
	std::fstream file(path);
	if (file.fail()) throw std::runtime_error("File isn't open!");

	std::map<int, std::map<std::string,double>> mapOfGenre;

	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		Game game(line);
		if (game[9].empty()) continue;

		bool checkDigit = true;
		for (char c : game[2])
			if (!isdigit(c))
				checkDigit = false;
		if(checkDigit)
			mapOfGenre[std::stoi(game[2])][game[3]] += std::stod(game[9]);
	}

	for (const auto& curr : mapOfGenre) {
		std::string tmp;
		double max = -123124124124;
		for (const auto& second: curr.second) {
			if (second.second > max) {
				tmp = second.first;
				max = second.second;
			}
		}
		std::cout << curr.first << " - " << tmp << " - " << max << std::endl;
	}
}

void findMostBeneficialDevelop(const std::string& path) {
	std::fstream file(path);
	if (file.fail()) throw std::runtime_error("File isn't open!");

	std::map<std::string, std::map<std::string, double>> mapOfVeryCoolDevelopers;

	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		Game game(line);
		if (game[14].empty()) continue;
		if (game[9].empty()) continue;

		mapOfVeryCoolDevelopers[game[14]][game[4]] += std::stod(game[9]);
	}

	for (const auto& curr : mapOfVeryCoolDevelopers) {
		std::vector<std::pair<std::string, double>> vect(curr.second.begin(), curr.second.end());
		std::sort(vect.begin(), vect.end(), [](auto a, auto b) { return a.second > b.second; });

		int size = vect.size();
		if (size > 5) size = 5;

		std::cout << "For " << curr.first << ": " << std::endl;
		for (int i = 0; i < size; i++)
			if (vect[i].first == "")
				std::cout << "    " << i + 1 << ") " << "*Null developer*" << std::endl;
			else
				std::cout << "    " << i + 1 << ") " << vect[i].first << std::endl;

		std::cout << std::endl;
	}
}
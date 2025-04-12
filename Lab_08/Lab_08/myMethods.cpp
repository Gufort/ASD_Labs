#include "myMethods.h"

//Решаем динамикой, разбиваем задачу на подзадачи.
//необходимо искать минимальные возможные очки между двумя отдельно взятыми индексами
void methodForTask3(const std::vector<int>& seq) {
	std::vector<std::vector<int>> res(seq.size(), std::vector<int>(seq.size(),0));

	for (int start = 2; start < seq.size(); start++) {
		for (int i = 0; start + i < seq.size(); i++) {
			int j = start + i;
			res[i][j] = INT_MAX;
			for (int k = i + 1; k < j; k++)
				//прибавляем также результат удалений слева и справа
				res[i][j] = std::min(res[i][j], res[i][k] + res[k][j] + seq[k] * seq[j] * seq[i]);
		}
	}

	std::cout << res[0][seq.size() - 1];
}

//Решаем динамикой, ибо мы рассматриваем подряды исходного ряда
void methodForTask7(int m) {
	std::vector<int> res;
	res.push_back(1);

	int n = 1;

	while (true) {
		auto count = res[n - 1];

		for (int k = m; k <= n; k++) {
			if (n - k == 0) count += 1; // если у нас один целый красный блок
			else if (n - k - 1 >= 0) count += res[n - k - 1];
		}

		res.push_back(count);

		if (count >= 1000000) {
			std::cout << n << std::endl;
			break;
		}

		n++;
	}
}

void methodForTask16b(Worker* root) {
	if (!root) return;

	std::stack<std::pair<Worker*, bool>> workers;
	workers.push(std::make_pair(root, false));

	std::map<Worker*, std::pair<int, int>> res;

	while (!workers.empty()) {
		auto curr = workers.top().first;
		auto invited = workers.top().second;
		workers.pop();

		if (invited) {
			int with_count = 1;
			int without_count = 0;

			for (auto sub : curr->sub) {
				with_count += res[sub].second;//Тут обрати внимание, мы не приглашаем подчиненных
				without_count += std::max(res[sub].first, res[sub].second);
			}

			res[curr] = std::make_pair(with_count, without_count);
		}

		else {
			workers.push(std::make_pair(curr, true));

			for (auto sub : curr->sub)
				workers.push(std::make_pair(sub, false));
		}
	}

	std::cout << std::max(res[root].first, res[root].second) << std::endl;
}

void methodForTask25(int n, const std::vector<std::pair<int, int>>& table) {
	std::vector<int> res(n + 1, 0);
	std::vector<int> prices(n + 1, 0);

	for (const auto& piece : table) {
		int length; int value;
		if(piece.first)
			length = piece.first;
		if (piece.second)
			value = piece.second;

		if (length <= n)
			prices[length] = value;
	}

	//Считаем максимальные цены на всевозможных отрезках
	for (int i = 1; i <= n; ++i) {
		for (const auto& piece : table) {
			int length = piece.first;
			int value = piece.second;
			if (length <= i) {
				res[i] = std::max(res[i], res[i - length] + value);
			}
		}
	}

	std::cout << res[n] << std::endl;
}

void methodForTask29(int n, std::vector<int> coins) {
	std::vector<int> res(n + 1, 0);
	res[0] = 1;

	for (int curr : coins) {
		for (int i = curr; i <= n; i++) {
			res[i] += res[i - curr];
		}
	}
	std::cout << res[n] << std::endl;
}
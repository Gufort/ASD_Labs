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
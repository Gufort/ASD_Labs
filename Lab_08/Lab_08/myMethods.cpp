#include "myMethods.h"

//������ ���������, ��������� ������ �� ���������.
//���������� ������ ����������� ��������� ���� ����� ����� �������� ������� ���������
void methodForTask3(const std::vector<int>& seq) {
	std::vector<std::vector<int>> res(seq.size(), std::vector<int>(seq.size(),0));

	for (int start = 2; start < seq.size(); start++) {
		for (int i = 0; start + i < seq.size(); i++) {
			int j = start + i;
			res[i][j] = INT_MAX;
			for (int k = i + 1; k < j; k++)
				//���������� ����� ��������� �������� ����� � ������
				res[i][j] = std::min(res[i][j], res[i][k] + res[k][j] + seq[k] * seq[j] * seq[i]);
		}
	}

	std::cout << res[0][seq.size() - 1];
}
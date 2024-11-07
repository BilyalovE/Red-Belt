#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    // Число групп
    int n;
    cin >> n;

    // Матрица участников, где хранятся собранные ими огурцы
    vector<vector<int>> p(n);
    // Суммарное количество собранных огурцов в каждой группе
    vector<int> sum_cuc_group(n);

    for (int i = 0; i < n; ++i) {
        // Размер группы
        int m;
        cin >> m;
        p[i].resize(m);
        for (int j = 0; j < m; ++j) {
            // Число огурцов
            cin >> p[i][j];
        }
        sum_cuc_group[i] = accumulate(p[i].begin(), p[i].end(), 0);
    }

    // Всего собрано огурцов
    int sum_cuc = accumulate(sum_cuc_group.begin(), sum_cuc_group.end(), 0);

    // Банки
    int T;
    cin >> T;

    // Банки для каждой группы
    vector<int> TGroup(n, 0);

    // Пропорциональное распределение банок
    if (sum_cuc > 0) {
        for (int i = 0; i < n; ++i) {
            TGroup[i] = static_cast<int>(static_cast<double>(sum_cuc_group[i]) * T / sum_cuc);
        }
    }

    // Подсчет оставшихся банок
    int given_T = accumulate(TGroup.begin(), TGroup.end(), 0);
    int remain_T = T - given_T;

    // Вектор разностей для корректировки
    vector<pair<int, int>> differences;
    for (int i = 0; i < n; ++i) {
        differences.push_back({abs(sum_cuc_group[i] - TGroup[i]), i});
    }

    // Сортируем по величине разности
    sort(differences.begin(), differences.end());

    // Распределяем оставшиеся банки, начиная с групп, которые нуждаются в них больше всего
    for (int i = 0; i < remain_T; ++i) {
        TGroup[differences[i % n].second]++;
    }

    // Выводим результат
    for (auto i : TGroup) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}


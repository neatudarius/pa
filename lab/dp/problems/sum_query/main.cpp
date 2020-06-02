// Copyright 2020 Nichita Radu <radunichita99@gmail.com>

// SumQuery - Programare dinamica
// Complexitate O(M * N)

// https://leetcode.com/problems/range-sum-query-2d-immutable/

#include <bits/stdc++.h>

class Task {
    // N si M sunt dimensiunile matricei, K e numarul de query-uri
    int N, M, K;

    // matricea de elemente
    std::vector<std::vector<int>> matrix;

    // query-urile de forma <(start_x, start,y), (finish_x), (finish_y)>.
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> queries;

    // pe pozitia [i][j] am suma elementelor submatricei (1,1) pana la (i, j).
    std::vector<std::vector<int>> dp;

    // vectorul se solutii
    std::vector<int> solution;

    void read_input() {
        std::cin >> N >> M >> K;
        matrix = std::vector<std::vector<int>>(N + 1, std::vector<int>(M + 1, 0));
        dp     = std::vector<std::vector<int>>(N + 1, std::vector<int>(M + 1, 0));

        for (int i = 1; i <= M; i++) {
            for (int j = 1; j <= N; j++) {
                std::cin >> matrix[i][j];
            }
        }

        queries = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>(K);
        for (int i = 0; i < K; i++) {
            int start_x, start_y, finish_x, finish_y;
            std::cin >> start_x >> start_y >> finish_x >> finish_y;
            queries[i] = {{start_x, start_y}, {finish_x, finish_y}};
        }
        return;
    }

    // Ideea de la care am plecat: crearea unei matrici auxiliare, in care pe
    // pozitia dp[i][j] voi retine suma elementelor submatri ceide la (1, 1) la
    //(i, j). Aici ne putem folosi
    // de faptul ca indexarea incepe de la 1. De exemplu, matricea
    // 0 1 2
    // 3 4 5
    // 6 7 8
    // va fi perceputa ca in memorie ca
    // 0 0 0 0
    // 0 0 1 2
    // 0 3 4 5
    // 0 6 7 8
    // Astfel pentru a calcula suma elementelor de prima linie, e suficient sa
    // facem dp[1][i] = dp[1][i - 1] + matrix[1][i]. Se aplica rationamentul
    // pentru toate liniile din matrice, dupa care se aplica un rationament
    // similar (doar ca pe coloane) pentru a calcula rezultatul dorit.

    void compute_sum_matrix() {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                dp[i][j] += dp[i][j - 1] + matrix[i][j];
            }
        }

        for (int j = 1; j <= M; j++) {
            for (int i = 1; i <= N; i++) {
                dp[i][j] += dp[i - 1][j];
            }
        }
    }

    void show_matrix(const std::vector<std::vector<int>> matrix) {
        for (auto const& line : matrix) {
            for (auto const& elem : line) {
                std::cout << elem << " ";
            }
            std::cout << "\n";
        }
    }

    // pentru a calcula suma elementelor dintre colturile stanga-sus (r1,c1) si
    // dreapta jos (r2,c2) aplicam un principiu similar calcularii ariei unui
    // dreptunghi prin scadere de dreptunghiuri. Adica, pentru a calcula suma
    // dorita ar trebui sa scadem din patratul de coordonate (1, 1)->(r2,c2)
    // patratele mai mici, dupa cum urmeaza:
    // +---------------+   +--------------+   +---------------+   +--------------+   +--------------+
    // |               |   |         |    |   |   |           |   |         |    |   |   |          |
    // |   (r1,c1)     |   |         |    |   |   |           |   |         |    |   |   |          |
    // |   +------+    |   |         |    |   |   |           |   +---------+    |   +---+          |
    // |   |      |    | = |         |    | - |   |           | - |      (r1,c2) | + |   (r1,c1)    |
    // |   |      |    |   |         |    |   |   |           |   |              |   |              |
    // |   +------+    |   +---------+    |   +---+           |   |              |   |              |
    // |        (r2,c2)|   |       (r2,c2)|   |   (r2,c1)     |   |              |   |              |
    // +---------------+   +--------------+   +---------------+   +--------------+   +--------------+
    void get_result() {
        compute_sum_matrix();
        for (const auto& [start, end] : queries) {
            int sol = dp[end.first][end.second];
            sol     = sol - dp[start.first - 1][end.second];
            sol     = sol - dp[end.first][start.second - 1];
            sol     = sol + dp[start.first - 1][start.second - 1];
            solution.push_back(sol);
        }
    }

    void print_output() {
        for (const auto& sol : solution) {
            std::cout << sol << "\n";
        }
    }

public:
    void solve() {
        read_input();
        get_result();
        print_output();
    }
};

int main() {
    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff  = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("sum_query.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    std::ofstream fout("sum_query.out");
    std::cout.rdbuf(fout.rdbuf()); // save and redirect

    // aici este rezolvarea propriu-zisa
    Task* task = new Task();
    task->solve();
    delete task;

    // restore pentru cin si cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide
    return 0;
}

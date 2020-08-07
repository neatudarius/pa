// Copyright 2020 Cristian Olaru <cristianolaru99@gmail.com>

// Extraterestrii
// Exponentiere pe matrice (Programare dinamica)
// Complexitate: O(m ^ 3 * log n)

// https://www.hackerrank.com/contests/test-practic-pa-2017-v1-plumbus/challenges/test-1-extraterestrii

#include <bits/stdc++.h>

#define MOD 666013 // Atentie la datele problemei!

using Matrix = std::vector<std::vector<int>>;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m, k;

    // matrice de m * m in care vom retine restrictiile
    // C[i][j] = 1  <=>  nu am restrictie de forma (si, sj)
    // C[i][j] = 0  <=>  am restrictie de forma (si, sj)
    // pentru a intelege aceasta matrice de coeficienti, vezi comentariile din functia get_result
    Matrix C;

    void read_input() {
        std::cin >> n >> m >> k;

        // aloc matricea C de m * m
        // initializez intreaga matrice cu 1, cu alte cuvinte, presupun initial ca nu am restrictii
        C = Matrix(m + 1, std::vector<int>(m + 1, 1));

        // citesc cele k restrictii
        // pentru fiecare pereche (i, j) citita, marchez restrictia ca C[i][j] = 0
        for (int l = 0; l < k; ++l) {
            int i, j;
            std::cin >> i >> j;
            C[i][j] = 0;
        }
    }

    int get_result() {
        // ideea problemei se bazeaza pe metoda exponentierii logaritmice pe matrice

        // consideram vectorii v1, v2, v3, ..., vn, fiecare vector avand m elemente
        // deci vi are elementele vi[1], vi[2], ..., vi[m]
        // vi[j] va reprezenta numarul de cuvinte care au i litere si care se termina cu caracterul sj

        // cazul de baza va fi v1, un vector care va fi plin de 1, deoarece putem cuvinte de o litera cu fiecare din cele m litere
        // observam ca raspunsul la problema va fi suma elementelor din vectorul vn

        // iar acum gasim relatia dintre vi si v(i + 1)
        // stiind vectorul vi, pentru a-l determina pe urmatorul, pentru fiecare litera putem alege toate celelalte litere
        // mai putin literele unde avem restrictii
        // cu alte cuvinte, avem relatia: v(i + 1) = vi * C, unde C este matricea coeficientilor determinata din citire

        // din acest motiv se pune 0 acolo unde am restrictie si 1 unde nu, pentru ca vrem sa extindem cuvintele vechi
        // cu toate literele, mai putin cele cu restrictia

        // revenind la recurenta, vom avea ca vn = v(n - 1) * C = v(n - 2) * (C ^ 2) = ... = v1 * C ^ (n - 1)
        // dar v1 este un vector de m elemente plin de 1, iar solutia finala este suma elementelor din vector
        // astfel ca, din punct de vedere matematic, solutia pentru problema este echivalenta cu a determina suma elementelor matricei C ^ (n - 1)

        // caclulez C ^ (n - 1)
        power_matrix(C, n - 1, C);
        
        // calculez suma elementelor matricii calculate
        int sol = sum_elements(C);

        // suma elementelor este chiar solutia finala pentru problema
        return sol;
    }

    void multiply_matrix(const Matrix &A, const Matrix &B, Matrix &C) {
        // functia este din lab 4: 
        // https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-04#gardurile_lui_gigel_optimizare
        // functia va primi referinta matricei C pentru a intoarce rezultatul final in C
        Matrix tmp(m + 1, std::vector<int>(m + 1));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                long long sum = 0;
                for (int k = 1; k <= m; ++k) {
                    sum += 1LL * A[i][k] * B[k][j];
                    sum = sum % MOD;
                }
                tmp[i][j] = sum;
            }
        }
        C = tmp;
    }

    void power_matrix(Matrix C, int exp, Matrix &R) {
        // functia este din lab 4: 
        // https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-04#gardurile_lui_gigel_optimizare
        // functia va primi referinta matricei C pentru a intoarce rezultatul final in C
        Matrix tmp(m + 1, std::vector<int>(m + 1));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                tmp[i][j] = (i == j) ? 1 : 0;
            }
        }
        while (exp != 1) {
            if  (exp % 2 == 0) {
                multiply_matrix(C, C, C);
                exp /= 2;
            } else {
                multiply_matrix(tmp, C, tmp);
                --exp;
            }
        }
        multiply_matrix(C, tmp, R);
    }

    int sum_elements(const Matrix &C) {
        // functie care calculeaza suma elementelor unei matrice
        long long sum = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                sum += C[i][j];
                sum = sum % MOD;
            }
        }
        return sum % MOD;
    }

    void print_output(int result) {
        std::cout << result << "\n";
    }
};

int main() {
    // din cauza ca fac redirectari, salvez starea lui std::cin si std::cout
    auto cin_buff  = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("extraterestrii.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    // std::ofstream fout("extraterestrii.out");
    // std::cout.rdbuf(fout.rdbuf()); //save and redirect

    // aici este rezolvarea propriu-zisa
    Task* task = new Task();
    task->solve();
    delete task;

    // restore pentru std::cin si std::cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide

    return 0;
}

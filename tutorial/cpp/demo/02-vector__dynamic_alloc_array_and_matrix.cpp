// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::vector (https://en.cppreference.com/w/cpp/container/vector).

class Task {
    // fisierul "in" contine n (numarul de elemente) si elementele vectorului v
    int n;
    std::vector<int> v;

    // in fisierul "out" se va afisa vectorul v sortat

    public:
        void read() {
            std::ifstream in("in");
            in >> n;
            
            // daca avem nevoie de a prealoca vectorul, putem face asta cu resize
            v.resize(n);

            for (int i = 0; i < n; ++i) {
                in >> v[i]; // acum exista deja elementele si putem citi in vector direct
            }
            in.close();
        }

        void compute_solution() {
            // in unele aplicatii o sa avem nevoie de tablouri auxiliare, de dimensiuni similare.
            // si initializate cu anumita valoare (ex. 0)

            // dp este un vector cu n elemente initializate cu 0
            std::vector<int> dp(n, 0);
            for (int i = 0; i < n; ++i) {
                // dp[i] = v[i] + ...; // ceva formula magica
            }

            // putem simula o matrice alocata dinamic cu vector de vector
            // matrix este un vector cu n elemente
            // fiecare elemente este un vector cu n elemente initializate cu 0
            // => matrice de n x n elemente initializate cu 0
            std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++n) {
                    matrix[i][j] = i + j; // ceva formula magica
                }
            }
        }

        void solve() {
            read();
            compute_solution();
            print();
        }

        void print() {
            std::ofstream out("out");
            out << "Hello Gigel\n";
            out.close();
        }
};

// Please always keep this simple main function!
int main() {
    // Allocate a Task object on heap in order to be able to
    // declare huge static-allocated data structures inside the class.
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}

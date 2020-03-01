// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::vector (https://en.cppreference.com/w/cpp/container/vector).
// Demo std::sort (https://en.cppreference.com/w/cpp/algorithm/sort).

// Metode de a folosi std::sort

// 1. sortare cu functie de comparare
// Functia returneaza true daca "a trebuie sa fie la stanga lui b" in vectorul sortat.
//
// Exemple:
// - daca a < b si se returneaza true, inseamna ca orice numar mai mic e la stanga
//      => sortare crescatoare
// - daca a > b si se returneaza true, inseamna ca orice numar mai mare e la stanga
//      => sortare decrescatoare
//
bool cmp_ascending(const int& a, const int&b) {
    return a < b;    // crescator
}
bool cmp_descending(const int& a, const int&b) {
    return a > b;    // descrescator
}

// 2. sortare cu functie lambda (vezi in compute_solution)
// (mai sunt si alte metode, dar 1 si 2 sunt cele mai comode)

class Task {
    // fisierul "in" contine n (numarul de elemente) si elementele vectorului v
    int n;
    std::vector<int> v;

    // in fisierul "out" se va afisa vectorul v sortat

    public:
        void read() {
            std::ifstream in("in");
            in >> n;
            for (int i = 0; i < n; ++i) {
                // citesc intr-o variabila temporara
                int x;
                in >> x;

                // salvez in vector
                v.push_back(x);
            }
            in.close();
        }

        void compute_solution() {
            // 1. sortare cu functie de comparatie
            //      *** 1.1 sortare crescatoare
            // std::sort(v.begin(), v.end(), cmp_ascending);
            //      *** 1.2 sortare crescatoare
            // std::sort(v.begin(), v.end(), cmp_descending);

            // 2. sortare cu functie lambda (recomandata daca nu folosim acelasi criteriu la mai multe sortari)
            //      *** 2.1. sortare crescatoare
            // std::sort(v.begin(), v.end(), [](const int& a, const int& b) { return a < b; });
            //      *** 2.2. sortare descrescatoare
            // std::sort(v.begin(), v.end(), [](const int& a, const int& b) { return a > b; });
        }

        void solve() {
            read();
            compute_solution();
            print();
        }

        void print() {
            std::ofstream out("out");
            for (auto& x :  v) {
                out << x << " ";
            }
            out << "\n";
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

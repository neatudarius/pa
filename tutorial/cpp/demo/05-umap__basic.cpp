// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::unordered_map (https://en.cppreference.com/w/cpp/container/unordered_map).
//
// De fiecare data cand nu ne pasa de ordinea cheilor la parcurgere, folosim unordered_map
// in loc de map. Sintaxa este identica

class Task {
    // citim un vector de n string-uri
    int n;
    std::vector<std::string> v;

    public:
        void read() {
            std::ifstream in("in");
            in >> n;
            for (int i = 0; i < n; ++i) {
                std::string x;
                in >> x;
                v.push_back(x);
            }
            in.close();
        }

        void compute_solution() {
            std::unordered_map<std::string, int> h;
            for (auto& x : v) {
                h[x]++;
            }
            std::cout << "h:\n";
            for (auto& p : h) {
                std::cout << p.first << " " << p.second << "\n";
            }
            std::cout << "\n";
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

// Example:
//
// Input:
// cat in
// 10
// gigel
// not_gigel
// gigel
// not_gigel
// gigel
// not_gigel
// gigel
// not_gigel
// gigel_again
// just_gigel
//
// Output
// ./05-umap__basic
// h:
// gigel_again 1
// just_gigel 1
// gigel 4
// not_gigel 4
//
// Atentie! Ordinea din output nu este garanta! Putem rula de mai multe ori si sa vedem
// gigel inainte de not_gigel sau invers.
//

// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::vector (https://en.cppreference.com/w/cpp/container/vector).
// Demo std::sort (https://en.cppreference.com/w/cpp/algorithm/sort).
// Demo std::pair (https://en.cppreference.com/w/cpp/utility/pair).

bool cmp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    // comparam mai intai dupa varstsa
    if (a.second != b.second) { // varste diferite
        return a.second < b.second; // crescator dupa varsta
    }
    // egalitate dupa varsta

    // comparam dupa nume
    return a.first > b.first;
}

class Task {
    // fisierul "in" contine n (numarul de elemente) si elementele vectorului v
    // un element este o pereche de forma (nume, varsta)
    // se va sorta v crescator dupa varsta, iar in caz de egalitate, descrescator dupa nume
    int n;
    std::vector<std::pair<std::string, int>> v;

    // in fisierul "out" se va afisa vectorul v sortat

    public:
        void read() {
            std::ifstream in("in");
            in >> n;
            for (int i = 0; i < n; ++i) {
                std::string name;
                int age;
                in >> name >> age;
                v.push_back({name, age});
            }
            in.close();
        }

        void compute_solution() {
            // sortare cu functie de comparare
            std::sort(v.begin(), v.end(), cmp);
        }

        void solve() {
            read();
            compute_solution();
            print();
        }

        void print() {
            std::ofstream out("out");
            for (auto& p :  v) {
                out << p.first << " " << p.second << "\n";
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


// Exemplu de output:
// not_gigel 15
// gigel 15
// not_gigel 18
// gigel 18
// just_gigel 69

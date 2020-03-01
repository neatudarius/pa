// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::vector (https://en.cppreference.com/w/cpp/container/vector).

class Task {
    // fisierul "in" contine n (numarul de elemente) si elementele vectorului v
    int n;
    std::vector<int> v;

    // rezultatul este suma elementelor din v
    int sum;

    public:
        void read() {
            std::ifstream in("in");
            in >> n;
            
            // daca dorim indexare de la 1 (ex. la programare dinamica ne ajuta)
            // atunci trebuie doar sa ocupam prima pozitie
            v.push_back(0); // adaugam un zero la inceput

            for (int i = 1; i <= n; ++i) {
                // citesc intr-o variabila temporara
                int x;
                in >> x;

                // salvez in vector
                v.push_back(x);
            }
            in.close();
        }

        void compute_solution() {
           // in cazul asta nu mai putem folosi for (x : v), intrucat va parcurge si elementul fictiv

           // solutie: parcurgere index
           for (int i = 1; i <= n; ++i) {
               sum += v[i];
           }
        }

        void solve() {
            read();
            compute_solution();
            print();
        }

        void print() {
            std::ofstream out("out");
            out << sum << "\n";
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

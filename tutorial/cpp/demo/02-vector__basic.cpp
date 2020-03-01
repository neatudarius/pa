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
            // parcurgere vector

            // 1: cu index
            // sum = 0;
            // for (int i = 0; i < n; ++i) {
            //     sum += v[i];
            // }

            // 2: cu iterator (varianta recomandata daca in for stergem elemente din v)
            // sum = 0;
            // for (auto it = v.begin(); it != v.end(); ++it) {
            //     sum += *it;
            // }

            // 3: cu range loop (varianta recomandata, in general)
            for (auto& x : v) {
                sum += x;
            }
            // de ce este recomandata varianta 3?
            // - merge pentru orice container STL (vector, stack, map, etc)
            // - este mai clara
            // - lucreaza cu referinte, deci putem sa modificam elementele in for
            //   (daca nu vrem sa le modificam, putem folosi const auto& x)
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

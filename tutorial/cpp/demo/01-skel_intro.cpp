// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>       // include toate headerele de care avem nevoie
// using namespace std;        // (optional): sa nu mai folositi std::

class Task {
    // declarare membri (vizibil in toata clasa)
    // ex. daca calculam fibonacci
    int n;          //  citim n din fisier in read()
    int fibo;       //  vom salva in fibo al n-lea termen fibonacci in compute_solution()
                    //  vom scrie fibo in fisier in print()

    public:
        void read() {
            std::ifstream in("in");
            in >> n;
            in.close();
        }

        void compute_solution() {
            if (n == 0) {
                fibo = 0;
                return;
            } else if (n <= 2) {
                fibo = 1;
                return;
            }

            // n >= 3
            int prev = 0, current = 1;
            for (int i = 2; i <= n; ++i) {
                int next = prev + current;
                prev = current;
                current = next;
            }
            fibo = current;
        }

        void solve() {
            read();
            compute_solution();
            print();
        }

        void print() {
            std::ofstream out("out");
            out << fibo << "\n";
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


// compilare: g++ -std=c++11 *.cpp -o gigel
// rulare   : ./gigel

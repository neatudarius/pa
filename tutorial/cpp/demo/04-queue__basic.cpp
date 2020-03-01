// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::queue (https://en.cppreference.com/w/cpp/container/queue).

class Task {
    // fisierul "in" contine n (numarul de elemente) si elementele vectorului v
    int n;
    std::vector<int> v;

    public:
        void read() {
            std::ifstream in("in");
            in >> n;
            for (int i = 0; i < n; ++i) {
                int x;
                in >> x;
                v.push_back(x);
            }
            in.close();
        }

        void compute_solution() {
            // folosesc o stiva de int-uri
            std::queue<int> q;

            // bag toate elementele in stiva
            for (auto& x : v) {
                q.push(x);
            }

            // scot toate elementele
            while (!q.empty()) {
                int x = q.front();
                q.pop();

                // fa ceva cu x
                std::cout << x << "\n";
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

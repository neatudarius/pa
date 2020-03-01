// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::map (https://en.cppreference.com/w/cpp/container/map).

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
            // initializare
            std::map<std::string, int> h;
            for (auto& x : v) {
                h[x]++;
            }

            // 1. find - cautare element in h
            std::string x = "gigel";
            auto it = h.find(x);
            if (it != h.end()) {
                std::cout <<  x << " este in map\n";
            } else {
                std::cout <<  x << " NU este in map\n";
            }

            // 2. erase - sterge elementul din h
            h.erase(x);

            // verificam daca mai este
            it = h.find(x);
            if (it != h.end()) {
                std::cout <<  x << " este in map\n";
            } else {
                std::cout <<  x << " NU este in map\n";
            }

            // 3. insert - adagaure element in h
            h[x]++; // echivalent cu h.insert(x, 0), h[x] = h[x] + 1 = 0 + 1 = 1

            // verificam daca mai este
            it = h.find(x);
            if (it != h.end()) {
                std::cout <<  x << " este in map\n";
            } else {
                std::cout <<  x << " NU este in map\n";
            }
        }

        void solve() {
            read();
            compute_solution();
            print();
        }

        void print() {
            std::ofstream out("out");
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

// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::map (https://en.cppreference.com/w/cpp/container/map).

class Task {
    public:
        void read() {
            std::ifstream in("in");
            in.close();
        }

        void compute_solution() {
            // declaram un hashtable pe care il folosim sa numaram string-uri
            std::map<std::string, int> h;

            // metode de intializare

            // 1. folosind operator de indexare []
            h["gigel1"] = 1;
            h["gigel2"] = 10;
            h["gigel3"] = 100;

            // 2. emplace_back
            // h.emplace("gigel1", 1);
            // h.emplace("gigel2", 10);
            // h.emplace("gigel3", 100);

            // 3. inserare pereche
            // h.insert({"gigel1", 1}); // se contruieste o pereche cu elementele date
            // h.insert({"gigel1", 10});
            // h.insert({"gigel1", 100});

            // parcurgerea este aceeasi, indiferent de initializare
            for (auto& p : h) {
                std::cout << p.first << " " << p.second << "\n";
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

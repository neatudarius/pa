// Copyright 2020 Darius Neatu <neatudarius@gmail.com>

#include <bits/stdc++.h>

// Demo std::map (https://en.cppreference.com/w/cpp/container/map).

struct CmpAscending {
    bool operator()(const std::string& k1, const std::string& k2) const {
        return k1 < k2; // crescator
    }
};

struct CmpDescending {
    bool operator()(const std::string& k1, const std::string& k2) const {
        return k1 > k2; // desccrescator
    }
};

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
            // numaram cu un map care tinem cheile in ordine crescatoare
            std::map<std::string, int> h_asc;
            // std::map<std::string, int, CmpAscending> h_asc; (declaratie echivalenta)
            for (auto& x : v) {
                h_asc[x]++;
            }
            std::cout << "h_asc:\n";
            for (auto& p : h_asc) {
                std::cout << p.first << " " << p.second << "\n";
            }
            std::cout << "\n";

            // numaram cu un map care tinem cheile in ordine descrescatoare
            std::map<std::string, int, CmpDescending> h_desc;
            for (auto& x : v) {
                h_desc[x]++;
            }
            std::cout << "h_desc:\n";
            for (auto& p : h_desc) {
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
// ./05-map__comparator 
// h_asc:
// gigel 4
// gigel_again 1
// just_gigel 1
// not_gigel 4

// h_desc:
// not_gigel 4
// just_gigel 1
// gigel_again 1
// gigel 4

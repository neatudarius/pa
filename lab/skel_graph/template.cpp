// Copyright 2018 ...
// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

// ProblemName RO (Shortcut) - ProblemName EN (Shortcut)
// AlgorithmName - Complexity

// links:
// - infoarena link
// - other link

#include <bits/stdc++.h>

#define NMAX 100010
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        get_result();
        print_output();
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // adj[node] lista de adiacenta a nodului node
    std::vector<int> adj[NMAX];

    void read_input() { }

    void get_result() { }

    void print_output() { }
};

int main() {
    // din cauza ca fac redirectari, salvez starea lui std::cin si std::cout
    auto cin_buff  = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    ifstream fin("in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    // ofstream fout("out");
    // std::cout.rdbuf(fout.rdbuf()); //save and redirect

    // aici este rezolvarea propriu-zisa
    Task* task = new Task();
    task->solve();
    delete task;

    // restore pentru std::cin si std::cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide

    return 0;
}

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
    vector<int> adj[NMAX];

    void read_input() { }

    void get_result() { }

    void print_output() { }
};

int main() {
    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff  = cin.rdbuf();
    auto cout_buff = cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    ifstream fin("in");
    cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    // ofstream fout("out");
    // cout.rdbuf(fout.rdbuf()); //save and redirect

    // aici este rezolvarea propriu-zisa
    Task* task = new Task();
    task->solve();
    delete task;

    // restore pentru cin si cout
    cin.rdbuf(cin_buff);
    cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide

    return 0;
}

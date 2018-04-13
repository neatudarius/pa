// Copyright 2018 Popescu Alexandru Gabriel <alexandru.popescu0697@gmail.com>
// Copyright 2018 Darius Neatu <neatudarius@gmail.com>
// Componente Tare Conexe (CTC) - Strongly Connected Components (SCC)
// Kosaraju - O(n + m)
// https://infoarena.ro/problema/ctc
#include <bits/stdc++.h>

#define NMAX 100010
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        kosaraju();
        print_output();
    }

private:
    int n, m, sol = 0;          // n = numar de noduri, m = numar de muchii, sol = numarul de comp. tare conexe
    vector<int> adj[NMAX];      // adj[node] lista de adiacenta a nodului node pentru graful initial
    vector<int> adj_t[NMAX];    // adj_t[node] lista de adiacenta a nodului node pentru graful transpus
    vector<vector<int> > CTC;   // retin solutia
    vector<int> visited;
    vector<int> Tsort;          // retin nodurile crescator dupa timpul de finalizare, nu folosim stiva

    void read_input() {
        cin >> n >> m;
        visited = vector<int>(n + 1, 0);
        Tsort = vector<int>(n + 1, 0);
        int x, y;
        for (int i = 1; i <= m; ++i) {
            cin >> x >> y;
            adj[x].push_back(y);
            adj_t[y].push_back(x);
        }
    }

    void kosaraju() {
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        for (int i = n; i >= 1; --i) {
            if (visited[Tsort[i]]) {
                vector<int> current_ctc;
                dfs_t(Tsort[i], current_ctc);
                CTC.push_back(current_ctc);
                ++sol;
            }
        }
    }

    void dfs(int node) {
        visited[node] = 1;
        for (auto &vecin : adj[node]) {
            if (!visited[vecin]) {
                dfs(vecin);
            }
        }
        Tsort[++Tsort[0]] = node;       //Tsort[0] functioneaza pe post de counter
    }

    void dfs_t(int node, vector<int> &current_ctc) {
        visited[node] = 0;
        current_ctc.push_back(node);
        for (auto &vecin : adj_t[node]) {
            if (visited[vecin]) {
                dfs_t(vecin, current_ctc);
            }
        }
    }

    void print_output() {
        // pentru verificare pe infoarena trebuie doar modificata afisarea
        // cout << sol << '\n';
        cout << "Graful are " << sol << " componente tare conexe\n";
        for (int i = 0; i < sol; ++i) {
            cout << "Componenta tare conexa [" << i + 1 << "]: ";
            for (auto &node : CTC[i]) {
                cout << node << " ";
            }
            cout << '\n';
        }
    }
};

int main() {
    Task *task = new Task();

    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff = cin.rdbuf();
    auto cout_buff = cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    ifstream fin("ctc.in");
    cin.rdbuf(fin.rdbuf()); //save and redirect

    // las liniile urmatoare daca afisez in fisier
    // ofstream fout("ctc.out");
    // cout.rdbuf(fout.rdbuf()); //save and redirect

    // aici este rezolvarea propriu-zisa
    task->solve();

    // restore pentru cin si cout
    cin.rdbuf(cin_buff);
    cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide
    delete task;
    return 0;
}

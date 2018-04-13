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
    get_result();
    print_output();
  }

private:
  // n = numar de noduri, m = numar de muchii
  int n, m;

  // adj[node] lista de adiacenta a nodului node pentru graful initial
  vector<int> adj[NMAX];

  // adj_trans[node] lista de adiacenta a nodului node pentru graful transpus
  vector<int> adj_trans[NMAX];

  // ctc[i] = componenta tare conexa cu indicele i
  vector<vector<int>> ctc;

  vector<int> visited;

  // retin nodurile crescator dupa timpul de finalizare, nu folosim stiva
  vector<int> topsort;

  void read_input() {
    cin >> n >> m;
    visited = vector<int>(n + 1, 0);
    int x, y;
    for (int i = 1; i <= m; ++i) {
      cin >> x >> y;
      adj[x].push_back(y);
      adj_trans[y].push_back(x);
    }
  }

  void get_result() {
    kosaraju();
  }

  void kosaraju() {
    topsort.push_back(-1); // indexare de la 1
    for (int i = 1; i <= n; ++i) {
      if (!visited[i]) {
        dfs(i);
      }
    }
    for (int i = n; i >= 1; --i) {
      if (visited[topsort[i]]) {
        vector<int> current_ctc;
        dfs_t(topsort[i], current_ctc);
        ctc.push_back(current_ctc);
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
    topsort.push_back(node);
  }

  void dfs_t(int node, vector<int> &current_ctc) {
    visited[node] = 0;
    current_ctc.push_back(node);
    for (auto &vecin : adj_trans[node]) {
      if (visited[vecin]) {
        dfs_t(vecin, current_ctc);
      }
    }
  }

  void print_output() {
    // pentru verificare pe infoarena trebuie doar modificata afisarea
    int sol = ctc.size();
    cout << "Graful are " << sol << " componente tare conexe\n";
    for (int i = 0; i < sol; ++i) {
      cout << "Componenta tare conexa [" << i + 1 << "]: ";
      for (auto &node : ctc[i]) {
        cout << node << " ";
      }
      cout << '\n';
    }
  }
};

int main() {
  // din cauza ca fac redirectari, salvez starea lui cin si cout
  auto cin_buff = cin.rdbuf();
  auto cout_buff = cout.rdbuf();

  // las liniile urmatoare daca citesc din fisier
  ifstream fin("ctc.in");
  cin.rdbuf(fin.rdbuf()); // save and redirect

  // las liniile urmatoare daca afisez in fisier
  // ofstream fout("ctc.out");
  // cout.rdbuf(fout.rdbuf()); //save and redirect

  // aici este rezolvarea propriu-zisa
  Task *task = new Task();
  task->solve();
  delete task;

  // restore pentru cin si cout
  cin.rdbuf(cin_buff);
  cout.rdbuf(cout_buff);

  // obs. nu e nevoie sa inchid fisierele
  // cand se apeleaza destructorii pentru fin si fout se vor inchide

  return 0;
}

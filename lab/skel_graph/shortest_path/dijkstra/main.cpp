// Copyright 2018 Popescu Alexandru Gabriel <alexandru.popescu0697@gmail.com>
// Copyright 2017 Darius Neatu <neatudarius@gmail.com>

// Dijkstra
// O(m log n)
// Deoarece folosesc heapuri binare (priority_queue),
// complexitatea este cea de mai sus

// http://www.infoarena.ro/problema/dijkstra

#include <bits/stdc++.h>

#define NMAX 50010   // ATENTIE la cat e in problema curenta !!!
#define oo (1 << 30) // ATENTIE la cat e in problema curenta !!!
#define NO_PARENT (-1)

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

  // source = sursa din Dijkstra
  int source;

  // adj[i] contine perechi de tipul : vecin , costul muchiei i -> vecin
  vector<pair<int, int>> adj[NMAX];

  // min-heap ce contine perechi de tipul: distanta de la source la
  // nodul x, nodul x
  // folosit pentru e extrage la fiecare pas nodul care are costul
  // estimat minim fata de sursa
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 std::greater<pair<int, int>>>
      pq;

  // d[i] = distanta minima de la de source la nodul i
  vector<int> d;

  // p[i] = parintele lui i de pe drumul minim de la source la nodul i
  vector<int> p;

  void read_input() {
    cin >> n >> m;

    d.resize(n + 1);

    p.resize(n + 1);

    // pe infoarena sursa este 1
    // modificati linia urmatoare pentru a seta alta sursa
    source = 1;

    for (int i = 1; i <= m; ++i) {
      // citim muchii x -> y, de cost c
      int x, y, c;
      cin >> x >> y >> c;

      // adaugam in lista de adiacenta a nodului x
      // nodul y cu costul muchiei x -> y = c
      adj[x].push_back({y, c});
    }
  }

  void get_result() { Dijkstra(source, d, p); }

  void Dijkstra(int source, vector<int> &d, vector<int> &p) {
    // ETAPA 1
    for (int i = 1; i <= n; ++i) {
      // presupun ca nu am drum
      d[i] = oo;

      // deci nici parinte (i inaccesibil)
      p[i] = NO_PARENT;
    }

    // ETAPA 2

    // parintele lui source este 0 - conventie
    p[source] = 0;

    // distanta de la source la source e 0
    d[source] = 0;

    pq.push({d[source], source});

    // ETAPA 3
    while (!pq.empty()) {
      // extragem nodul care are costul estimat minim fata de sursa
      auto entry = pq.top();
      pq.pop();
      int cost = entry.first;
      int node = entry.second;

      // daca intrarea curenta nu este up-to-date
      if (cost > d[node]) {
        continue;
      }

      // pentru fiecare vecin, incercam sa relaxam costul de la sursa
      // la el trecand prin nodul node
      for (auto &edge : adj[node]) {
        int neighbour = edge.first;
        int cost_edge = edge.second;

        // daca obtinem un costmai mic trecand prin node
        if (d[node] + cost_edge < d[neighbour]) {

          // salvam noua distanta
          d[neighbour] = d[node] + cost_edge;

          // noul parinte devine node
          p[neighbour] = node;

          // actualizez costul drumului de la sursa la vecin
          pq.push({d[neighbour], neighbour});
        }
      }
    }

    // ETAPA 4 - daca e cazul
    // infoarena vrea sa nu afisez oo, ci 0
    for (int i = 1; i <= n; ++i) {
      if (d[i] == oo) {
        d[i] = 0;
      }
    }
  }

  // rebuild source -> ... -> node (if exists)
  vector<int> rebuild_path(int node, vector<int> &p) {
    // nu exista drum de la source la node
    if (p[node] == NO_PARENT) {
      return {};
    }

    // path = {source, ..., node}
    vector<int> path;

    // rebuild node -> ... -> source (if exists)
    for (; node != 0; node = p[node]) {
      path.push_back(node);
    }
    // cand node == source, p[node] == 0
    // (asta ma asigura ca forul se opreste la iteratia urmatoare)

    // s-a obtinut drumul node -> ... -> source
    // inversam solutia
    reverse(path.begin(), path.end());

    return path;
  }

  void print_output() {
    for (int i = 1; i <= n; ++i) {
      if (i == source) {
        continue;
      }
      if (d[i] == 0) {
        cout << "Nu exista drum de la " << source << " la nodul " << i << '\n';
        continue;
      }
      cout << "Distanta minima de la nodul " << source << " la nodul " << i
           << " este ";
      cout << d[i] << " ";
      cout << "pe drumul:\n";
      auto path = rebuild_path(i, p);
      for (auto &node : path) {
        cout << node << ' ';
      }
      cout << '\n';
    }
    cout << "\n";
  }
};

int main() {
  // din cauza ca fac redirectari, salvez starea lui cin si cout
  auto cin_buff = cin.rdbuf();
  auto cout_buff = cout.rdbuf();

  // las liniile urmatoare daca citesc din fisier
  ifstream fin("dijkstra.in");
  cin.rdbuf(fin.rdbuf()); // save and redirect

  // las liniile urmatoare daca afisez in fisier
  // ofstream fout("dijkstra.out");
  // cout.rdbuf(fout.rdbuf()); // save and redirect

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

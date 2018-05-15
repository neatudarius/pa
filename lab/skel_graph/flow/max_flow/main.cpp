// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

// Edmonds-Karp - O(n * m^2)
// http://www.infoarena.ro/problema/maxflow

// Aceasta sursa ia 70p pe infoarena: https://infoarena.ro/job_detail/2204311
// Este suficient pentru PA!

#include <bits/stdc++.h>
using namespace std;

const int kNmax = 1005;
const int kInf = (1 << 30);

class Task {
public:
  void solve() {
    read_input();
    print_output(get_result());
  }

private:
  int n, m;
  vector<int> adj[kNmax];

  // p[node] = parintele lui node din parcurgerea BFS
  int p[kNmax];

  // sursa si destinatia din retea
  int source, sink;

  // cap[i][j] = capacitatea muchiei i->j
  int cap[kNmax][kNmax];

  // flow[i][j] = fluxul curent pe muchia i->j
  // ATENTIE! Mereu flow[i][j] = -flow[j][i]
  int flow[kNmax][kNmax];

  void read_input() {
    cin >> n >> m;
    source = 1;
    sink = n;

    memset(cap, 0, sizeof cap); // retea cu toate cacitatile initial pe 0

    for (int i = 1, x, y, z; i <= m; ++i) {
      cin >> x >> y >> z;
      adj[x].push_back(y);
      adj[y].push_back(x);

      cap[x][y] += z;
    }
  }

  int get_result() { return get_maxflow(source, sink); }

  int get_maxflow(int source, int sink) {
    cout << "get_maxflow from " << source << " to " << sink << "\n\n";

    // nu am bagat flux in retea...
    int maxFlow = 0;
    memset(flow, 0, sizeof flow);

    // cat timp se gaseste un drum VALID de la source la sink
    while (BFS(source, sink)) {
      print_path(source, sink);

      // parcurg drumul: d = sink <- x <- ... <- source (il am inversat)
      // minFlow = min(cap[ parent ][ node ] - flow[ parent ][ node ])
      // unde node <- parent este o muchie de pe drumul d
      int minFlow = kInf;
      for (int node = sink; node != source; node = p[node]) {
        int available_flow = cap[p[node]][node] - flow[p[node]][node];
        minFlow = min(minFlow, available_flow);
      }

      // DACA se poate baga pe acest drum cel putin o unitate de flux
      if (minFlow >= 1) {
        cout << "increment flow with " << minFlow << "\n\n";
        maxFlow += minFlow; // il vom baga

        // actualizez drumul
        for (int node = sink; node != source; node = p[node]) {
          flow[p[node]][node] += minFlow; // adaug fluxul pe muchia de pe drum
          flow[node][p[node]] -= minFlow; // scad  fluxul in sens invers
        }
      }
    }

    return maxFlow;
  }

  // gaseste drum VALID de la source la sink
  // drum valid == drum pt care capacitatea reziduala a fiecarui arc este strict
  // pozitiva
  // a.k.a. cap[i][j] - flow[i][j] > 0, pentru arcul i->j
  //         (muchia i->j nu e saturata)
  bool BFS(int source, int sink) {
    queue<int> Q;

    // initializare vector parinti din BFS
    for (int i = 1; i <= n; ++i) {
      p[i] = -1; // nimeni nu are parinte
    }

    // sursa este radacina in arborele BFS - singura cu parinte 0
    Q.push(source);
    p[source] = 0;

    while (!Q.empty()) {
      int node = Q.front();
      Q.pop();

      for (auto &x : adj[node]) {
        // daca x NU are parinte si muchia node->x NU este saturata
        if (p[x] == -1 && flow[node][x] < cap[node][x]) {
          p[x] = node;
          Q.push(x);
        }
      }
    }

    // returnez TRUE daca se poate ajunge se la source la sink
    return p[sink] != -1;
  }

  void print_path(int source, int sink) {
    vector<int> path;
    for (int node = sink; node != source; node = p[node]) {
      path.push_back(node);
    }
    path.push_back(source);

    reverse(path.begin(), path.end());

    cout << "path: ";
    for (auto &node : path) {
      cout << node << " ";
    }
    cout << "\n";
  }

  void print_output(int result) { cout << "maxflow = " << result << "\n"; }
};

int main() {
  // din cauza ca fac redirectari, salvez starea lui cin si cout
  auto cin_buff = cin.rdbuf();
  auto cout_buff = cout.rdbuf();

  // las liniile urmatoare daca citesc din fisier
  ifstream fin("maxflow.in");
  cin.rdbuf(fin.rdbuf()); // save and redirect

  // las liniile urmatoare daca afisez in fisier
  // ofstream fout("maxflow.out");
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

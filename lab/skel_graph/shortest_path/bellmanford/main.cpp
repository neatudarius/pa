// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

/*
    skel_graph - BellmanFord - O(mn)
    (Sau cu notatia din lab O(EV))
    http://www.infoarena.ro/problema/bellmanford

    Varianta infoarena - simple as bfs :*
    In practica facem altfel decat in laborator.
    Imi place ca si coding style varianta asta.

    In plus, ma opresc daca un nod a fost folosit de n ori,
    pentru ca atunci am gasit un ciclu de cost negativ.
    => ca in practica fac < m * (n - 1) relaxari
*/

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define NMAX 50009   // ATENTIE la cat e in problema curenta !!!
#define MMAX 250009  // ATENTIE la cat e in problema curenta !!!
#define oo (1 << 30) // ATENTIE la cat e in problema curenta !!!
using namespace std;

// tipul edge
// muchia de cost "cost", de la node la neighbour,
// va fi un element edge(neighbour, cost) in G[node]
typedef pair<int, int> edge;
#define neighbour first
#define cost second

// aceleasi semnificatii ca la BFS
int n, m;
int d[NMAX], p[NMAX], used[NMAX];
vector<edge> G[NMAX];

// coada
queue<int> Q;

void read_input() {
  cin >> n >> m;

  for (int i = 1; i <= m; ++i) {
    int x, y, c; // x -> y, de cost c
    cin >> x >> y >> c;

    G[x].push_back(edge(y, c));
    // G[y].push_back(edge(x, c)); // sterg daca e orientat !!!
  }
}

// return true = ciclu de cost negativ
// return false = nu are ciclu de cost negativ
bool BellmanFord(int source) {
  // ETAPA 1
  for (int i = 1; i <= n; ++i) {
    d[i] = oo;
    p[i] = oo;
  }

  // ETAPA 2
  Q.push(source);
  d[source] = 0;
  p[source] = 0;

  // ETAPA 3
  while (!Q.empty()) {
    int node = Q.front();
    Q.pop();

    ++used[node];
    if (used[node] == n) {
      return true; // am gasit ciclu de cost negativ
    }

    for (auto it = G[node].begin(); it != G[node].end(); ++it) {
      int neighbour = it->neighbour;
      int cost_edge = it->cost;

      if (d[node] + cost_edge < d[neighbour]) {
        d[neighbour] = d[node] + cost_edge;
        p[neighbour] = node;

        Q.push(neighbour);
      }
    }
  }

  // ETAPA 4 - daca e cazul
  return false;
}

// in solve scriu tot ce tine de rezolvare - e ca un main
void solve() {
  // pe infoarena sursa este 1
  if (BellmanFord(1)) {
    cout << "Ciclu negativ!\n";
  } else {
    for (int i = 2; i <= n; ++i) {
      cout << d[i] << " ";
    }
    cout << "\n";
  }
}

// rebuild source -> ... -> node (if exists)
void rebuild_path_recursive(int node, int source) {
  if (d[node] == oo) {
    cout << "Drum inexistent!";
    return;
  }

  if (node == source) { // sau p[node] = 0; // conditie echivalenta
    cout << node << " ";
    return;
  }

  // rebuild first source -> ...-> p[node]
  rebuild_path_recursive(p[node], source);

  // then p[node] -> node
  cout << node << " ";
}

// puteti pastra main-ul mereu cum e acum
int main() {
  // las linia urmatoare daca citesc din fisier
  assert(freopen("bellmanford.in", "r", stdin) != NULL);

  // las linia urmatoare daca afisez in fisier
  assert(freopen("bellmanford.out", "w", stdout) != NULL);

  read_input();
  solve();
  // print_output();

  return 0;
}

// Obs: pe infoarena ia 85p din cauza citirii (ignorati faptul ca testele sunt
// grupate, nu ne intereseaza asa ceva la PA :D)
// http://www.infoarena.ro/job_detail/1970189
// oricum mai rapid decat pseudocodul din laborator
// desigur.. il puteti adapta sa se opreasca mai devreme, daca vreti

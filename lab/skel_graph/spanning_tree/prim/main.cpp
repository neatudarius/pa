/*
    skel_graph - Prim -  O(MlogN)
    http://www.infoarena.ro/problema/apm
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#define NMAX 200009  // ATENTIE la cat e in problema curenta !!!
#define MMAX 400009  // ATENTIE la cat e in problema curenta !!!
#define oo (1 << 30) // ATENTIE la cat e in problema curenta !!!
using namespace std;

// citire doar pt infoarena
ifstream in("apm.in");
ofstream out("apm.out");
#define cin in
#define cout out

// tipul edge
// muchia first_node -> second_node de cost edge_cost
typedef tuple<int, int> edge;
#define get_cost(t)                                                            \
  std::get<0>(t) // l-am pus primul pentru a fi primul folosit in sortare de
                 // catre greater
#define get_neighbour(t) std::get<1>(t)

int n, m, cost_apm, root;
int d[NMAX], p[NMAX];
vector<edge> G[NMAX];
vector<edge> apm;

// d[node] este distanta minima de la arbore la node <=> muchia de cost minim
// aleasa pentru a unui node cu apm-ul curent

// coada
priority_queue<edge, vector<edge>, std::greater<edge>> pq;
// vector de folosire
bitset<NMAX> used;

void read_input() {
  cin >> n >> m;

  for (int i = 1; i <= m; ++i) {
    int x, y, c; // x -> y, de cost c
    cin >> x >> y >> c;

    G[x].push_back(edge(c, y));
    G[y].push_back(edge(c, x));
  }
}

void Prim() {
  // ETAPA 1
  for (int i = 1; i <= n; ++i) {
    d[i] = oo;
    p[i] = 0;
  }

  // ETAPA 2 - alege o radacina random
  root = 1;
  d[root] = 0;
  p[root] = 0;
  pq.push(edge(d[root], root));

  cost_apm = 0;
  for (int i = 1; i <= n;
       ++i) { // adauga n - 1 muchii la arbore <=> adauga n noduri in arbore
    tuple<int, int> e;
    int node;
    do {
      e = pq.top();
      pq.pop();

      node = get_neighbour(e);
    } while (used[node]); // daca node este deja in subarborele construit,
                          // inseamna ca nu am ce face cu el. scot altul din
                          // heap

    cost_apm += d[node];
    used[node] = 1;

    for (auto it = G[node].begin(); it != G[node].end(); ++it) {
      int neighbour = get_neighbour(*it), cost = get_cost(*it);

      if (!used[neighbour] && cost < d[neighbour]) {
        d[neighbour] = cost;
        p[neighbour] = node;
        pq.push(edge(d[neighbour], neighbour));
      }
    }
  }
}

// in solve scriu tot ce tine de rezolvare - e ca un main
void solve() {
  Prim();

  cout << cost_apm << "\n";
  cout << (n - 1) << "\n"; // ghici ce? e mereu n-1 :p
  for (int i = 1; i <= n; ++i) {
    if (i != root) {
      cout << i << " " << p[i] << "\n";
    }
  }
}

// puteti pastra main-ul mereu cum e acum
int main() {
  // // las linia urmatoare daca citesc din fisier
  // assert( freopen("apm.in", "r", stdin) != NULL);

  // // las linia urmatoare daca afisez in fisier
  // assert( freopen("apm.out", "w", stdout) != NULL) ;

  read_input();
  solve();

  return 0;
}

// http://www.infoarena.ro/job_detail/1970248

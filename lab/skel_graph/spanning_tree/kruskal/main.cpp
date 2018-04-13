/*
    skel_graph - Kruskal -  O(Mlog*N + MlogM)
    http://www.infoarena.ro/problema/apm

    (cine e intersat de ce log* si nu log =>
   https://en.wikipedia.org/wiki/Iterated_logarithm)
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
typedef tuple<int, int, int> edge;
#define edge_cost(t)                                                           \
  std::get<0>(t) // l-am pus primul pentru a fi primul folosit in sortare
#define first_node(t) std::get<1>(t)
#define second_node(t) std::get<2>(t)

// aceleasi semnificatii ca la BFS
int n, m, cost_apm, p[NMAX];
vector<edge> edges;
vector<edge> apm;

void read_input() {
  cin >> n >> m;

  for (int i = 1; i <= m; ++i) {
    int x, y, c; // x -> y, de cost c
    cin >> x >> y >> c;

    edges.push_back(edge(c, x, y));
  }
}

// daca node nu este radacina, urca din tata in tata
// pana la radacina (radacina este reprezentantul componentei conexe)
int get_set(int node) {
  if (p[node] != node) {
    p[node] = get_set(p[node]);
  }

  return p[node];
}

// reuneste cele 2 componente intr-una singura
// un root va deveni tatal celuilalt root
void reunion_set(int x, int y) { p[get_set(x)] = get_set(y); }

void Kruskal() {
  // ETAPA 1
  for (int i = 1; i <= n; ++i) {
    p[i] = i; // i este parintele lui i <=> fiecare nod este o componenta conexa
              // (la inceput)
  }

  // ETAPA 2
  cost_apm = 0;
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    int x = first_node(*it), y = second_node(*it), c = edge_cost(*it);

    // daca x si y sunt in componente conexe diferite
    if (get_set(x) != get_set(y)) {
      // adauga muchia la apm
      cost_apm += c;
      apm.push_back(*it);

      // reuneste cele 2 componente intr-una singura
      reunion_set(x, y);
    }
  }
}

// in solve scriu tot ce tine de rezolvare - e ca un main
void solve() {
  sort(edges.begin(), edges.end());

  // aplic Kruskal pe muchiile sortate crescator dupa cost
  Kruskal();

  cout << cost_apm << "\n";
  cout << apm.size() << "\n"; // ghici ce? e mereu n-1 :p
  for (auto it = apm.begin(); it != apm.end(); ++it) {
    cout << first_node(*it) << " " << second_node(*it) << "\n";
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

// http://www.infoarena.ro/job_detail/1970225

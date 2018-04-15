// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

// Ciclu in graf orientat
// Kahn - O(n + m)

// 		Idee: se incearca sa se gaseasca o sortare topologica cu
// algoritmul
// lui Kahn. Daca la finalul algoritmului exista cel putin un nod cu grad
// intern mai mare ca zero, atunci graful are ciclu (nu s-a putut sorta
// topologic).

// links:
// - description: https://leetcode.com/problems/course-schedule/description/
// - tested here: https://discuss.leetcode.com/topic/121588/pa-hahn-cpp-solution

#include <bits/stdc++.h>
using namespace std;

#define NMAX 100009 // numar maxim de noduri

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

  // adj[node] = lista de adiacenta a lui node
  vector<int> adj[NMAX];
  // (observatie: prin conventie nodurile sunt indexate de la 1
  //  deci listele sunt adj[1], ..., adj[n])

  // in_degree[i] = gradul intern al nodului i
  vector<int> in_degree;
  // grad intern == nr de muchii care intra in i
  // arce de forma x -> i

  // graful este aciclic
  bool is_acyclic;

  void read_input() {
    // citesc numar de noduri, numar de muchii
    cin >> n >> m;

    // grad intern 0 pentru toate nodurile... momentan
    in_degree = vector<int>(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
      int x, y;
      cin >> x >> y; // citesc muchia x-y

      adj[x].push_back(y); // graful e orientat
      ++in_degree[y];      // inca o muchie care intra in y
    }
  }

  void get_result() {
    // se va dace o parcurge BFS din TOATE nodurile cu grad intern 0
    bfs();

    // verifica ca s-a realizat o sortare topologica valida!
    // ce inseamna asta? s-au sters toate muchiile din graf.
    // daca nu s-a sters tot, atunci graful este ciclic!
    bool is_valid = true;
    for (int i = 1; i <= n; ++i) {
      if (in_degree[i] > 0) {
        is_valid = false;
        break;
      }
    }

    if (is_valid) {
      is_acyclic = true; // graf ACICLIC (valid topsort)
    } else {
      is_acyclic = false; // graf CICLIC  (invalid topsort)
    }
  }

  void bfs() {
    // declaram o coada in care putem baga noduri
    queue<int> Q;

    // pasul initial: pun in coada TOATE nodurile cu grad intern 0
    for (int i = 1; i <= n; ++i) {
      if (in_degree[i] == 0) {
        Q.push(i);
      }
    }

    // parcurg in latime graful
    while (!Q.empty()) {
      // SCOT primul nod din coada
      int node = Q.front();
      Q.pop();

      // Ii parcurg toti vecinii
      for (auto &it : adj[node]) {
        // sterg muchia node->it
        // obs1. NU e nevoie sa o sterg la propriu
        //       Daca nu am cicluri, nu se va ajunge aici.
        // obs2. Simulez stergerea prin scaderea gradului intern a lui it
        --in_degree[it];

        // daca it a ajuns nod cu grad intern 0, atunci este adaugat in coada
        if (in_degree[it] == 0) {
          Q.push(it);
        }
      }
    }
  }

  void print_output() {
    if (is_acyclic) {
      cout << "Graful ESTE aciclic!\n";
    } else {
      cout << "Graful ARE ciclu (rosu)!\n";
    }
  }
};

int main() {
  // din cauza ca fac redirectari, salvez starea lui cin si cout
  auto cin_buff = cin.rdbuf();
  auto cout_buff = cout.rdbuf();

  // las liniile urmatoare daca citesc din fisier
  ifstream fin("cycle.in");
  cin.rdbuf(fin.rdbuf()); // save and redirect

  // las liniile urmatoare daca afisez in fisier
  // ofstream fout("cycle.out");
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

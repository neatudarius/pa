// Copyright 2018 Dariu// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

// Ciclu in graf orientat
// DFS - O(n + m)

// 		Idee: gasim o muchie de intoarcere.
// (muchie de la un nod in curs de vizitare la un nod care inca e
//  e in curs de vizitare)

// links:
// - description: https://leetcode.com/problems/course-schedule/description/
// - tested here: https://discuss.leetcode.com/topic/121590/pa-dfs-cpp-solution

#include <bits/stdc++.h>
using namespace std;

#define NMAX 100009 // numar maxim de noduri

// orice nod poate avea 3 stari cand vizitam graful:
// NOT_DISCOVERED: inca nu l-am descoperit (initial toate sunt asa)
// DISCOVERED    : atunci cand intram intr-un nod sa il vizitam recursiv
// FINISHED      : marcam un nod ca fiind FINISHED imediat dupa ce am terminat
//                 parcurgerea recursiva din acel nod
#define NOT_DISCOVERED 0
#define DISCOVERED 1
#define FINISHED 2

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

  // graful este aciclic
  bool is_acyclic;

  void read_input() {
    // citesc numar de noduri, numar de muchii
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
      int x, y;
      cin >> x >> y; // citesc muchia x-y

      adj[x].push_back(y); // graful e orientat
    }
  }

  void get_result() {
    // visited[node] = starea lui nod in parcurgerea curenta
    vector<int> visited(n + 1, NOT_DISCOVERED);

    // presupun ca graful e aciclic
    is_acyclic = true;

    // incerc sa pornesc un DFS din fiecare nod nevizitat
    for (int i = 1; i <= n; ++i) {
      if (!visited[i]) {
        // vad daca pornind din i se gaseste un ciclu
        auto has_cycle = dfs(i, visited);

        // am gasit un ciclu (rosu)
        if (has_cycle) {
          is_acyclic = false;
          break;
        }
      }
    }
  }

  // dfs viziteaza recursiv pornind din node si returneaza
  // - true, daca a gasit un ciclu
  // - false, altfel
  bool dfs(int node, vector<int> &visited) {
    // marched nodul ca fiind descoperit
    // incep sa il vizitez
    visited[node] = DISCOVERED;

    for (auto &x : adj[node]) {
      // am ciclu daca:
      // 1. daca x este un nod descoperit, dar neterminat
      // (muchie de intoarcere == DISCOVERED->DISCOVERED)
      // 2. x este un nod nou, dar vizitand recursiv prin x gasesc un ciclu
      if (visited[x] == DISCOVERED || dfs(x, visited)) {
        return true;
      }
    }

    // am terminat de vizitat nodul
    visited[node] = FINISHED;
    return false;
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

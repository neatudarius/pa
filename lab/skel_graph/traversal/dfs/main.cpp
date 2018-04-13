// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

// Parcurgere in adancime
// DFS - O(n + m)

// Exemplificare: determinare componente conexe
// https://infoarena.ro/problema/dfs

#include <bits/stdc++.h>
using namespace std;

// Constante in program
// ATENTIE la cat sunt in problema curenta !!!
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

  void read_input() {
    // citesc numar de noduri si numar de muschii
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
      int x, y;
      cin >> x >> y; // citesc muchia x-y

      adj[x].push_back(y);
      adj[y].push_back(x); // sterg daca e orientat !!!
    }
  }

  void get_result() {
    // in functia asta se scrie toata rezolvarea
    // se pot creea alte functii care pot fi apelate de aici
    // in acest demo am ales ca get_result sa nu intoarca ceva

    // aplica DFS pe un graf - viziteaza TOT graful
    do_dfs();
  }

  // aplica DFS pe un graf - viziteaza TOT graful
  void do_dfs() {
    // used[i] = 0, daca nodul i NU a mai fost folosit/vizitat
    //           1, daca nodul i a fost deja folosit/vizitat
    vector<int> used(n + 1);

    // STEP 1: marchez toate nodurile ca fiind nevizitate (si altele)
    for (int i = 1; i <= n; ++i) {
      used[i] = 0;
    }

    // STEP 2: vizitez tot graful - poate am mai multe componente conexe
    for (int i = 1; i <= n; ++i) { // incerc sa vizitez pe rand fiecare nod
      if (!used[i]) {              // daca este nevizitat
        cout << "new conex component: \n";
        dfs(i, used, " "); // il vizitez acum
      }
    }
  }

  // viziteaza recursiv nodul node
  // @node        - node este nodul curent de vizitat
  // @used        - used este vectorul in care se tin minte nodurile vizitate
  // @tabs        - e doar specific acestui tutorial
  //                (e folosit pentru a afisa indentat atunci cand se ruleaza)
  void dfs(int node, vector<int> &used, string tabs) {
    // STEP 1: aici incepe vizitarea nodului node
    used[node] = 1; // marchez nodul curent ca fiind vizitat
    cout << tabs << node << "++\n";

    // STEP 2: aici vizitez recursiv toti vecinii (nevizitati)
    for (auto &it : adj[node]) {    // pentru fiecare vecin al lui
      if (!used[it]) {              // daca vecinul este nevizitat
        dfs(it, used, tabs + "\t"); // il vizitez acum
      }
    }

    // STEP 3: aici se termina vizitarea lui node (mai pot face alte lucruri)
    cout << tabs << node << "--\n";
  }

  void print_output() { cout << "\nend of DFS demo - pwp\n"; }
};

void legend() {
  cout << "legend: node++ => enter in   node\n";
  cout << "legend: node-- => exit  from node\n";
  cout << "\n";
}

int main() {
  // las linia urmatoare daca citesc din fisier
  assert(freopen("in", "r", stdin) != NULL);

  // las linia urmatoare daca afisez in fisier
  // assert( freopen("out", "w", stdout) != NULL) ;

  legend();

  // din cauza ca avem tablouri cu NMAX elemente in clasa,
  // totul trebuie alocat dinamic - evit stack smash
  Task *task = new Task();
  task->solve();
  delete task;

  return 0;
}

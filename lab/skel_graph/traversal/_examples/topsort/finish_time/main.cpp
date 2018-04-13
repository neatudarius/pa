// Darius Neatu <neatudarius@gmail.com>
// 2018

// skel_graph - Topological Sort (DFS) - O(n + m)

// Sortare topologica cu DFS - sortare dupa timpii de finalizare
// https://infoarena.ro/problema/sortaret

#include <bits/stdc++.h>
using namespace std;

// Constante in program
// ATENTIE la cat sunt in problema curenta !!!
#define NMAX 100009 // numar maxim de noduri

class Task {
public:
  void solve() {
    read_input();
    print_output(get_result());
  }

private:
  // n = numar de noduri, m = numar de muchii
  int n, m;

  // adj[node] = lista de adiacenta a lui node
  vector<int> adj[NMAX];

  void read_input() {
    // citesc numar de noduri si numar de muschii
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
      int x, y;
      cin >> x >> y; // citesc muchia x-y

      adj[x].push_back(y); // graf orientat
    }
  }

  vector<int> get_result() {
    // vectorul care ca contine permutarea multimii {1, .. , n}
    // aceasta permutare va fi o sortare topologica valida
    vector<int> topsort;

    // used[i] = 0, daca nodul i NU a mai fost folosit/vizitat
    //           1, daca nodul i a fost deja folosit/vizitat
    vector<int> used(n + 1, 0); // initial toate sunt nefolosite

    // poate am mai multe componente - ma asigur ca le vizitez pe toate
    for (int i = 1; i <= n; ++i) { // incerc sa vizitez pe rand fiecare nod
      if (!used[i]) {              // daca este nevizitat
        dfs(i, used, topsort);     // il vizitez acum
      }
    }

    // sortarea topologica este sortarea decrescatoare dupa timp de finalizare
    // deoarece primul nod in care intru este cel adaugat ultimul in vector,
    // el are cel mai mare timp de finalizare. Am obtinut raspunsul inversat
    reverse(topsort.begin(), topsort.end());

    return topsort;
  }

  // viziteaza recursiv nodul node
  // @node        - node este nodul curent de vizitat
  // @used        - used este vectorul in care se tin minte nodurile vizitate
  // @topsort     - sortarea topologica obtinuta pana acum
  //                (nodurile ordonate dupa timpul de finalizare)
  void dfs(int node, vector<int> &used, vector<int> &topsort) {
    // STEP 1: aici incepe vizitarea nodului node
    used[node] = 1; // marchez nodul curent ca fiind vizitat

    // STEP 2: aici vizitez recursiv toti vecinii (nevizitati)
    for (auto &it : adj[node]) { // pentru fiecare vecin al lui
      if (!used[it]) {           // daca vecinul este nevizitat
        dfs(it, used, topsort);  // il vizitez acum
      }
    }

    // STEP 3: aici se termina vizitarea lui node (mai pot face alte lucruri)
    topsort.push_back(node); // adaug nodul in lista de noduri terminate
  }

  void print_output(vector<int> result) {
    if (result.size() == 0) {
      cout << "Graful NU este aciclic!\n";
      return;
    }

    for (int i = 0; i < (int)result.size(); ++i) {
      cout << result[i] << " ";
    }
    cout << "\n";
  }
};

void legend() {
  cerr << "legend: sirul afisat este o sortare topologica valida\n";
  cerr << "        (solutia nu e unica)\n";
  cerr << "\n";
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

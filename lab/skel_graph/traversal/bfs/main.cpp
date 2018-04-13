// Darius Neatu <neatudarius@gmail.com>
// 2018

// skel_graph - BFS - O(n + m)

// BFS - parcugere in latime
// Exemplificare: drumul minim ca si numar de arce de la o sursa source
//                la toate celelalte noduri din graf
// https://infoarena.ro/problema/bfs

#include <bits/stdc++.h>
using namespace std;

// Constante in program
// ATENTIE la cat sunt in problema curenta !!!
#define NMAX 100009    // numar maxim de noduri
#define kInf (1 << 30) // infinit pe 32 biti ;)
#define NO_PARENT -1   // nod fara parinte in arborele BFS - nod nevizitat

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

  // source = sursa din BFS
  int source;

  void read_input() {
    // citesc numar de noduri, numar de muschii, sursa din BFS
    cin >> n >> m >> source;

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

    do_bfs();
  }

  void do_bfs() {
    // se va dace o parcurge BFS din sursa s
    // in urma careia vom avea construite urmatoarele 2 tablouri

    // d[i] = lungimea minima a unui drum de la sursa s la nodul i
    //        (lungime = numar de arce)
    vector<int> d(n + 1);

    // p[i] = parintele nodului i din arborele de parcurgere BFS
    vector<int> p(n + 1);

    // aplica BFS pe un graf - viziteaza ce este accesibil din sursa source
    bfs(source, d, p);

    // exemplificare folosire "rezultate" d si p
    example(d, p);
  }

  // aplica BFS pe un graf - viziteaza ce este accesibil din sursa s
  void bfs(int source, vector<int> &d, vector<int> &p) {
    // Step 0: declaram o coada in care putem baga noduri
    queue<int> Q;

    // Step 1: initializare distante & parinti
    for (int i = 1; i <= n; ++i) {
      d[i] = kInf;      // presupun ca nu am drum
      p[i] = NO_PARENT; // deci nici parinte (i inaccesibil)
    }

    // Step 2: pasul initial: cunosc sursa s, o adaug in coada
    Q.push(source);
    d[source] = 0; // distanta de la source la source e 0
    p[source] = 0; // parintele lui source este 0 - conventie pentru
                   // radacina arborelui BFS obtinut

    // Step 3: parcurg in latime graful pornind din s
    while (!Q.empty()) {
      // 3.1: SCOT primul nod din coada
      int node = Q.front();
      Q.pop();

      // 3.2 Ii parcurg toti vecinii
      for (auto &it : adj[node]) {
        // daca se poate ajunge pe un drum mai scurt, aleg acest drum
        // constanta + 1 < kInf => gasesc drumul optim
        if (d[node] + 1 < d[it]) {
          d[it] = d[node] + 1; // actualizez distanta
          p[it] = node;        // salvez cine este parintele din arborele BFS

          Q.push(it); // pun vecinul in coada
        }
      }
    }

    // Step 4 - daca e cazul, modific vectorul d si p conform problemei
    //          sau alte procesari
    //         (ex. functia poate returna true/false daca s-a ajuns intr-un nod
    //          destinatie dest)
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
    // cand node == souce, p[node] == 0
    // (asta ma asigura ca forul se opreste la iteratia urmatoare)

    // s-a obtinut drumul node -> ... -> source
    // inversam solutia
    reverse(path.begin(), path.end());

    return path;
  }

  void example(vector<int> &d, vector<int> &p) {
    cout << "d: ";
    for (int i = 1; i <= n; ++i) {
      cout << d[i] << " ";
    }
    cout << "\n\n";

    // Exemplu: reconstituie drumul de la sursa source la nodul i
    // cu recursivitate
    cout << "rebuild_path\n";
    for (int i = 1; i <= n; ++i) {
      cout << source << "->" << i << " : ";

      // rebuild source-> ... -> i
      // obs. vectorul p contine toata informatia necesara pentru reconstituire
      vector<int> path = rebuild_path(i, p);

      // nu am drum de la source la i
      if (path.size() == 0) {
        cout << "No such path!\n";
        continue;
      }

      // am drum de la source la i - il afisez
      for (auto &node : path) {
        cout << node << " ";
      }
      cout << "\n";
    }
    cout << "\n";
  }

  void print_output() { cout << "\nend of BFS demo - pwp\n"; }
};

void legend() {
  cout << "legend: d[i] = distance from source to node i\n";
  cout << "legend: x->y = path from node x to node y\n";
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

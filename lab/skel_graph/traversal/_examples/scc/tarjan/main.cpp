// Copyright 2018 Bogdan-Cristian Firuti <firutibogdan@gmail.com>
// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

// Componente Tare Conexe (CTC) - Strongly Connected Components (SCC)
// Tarjan - O(n + m)

// links:
// - https://infoarena.ro/problema/ctc
// - https://youtu.be/z9oOadBgO9I?t=5m

#include <bits/stdc++.h>

using namespace std;

#define NMAX 100010

class Task {

public:
  void solve() {
    read_input();
    get_result();
    print_output();
  }

private:
  // adj[node] lista de adiacenta a nodului node pentru graful initial
  vector<int> adj[NMAX];

  // ctc[i] = componenta tare conexa cu indicele i
  vector<vector<int>> ctc;

  // ordinea de vizitare
  // found[node] = timpul de start a lui node in parcurgerea DFS
  // in laborator found se numeste idx
  vector<int> found;

  // low_link[node] = min { found[x] | x este accesibil din node }
  // adica timpul minim al unui nou
  vector<int> low_link;

  // in_stack[i] = 1 daca i este pe stiva
  vector<int> in_stack;

  // stiva in care tin nodurile prin care trec
  stack<int> st;

  // n = numar de noduri, m = numar de muchii
  int n, m;

  void read_input() {
    cin >> n >> m;

    in_stack = vector<int>(n + 1, 0);
    found = vector<int>(n + 1, -1);
    low_link = vector<int>(n + 1, 0);
    int x, y;

    for (int i = 0; i < m; ++i) {
      cin >> x >> y;

      adj[x].push_back(y);
    }
  }

  void get_result() {
    // momentul curent de start
    int current_start = 0;
    for (int i = 1; i <= n; ++i) {
      // am gasit un nod la care nu s-a ajuns pana acum
      if (found[i] == -1) {
        tarjan(i, current_start);
      }
    }
  }

  void tarjan(int node, int &current_start) {
    // atat idx, cat si low_link vor primi valoarea lui current_start
    // current_start = momentul curent de start
    found[node] = current_start;
    low_link[node] = current_start;

    // adaug in stiva nodul, si il marchez ca fiind in stiva
    in_stack[node] = 1;
    st.push(node);

    // cresc timpul de start, deoarece vecinii lui node vor avea timpul de start
    // current_start + 1
    current_start = current_start + 1;

    for (int neighbour : adj[node]) {
      // am gasit un vecin nevizitat
      if (found[neighbour] == -1) {
        tarjan(neighbour, current_start);

        // updatez low_link:
        // - low_link[node]  = timpul de start cel mai mic pe care NODE  il
        // cunoaste
        // - low_link[vecin] = timpul de start cel mai mic pe care VECIN il
        // cunoaste
        // Tot ce acceseaza vecin (Ex. vecin - ... - x) poate accesa si node
        // (ex. node - vecin - ... - x)
        low_link[node] = min(low_link[node], low_link[neighbour]);
      } else {
        // daca am gasit un vecin vizitat, care e deja in stiva
        // verific daca timpul lui de start e mai mic decat
        // timpul de start cel mai mic pe care il cunosc
        if (in_stack[neighbour] == 1) {
          low_link[node] = min(low_link[node], found[neighbour]);
        }
      }
    }

    // verific daca node este radacina a unei CTC
    if (low_link[node] == found[node]) {
      int current;
      vector<int> new_ctc;

      // inseamna ca toate nodurile bagate in stiva dupa node
      // fac parte din CTC cu radacina in node
      while (!st.empty() && current != node) {
        // scot din stiva si adaug elementul la noua CTC
        current = st.top();
        st.pop();
        new_ctc.push_back(current);

        // marchez si faptul ca am scos nodul din stiva
        in_stack[current] = 0;
      }
      // adaug in multimea de CTC noua CTC
      ctc.push_back(new_ctc);
    }
  }

  void print_output() {
    // pentru verificare pe infoarena trebuie doar modificata afisarea
    cout << "Graful are " << ctc.size() << " componente tare conexe\n";
    // cout << ctc.size() << "\n";
    int index = 1;

    for (vector<int> comp : ctc) {
      cout << "Componenta tare conexa [" << index++ << "]: ";
      for (int el : comp) {
        cout << el << " ";
      }
      cout << "\n";
    }
  }
};

int main() {
  // din cauza ca fac redirectari, salvez starea lui cin si cout
  auto cin_buff = cin.rdbuf();
  auto cout_buff = cout.rdbuf();

  // las liniile urmatoare daca citesc din fisier
  ifstream fin("ctc.in");
  cin.rdbuf(fin.rdbuf()); // save and redirect

  // las liniile urmatoare daca afisez in fisier
  // ofstream fout("ctc.out");
  // cout.rdbuf(fout.rdbuf()); //save and redirect

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

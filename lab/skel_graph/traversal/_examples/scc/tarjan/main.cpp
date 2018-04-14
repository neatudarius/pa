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

  // nivelul / ordinea de vizitare
  // idx[i] = -1 daca inca nu am ajuns la nodul i
  vector<int> idx;

  // min { idx[u] | u este accesibil din v }
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
    idx = vector<int>(n + 1, -1);
    low_link = vector<int>(n + 1, 0);
    int x, y;

    for (int i = 0; i < m; ++i) {
      cin >> x >> y;

      adj[x].push_back(y);
    }
  }

  void get_result() {
    // pornesc de pe nivelul 0 de vizitare
    int index = 0;
    for (int i = 1; i <= n; ++i) {
      // am gasit un nod la care nu s-a ajuns pana acum
      if (idx[i] == -1) {
        tarjan(i, index);
      }
    }
  }

  void tarjan(int node, int& index) {
    // atat idx, cat si low_link vor primi valoarea lui index
    // index = nivelul la care am ajuns cu parcurgerea
    idx[node] = index;
    low_link[node] = index;

    // adaug in stiva nodul, si il marchez ca fiind in stiva
    in_stack[node] = 1;
    st.push(node);

    // cresc nivelul, deoarece vecinii lui node vor fi pe nivelul index + 1
    index = index + 1;

    for (int neighbour : adj[node]) {
      // am gasit un vecin nevizitat
      if (idx[neighbour] == -1) {
        tarjan(neighbour, index);
        low_link[node] = min(low_link[node], low_link[neighbour]);
      } else {
        if (in_stack[neighbour] == 1) {
          low_link[node] = min(low_link[node], idx[neighbour]);
        }
      }
    }

    // verific daca node este radacina a unei CTC
    if (low_link[node] == idx[node]) {
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
  // ifstream fin("ctc.in");
  // cin.rdbuf(fin.rdbuf()); // save and redirect

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

// Copyright 2018 Popescu Alexandru Gabriel <alexandru.popescu0697@gmail.com>
// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

// Componente biconexe + puncte de articulatie + muchii critice (punti)
// O(n + m)

// https://infoarena.ro/problema/biconex

#include <bits/stdc++.h>

#define NMAX 100010
#define edge pair<int, int>

using namespace std;

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

    // adj[node] lista de adiacenta a nodului node pentru graful initial
    vector<int> adj[NMAX];

    // nivelul / ordinea de vizitare
    vector<int> idx;

    // min { idx[u] | u este accesibil din v }
    vector<int> low_link;

    // vector in care retin punctele de articulatie
    vector<int> cut_vertex;

    // vector in care retin muchiile critice (puntile)
    vector<edge > critical_edges;

    // parent[i] = parintele nodului i
    vector<int> parent;

    void read_input() {
        cin >> n >> m;
        idx = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, 0);
        parent = vector<int>(n + 1, 0);
        int x, y;
        for (int i = 1; i <= m; ++i) {
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }

    void get_result() {
        tarjan();
    }

    void tarjan() {
        int index = 0;
        for (int i = 1; i <= n; ++i) {
            if (idx[i] == -1) {
                // marcam nodul i ca fiind radacina
                parent[i] = 0;
                // pornim o noua cautare din nodul respectiv
                dfs(i, index);
            }
        }
    }

    void dfs(int node, int &index) {
        // atat idx, cat si low_link vor primi valoarea lui index
        // index = nivelul la care am ajuns cu parcurgerea
        idx[node] = index;
        low_link[node] = index;

        // cresc nivelul, deoarece vecinii lui node vor fi pe nivelul index + 1
        ++index;

        // initializez numarul de copii al nodului curent cu 0
        int children = 0;

        for (auto &vecin : adj[node]) {
            if (idx[vecin] == -1) {
                // parintele nodului in care ma duc este chiar nodul curent
                parent[vecin] = node;

                // cresc numarul de copii
                ++children;

                // pornesc un nou dfs
                dfs(vecin, index);

                // updatez low_link dupa modelul componente tare conexe
                low_link[node] = std::min(low_link[node], low_link[vecin]);

                // daca nu au existat muchii de intoarcere spre un parinte al lui node
                // inseamna ca nodul curent este punct de articulatie
                if (low_link[vecin] >= idx[node] && parent[node] != 0) {
                    cut_vertex.push_back(node);
                }

                // daca nu au existat muchii de intoarcere spre node sau spre un parinte al lui node
                // inseamna ca muchia (node, vecin) este muchie critica
                if (low_link[vecin] > idx[node]) {
                    critical_edges.push_back(edge(node, vecin));
                }
            } else {
                // !!!graful fiind neorientat as updata fiecare copil in functie de parintele sau
                // trebuie sa am grija sa nu fac asta
                if (vecin != parent[node]) {
                    // am gasit o muchie de intoarcere
                    low_link[node] = std::min(low_link[node], idx[vecin]);
                }
            }
        }

        // daca nodul curent este radacina si are mai mult de 2 copii
        if (parent[node] == 0 && children >= 2) {
            cut_vertex.push_back((node));
        }
    }

    void print_output() {
        // decomentati liniile urmatoare daca vreti sa afisati punctele de articulatie
        if (cut_vertex.empty()) {
            cout << "Graful nu contine puncte de articulatie\n";
        } else {
            cout << "Punctele de articulatie ale grafului sunt:\n";
            for (auto &node : cut_vertex) {
                cout << node << ' ';
            }
            cout << '\n';
        }

        // decomentati liniile urmatoare daca vreti sa afisati muchiile critice
        if (critical_edges.empty()) {
            cout << "Graful nu contine muchii critice\n";
        }
        else {
            cout << "Muhciile critice ale grafului sunt:\n";
            for (auto &m : critical_edges) {
                cout << '(' << m.first << ", " << m.second << ") ";
            }
            cout << '\n';
        }
    }
};

int main() {
    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff = cin.rdbuf();
    auto cout_buff = cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    ifstream fin("biconex.in");
    cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    ofstream fout("biconex.out");
    cout.rdbuf(fout.rdbuf()); //save and redirect

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

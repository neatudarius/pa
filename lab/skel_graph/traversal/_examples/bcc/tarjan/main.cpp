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
    void solve()
    {
        read_input();
        get_result();
        print_output();
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // adj[node] lista de adiacenta a nodului node pentru graful initial
    vector<int> adj[NMAX];

    // bcc[i] = componenta biconexa cu indicele i
    vector<vector<int>> bcc;

    // stiva folosita pentru a reconstrui componentele biconexe
    stack<edge> sc;

    // ordinea de vizitare
    // found[node] = timpul de start a lui node in parcurgerea DFS
    // in laborator found se numeste idx
    vector<int> found;

    // low_link[node] = min { found[x] | x este accesibil din node }
    // adica timpul minim al unui nou
    vector<int> low_link;

    // vector in care retin punctele de articulatie
    vector<int> cut_vertex;

    // vector cu are marchez ca node este deja in cut_vertex
    // (evit duplicatele)
    vector<int> is_cv;

    // vector in care retin muchiile critice (puntile)
    vector<edge> critical_edges;

    // parent[i] = parintele nodului i
    vector<int> parent;

    void read_input()
    {
        cin >> n >> m;

        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, 0);
        parent = vector<int>(n + 1, 0);
        is_cv = vector<int>(n + 1, 0);

        for (int i = 1; i <= m; ++i) {
            int x, y;
            cin >> x >> y;

            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }

    void get_result() { tarjan(); }

    void tarjan()
    {
        // momentul curent de start
        // pe masura ce vizita nodurile el va creste (++)
        int current_start = 0;

        for (int i = 1; i <= n; ++i) {
            if (found[i] == -1) { // acest nod nu a fost descoperit, deci il putem folosi
                // marcam nodul i ca fiind radacina
                parent[i] = 0;

                // pornim o noua cautare din nodul respectiv
                dfs(i, current_start);
            }
        }
    }

    void dfs(int node, int& current_start)
    {
        // incep un nou nod, deci un nod timp de start
        ++current_start;

        // atat found, cat si low_link vor primi valoarea lui current_start
        found[node] = current_start;
        low_link[node] = current_start;

        // initializez numarul de copii al nodului curent cu 0
        int children = 0;

        for (auto& vecin : adj[node]) {
            if (found[vecin] == -1) { // deci il pot vizita
                // parintele nodului in care ma duc este chiar nodul curent
                parent[vecin] = node;

                // cresc numarul de copii
                ++children;

                // retin muchiile de avansare
                sc.push(edge(node, vecin));

                // pornesc un nou dfs
                dfs(vecin, current_start);

                // updatez low_link:
                // - low_link[node]  = timpul de start cel mai mic pe care NODE  il
                // cunoaste
                // - low_link[vecin] = timpul de start cel mai mic pe care VECIN il
                // cunoaste
                // Tot ce acceseaza vecin (Ex. vecin - ... - x) poate accesa si node
                // (ex. node - vecin - ... - x)
                low_link[node] = std::min(low_link[node], low_link[vecin]);

                // CUT VERTEX - caz 2:
                // daca nu au existat muchii de intoarcere spre un STRAMOS al lui node
                // inseamna ca nodul curent este punct de articulatie
                // adica VECIN nu a putut sa sara inapoi in arbore PESTE node
                if (low_link[vecin] >= found[node]) {
                    // radacina este tratata separat (adica conditia de mai sus nu este
                    // pentru radacina)
                    if (parent[node] != 0) {
                        // am grija sa nu adaug duplicate in cut_vertex
                        if (!is_cv[node]) {
                            is_cv[node] = 1;
                            cut_vertex.push_back(node);
                        }
                    }

                    // daca am gasit un punct de articulatie inseamna ca am descoperit
                    // o noua componenta biconexa
                    get_bcc(edge(node, vecin));
                }

                // daca nu au existat muchii de intoarcere spre node sau spre un parinte
                // al lui node
                // inseamna ca muchia (node, vecin) este muchie critica
                if (low_link[vecin] > found[node]) {
                    critical_edges.push_back(edge(node, vecin));
                }
            } else {
                // !!!graful fiind neorientat as updata fiecare copil in functie de
                // parintele sau
                // trebuie sa am grija sa nu fac asta
                if (vecin != parent[node]) {
                    // am gasit o muchie de intoarcere
                    low_link[node] = std::min(low_link[node], found[vecin]);
                }
            }
        }

        // CUT VERTEX - caz 1:
        // daca nodul curent este radacina si are mai mult de 2 copii
        if (parent[node] == 0 && children >= 2) {
            // am grija sa nu adaug duplicate in cut_vertex
            if (!is_cv[node]) {
                is_cv[node] = 1;
                cut_vertex.push_back(node);
            }
        }
    }

    void get_bcc(edge target_edge)
    {
        // construim o noua componenta biconexa
        vector<int> current_bcc;

        // extragem muchii din stiva pana am extras muchia E
        edge current_edge = edge(-1, -1);

        // cat timp nu am extras muchia dorita
        while (current_edge != target_edge) {
            current_edge = sc.top();
            sc.pop();

            // adaug capetele muchiei in bcc
            current_bcc.push_back(current_edge.first);
            current_bcc.push_back(current_edge.second);
        }

        // trebuie sa eliminam duplicatele
        // vom sorta vectorul si vom folosi functia unique
        // pentru detalii, vezi: http://en.cppreference.com/w/cpp/algorithm/unique
        sort(current_bcc.begin(), current_bcc.end());
        auto it = unique(current_bcc.begin(), current_bcc.end());
        current_bcc.erase(it, current_bcc.end());

        // current_bcc este o BCC valida
        bcc.push_back(current_bcc);
    }

    void print_output()
    {
        // decomentati liniile urmatoare daca vreti sa afisati punctele de
        // articulatie
        if (cut_vertex.empty()) {
            cout << "Graful nu contine puncte de articulatie\n";
        } else {
            cout << "Punctele de articulatie ale grafului sunt:\n";
            for (auto& node : cut_vertex) {
                cout << node << ' ';
            }
            cout << '\n';
        }

        // decomentati liniile urmatoare daca vreti sa afisati muchiile critice
        if (critical_edges.empty()) {
            cout << "Graful nu contine muchii critice\n";
        } else {
            cout << "Muchiile critice ale grafului sunt:\n";
            for (auto& E : critical_edges) {
                cout << '(' << E.first << ", " << E.second << ") ";
            }
            cout << '\n';
        }

        int sol = bcc.size();
        cout << "Graful are " << sol << " componente biconexe\n";
        for (int i = 0; i < sol; ++i) {
            cout << "Componenta biconexa [" << i + 1 << "]: ";
            for (auto& node : bcc[i]) {
                cout << node << " ";
            }
            cout << '\n';
        }
    }
};

int main()
{
    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff = cin.rdbuf();
    auto cout_buff = cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    ifstream fin("biconex.in");
    cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    // ofstream fout("biconex.out");
    // cout.rdbuf(fout.rdbuf()); // save and redirect

    // aici este rezolvarea propriu-zisa
    Task* task = new Task();
    task->solve();
    delete task;

    // restore pentru cin si cout
    cin.rdbuf(cin_buff);
    cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide

    return 0;
}

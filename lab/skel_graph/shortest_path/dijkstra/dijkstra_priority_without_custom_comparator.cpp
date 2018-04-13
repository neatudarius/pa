/*
    dijkstra_priority_without_custom_comparator
    O sa intelegeti la tema 2 de ce am pus asta aici :D
*/

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <bitset>
#include <cassert>
#include <queue> // std::priority_queue
#include <cstring>
#include <algorithm>
#define NMAX 50009  // ATENTIE la cat e in problema curenta !!!
#define MMAX 250009  // ATENTIE la cat e in problema curenta !!!
#define oo (1 << 30) // ATENTIE la cat e in problema curenta !!!
using namespace std;

// tipul edge
// muchia de cost "cost", de la node la neighbour,
// va fi un element edge(neighbour, cost) in G[node]
typedef pair<int, int> edge;
#define neighbour first
#define cost second

// aceleasi semnificatii ca la BFS
int n, m;
int d[NMAX], p[NMAX];
vector<edge> G[NMAX];

// declararea unui priority queue in care pun numere intregi (noduri)
// si cu un criteriu custom de prioritate

// varianta 3
// nu stiu de ce, dar un comparator facut de mana e mult mai lenta decat
// std::greater - o sa vedeti la tema 2 asta :D

// o stare este determinata de o actualizare a distantei pentru nodul node
typedef pair<int, int> state;
#define distance first
#define node second
priority_queue<state, vector<state>, std::greater<state> > pq;

// P.S. solutia de mai sus poate aduce un boot de pana la 10x daca in loc de
// pair<int, int> o sa lucrati cu std::tuple<..> cu multi membri

void read_input() {
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y, c; // x -> y, de cost c
        cin >>  x >> y >> c;

        G[x].push_back(edge(y, c));
        // G[y].push_back(edge(x, c)); // sterg daca e orientat !!!
    }
}

void Dijkstra(int source) {
    // ETAPA 1
    for (int i = 1; i <= n; ++i) {
        d[i] = oo;
        p[i] = oo;
    }

    // ETAPA 2
    pq.push(state(0, source));
    d[source] = 0;
    p[source] = 0;

    // ETAPA 3
    while (!pq.empty()) {
        state s = pq.top();
        pq.pop();

        // daca starea asta e inutila
        // (ulterior a fost introdusa o alta stare pt s.node, cu o
        // distanta mai mica)
        if (s.distance > d[s.node]) {
            continue;
        }

        int node = s.node;
        for (auto it = G[node].begin(); it != G[node].end(); ++it) {
            int neighbour = it->neighbour;
            int cost_edge = it->cost;

            if (d[ node ] + cost_edge < d[ neighbour ]) {
                d[ neighbour ] = d[ node ] + cost_edge;
                p[ neighbour ] = node;

                pq.push( state( d[neighbour], neighbour ) );
            }
        }
    }

    // ETAPA 4 - daca e cazul
    // infoarena vrea sa nu afisez oo, ci 0
    for (int i = 1; i <= n; ++i) {
        if (d[i] == oo) {
            d[i] = 0;
        }
    }
}



// in solve scriu tot ce tine de rezolvare - e ca un main
void solve() {
    // pe infoarena sursa este 1
    Dijkstra(1);
}

// rebuild source -> ... -> node (if exists)
void rebuild_path_recursive(int node, int source) {
    if (d[ node ] == oo) {
        cout << "Drum inexistent!";
        return;
    }

    if (node == source) { // sau p[node] = 0; // conditie echivalenta
        cout << node << " ";
        return;
    }

    // rebuild first source -> ...-> p[node]
    rebuild_path_recursive(p[node], source);

    // then p[node] -> node
    cout << node << " ";
}


// afisez vectori si tot ce mai trebuie
void print_output() {
    // cout << "d: ";
    for (int i = 2; i <= n; ++i) {
        cout << d[i] <<  " ";
    }
    cout << "\n";

    // Exemplu: reconstituie drumul de la i la n

    // cu recursivitate - de obicei pe asta o folosesc
    // pentru ca daca nu vreau sa stochez drumul, o pot face
    // cout << "rebuild_path_recursive\n";
    // for (int i = 1; i <= n; ++i) {
    //     cout << s << "->" << i << " : ";
    //     rebuild_path_recursive(i, s); // rebuild s-> ... -> i
    //     cout << "\n";
    // }
}



// puteti pastra main-ul mereu cum e acum
int main() {
    // las linia urmatoare daca citesc din fisier
    assert( freopen("dijkstra.in", "r", stdin) != NULL);

    // las linia urmatoare daca afisez in fisier
    assert( freopen("dijkstra.out", "w", stdout) != NULL) ;

    read_input();
    solve();
    print_output();

    return 0;
}


// Obs: pe infoarena ia 90p din cauza citirii
// http://www.infoarena.ro/job_detail/1970178

/*
    skel_graph - Dijkstra - O(m log n)
    (Sau cu notatia din lab O(E log V))
    http://www.infoarena.ro/problema/dijkstra

    Deoarece folosesc heapuri binare (priority_queue),
    complexitatea este cea de mai sus
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

// varianta 1
// http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/
struct cmp {
    // returneaza true daca x ar trebui "sa fie sub" y in arbore
    bool operator()(const int &x, const int &y) const {
        return d[x] > d[y];
    }
};
priority_queue<int, vector<int>, cmp > pq;


// varianta 2 - C++11 :D
// http://en.cppreference.com/w/cpp/language/decltype
// bool cmp(const int &x, const int &y) {
//     // returneaza true daca x ar trebui "sa fie sub" y in arbore
//     return d[x] > d[y];
// }
// priority_queue<int, vector<int>, decltype(&cmp)> pq(cmp);


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
    pq.push(source);
    d[source] = 0;
    p[source] = 0;

    // ETAPA 3
    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();

        for (auto it = G[node].begin(); it != G[node].end(); ++it) {
            int neighbour = it->neighbour;
            int cost_edge = it->cost;

            if (d[ node ] + cost_edge < d[ neighbour ]) {
                d[ neighbour ] = d[ node ] + cost_edge;
                p[ neighbour ] = node ;

                pq.push( neighbour );
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


// Obs: pe infoarena ia 80p din cauza citirii
// http://www.infoarena.ro/job_detail/1970166

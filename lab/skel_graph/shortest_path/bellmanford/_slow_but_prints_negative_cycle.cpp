/*
    skel_graph - BellmanFord - O(mn)
    (Sau cu notatia din lab O(EV))
    http://www.infoarena.ro/problema/bellmanford

    VARIANTA DIN LAB POATE AFISA SI CICLUL NEGATIV! (la propriu)
    ATENTIE! ASTA FACE MEREU m * (n-1) relaxari, apoi verifica existenta ciclului!!!
    deci e mai lenta
*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <bitset>
#include <cassert>
#include <queue>
#include <cstring>
#include <algorithm>
#include <tuple>
#define NMAX 50009  // ATENTIE la cat e in problema curenta !!!
#define MMAX 250009  // ATENTIE la cat e in problema curenta !!!
#define oo (1 << 30LL) // ATENTIE la cat e in problema curenta !!!
using namespace std;

// tipul edge
// muchia first_node -> second_node de cost edge_cost
typedef tuple<int, int, int> edge;
#define first_node(t)  std::get<0>(t)
#define second_node(t) std::get<1>(t)
#define edge_cost(t)   std::get<2>(t)

// aceleasi semnificatii ca la BFS
int n, m;
long long d[NMAX];
int p[NMAX], used[NMAX];
vector<edge> edges;

//coada
queue<int> Q;

void read_input() {
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y, c; // x -> y, de cost c
        cin >>  x >> y >> c;

        edges.push_back( edge(x, y, c) );
        // edges.push_back( edge(x, y, c) ); // sterg daca e orientat !!!
    }
}


// return true = ciclu de cost negativ
// return false = nu are ciclu de cost negativ
bool BellmanFord(int source) {
    // ETAPA 1
    for (int i = 1; i <= n; ++i) {
        d[i] = oo;
        p[i] = oo;
    }


    // ETAPA 2
    Q.push(source);
    d[source] = 0;
    p[source] = 0;
    // relaxari succesive
    for (int i = 1; i < n; ++i) {
        for (auto it = edges.begin();  it != edges.end(); ++it) {
            int node = first_node(*it),
                neighbour = second_node(*it),
                cost_edge = edge_cost(*it);


            if (d[node] + cost_edge < d[neighbour]) {
                d[neighbour] = d[node] + cost_edge;
                p[neighbour] = node;
            }
        }
    }

    // ETAPA 3
    // daca se mai pot relaxa muchii => ciclu de cost negativ
    for (auto it = edges.begin();  it != edges.end(); ++it) {
        int node = first_node(*it),
            neighbour = second_node(*it),
            cost_edge = edge_cost(*it);


        if (d[node] + cost_edge < d[neighbour]) {
            return true;
        }
    }
    return false; // nu exista ciclu de cost negativ
}

// in solve scriu tot ce tine de rezolvare - e ca un main
void solve() {
    // pe infoarena sursa este 1
    if (BellmanFord(1)) {
        cout << "Ciclu negativ!\n";

        // daca vreau sa aflu ciclu
        // aici il aflu
        // http://qa.geeksforgeeks.org/1735/how-to-print-negative-cycle-in-a-graph
    } else {
        for (int i = 2; i <= n; ++i) {
            cout << d[i] <<  " ";
        }
        cout << "\n";
    }
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

// puteti pastra main-ul mereu cum e acum
int main() {
    // las linia urmatoare daca citesc din fisier
    assert( freopen("bellmanford.in", "r", stdin) != NULL);

    // las linia urmatoare daca afisez in fisier
    assert( freopen("bellmanford.out", "w", stdout) != NULL) ;

    read_input();
    solve();
    // print_output();

    return 0;
}


// Obs: pe infoarena ia 35p din cauza citirii + ca e pseudocod naiv
// http://www.infoarena.ro/job_detail/1970204
// varianta din lab face mereu m * (n - 1) operatii in etapa 2

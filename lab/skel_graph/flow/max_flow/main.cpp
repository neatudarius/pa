/*
    skel_graph - MaxFlow (Ford-Fulkerson) - O(N*M^2)
    http://www.infoarena.ro/problema/maxflow

    source = sursa
    sink = destinatie
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
#define NMAX 1009    // ATENTIE la cat e in problema curenta !!!
#define oo (1 << 30) // ATENTIE la cat e in problema curenta !!!
using namespace std;

// citire doar pt infoarena
ifstream in("maxflow.in");
ofstream out("maxflow.out");
#define cin in
#define cout out

int n, m;
vector<int> G[NMAX];

// BFS
int p[NMAX];
queue<int> Q;

// maxflow
int flow[NMAX][NMAX], cap[NMAX][NMAX];
// cap[i][j] = capacitatea maxima a fluxului de pe muchia i->j
// flow[i][j] = fluxul curent de pe muchia i -> j (flow[i][j] <= cap[i][j])


void read_input() {
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y, c;
        cin >>  x >> y >> c;

        G[x].push_back(y);
        G[y].push_back(x);
        cap[x][y] += c;
    }
}

// BFS de la source la sink
// returneaza true daca a reusit sa se ajunga la sink (adica am cel putin un drum de ameliorare)
bool BFS(int source, int sink) {
    // ETAPA 1
    for (int i = 1; i <= n; ++i) {
        p[i] = oo;
    }

    // ETAPA 2
    Q.push(source);
    p[source] = 0;

    // ETAPA 3
    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();

        // drum de ameliorare terminat, nu trebuie sa mai fac nimic cu acest drum
        if (node == sink) {
            continue;
        }

        for (auto it = G[node].begin(); it != G[node].end(); ++it) {
            int neighbour = *it;

            // neighbour nu a fost deja folosit in alt drum de ameliorare in BFS-ul curent
            // si muchia node->neighbour nu e saturata (mai accepta flux)
            if (p[neighbour] == oo && flow[node][neighbour] < cap[node][neighbour]) {
                p[neighbour] = node;
                Q.push( neighbour );
            }
        }
    }

    // ETAPA 4 - verifica daca sink a fost atins <=> are parinte
    return p[sink] != oo;
}


void MaxFlow(int source, int sink) {
    int maxFlow = 0;

    // repeta cat timp exista drum/drumuri de ameliorare de la source la sink
    while (BFS(source, sink)) {
        // pentru fiecare drum de ameliorare POSIBIL de forma source -> ... -> *it->sink
        for (auto it = G[sink].begin(); it != G[sink].end(); ++it) {
            // *it a fost folosit intr-un drum de ameliorare in BFS-ul curent
            // si muchia *it->sink nu e saturata (mai accepta flux - adica drumul se termina in sink, nu mai devreme)
            if (p[*it] != oo && flow[*it][sink] < cap[*it][sink]) {
                p[sink] = *it; // atunci *it e parintele lui sink

                int minFlow = oo; // fluxul minim de pe acest drum (minimul dintre fluxurile acceptate de muchiile de pe drum)
                for (int node = sink; node != source; node = p[node]) {
                    int parent = p[node],
                        available_flow = cap[ parent ][ node ] - flow[ parent ][ node ];

                    minFlow = min(minFlow, available_flow);
                }

                // daca minFlow == 0, inseamna ca pe acel drum exista cel putin o muchie saturata
                // daca minFlow > 0, toate muchiile de pe drum sunt nesaturate, deci poti creste fluxul de pe tot drumul
                // cu minFlow unitati
                if (minFlow > 0) {
                    maxFlow += minFlow;

                    for (int node = sink; node != source; node = p[node]) {
                        int parent = p[node];

                        // in sens direct cresc fluxul
                        flow[ parent ][ node ] += minFlow;

                        // in sens opus il scad
                        flow[ node ][ parent ] -= minFlow;
                    }
                }
            }
        }
    }

    cout << maxFlow << "\n";
}


// in solve scriu tot ce tine de rezolvare - e ca un main
void solve() {
    MaxFlow(1, n);
}


// puteti pastra main-ul mereu cum e acum
int main() {
    // las linia urmatoare daca citesc din fisier
    // assert( freopen("maxflow.in", "r", stdin) != NULL);

    // las linia urmatoare daca afisez in fisier
    // assert( freopen("maxflow.out", "w", stdout) != NULL) ;

    read_input();
    solve();

    return 0;
}

// http://www.infoarena.ro/job_detail/1970265

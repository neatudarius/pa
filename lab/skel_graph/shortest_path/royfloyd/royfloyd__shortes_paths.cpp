/*
    skel_graph - RoyFloyd - O(n^3)
    (Sau cu notatia din lab O(V^3))
    http://www.infoarena.ro/problema/royfloyd
*/

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <bitset>
#include <cassert>
#include <cstring>
#include <algorithm>
#define NMAX 109  // ATENTIE la cat e in problema curenta !!!
#define oo (1 << 20) // ATENTIE la cat e in problema curenta !!!
using namespace std;

// aceleasi semnificatii ca la BFS
int n;
int d[NMAX][NMAX], p[NMAX][NMAX];
// p[i][j] = parintele lui j, de pe drumul de lungime minima de la i la j
// i->...->k->j (k este ultimul nod prin care trec inainte de a ajunge la destinatie; k este parinte!)

void read_input() {
    cin >> n;

    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= n; ++y) {
            int c; // x -> y, de cost c
            cin >> c;

            if (c == 0) {
                c = oo;
            }

            d[x][y] = c;
            p[x][y] = x;
        }
    }
}

void RoyFloyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j && d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }
}

// in solve scriu tot ce tine de rezolvare - e ca un main
void solve() {
   RoyFloyd();
}

// rebuild source -> ... -> node (if exists)
void rebuild_path_recursive(int node, int source) {
    if (d[ node ][source] == oo) {
        cout << "Drum inexistent!";
        return;
    }

    if (node == source) {
        cout << node << " ";
        return;
    }

    // rebuild first source -> ...-> p[node]
    rebuild_path_recursive(p[node][source], source);

    // then p[node] -> node
    cout << node << " ";
}


// afisez vectori si tot ce mai trebuie
void print_output() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (d[i][j] == oo) {
                d[i][j] = 0;
            }
            cout << d[i][j] << " ";
        }
        cout << "\n";
    }
}

// puteti pastra main-ul mereu cum e acum
int main() {
    // las linia urmatoare daca citesc din fisier
    assert( freopen("royfloyd.in", "r", stdin) != NULL);

    // las linia urmatoare daca afisez in fisier
    assert( freopen("royfloyd.out", "w", stdout) != NULL) ;

    read_input();
    solve();
    print_output();

    return 0;
}


// 100p pe infoarena - citirea nu conteaza
// http://www.infoarena.ro/job_detail/1970186

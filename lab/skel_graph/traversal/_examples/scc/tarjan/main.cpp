// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

//Componente tare conexe - Tarjan - O(N+M)
// https://infoarena.ro/problema/ctc

#include <cstdio>
#include <vector>
#include <bitset>
#include <stack>
#define NMAX 100009
using namespace std;
 
int N, M, order, found[NMAX], low[NMAX];
vector<int> G[NMAX];
 
stack<int> st;
bitset<NMAX> inStack;
vector< vector<int> > ctc;
 
 
 
void tarjan(const int& node) {
    found[ node ] = low[ node ] = ++order;
 
    st.push(node);
    inStack[ node ] = 1;
 
    for (auto it = G[node].begin(); it != G[node].end(); ++it) {
        if (!found[ *it ]) {
            tarjan(*it);
            // low[ node ] = min(low[ node ], low[ *it ]);
            if (low[ *it ] < low[ node ]) {
                low[ node ] = low[ *it ];
            }
        } else {
            // if (inStack[ *it ]) {
            //  low[ node ] = min(low[ node ], found[ *it ]);
            // }
            if (inStack[ *it ] && found[ *it ] < low[ node ]) {
                low[ node ] = found[ *it ];
            }
        }
    }
 
    if (found[ node ] == low[ node ]) {
        int current;
        vector<int> tmp;
        ctc.push_back(tmp);
 
        while (!st.empty() && current != node) {
            ctc.back().push_back( current = st.top() ); 
            st.pop();
 
            inStack[ current ] = 0;
        } 
 
         
    }
}
 
void ctcTarjan() {
    ctc.reserve(N);
     
    order = 0;
    for (int i = 1; i <= N; ++i) {
        if (!found[ i ]) {
            tarjan(i);
        }
    }
}
 
void printCTC() {
    printf("%d\n", (int) ctc.size());
 
    for (auto it = ctc.begin(); it != ctc.end(); ++it) {
        for (auto node = it->begin(); node != it->end(); ++node) {
            printf("%d ", *node);
        }
        printf("\n");
    }
}
 
void read() {
    scanf("%d%d", &N, &M);
 
 
    for (int i = 1; i <= M; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
 
        G[x].push_back(y);
    }
}
 
 
 
 
int main() {
    freopen("ctc.in", "r", stdin);
    freopen("ctc.out", "w", stdout);
 
 
    read();
    ctcTarjan();
    printCTC();
 
 
    return 0;
}
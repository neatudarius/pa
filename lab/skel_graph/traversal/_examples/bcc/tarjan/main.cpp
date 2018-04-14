// Copyright 2018 Darius Neatu <neatudarius@gmail.com>

// Componente biconexe + puncte de articulatie + muchii critice (punti)
// O(n + m)
// https://infoarena.ro/problema/biconex

#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <stack>
 
#define NMAX 100009
using namespace std;
 
typedef pair<int, int> edge;
 
int n, m;
vector<int> G[NMAX];
stack< edge > st;
 
 
//vector<int> cutVertex;
//vector< edge > criticalEdges;
vector< vector<int> > BCC;
 
// parent[node] = tata lui node
int parent[NMAX];
 
 
// found[node] = momentul in care l-am descoperit pe nod
int found[NMAX];
 
 
// low[node] = cat de mult a reusit sa urce in arbore
// recursiv prin copii (low e tot un timp)
int low[NMAX];
 
// ceasul pe care il incrementam
int clk = 0;
 
void getBCC(edge E) {
    vector<int> v;
    edge aux;
 
    do {
        aux = st.top();
        st.pop();
 
        v.push_back(aux.first);
        v.push_back(aux.second);
    } while (aux != E);
 
    sort(v.begin(), v.end());
    auto it = unique(v.begin(), v.end());
    v.erase(it, v.end());
 
    BCC.push_back(v);
}
 
void DFS(int node) {
    found[node] = ++clk;
    low[node] = found[node];
 
    int children = 0;
    for (auto &x : G[node]) {
        if (!parent[x]) {
            ++children;
            parent[x] = node;
            st.push(edge(node, x));
 
            DFS(x);
 
            low[node] = min(low[node], low[x]);
 
//            if (parent[node] != node && low[x] >= found[node]) {
//                cutVertex.push_back(node);
//            }
 
 
            if (low[x] >= found[node]) {
                getBCC(edge(node, x)); // node,x termina o componenta biconexa
            }
 
//            if (low[x] > found[node]) {
//                criticalEdges.push_back(edge(node, x));
//            }
        } else {
            if (x != parent[node]) {
                low[node] = min(low[node], found[x]);
            }
        }
    }
 
//    if (parent[node] == node && children > 1) {
//        cutVertex.push_back(node);
//    }
}
void Tarjan() {
    for (int i = 1; i <= n; ++i) {
        if (!parent[i]) {
            parent[i] = i;
            DFS(i);
        }
    }
}
int main() {
    ifstream in("biconex.in");
    ofstream out("biconex.out");
 
    in >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        in >> x >> y;
 
        G[x].push_back(y);
        G[y].push_back(x);
    }
 
    Tarjan();
 
 
 
//    out << cutVertex.size() << "\n";
//    for (auto &x : cutVertex) {
//        out << x << " ";
//    }
//    out << "\n";
//
//    for (auto &p : criticalEdges) {
//        out << p.first << " " << p.second << "\n";
//    }
 
    out << BCC.size() << "\n";
    for (auto &bcc : BCC) {
        for (auto &x : bcc) {
            out << x << " ";
        }
        out << "\n";
    }
 
    in.close();
    out.close();
 
    return 0;
}
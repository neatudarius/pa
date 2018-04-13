// Copyright Popescu Alexandru Gabriel <alexandru.popescu0697@gmail.com> 2018
// Copyright Darius Neatu <neatudarius@gmail.com> 2018
// Componente tare conexe - Kosaraju - O(n + m)
// https://infoarena.ro/problema/ctc
#include <bits/stdc++.h>

#define NMAX 100001
#define pb push_back
std::ifstream f("ctc.in");

class Task {
public:
    void solve() {
        read_input();
        kosaraju();
        print_output();
    }

private:
    int n, m, sol = 0;
    std::vector<int> G[NMAX];  // graful initial
    std::vector<int> T[NMAX];  // graful transpus
    std::vector<int> CTC[NMAX];  // retin solutia
    std::vector<bool> visited;
    std::vector<int> Tsort;  // retin nodurile crescator dupa timpul de finalizare
                             // nu mai folosesc stiva si o sa parcurg vectorul invers
                             // asemanator ca la sortarea topologica cu dfs

    void read_input() {
        f >> n >> m;
        visited = std::vector<bool>(n + 1, false);
        Tsort = std::vector<int> (n + 1, 0);
        int x, y;
        for (int i = 1; i <= m; ++i) {
            f >> x >> y;
            G[x].pb(y);
            T[y].pb(x);
        }
    }

    void kosaraju() {
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        for (int i = n; i >= 1; --i) {
            if (visited[Tsort[i]]) {
                dfs_t(Tsort[i], sol);
                ++sol;
            }
        }
    }

    void dfs(int node) {
        visited[node] = true;
        for (auto &vecin : G[node]) {
            if (!visited[vecin]) {
                dfs(vecin);
            }
        }
        Tsort[++Tsort[0]] = node;  //Tsort[0] functioneaza pe post de counter
    }

    void dfs_t(int node, int &sol) {
        visited[node] = false;
        CTC[sol].pb(node);
        for (auto &vecin : T[node]) {
            if (visited[vecin]) {
                dfs_t(vecin, sol);
            }
        }
    }

    void print_output() {
        // pentru verificare pe infoarena trebuie doar modificata afisarea
        std::cout << "Graful are " << sol << " componente tare conexe\n";
        for (int i = 0; i < sol; ++i) {
            std::cout << "Componenta tare conexa [" << i + 1 << "]: ";
            for (auto &node : CTC[i]) {
                std::cout << node << " ";
            }
            std::cout << '\n';
        }
    }
};

int main() {
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}

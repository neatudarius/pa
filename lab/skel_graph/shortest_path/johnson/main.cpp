// Copyright 2020 Miruna-Elena Banu <mirunaelena.banu@gmail.com>

// Gasirea celui mai scurt drum intre oricare doua noduri
// All-Pairs Shortest Path Problem

// Johnson - T = O(n * m  * log n + n * m) (Binary Heap)
//         - T = O(n^2 * log n + n * m) (Fibonacci Heap)

// links:
// - TODO: Gaseste un link mai bun
// - https://infoarena.ro/problema/royfloyd

#include <bits/stdc++.h>

#define NMAX      110       // ATENTIE la cat e in problema curenta !!!
#define oo        (1 << 30) // ATENTIE la cat e in problema curenta !!!
#define NO_PARENT (-1)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // Listele de adiacenta pentru fiecare nod
    int adj[NMAX][NMAX];

    void read_input() {
        std::cin >> n;
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= n; ++y) {
                int c; // x -> y, de cost c
                std::cin >> c;
                if (c == 0) {
                    c = oo;
                }
                adj[x][y] = c;
            }
        }
    }

    bool get_result() { return Johnson(); }

    void Dijkstra(int source, std::vector<int>& d) {
        // Min-heap ce contine perechi de tipul: distanta source -> x
        // Folosit pentru a extrage la fiecare pas nodul care are costul
        // estimat minim fata de sursa
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>
            pq;

        // Presupunem ca nu exista drum de la source la i
        for (int i = 1; i <= n; ++i) {
            d[i] = oo;
        }

        // Initializam distanta source -> source = 0
        d[source] = 0;
        // Adaugam in heap sursa cu prioritate = cost
        pq.push({d[source], source});

        while (!pq.empty()) {
            // Extragem nodul cu costul estimat minim fata de sursa
            auto entry = pq.top();
            pq.pop();

            int cost = entry.first;
            int node = entry.second;

            // Daca intrarea curenta nu este up-to-date
            // Adica s-a modificat costul fata de cel deja existent in heap
            if (cost > d[node]) {
                continue;
            }

            // Pentru fiecare vecin incercam sa relaxam costul de la sursa
            // la el trecand prin nodul node
            for (int i = 1; i <= n; ++i) {
                int neighbour = i;
                int cost_edge = adj[node][i];

                // Daca obtinem un cost mai mic trecand prin node
                if (d[node] + cost_edge < d[neighbour]) {
                    // Salvam noua distanta
                    d[neighbour] = d[node] + cost_edge;

                    // Actualizam costul drumului de la sursa la vecin
                    pq.push({d[neighbour], neighbour});
                }
            }
        }
    }

    bool BellmanFord(int source, std::vector<int>& d) {
        // Coada folosita la algoritmul BellmanFord
        std::queue<int> q;

        // used[i] = de cate ori a fost folosit nodul i
        std::vector<int> used(n + 2, 0);

        // Presupunem ca nu exista drum de la source la i
        for (int i = 1; i <= n + 1; ++i) {
            d[i] = oo;
        }

        // Distanta source -> source = 0
        d[source] = 0;

        // Adaugam source in coada
        q.push(source);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            // Crestem numarul de utilizari al nodului node
            ++used[node];
            if (used[node] > n + 1) {
                return true; // Am gasit ciclu de cost negativ
            }

            // Pentru fiecare vecin incercam sa relaxam costul de la sursa
            // la el trecand prin nodul node
            for (int i = 1; i <= n; ++i) {
                int neighbour = i;
                int cost_edge = adj[node][i];

                // Daca obtinem un cost mai mic trecand prin node
                if (d[node] + cost_edge < d[neighbour]) {

                    // Salvam noua distanta
                    d[neighbour] = d[node] + cost_edge;

                    // Actualizam costul drumului de la sursa la vecin
                    q.push(neighbour);
                }
            }
        }

        // Nu s-a gasit ciclu de cost negativ, costurile au putut fi calculate.
        return false;
    }

    bool Johnson() {
        // Cream legaturi de la nodul nou la toate celelalte
        for (int i = 1; i <= n; ++i) {
            adj[n + 1][i] = 0;
        }

        // Initializam vectorul pe care il vom trimite la BellmanFord cu valoarea oo
        std::vector<int> h(n + 2, oo);

        // Setam n + 1 ca sursa pentru BellmanFord
        int source = n + 1;

        // Aplicam BellmanFord cu noul nod ca sursa pentru a afla costurile nodurilor
        bool neg_cycle = BellmanFord(source, h);

        // Daca s-a gasit un ciclu negativ, oprim algoritmul
        if (neg_cycle) {
            return true;
        }

        // Aflam noile costuri ale muchiilor
        for (int i = 1; i <= n + 1; ++i) {
            for (int j = 1; j <= n + 1; ++j) {
                adj[i][j] += (h[i] - h[j]);
            }
        }

        // Aplicam Dijkstra din fiecare nod pentru a afla distantele
        for (int i = 1; i <= n; ++i) {
            std::vector<int> d(n + 1, oo);
            Dijkstra(i, d);
            for (int j = 1; j <= n; ++j) {
                adj[i][j] = d[j];
            }
        }

        // Nu s-a gasit ciclu de cost negativ, costurile au putut fi calculate.
        return false;
    }

    void print_output(bool negative_cycle) {
        if (negative_cycle) {
            std::cout << "S-a gasit un ciclu negativ";
            return;
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                std::cout << adj[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    // din cauza ca fac redirectari, salvez starea lui std::cin si std::cout
    auto cin_buff  = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("johnson.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    std::ofstream fout("johnson.out");
    std::cout.rdbuf(fout.rdbuf()); // save and redirect

    // aici este rezolvarea propriu-zisa
    Task* task = new Task();
    task->solve();
    delete task;

    // restore pentru std::cin si std::cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide

    return 0;
}

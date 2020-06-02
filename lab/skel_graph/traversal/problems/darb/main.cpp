// Copyright 2020 Cristian Olaru <cristianolaru99@gmail.com>

// Diametrul unui arbore (DARB) - Diameter of a tree
// Se folosesc 2 parcurgeri in latime (BFS) - O(n + m)
// Obs: Problema se poate rezolva similar si cu 2 parcurgeri in adancime (DFS)

// Exemplificare si testare:
// https://infoarena.ro/problema/darb

#include <bits/stdc++.h>

// Constante in program
// ATENTIE la cat sunt in problema curenta !!!
#define NMAX 100009    // numar maxim de noduri
#define kInf (1 << 30) // infinit pe 32 biti

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // adj[node] lista de adiacenta a nodului node
    std::vector<int> adj[NMAX];

    void read_input() {
        std::cin >> n;

        // citesc n - 1 muchii, deoarece este un arbore
        for (int i = 1; i < n; ++i) {
            int x, y;
            std::cin >> x >> y; // citesc muchia x-y

            adj[x].push_back(y);
            adj[y].push_back(x); // graful este neorientat
        }
    }

    int get_result() {
        // intreaga logica a programului se afla aici
        
        // d[i] = lungimea minima a unui drum de la sursa s la nodul i
        //        (lungime = numar de muchii)
        std::vector<int> d(n + 1);

        // diametrul unui arbore reprezintă lungimea drumului
        // (ca numar de noduri) intre cele mai departate două frunze.

        // efectuam o prima parcurgere BFS initiala din nodul 1
        // scopul acestei parcurgeri este de a determina un capat al
        // celui mai lung lant din graf (el ne va da diametrul cerut)
        // acest capat va fi cel mai departat nod din prima parcurgere
        // fata de nodul 1
        // OBS: se poate alege orice nod sursa pentru aceasta prima parcurgere
        int diameter_start = bfs(1, d);

        // odata ce am determinat un capat al celui mai lung lant,
        // tot ce ramane de facut este sa mai efectuam o parcurgere BFS
        // distanta maxima obtinuta va fi chiar lungimea lantului cerut
        int diameter_end = bfs(diameter_start, d);

        // observam ca diametrul se masoara ca lungimea drumului ca numar de noduri
        // deoarece BFS de ofera lungimea drumului ca numar de muchii,
        // mai adaugam 1 la lungimea celui mai lung lant pentru a obtine diametrul
        int diameter = d[diameter_end] + 1;

        return diameter;
    }

    // aplica BFS pe un graf - viziteaza ce este accesibil din sursa source
    int bfs(int source, std::vector<int> &d) {
        // Step 0: declaram o coada in care putem baga noduri
        std::queue<int> q;

        // Step 1: initializare distante & parinti
        for (int i = 1; i <= n; ++i) {
            d[i] = kInf;      // presupun ca nu am drum
        }

        // Step 2: pasul initial: cunosc sursa source, o adaug in coada
        q.push(source);
        d[source] = 0; // distanta de la source la source e 0

        // Step 3: parcurg in latime graful pornind din ssource
        while (!q.empty()) {
            // 3.1: SCOT primul nod din coada
            int node = q.front();
            q.pop();

            // 3.2 Ii parcurg toti vecinii
            for (auto &neighbour : adj[node]) {
                // daca se poate ajunge pe un drum mai scurt, aleg acest drum
                // constanta + 1 < kInf => gasesc drumul optim
                if (d[node] + 1 < d[neighbour]) {
                    d[neighbour] = d[node] + 1; // actualizez distanta

                    q.push(neighbour); // pun vecinul in coada
                }
            }
        }

        // Step 4 - determinam cel mai indepartat nod obtinut din parcurgere
        // Atentie! Distantele sunt initializare cu kInf, trebuie sa
        // obtinem distanta maxima din parcurgere diferita de kInf

        // initializam distanta maxima cu -1 si indicele corespunzator acestei distante cu 0
        int max = 0, dist_max = -1;

        // parcurgem vectorul de distante
        for (int i = 1; i <= n; ++i) {
            if (d[i] > dist_max && d[i] != kInf) {
                // am gasit o distanta mai mare in arbore
                max = i; // actualizam indicele
                dist_max = d[i]; // actualizam distanta maxima
            }
        }

        // returnam nodul cel mai indepartat de source
        return max;
    }

    void print_output(int result) {
        std::cout << result << "\n";
    }
};

int main() {
    // din cauza ca fac redirectari, salvez starea lui std::cin si std::cout
    auto cin_buff  = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("darb.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    std::ofstream fout("darb.out");
    std::cout.rdbuf(fout.rdbuf()); //save and redirect

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

// Darius Neatu <neatudarius@gmail.com>
// 2018

// skel_graph - shortest path (one soruce) - O(n * m)

// parcugere in latime pe matrice - atentie
// este o ANALOGIE cu BFS pe graf
// Daca am transforma o matrice n x m in graf =>
// => n*m noduri
// => 4 * n*m muchii (daca fiecare nod are exact 4 vecini)
// => O(n + m) de la BFS devine O(n*m + 4 *n *m)  = O(n * m) pe matrice

// https://infoarena.ro/algoritmul-lee

#include <bits/stdc++.h>
using namespace std;

// Constante in program
// ATENTIE la cat sunt in problema curenta !!!
#define NMAX      1009      // dimensiune matrice
#define kInf      (1 << 30) // infinit pe 32 biti ;)
#define CELL_FREE     0
#define CELL_BLOCKED -1
#define CELL_GATE    -2

#define KMAX 4              // numar maxim de vecini
const int dx[] = {+0, +0, +1, -1, };
const int dy[] = {+1, -1, +0, +0, };
// vecinul al k-lea pentru celula (i, j) este (i + dx[k], j + dy[k])

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    // labirint n x m celule
    int n, m;

    // labyrith[i][j] =
    //                   0 => celula libera
    //                  -1 => obstacole
    //                  -2 => poarta
    int labyrinth[NMAX][NMAX];     

    // start.first, start.second - coordonatele pozitiei de start
    pair<int, int> source;

    // d[ (i, j) ] = distanta minima a unui drum de la start la pozitia (i, j)
    //           (distanta == numar de celule parcurs)
    map< pair<int, int>, int > d;

    // p[ (i, j) ] = parintele nodului (i, j) din parcurgerea BFS
    //           (coordonatei celulei din care se trece in i,j pe drumul minim
    //            de la source la i, j)
    map< pair<int, int>, pair<int, int> > p;

    void read_input() {
        // citesc numar de noduri, numar de muschii, sursa din BFS
        cin >> n >> m >> source.first >> source.second;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> labyrinth[i][j];

                // pot sa alterez codificarea din fisier cu propria mea codificare
                if (labyrinth[i][j] == 0) {
                    labyrinth[i][j] = CELL_FREE;
                } else if (labyrinth[i][j] == 1) {
                    labyrinth[i][j] = CELL_BLOCKED;
                } else if (labyrinth[i][j] == 2) {
                    labyrinth[i][j] = CELL_GATE;
                }
            }
        }
    }

    vector< pair<int, int> > get_result() {
        // path = {source, ..., gate};
        vector< pair<int, int> > path;

        // gasesc toate drumurile minime cu BFS pe matrice
        bfs(source);

        // parcurg extremitatile unei matrice si caut unde am porti
        // o aleg pe cea mai apropiata
        int sol = kInf;
        pair<int, int> best_gate;
        for (int i = 1; i <= n; ++i) {
            // coloana 1
            if (labyrinth[i][1] == CELL_GATE && d[ {i, 1}  ] < sol) {
                sol = d[ {i, 1} ];
                best_gate = {i, 1};
            }

            // coloana n
            if (labyrinth[i][n] == CELL_GATE && d[ {i, n}  ] < sol) {
                sol = d[ {i, n} ];
                best_gate = {i, n};
            }

            // linia 1
            if (labyrinth[1][i] == CELL_GATE && d[ {1, i}  ] < sol) {
                sol = d[ {1, i} ];
                best_gate = {1, i};
            }

            // linia n
            if (labyrinth[n][i] == CELL_GATE && d[ {n, i}  ] < sol) {
                sol = d[ {n, i} ];
                best_gate = {n, i};
            }
        }

        // reconstitui drumul de la source la best_gate
        path = rebuild_path(best_gate);

        return path;
    }

    bool in_matrix(pair<int, int> cell) {
        return (cell.first  >= 1 && cell.first  <= n) &&
               (cell.second >= 1 && cell.second <= m);
    }

    void bfs(pair<int, int> source) {
        // Step 0: declaram o coada in care putem baga noduri/celule
        queue< pair<int, int> > Q;

        // Step 1: initializare distante & parinti
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                d[ {i, j} ] = kInf;
            }
        }

        // Step 2: pasul initial: cunosc sursa soruce, o adaug in coada
        Q.push(source);
        d[source] = 0;         // distanta de la source la source e 0
        p[source] = {0, 0};    // parintele lui source este 0, 0 - conventie

        // Step 3: parcurg in latime
        while (!Q.empty()) {
            // 3.1: SCOT prima celula din coada
            pair<int, int> node = Q.front();
            Q.pop();
            int x = node.first, y = node.second;

            // 3.2 Ii parcurg toti vecinii
            for (int k = 0; k < KMAX; ++k) {
                int new_x = x + dx[k];
                int new_y = y + dy[k];

                // celula inafara limitelor terenului
                if (!in_matrix({new_x, new_y})) {
                    continue;
                }

                // celula blocata
                if (labyrinth[new_x][new_y] == CELL_BLOCKED) {
                    continue;
                }

                // celula este disponibila - se poate intra in ea
                // verific daca se poate intra cu o distanta mai mica decat ceva curenta
                pair<int, int> it = {new_x, new_y};
                if (d[node] + 1 < d[it]) {
                    d[ it ] = d[ node ] + 1;    // actualizez distanta
                    p[ it ] = node;             // actualizez parintele

                    Q.push(it);                 // celula {new_x, new_y} este pusa in coada
                }
            }
        }
    }

    // rebuild source -> ... -> cell (if exists)
    vector< pair<int, int> > rebuild_path(pair<int, int> node) {
        // nu exista drum de la source la node => distanta infinita
        if (d[ node ] == kInf) {
            return {};
        }

        // path = {source, ..., node}
        vector< pair<int, int> > path;

        // rebuild node -> ... -> source (if exists)
        for (; !(node.first == 0 && node.second == 0); node = p[node]) {
            path.push_back( node );
        }
        // cand node == souce, p[node] == {0, 0}
        // (asta ma asigura ca forul se opreste la iteratia urmatoare)

        // s-a obtinut drumul node -> ... -> source
        // inversam solutia
        reverse(path.begin(), path.end());

        return path;
    }   

    void print_output(vector< pair<int, int> > result) {
        cout << "source: " << source.first << " " << source.second << "\n";

        cout << "labyrinth: " << "\n";
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                printf("%2d ", labyrinth[i][j]);
            }
            cout << "\n";
        }

        cout << "\n";
        cout << "d: " << "\n";
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                printf("%2d ", (d[ {i, j} ] < kInf ? d[ {i, j} ] : -1));
            }
            cout << "\n";
        }
        cout << "\n";


        cout << result.size() << "\n";
        for (int i = 0; i < (int) result.size(); ++i) {
            cout << result[i].first << " " << result[i].second << "\n";
        }
    }
};

void legend() {
    cout << "legend: d[i][j] = distance from source to {i, j} cell\n";
    cout << "\n";
}

int main() {
    // las linia urmatoare daca citesc din fisier
    assert( freopen("in", "r", stdin) != NULL);

    // las linia urmatoare daca afisez in fisier
    // assert( freopen("out", "w", stdout) != NULL) ;

    legend();

    // din cauza ca avem tablouri cu NMAX elemente in clasa,
    // totul trebuie alocat dinamic - evit stack smash
    Task *task = new Task();
    task->solve();
    delete task;

    return 0;
}

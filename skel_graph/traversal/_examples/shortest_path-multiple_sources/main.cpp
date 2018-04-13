// Darius Neatu <neatudarius@gmail.com>
// 2018

// skel_graph - shortest path (multiple soruce) - O(n * m)

// parcugere in latime pe matrice
// surse multiple => le bag pe toate in coada
// ATENTIE! Se cere pentru fiecare celula distanta minima de
// la o sursa OARECARE la o celula data

// Exemplificare:
// https://infoarena.ro/problema/muzeu

#include <bits/stdc++.h>
using namespace std;

// Constante in program
// ATENTIE la cat sunt in problema curenta !!!
#define NMAX         1009      // dimensiune matrice
#define kInf         (1 << 30) // infinit pe 32 biti ;)
#define CELL_FREE     0
#define CELL_ISOLATED -1
#define CELL_BLOCKED  -2
#define CELL_P        -3

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

    // d[i, j] = distanta minima a unui drum de la start la pozitia (i, j)
    //           (distanta == numar de celule parcurs)
    int d[NMAX][NMAX];

    // pozitiile paznicillor
    vector< pair<int, int> > ps;

    void read_input() {
        // citesc numar de noduri, numar de muschii, sursa din BFS
        cin >> n;
        m = n;   // patratica

        for (int i = 1; i <= n; ++i) {
            string line;
            cin >> line;

            for (int j = 1; j <= m; ++j) {
                if (line[j - 1] == '.') {
                    labyrinth[i][j] = CELL_FREE;
                } else if (line[j - 1] == 'P') {
                    labyrinth[i][j] = CELL_P;
                    ps.push_back({i, j});
                } else if (line[j - 1] == '#') {
                    labyrinth[i][j] = CELL_BLOCKED;
                }
            }
        }
    }

    int get_result() {
        // gasesc toate drumurile minime cu BFS pe matrice
        bfs();

        return 0;
    }

    bool in_matrix(pair<int, int> cell) {
        return (cell.first  >= 1 && cell.first  <= n) &&
               (cell.second >= 1 && cell.second <= m);
    }

    void bfs() {
        // Step 0: declaram o coada in care putem baga noduri/celule
        queue< pair<int, int> > Q;

        // Step 1: initializare distante & parinti
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                d[i][j] = kInf;
            }
        }

        // Step 2: pasul initial: cunosc sursa soruce, o adaug in coada
        for (auto &source : ps) {
            Q.push(source);
            d[source.first][source.second] = 0;
        }

        // Step 3: parcurg in latime
        while (!Q.empty()) {
            // 3.1: SCOT prima celula din coada
            pair<int, int> cell = Q.front();
            Q.pop();
            int x = cell.first, y = cell.second;

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
                if (d[x][y] + 1 < d[new_x][new_y]) {
                    d[new_x][new_y] = d[x][y] + 1;          // actualizez distanta

                    Q.push({new_x, new_y});                 // celula {new_x, new_y} este pusa in coada
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (labyrinth[i][j] == CELL_BLOCKED) {
                    d[i][j] = -2;
                } else if (d[i][j] == kInf) {
                    d[i][j] = -1;
                }   
            }
        }
    }

    void print_output(int result) {
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
                printf("%2d ", (d[i][j] < kInf ? d[i][j] : -1));
            }
            cout << "\n";
        }
        cout << "\n";
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

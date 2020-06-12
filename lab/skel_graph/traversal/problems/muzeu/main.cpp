// Copyright Radu Nichita 2020 radunichita99@gmail.com

// Muzeu - Problema parcurgeri
// BFS din mai multe surse

// Complexitate O(N ^ 2)
// N este dimensiunea matricei

// https://infoarena.ro/problema/muzeu

#include <bits/stdc++.h>
#define KMAX 300
#define kInf (1 << 30)

class Task {
    // coada cu nodurile ce urmeaza a fi explorate
    std::queue<std::pair<int, int>> explore;
    // vector de distante, nu am nevoie de matricea de caractere
    // distances[i][j] = distanta de la cel mai apropiat paznic la celula
    // din matrice de coordonate i j.
    int distances[KMAX][KMAX];
    // cele 4 directii in care pot merge prin matrice
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    // dimensiunea muzeului
    int n;

    // Nu am nevoie sa stochez matricea pe care o primesc, ci
    // doar sa prelucrez datele on the fly intr-o matrice de
    // distante.
    void read_input() {
        std::cin >> n;
        char c;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                std::cin >> c;
                switch (c) {
                case '#':
                    // Intalnesc un blocaj, niciun paznic nu poate ajunge
                    // aici, distanta va fi -2.
                    distances[i][j] = -2;
                    break;
                case 'P':
                    // Exista un paznic in camera, distanta pana la el e 0.
                    distances[i][j] = 0;
                    // Fiind paznic, adaug coordonatele lui in coada.
                    explore.push({i, j});
                    break;
                default:
                    // Caz cu . , camera in care nu se afla paznic.
                    distances[i][j] = kInf;
                    break;
                }
            }
        }
    }

    // Solutia problemei se bazeaza pe aplicarea unui BFS modificat, ce contine
    // initial in coada mai multe noduri, intrucat cautam distanta minima intre
    // orice paznic si fiecare celula din matrice. Asadar, in loc de a face un
    // (numar paznic) BFS-uri, se va face unul singur. Si practic unele celule
    // pot fi vizitate de un numar mai mare de paznici, dar distanta pana la
    // aceasta va fi modificata doar de primul paznic care ajunge la ea, daca
    // acest lucru este posibil.
    void get_result() {
        // Cat timp mai sunt noduri de vizitat
        while (!explore.empty()) {
            // Iau primul nod de explorat
            auto node = explore.front();
            explore.pop();
            // Pentru fiecare directie posibila in care pot merge
            for (auto const& direction : directions) {
                // Iau noile coordonate
                int newX            = node.first + direction.first;
                int newY            = node.second + direction.second;
                int parent_distance = distances[node.first][node.second];
                // Daca coordonatele pe care testez sunt valide si nu am o
                // distanta anterioara
                if (newX >= 1 && newX <= n && newY >= 1 && newY <= n && distances[newX][newY] == kInf) {
                    // S-a gasit o cale catre nodul respectiv.
                    distances[newX][newY] = parent_distance + 1;
                    // Pun nodul in coada, pentru a fi explorat.
                    explore.push({newX, newY});
                }
            }
        }
    }

    void print_output() {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                std::cout << (distances[i][j] != kInf ? distances[i][j] : -1) << ' ';
            }
            std::cout << "\n";
        }
        return;
    }

public:
    void solve() {
        read_input();
        get_result();
        print_output();
    }
};

int main() {
    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff  = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("muzeu.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    std::ofstream fout("muzeu.out");
    std::cout.rdbuf(fout.rdbuf()); // save and redirect

    // aici este rezolvarea propriu-zisa
    Task* task = new Task();
    task->solve();
    delete task;

    // restore pentru cin si cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide

    return 0;
}

// Copyright Radu Nichita 2020 radunichita99@gmail.com

// Algoritmul A* - complexitate O(b ^ d), b = branching factor, d = depth.

#include <bits/stdc++.h>
#define get_f(t) std::get<0>(t);
#define get_g(t) std::get<1>(t);
#define get_h(t) std::get<2>(t);


using Cell = std::pair<int, int>;


class Task {
    // n = numar de linii, m = numar de coloane.
    int n, m;

    // vector in care se va stoca drumul de la destinatie la sursa.
    std::vector<int> path;

    // celula sursa si celula destinatie
    Cell source, destination;

    // matricea cu celule libere si celule blocate
    std::vector<std::vector<int>> adj_matrix;
    std::set<Cell> closed;
    std::set<Cell> open;

    // parent[node.first][node.second] -> parintele nodului node. 
    std::vector<std::vector<Cell>> parent;

    // matrice de tupluri <f, g, h> pentru fiecare valoare din matrice
    std::vector<std::vector<std::tuple<double, double, double>>> fgh;


    void read_input() {
        std::cin >> n >> m;
        adj_matrix = std::vector<std::vector<int>>(n + 1, std::vector<int> (m + 1 , 0));
        parent = std::vector<std::vector<Cell>>(
        n + 1, std::vector<Cell>
        (m + 1, {-1, -1}));
        fgh =  std::vector<std::vector<std::tuple<double, double, double>>>
        (n + 1, std::vector<std::tuple<double, double, double>>
        (m + 1, std::make_tuple(DBL_MAX, DBL_MAX, DBL_MAX)));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                std::cin >> adj_matrix[i][j];
            }
        }


        std::cin >> source.first >> source.second;
        std::cin >> destination.first >> destination.second;
    }


    void print_output() {
        for (auto &pos : build_path(destination)) {
            std::cout<< "Trec prin punctul" << pos.first << " " << pos.second;
            std::cout << "\n";
        }
    }

    std::vector<std::pair <int, int>>  expand(std::pair <int, int> node) {
        std::vector<std::pair <int, int>> directions =
        {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1},};
        std::vector<std::pair <int, int>> succ;
        for (const auto &[dx, dy] : directions) {
            int x = node.first + dx;
            int y = node.second + dy;
            if (x >= 1 && x <= n && y >= 1 && y <= n && adj_matrix[x][y] == 1) {
                succ.push_back({x, y});
            }
        }
        return succ;
    }

    bool is_goal(const Cell &node) {
        return (node == destination);
    }

    double euclidian_distance_heuristic(Cell node) {
        int abs_x = abs(node.first - destination.first);
        int abs_y = abs(node.second - destination.second);
        return sqrt(abs_x * abs_x + abs_y * abs_y);
    }

    std::vector<std::pair <int, int>> build_path(Cell node) {
        auto current = node;
        std::vector<Cell> path;
        while (!(current.first == -1 && current.second == -1)) {
            path.push_back(current);
            current = parent[current.first][current.second];
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    bool astar(const std::pair<int, int> &start_state) {
         // initializari
        open.clear();  // multimea nodurilor in curs de explorare
        closed.clear();  // multimea nodurilor expandate

        // functie lambda pentru a compara doua perechi
        auto comparator = [](auto x1, auto x2) {
        return x1.first > x2.first;
        };

        //  priority queue cu nodurile in curs de explorare
        std::priority_queue<std::pair<double, Cell>,
        std::vector<std::pair <double, Cell>>,
        decltype(comparator)> openlist(comparator);

        // pentru s_i avem distanta 0 si parinte NULL
        std::get<1>(fgh[start_state.first][start_state.second]) = 0.0;
        std::get<2>(fgh[start_state.first][start_state.second]) =
        euclidian_distance_heuristic(start_state);
        std::get<0>(fgh[start_state.first][start_state.second]) =
        std::get<1>(fgh[start_state.first][start_state.second])
        + std::get<2>(fgh[start_state.first][start_state.second]);

        // adaugare nod atat in lista de open, cat si in coada de prioritati.
        openlist.push
        (std::make_pair(std::get<0>
        (fgh[start_state.first][start_state.second]), start_state));
        open.insert(start_state);

        // parcurgerea continua cat timp avem noduri in open
        while (!openlist.empty()) {
            // extrage nodul s cu f(s) minim
            auto s = openlist.top().second;
            openlist.pop();
            open.erase(s);

            // daca s este stare finala
            if (is_goal(s)) {
                return true;
            }

            // daca nodul nu este deja expandat
            if (closed.find(s) == closed.end()) {
                 // il adaug in closed
                closed.insert(s);

                // pentru fiecare copil c al starii s
                for (auto &c : expand(s)) {
                    double f, g, h;
                    if (std::get<1>(fgh[c.first][c.second]) == DBL_MAX ||
                    std::get<1>(fgh[s.first][s.second]) + 1.0
                    < std::get<1>(fgh[c.first][c.second])) {
                        // actualizez distanta si parintele
                        g = std::get<1>(fgh[c.first][c.second]) =
                        std::get<1>(fgh[s.first][s.second]) + 1.0;
                        parent[c.first][c.second] = s;

                        // daca nodul c nu a mai fost intalnit
                        if (!(closed.find(c) != closed.end() ||
                        open.find(c) != open.end())) {
                            h = euclidian_distance_heuristic(c);
                            std::get<2>(fgh[c.first][c.second]) = h;
                            f = g + h;
                            std::get<0>(fgh[c.first][c.second]) = f;
                            // c intra in open
                            open.insert(c);
                            openlist.push({f, c});
                        // daca nodul c a mai fost expandat
                        } else if (closed.find(c) != closed.end()) {
                            h = euclidian_distance_heuristic(c);
                            f = g + h;

                            // c trece din closed in open
                            closed.erase(c);
                            open.insert(c);
                            openlist.push({f, c});
                        }
                    }
                }
            }
        }

        // nu a fost gasita o cale de la source la o stare goal s
        return false;
    }

    bool get_result() {
       return astar(source);
    }

 public:
    void solve() {
        read_input();
        if (get_result()) {
            print_output();
        } else {
            std::cout << "Nu s-a gasit cale\n";
        }
    }
};



int main() {
  // din cauza ca fac redirectari, salvez starea lui cin si cout
  auto cin_buff = std::cin.rdbuf();
  auto cout_buff = std::cout.rdbuf();

  // las liniile urmatoare daca citesc din fisier
  std::ifstream fin("astar.in");
  std::cin.rdbuf(fin.rdbuf());  // save and redirect

  // las liniile urmatoare daca afisez in fisier
  // cout.rdbuf(fout.rdbuf()); // save and redirect

  // aici este rezolvarea propriu-zisa
  Task *task = new Task();
  task->solve();
  delete task;

  // restore pentru cin si cout
  std::cin.rdbuf(cin_buff);
  std::cout.rdbuf(cout_buff);

  // obs. nu e nevoie sa inchid fisierele
  // cand se apeleaza destructorii pentru fin si fout se vor inchide

  return 0;
}

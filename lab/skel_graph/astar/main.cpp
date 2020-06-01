// Copyright Radu Nichita 2020 radunichita99@gmail.com


// Algoritmul A* - complexitate O(b ** d), b = branching factor, d = depth.

#include <bits/stdc++.h>

using Matrix = std::vector<std::vector<int>>;
using Parents = std::vector<std::vector<std::pair<int, int>>>;

class Task {
    int n, m;
    std::vector<int> path;
    std::pair<int, int> source;
    std::pair<int, int> destination;
    Matrix adj_matrix;
    std::set<std::pair<int, int>> closed;
    std::set<std::pair<int, int>> open;
    Parents parent;

    // matrix of a tuple <f,g, h> for every value
    std::vector<std::vector<std::tuple<double, double, double>>> fgh;

    void read_input() {
        std::cin >> n >> m;
        adj_matrix = Matrix(n + 1, std::vector<int> (m + 1 , 0));
        parent = Parents(n + 1, std::vector<std::pair<int, int>>
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
        for (auto &pos : buildPath(destination)) {
            std::cout<< "Trec prin punctul" << pos.first << " " << pos.second;
            std::cout << "\n";
        }
    }

    std::vector<std::pair <int, int>>  expand(std::pair <int, int> node) {
        std::vector<std::pair <int, int>> directions =
        {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
        std::vector<std::pair <int, int>> succ;
        for (auto const &direction : directions) {
            int dx = direction.first;
            int dy = direction.second;
            int x = node.first + dx;
            int y = node.second + dy;
            if (x >= 1 && x <= n && y >= 1 && y <= n && adj_matrix[x][y] == 1) {
                succ.push_back({x, y});
            }
        }
        return succ;
    }

    bool is_goal(std::pair<int, int> node) {
        return (node == destination);
    }

    double euclidian_distance_heuristic(std::pair<int, int> node) {
        int abs_x = abs(node.first - destination.first);
        int abs_y = abs(node.second - destination.second);
        return sqrt(abs_x * abs_x + abs_y * abs_y);
    }

    std::vector<std::pair <int, int>> buildPath(std::pair<int, int> node) {
        auto current = node;
        std::vector<std::pair<int, int>> path;
        while (!(current.first == -1 && current.second == -1)) {
            path.push_back(current);
            current = parent[current.first][current.second];
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    bool get_result() {
        // initializari
        open.clear();  // multimea nodurilor in curs de explorare
        closed.clear();  // multimea nodurilor expandate

        // functie lambda pentru a compara doua perechi
        auto comparator = []
        (std::pair<double, std::pair<int, int>> x1,
        std::pair<double, std::pair<int, int>> x2) {
        return x1.first > x2.first;
        };

        //  priority queue cu nodurile in curs de explorare
        std::priority_queue<std::pair<double, std::pair<int, int>>,
        std::vector<std::pair <double, std::pair<int, int>>>,
        decltype(comparator)> openlist(comparator);

        // pentru s_i avem distanta 0 si parinte NULL
        std::get<1>(fgh[source.first][source.second]) = 0.0;
        std::get<2>(fgh[source.first][source.second]) =
        euclidian_distance_heuristic(source);
        std::get<0>(fgh[source.first][source.second]) =
        std::get<1>(fgh[source.first][source.second])
        + std::get<2>(fgh[source.first][source.second]);

        // adaugare nod atat in lista de open, cat si in coada de prioritati.
        openlist.push
        (std::make_pair(std::get<0>(fgh[source.first][source.second]), source));
        open.insert(source);

        // parcurgerea continua cat timp avem noduri in open
        while (!openlist.empty()) {
            // extrage nodul s cu f(s) minim
            auto q = openlist.top();
            auto s = q.second;
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

 public:
    void solve() {
        read_input();
        if (get_result() == true) {
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
  // ofstream fout("maxflow.out");
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

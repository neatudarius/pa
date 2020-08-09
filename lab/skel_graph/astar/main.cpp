// Copyright Radu Nichita 2020 radunichita99@gmail.com

// Algoritmul A* - complexitate O(b ^ d), b = branching factor, d = depth.

#include <bits/stdc++.h>


using Cell = std::pair<int, int>;

namespace std {
template<> struct hash<Cell> {
    inline size_t operator()(const Cell& cell) const {
        std::hash<int> int_hasher;
        return int_hasher(cell.first) ^ int_hasher(cell.second);
    }
};

}

class Task {
    // n = numar de linii, m = numar de coloane.
    int n, m;

    // vector in care se va stoca drumul de la destinatie la sursa.
    std::vector<int> path;

    // celula sursa si celula destinatie
    Cell source, destination;

    // matricea cu celule libere si celule blocate
    std::vector<std::vector<int>> adj_matrix;

    // multimea nodurilor closed
    std::unordered_set<Cell> closed;
    std::set<double, Cell> openlist; 

    // dictionar de parinti
    std::unordered_map<Cell, Cell> parent;

    // dictionar pentru fiecare dintre f,g,h
    std::unordered_map<Cell, double> f;
    std::unordered_map<Cell, double> g;
    std::unordered_map<Cell, double> h;

    void init() {
        adj_matrix = std::vector<std::vector<int>>(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                f[{i, j}]      = DBL_MAX;
                g[{i, j}]      = DBL_MAX;
                h[{i, j}]      = DBL_MAX;
                parent[{i, j}] = {-1, -1};
            }
        }
    }

    void read_input() {
        std::cin >> n >> m;
        init();

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                std::cin >> adj_matrix[i][j];
            }
        }

        std::cin >> source.first >> source.second;
        std::cin >> destination.first >> destination.second;
    }

    void print_output() {
        for (auto& pos : build_path(destination)) {
            std::cout << "Trec prin punctul" << pos.first << " " << pos.second;
            std::cout << "\n";
        }
    }

    std::vector<Cell> expand(Cell& node) {
        std::vector<std::pair<int, int>> directions = {
            {1, 1},
            {1, 0},
            {1, -1},
            {0, 1},
            {0, -1},
            {-1, 1},
            {-1, 0},
            {-1, -1},
        };
        std::vector<Cell> succ;
        for (const auto& [dx, dy] : directions) {
            int x = node.first + dx;
            int y = node.second + dy;
            if (x >= 1 && x <= n && y >= 1 && y <= n && adj_matrix[x][y] == 1) {
                succ.push_back({x, y});
            }
        }
        return succ;
    }

    bool is_goal(const Cell& node) { return (node == destination); }

    double euclidian_distance_heuristic(Cell node) {
        int abs_x = abs(node.first - destination.first);
        int abs_y = abs(node.second - destination.second);
        return sqrt(abs_x * abs_x + abs_y * abs_y);
    }

    std::vector<Cell> build_path(Cell& node) {
        auto current = node;
        std::vector<Cell> path;
        while (!(current.first == -1 && current.second == -1)) {
            path.push_back(current);
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    bool astar(const Cell& start_state) {
        // initializari
        closed.clear(); // multimea nodurilor expandate

        // functie lambda pentru a compara doua perechi
        auto comparator = [](auto x1, auto x2) { return x1.first > x2.first; };

        //  set cu nodurile in curs de explorare
        std::set<std::pair<double, Cell>, decltype(comparator)> openlist(comparator);

        g[start_state] = 0.0;
        h[start_state] = euclidian_distance_heuristic(start_state);
        f[start_state] = g[start_state] + h[start_state];
        // adaugare nod atat in lista de open, cat si in coada de prioritati.
        openlist.insert({f[start_state], start_state});

        // parcurgerea continua cat timp avem noduri in open
        while (!openlist.empty()) {
            // extrage nodul s cu f(s) minim
            auto s = (*(openlist.begin())).second;
            openlist.erase(openlist.begin());
            // daca s este stare finala
            if (is_goal(s)) {
                return true;
            }
            // daca nodul nu este deja expandat
            if (closed.find(s) == closed.end()) {
                // il adaug in closed
                closed.insert(s);
                // pentru fiecare copil c al starii s
                for (auto& c : expand(s)) {
                    if (g[c] == DBL_MAX || g[s] + 1.0 < g[c]) {
                        // actualizez distanta si parintele
                        g[c]      = g[s] + 1.0;
                        parent[c] = s;
                        // daca nodul c nu a mai fost intalnit
                        if (!(closed.find(c) != closed.end()
                                || std::find_if(openlist.begin(), openlist.end(), [&c](auto& p) {
                                       return p.second == c;
                                   }) != openlist.end())) {
                            h[c] = euclidian_distance_heuristic(c);
                            f[c] = g[c] + h[c];
                            // c intra in open
                            openlist.insert({f[c], c});
                            // daca nodul c a mai fost expandat
                        } else if (closed.find(c) != closed.end()) {
                            // c trece din closed in open
                            int h_new = euclidian_distance_heuristic(c);
                            int f_new = h_new + g[c];
                            openlist.insert({f_new, c});
                            closed.erase(c);
                        }
                    }
                }
            }
        }

        // nu a fost gasita o cale de la source la o stare goal s
        return false;
    }

    bool get_result() { return astar(source); }

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
    auto cin_buff  = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("astar.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    // cout.rdbuf(fout.rdbuf()); // save and redirect

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

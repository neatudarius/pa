// Copyright 2020 Nicolae Mara-Ioana <maraioana9967@gmail.com>

// Alee - Drumuri minime in graf
// Complexitate: O(n * m)

// https://www.infoarena.ro/problema/alee

#include <bits/stdc++.h>

class Task
{
public:
    void solve()
    {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    int m;
    int source;
    std::vector<std::vector<char>> graph;
    std::pair<int, int> startGate;
    std::pair<int, int> endGate;

    // s-a ales urmatoarea codificare:
    // graph[i][j] = 'T', atunci exista un copcac la coordonatele i, j
    // graph[i][j] = ' ', atunci exista zona libera la coordonatele i, j
    void read_input()
    {
        std::cin >> n >> m;
        // initial se marcheaza toate elementele din matrice ca fiind zone libere
        graph = std::vector<std::vector<char>>(n + 1, std::vector<char>(n + 1, ' '));
        for (int i = 1, x, y; i <= m; i++)
        {
            // se citesc coordonatele la care se afla copacii
            // se actualizeaza valorile din celulele in care se regasesc obstacole
            std::cin >> x >> y;
            graph[x][y] = 'T';
        }

        // Se citesc coordonatele portii din care se porneste cautarea,
        // si cele ale portii ce reprezinta destinatia
        std::cin >> startGate.first >> startGate.second;
        std::cin >> endGate.first >> endGate.second;
    }

    // intrucat graful este reprezentat sub forma unei matrice
    // se va aplica Algoritmul lui Lee
    int get_result()
    {
        // se tine evidenta nodurilor vizitate,
        // initial toate nodurile sunt nevizitate
        std::vector<std::vector<bool>> visited(n + 1, std::vector<bool>(n + 1, false));

        // vectorul de distante pornind de la poarta de start
        std::vector<std::vector<int>> minPath(n + 1, std::vector<int>(n + 1, INT_MAX));

        // in coada se vor retine nodurile descoperite, dar inca nefinalizate
        std::queue<std::pair<int, int>> nodeQueue;

        // vectorul ce reprezinta posibilele pozitii
        // ale vecinilor unui element din matrice
        std::vector<std::pair<int, int>> directions;
        directions.push_back({ 1, 0 });
        directions.push_back({ 0, 1 });
        directions.push_back({ -1, 0 });
        directions.push_back({ 0, -1 });

        // initializari pentru poarta de start
        visited[startGate.first][startGate.second] = true;
        minPath[startGate.first][startGate.second] = 1;
        nodeQueue.push({ startGate.first, startGate.second });

        while (nodeQueue.size())
        {
            // se extrage primul element din coada
            auto node = nodeQueue.front();

            // se parcurg vecinii acestuia folosind vectorul de directii
            // acestia pot fi maximum patru
            for (auto& dir : directions)
            {
                // se verifica daca se respecta granitele matricei
                if (correctBounds(node, dir))
                {
                    int x = node.first + dir.first;
                    int y = node.second + dir.second;
                    if (!visited[x][y])
                    {
                        minPath[x][y] = minPath[node.first][node.second] + 1;
                        visited[x][y] = true;

                        // elementul curent este bagat in coada
                        // doar daca reprezinta o zona libera
                        // un copac ar impiedica inaintarea pe un drum
                        if (graph[x][y] == ' ')
                        {
                            nodeQueue.push({ x, y });
                        }
                    }
                }
            }
            // se elimina din coada
            nodeQueue.pop();
        }

        // returneaza distanta de la poarta de start la poarta destinatie
        return minPath[endGate.first][endGate.second];
    }

    // verifica daca coordonatele unui vecin sunt valide
    // adica nu depasesc extremele matricei
    bool correctBounds(const std::pair<int, int>& p1, const std::pair<int, int>& p2)
    {
        if (p1.first + p2.first <= n && p1.first + p2.first >= 1 
            && p1.second + p2.second <= n && p1.second + p2.second >= 1)
        {
            return true;
        }
        return false;
    }

    void print_output(int result)
    {
        std::cout << result << "\n";
    }
};

int main()
{
    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("alee.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    std::ofstream fout("alee.out");
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

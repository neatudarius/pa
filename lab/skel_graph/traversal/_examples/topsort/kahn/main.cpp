// Darius Neatu <neatudarius@gmail.com>
// 2018

// skel_graph - Topological Sort (Kahn) - O(n + m)

// Sortare Topologica cu BFS
// https://infoarena.ro/problema/sortaret

#include <bits/stdc++.h>
using namespace std;

// Constante in program
// ATENTIE la cat sunt in problema curenta !!!
#define NMAX      100009    // numar maxim de noduri
#define kInf      (1 << 30) // infinit pe 32 biti ;)
#define NO_PARENT -1        // nod fara parinte in arborele BFS - nod nevizitat

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // adj[node] = lista de adiacenta a lui node
    vector<int> adj[NMAX];
    // (observatie: prin conventie nodurile sunt indexate de la 1
    //  deci listele sunt adj[1], ..., adj[n])

    // in_degree[i] = gradul intern al nodului i
    vector<int> in_degree;
    // grad intern == nr de muchii care intra in i
    // arce de forma x -> i

    void read_input() {
        // citesc numar de noduri, numar de muchii
        cin >> n >> m;

        // grad intern 0 pentru toate nodurile... momentan
        in_degree = vector<int> (n + 1, 0);

        for (int i = 1; i <= m; ++i) {
            int x, y;
            cin >> x >> y;       // citesc muchia x-y

            adj[x].push_back(y); // graful e orientat
            ++in_degree[y];      // inca o muchie care intra in y
        }
    }

    vector<int> get_result() {
        // vectorul care ca contine permutarea multimii {1, .. , n}
        // aceasta permutare va fi o sortare topologica valida
        vector<int> topsort;

        // se va dace o parcurge BFS din TOATE nodurile cu grad intern 0
        // in aceasta problema este irelevanta distanta d sau parintele p
        topsort = bfs();

        return topsort;
    }


    // aplica BFS pe un graf - viziteaza ce este accesibil din sursa s
    vector<int> bfs() {
        // Step 0: declaram o coada in care putem baga noduri
        queue<int> Q;

        // Step 1: initializare topsort - permutare vida initial
        vector<int> topsort;

        // Step 2: pasul initial: pun in coada TOATe nodurile cu grad intern 0
        for (int i = 1; i <= n; ++i) {
            if (in_degree[i] == 0) {
                Q.push(i);
            }
        }

        // Step 3: parcurg in latime graful
        while (!Q.empty()) {
            // 3.1: SCOT primul nod din coada
            int node = Q.front();
            Q.pop();

            // adaug element scos la solutie
            topsort.push_back(node);

            // 3.2 Ii parcurg toti vecinii
            for (auto &it : adj[node]) {
                // sterg muchia node->it
                // obs1. NU e nevoie sa o sterg la propriu
                //       Daca nu am cicluri, nu se va ajunge aici
                // obs2. Simulez stergerea prin scaderea gradului intern a lui it
                --in_degree[it];

                // daca it a ajuns nod cu grad intern 0, atunci este adaugat in coada
                if (in_degree[it] == 0) {
                    Q.push(it);
                }
            }
        }

        // STEP 4: verifica ca topsort chiar reprezinta o sortare topologica valida
        // Ce inseamna asta? S-au sters toate muchiile din graf.
        // Daca nu s-a sters tot, atunci graful este ciclic!
        bool is_valid = true;
        for (int i = 1; i <= n; ++i) {
            if (in_degree[i] > 0) {
                is_valid = false;
                break;
            }
        }

        if (is_valid) {
            return topsort;  // sortarea topologica obtinuta
        } else { 
            return {};       // vector gol == nu se poate face o sortare topologica
        }
    }

    
    void print_output(vector<int> result) {
        if (result.size() == 0) {
            cout << "Graful NU este aciclic!\n";
            return;
        }

        for (int i = 0; i < (int) result.size(); ++i) {
            cout << result[i] << " ";
        }
        cout << "\n";
    }
};

void legend() {
    cerr << "legend: sirul afisat este o sortare topologica valida\n";
    cerr << "        (solutia nu e unica)\n";
    cerr << "\n";
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

// Copyright 2020 Nicolae Mara-Ioana <maraioana9967@gmail.com>

// Custi - Programare dinamica
// Complexitate: O(n^2)

// https://www.infoarena.ro/problema/custi

#include <bits/stdc++.h>

class Task
{
public:
    void solve()
    {
        read_input();
        get_result();
        print_output();
    }

private:
    int n; // dimensiunea matricei

    std::vector<std::vector<int>> matrix; // matricea de input

    // fiecare element solution[i] reprezinta numarul de custi
    // de dimensiune maxima i x i ce se pot forma
    // fiecare celula se foloseste o singura data ca si colt dreapta jos
    // a unei custi, aceasta fiind cea de dimesniune maxima
    std::vector<int> solution;

    // citeste datele de intare din fisier si populeaza matricea
    void read_input()
    {
        std::cin >> n;
        matrix = std::vector<std::vector<int>>(n + 1, std::vector<int>(n + 1, 0));
        solution = std::vector<int>(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                std::cin >> matrix[i][j];
            }
        }
    }

    // ideea de la care am plecat: fiecare element este testat daca poate
    // reprezenta coltul din dreapta jos al unui patrat, astfel:
    // CAZUL DE BAZA:
    // dp[i][1] = matrix[i][1]
    // dp[1][i] = matrix[1][i]
    // FORMULA:
    // dp[i][j] = min(celelalte 3 colturi) + 1, adica
    //            min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]) + 1
    //      (daca elementul poate defini un dreptunghi)
    // altfel dp[i][j] = 0
    void get_result()
    {
        // initializarea tabloului dp
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));

        // tratarea cazului de baza: elementele de pe prima linie/coloana
        // ce au valori nenule vor reprezenta custi de dimensiune 1 x 1,
        // deoarece aceste elemente nu pot reprezenta
        // coltul din dreapta jos al unui patrat mai mare
        if (matrix[1][1])
        {
            solution[1]++;
        }
        dp[1][1] = matrix[1][1];
        for (int i = 2; i <= n; i++)
        {
            if (matrix[i][1])
            {
                solution[1]++;
            }
            if (matrix[1][i])
            {
                solution[1]++;
            }
            dp[1][i] = matrix[1][i];
            dp[i][1] = matrix[i][1];
        }

        // actualizarea tabloului conform formulei
        // se parcurg toate elementele matricei
        for (int i = 2; i <= n; i++)
        {
            for (int j = 2; j <= n; j++)
            {
                // elementul este valid, are valoarea 1,
                // deci poate reprezenta coltul din dreapta jos
                if (matrix[i][j])
                {
                    // se actualizeaza tabloul dp, cat si tabloul solutiei finale
                    dp[i][j] = std::min(dp[i - 1][j - 1],
                                        std::min(dp[i - 1][j], dp[i][j - 1])) + 1;
                    solution[dp[i][j]]++;
                }
                else
                {
                    // elementul are valoarea 0,
                    // deci nu se mai poate forma un patrat
                    dp[i][j] = 0;
                }
            }
        }
    }

    void print_output()
    {
        // la final dorim sa afisam totalul de submatrice in ordinea dimensiunii
        // se va tine cont de faptul ca matricele de dimensiune mai mare
        // se pot sparge in submatrci de dimensiune mai mica
        for (int i = 1; i <= n; i++)
        {
            // la solutia curenta se vor adauga numarul submatricelor
            // ce au dimensiunea mai mare sau egala cu i x i
            int sol = 0;
            for (int j = i; j <= n; j++)
            {
                sol += solution[j];
            }
            std::cout << sol << "\n";
        }
    }
};

int main()
{
    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("custi.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    std::ofstream fout("custi.out");
    std::cout.rdbuf(fout.rdbuf()); //save and redirect

    // aici este rezolvarea propriu-zisa
    Task *task = new Task();
    task->solve();
    delete task;

    // restore pentru cin si cout
    std::cin.rdbuf(cin_buff);
    std::cout.rdbuf(cout_buff);

    // obs. nu e nevoie sa inchid fisierele
    // cand se apeleaza destructorii pentru fin si fout se vor inchide1
    return 0;
}

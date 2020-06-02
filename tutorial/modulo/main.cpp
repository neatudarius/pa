// Copyright 2020 Nicolae Mara-Ioana <maraioana9967@gmail.com>

// Coeficient binomial - Binomial Coefficient

// primind doi parametri n si k sa se calculeze coeficientul binomial C(n, k)
// Formula: C(n, k) = n! / ((n - k)! * k!), dupa simplificari:
// (n * (n - 1) * ... * (n - k + 1)) / (k * (k - 1) * ... * 1)

#include <bits/stdc++.h>

// se alege un numar prim pentru a calcula inversul modular cu usurinta
#define MOD 10007

class Task {
 public:
    void solve() {
        read_input();
        get_result();
        print_output();
    }

 private:
    int n, k, result;
    void read_input() { 
        std::cin >> n >> k;
    }

    // intrucat rezultatul poate ajunge la o valoare ce nu poate fi reprezentata
    // pe 32 de biti, se va calcula restul rezultatului cautat la numarul MOD
    int get_result() {
        result = 1;
        if (k > n - k) {
            k = n - k; // deoarece C(n, k) = C(n, n-k)
        }

        // la fiecare pas de iteratie se retine restul
        // se calculeaza (n * (n - 1) * ... * (n - k + 1)) / (k * (k - 1) * ... * 1)
        for (int i = 0; i < k; i++) {
            // pentru numarator se utilizeaza formula de inmultire (a * b) % MOD
            result = (1LL * result * ((n - i) % MOD)) % MOD;
            // pentru numitor se utilizeaza formula de impartire (a / b) % MOD;
            // se va calcula inversul modular
            result = (1LL * result * fast_pow(i + 1, MOD - 2)) % MOD;
        }

        return result;  
    }

    // ridicare la putere in O(log exponent)
    // abordare recursiva => Divide et impera
    int fast_pow(int base, int exponent) {
		if (exponent == 1) {
			return base % MOD;
		}

		if (exponent == 0) {
			return 1;
		}

		if (exponent % 2 == 1) {
			return (1LL * base * fast_pow(base, exponent - 1)) % MOD;
		} else {
			int aux = fast_pow(base, exponent / 2);
			return (1LL * aux * aux) %  MOD;
		}
	}

    void print_output() {
        std::cout << result << "\n";
    }
};


int main() {
    // din cauza ca fac redirectari, salvez starea lui cin si cout
    auto cin_buff = std::cin.rdbuf();
    auto cout_buff = std::cout.rdbuf();

    // las liniile urmatoare daca citesc din fisier
    std::ifstream fin("binom.in");
    std::cin.rdbuf(fin.rdbuf()); // save and redirect

    // las liniile urmatoare daca afisez in fisier
    std::ofstream fout("binom.out");
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

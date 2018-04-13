/*
    skel_graph - RoyFloyd - O(n^3)
    (Sau cu notatia din lab O(V^3))
    Închiderea tranzitivă a grafului asociat;
    închiderea tranzitivă poate fi reprezentată ca matricea care descrie,
    pentru fiecare nod în parte, care sunt nodurile accesibile din acest nod.

    daca consideram ca distanta de la i la j este numarul de muchii traversate,
    atunci pornim intial cu d[i][j] = 1, daca exista muchia i->j
    d[i][i] = 0 (evident)
    d[i][j] = oo, daca i != j si nu exista muchia i->j (inseamna ca nu am
   descoperit inca drum de la i la j)

    in final d[i][j] = numarul minim de muchii de parcurs de la i ca sa ajungem
   la j
    daca d[i][j] < oo, atunci exista drum de lungime d[i][j] de la i la j,
    deci clar ca j este accesibil din i

    (daca nu ne intereseaza efectiv valorile drumurilor, putem lucra doar cu 0
   si 1 (exista sau nu exista drum))
*/

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#define NMAX 109     // ATENTIE la cat e in problema curenta !!!
#define oo (1 << 20) // ATENTIE la cat e in problema curenta !!!
using namespace std;

int n, m;
int d[NMAX][NMAX];

void read_input() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      d[i][j] = oo;
    }

    d[i][i] = 0;
  }
  for (int i = 1; i <= m; ++i) {
    int x, y; // x -> y
    cin >> x >> y;

    d[x][y] = 1; // exista drum de lungime "o muchie" de la x la y
    d[y][x] = 1; // presupun ca e neorientat
  }
}

void RoyFloyd() {
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (i != j && d[i][k] + d[k][j] < d[i][j]) {
          d[i][j] = d[i][k] + d[k][j];
        }
      }
    }
  }
}

// afisez vectori si tot ce mai trebuie
void print_output() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      printf("%4d ", (d[i][j] != oo ? d[i][j] : -1));
    }
    printf("\n");
  }
}

// in solve scriu tot ce tine de rezolvare - e ca un main
void solve() {
  cout << "initial: 1 => drum de lungime 1 de la i la j; 0 pt muchie i,i; -1 "
          "nu exista drum de la i la j\n";
  print_output();

  RoyFloyd();

  cout << "final: x => drum de lungime x de la i la j; 0 pt muchie i,i; -1 nu "
          "exista drum de la i la j\n";
  print_output();
}

// puteti pastra main-ul mereu cum e acum
int main() {
  // las linia urmatoare daca citesc din fisier
  assert(freopen("royfloyd_inchidere.in", "r", stdin) != NULL);

  // las linia urmatoare daca afisez in fisier
  assert(freopen("royfloyd_inchidere.out", "w", stdout) != NULL);

  read_input();
  solve();

  return 0;
}

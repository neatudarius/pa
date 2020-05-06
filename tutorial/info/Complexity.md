# Complexitati cheatsheet

## Clase de complexitati

- Pentru un procesor modern, in **C/C++**, numarul de instructiuni executate in $1s$ este in $[10^6,  10^7]$.
- Pentru **Java** timpul de executie este cel putin dublu, de obicei.

|Ordin de marime| Complexitate|
|-|-|
|<img width=300/>| <img width=200/>|
|$[10^{12}, 10^{18}]$| $O(\log n)$ |
|$[10^7, 10^{12}]$ | $O(\sqrt{n})$ |
|$[10^6 , 10^7]$ | $O(n)$ |
|$10^5$ | $O(n * \log n)$|
|$10^4$ | $O(n  * \sqrt{n})$ |
|$10^3$ | $O(n^2)$ |
|$10^2$ | $O(n^3)$ |
|10 | $O(n!)$ / $O(2^n)$ / $O(3^n)$ |
| 15 | $O(n!)$ / $O(2^n)$ |
| 30 - 40 (par) | $O((\frac{n}{2})!)$ / $O(2 ^ {\frac{n}{2}})$ (Meet in the middle) |

**Ideal: O(1)**

# Algoritmi studiati

| Clasa de complexitate| Algoritmi |
|-|-|
|<img width=300/>| <img width=200/>|
|$O(1)$ | - raspunsuri directe (par, impar, etc.)<br> - formule simple (ex: $n *\frac{n - 1}{2}$)|
|$O(\log{n})$ | - algoritmi de tipul DEI: Cautare Binara (normala, lower bound, upper bound), exponentiere logaritimica, exponentiere logaritmica pe matrice (optimizarea de la DP) <br> - cmmdc, cmmmc |
|$O(\sqrt{n})$| - factorizarea numerelor<br>- verificare ca un numar e prim |
|$O(n)$ = liniar| - parcurgere de vector<br>- recurente liniare la DP: SSM, numarare<br>- greedy (ex: pe vector) |
|$O(n * \log n)$| - sortari<br>- n cautari binare pe vector deja sortat<br>- n = parcurgerea unui sir de n elemente, log n = fiecarui element i se aplica log n operatii (ex: push/pop heap, compute power) |
|$O(n^2)$ <br> $O(n * m)$| - recurente la DP mai complexe (ex: SCMAX)<br>- operatii pe matrice<br>- BFS pe matrice |
|$O(n^3)$| - recurente DP de tip PODM |
|||
|**Backtracking**|
|$O(2^n)$|- submultimile unei multimi cu n elemente<br>- combinatii in probleme de tipul: mereu se poate face stanga sau dreapta, care este numarul total de posibilitati? |
|$O(C(n, k))$| - probleme care se reduc la generarea combinarilor|
|$O(A(n, k))$|- probleme care se reduc la generarea aranjamentelor|
|$O(n!)$|- probleme care se reduc la generarea permutarilor|
|||
|**Grafuri**|
|$O(n + m)$ = liniar| - DFS/BFS<br>- orice algoritm bazat pe 1 / k parcurgeri: <br> &nbsp;&nbsp;&nbsp;&nbsp; $*$ ciclu in graf <br> &nbsp;&nbsp;&nbsp;&nbsp; $*$ TopSort<br> &nbsp;&nbsp;&nbsp;&nbsp; $*$ CC <br> &nbsp;&nbsp;&nbsp;&nbsp; $*$ CTC (SCC) <br> &nbsp;&nbsp;&nbsp;&nbsp; $*$ BCC / CV / CE <br> &nbsp;&nbsp;&nbsp;&nbsp; $*$ distante pe grafuri particulare (arbore, DAG, costuri egale / fara cost)
|$O(m * \log n)$|- Dijkstra |
|$O(m * \log m)$| - Kruskal / Prim |
|$O(n * \log (n + m))$| - sortarea nodurilor dupa un criteriu, apoi o parcurgere a grafului|
|$O(m * \log (m + n))$| - sortarea muchiilor dupa un criteriu, apoi o parcurgere a grafului|
|$O(m * n)$<br>$O(n^2)$<br>$O(m^2)$| - BellmanFord <br> - n parcurgeri pe un graf ($n$ * O(DFS/BFS))|
|O($n^3$)|- RoyFloyd (grafuri dense)|
|$O(n * m * \log n)$| - Johnson (grafuri rare)|
|$O(n * m^2)$| - Edmonds-Karp|
|$O(b^d)$|- A* <br>- Minimax|

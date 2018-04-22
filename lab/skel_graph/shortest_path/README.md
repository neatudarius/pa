### shortest_path(s)

#### context

  * shortest_path(s) = drumul/drumurile de lungime/cost minim de la o sursa/mai multe surse
  					   la o destinatie/mai multe destinatii

#### discutie
  * `Arbore`
    * Drum in arbore (drumul de la x la y este `unic`).
    * Solutie: `DFS/BFS`
    * `Complexitate`:
      * `T = O(n + m)`
      * `S = O(n)` (recursivitate)
  * `Graf fara costuri`:
    * Drum in `graf fara costuri` / graf in care costurile tuturor muchiile sunt egale.
    * Solutie: `BFS`
    * `Complexitate`:
      * `T = O(n + m)`
      * `S = O(n)` (coada)
  * `DAG`
    * Daca avem un `DAG` (`Directed acyclic graph`), atunci parcurgem graful in ordinea data de sortarea topologica.
    * Solutie: `topsort` (DFS/BFS)
    * `Complexitate`:
      * `T = O(n + m)` (DFS/BFS)
      * `S = O(n)` (recursiviate/coada)
  * `Sursa unica` si `graf cu costuri pozitive`
    * Solutie: `Dijkstra`
    * Drum de la `o sursa` la `toate celelalte noduri`. Graful trebuie sa aiba `costuri pozive`.
  	* `Complexitate`: 
  	  * `T = O(m * log n)` (binary heap)
  	    * Se poate obtine `T = O(n * log n  + m)` daca se foloseste un `heap fibonacci` (nu implementam asa ceva). 
  	  * `S = O(n)` (heap)
  * `Sursa unica` si `graf fara cicluri de cost negativ`
    * Solutie: `Bellman-Ford`
    * Drum de la `o sursa` la `toate celelalte noduri`. Graful trebuie sa aiba `costuri pozive`.
    * `Complexitate`:
      * `T = O(n * m)`
      * `S = O(n)` (coada)
  * `Surse multiple` si `destinatii multiple` in `graf dens` cu `costuri oarecare`, DAR `fara cicluri negative`.
    * Drum de la oricare nod din graf la oricare alt nod din graf.
    * Soltutie:`Roy-Floyd`:
    * `Complexitate`:
      * `T = O(n^3)`
      * `S = O(n^2)` (d - distances) 
  * `Surse multiple` si `destinatii multiple` in `graf rar`
    * Drum de la oricare nod din graf la oricare alt nod din graf.
    * Solutie: `Johnson`
    * `Complexitate`:
      * `T = O(n * m  * log n + n * m)` (binary heap)
      	* `T = O(n^2 * log n + n * m)` (fibonacci heap)
      	  * Aceasta implementare bate RoyFlod pe grafuri `rare`.
      * `S = O(n ^ 2)` (d - distances)

Toti algoritmii au ceva in comun:
  * `d[i]` sau `d[i][j]` = distanta minima de la `SURSA` la `UN NOD`
    * pentru algoritmii cu o singura sursa: `d[i]` = distanta minima de la de `source` la nodul `i`
    * pentru algoritmii cu surse multiple:  `d[i][j]` = distanta minima de la nodul `i` la nodul `j`
  * `p[i]` sau `p[i][j]` = parintele `NODULUI` pe drumul minim de la `SURSA` la `NOD`
    * pentru algoritmii cu o singura sursa: `p[i]` = parintele lui `i` de pe drumul minim de la `source` la nodul `i`
    * pentru algoritmii cu surse multiple:  `p[i][j]` = parintele lui `j` de pe drumul minim de la nodul `i` la nodul `j`
  
#### infoarena
 - [dfs](https://infoarena.ro/problema/dfs)
 - [bfs](https://infoarena.ro/problema/bfs)
 - [sortaret](https://infoarena.ro/problema/sortaret)
 - [dijkstra](https://infoarena.ro/problema/dijkstra)
 - [bellmanford](https://infoarena.ro/problema/bellmanford)
 - [royfloyd](https://infoarena.ro/problema/royfloyd)


#### lab

Toate pozele se gasesc in `_lab`.

TODO: poze

### spanning tree

#### context

  * spanning tree               = arbore partial / arbore de acoperire
  * minimum spanning tree (MST) = arbore partial de cost minim (APM) / arbore minim de acoperire (AMA)

Vom folosi notatia `APM`.

#### discutie
  * `arbore oarecare`
    * Graf in care nu avem costuri, atunci orice arbore partial este bun.
    * Solutie: `arbore de parcurgere DFS/BFS`
    * Complexitate:
      * `T = O(n + m)`
      * `S = O(n)` (recursivitate/coada)

  * `arbore partial de cost minim` (APM)
    * Graf in care avem costuri. Vrem (un) arbore partial cu cost minim.
    * Solutii: `Kruskal / Prim`
    * `Kruskal`
      * Determina un APM `sortand` muchiile crescator dupa cost. Foloseste
      structura de date `paduri de multimi disjuncte` (disjoint set). Initial
      considera fiecare nod un arbore. Reuneste cate 2 arbori pana cand ramane
      un singur arbore.
      * Complexitate:
      	* `T = O(m log m)` (sortare)
      	  * Complet este `m log m + m log* n`. `log* n` (iterated logarithm)
      	  este dat de operatiile pe disjoint set si este mai mic decat `log n`.
      	* `S = O(n)` (disjoint set)
    * `Prim`
      * Determina un APM prin relaxari succesive de muchii. Porneste cu un arbore
      pe care il extinde pana cuprinde toate nodurile din graf.
      * Complexitate:
        * `T = O(m log n)`
        * `S = O(n)` (heap)


#### infoarena
 - [apm](https://infoarena.ro/problema/apm)


#### lab
Toate pozele se gasesc in `_lab`.

TODO: poze
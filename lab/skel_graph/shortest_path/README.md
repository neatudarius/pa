### shortest_path(s)

  * shortest_path(s) = drumul de lungime/cost minim de la o sursa/mai multe surse
  					   la o destinatie/mai multe destinatii



Discutie:
  * `DFS/BFS`
    * Drum in arbore (drumul de la x la y este unic).
  * `BFS`:
    * Drum in graf fara costuri / graf in care costurile tuturor muchiile sunt egale.
  * `Dijkstra`
    * Drum de la `o sursa` la `toate celelalte noduri`. Graful trebuie sa aiba `costuri pozive`.
  	* `Complexitate`: 
  	  * `T = O(m log n)`
  * `Bellman-Ford`:
    * Drum de la `o sursa` la `toate celelalte noduri`. Graful trebuie sa aiba `costuri pozive`.
    * `Complexitate`:
      * `T = O(m * n)`
  * `Roy-Floyd`:
    * Drum de la oricare nod din graf la oricare alt nod din graf.
    * `Complexitate`:
      * `T = O(n ^3)` 
  * `Johnson`
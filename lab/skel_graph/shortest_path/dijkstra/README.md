### Dijkstra

#### descriere
  * `Sursa unica` si `graf cu costuri pozitive`
    * Solutie: `Dijkstra`
    * Drum de la `o sursa` la `toate celelalte noduri`. Graful trebuie sa aiba `costuri pozive`.
  	* `Complexitate`: 
  	  * `T = O(m * log n)` (binary heap)
  	    * Se poate obtine `T = O(n * log n  + m)` daca se foloseste un `heap fibonacci` (nu implementam asa ceva). 
  	  * `S = O(n)` (heap)
  	  
#### lab
 <img src="_example.png" height="100%" width="100%"/>

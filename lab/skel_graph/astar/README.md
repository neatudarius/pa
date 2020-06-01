### A*

#### descriere

 In principiu, orice algoritm pe grafuri discutat in laboratoarele si cursurile anterioare poate fi utilizat pentru gasirea solutiei unei probleme astfel definite. In practica, insa, multi dintre acesti algoritmi nu sunt utilizati in acest context, fie pentru ca exploreaza mult prea multe noduri, fie pentru ca nu garanteaza o solutie pentru grafuri definite implicit (prin stare initiala si functie de expandare). 

 

  * Algoritm euristic pentru determinarea distantei minime
    * Solutie: `A* `


    
  	* `Complexitate (depinde de tipul euristicii)`:

      * `daca |h(n) - h*(n)| ≤ O(logh*(n)), atunci si exista un singur nod destinatie, atunci avem o complexitate O(n^k) - adica polinomiala.`

      * `daca nu e indeplinita conditia |h(n) - h*(n)| ≤ O(logh*(n)), atunci complexitatea este O(b^d), unde b = factorul de ramificare si d inaltimea arborelui. ` 

  	  
  	* [Exemplu wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm)

``` cpp
// s_i      = stare initiala
// expand   = functie de expandare care returneaza toti succesorii unei stari
// h        = functie euristica (h(n) = aproximarea drumului minim de la n la o destinatie)
// is_goal  = is_goal(n) returneaza true daca n este o destinatie (stare goal/finala)
// w        = w[x][y] reprezinta costul muchiei directe intre starile x si y
A*(s_i, expand, h, is_goal)
	//initializari
    closed ← {}     // multimea nodurilor expandate
    open   ← { }    // multimea nodurilor in curs de explorare
 
    // pentru fiecare stare s
    for each s
        g(s) ← Infinity // initializare distante
        π(s) ← Infinity // initializare parinti
 
    // pentru s_i avem distanta 0 si parinte NULL
    g(s_i) ← 0
    π(s_i) ← NULL
    open   ← open U { s_i }
 
    // parcurgerea continua cat timp avem noduri in open
    while !open.empty()
        // extrage nodul s cu f(s) minim
        s ← get_best(open) with minimum f(s) = g(s) + h(s)
        open ← open - { s }
 
        // daca s este stare finala
        if is_goal(s) 
            // reconstituie drumul de la s la s_i
            return build_path(s, s_i)
 
        // daca nodul nu este deja expandat 
        if s not in closed
            // il adaug in closed
            closed ← closed U { s }
 
            // pentru fiecare copil c al starii s
            for each c in expand(s)
                if g(s) + w[s][c] < g(c)
                    // actualizez distanta si parintele
                    g(c) ← g(s) + w[s][c]
                    π(c) ← s
 
                    if not (c in closed U open) // daca nodul c nu a mai fost intalnit
                        open   ← open U { c }   // c intra in open
                    else if c in closed         // daca nodul c a mai fost expandat
                        closed ← closed – { c } // c trece din closed in open
                        open   ← open U { c }
 
    // nu a fost gasita o cale de la s_i la o stare goal s
    return failure

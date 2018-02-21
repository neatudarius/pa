# C++ tutorial
Responsabil: [Darius Neațu](neatudarius@gmail.com)

# Intro
## C++
### De ce C++? 
La PA dorim sa avem o implementare cat mai scurta din mai multe motive:
  - dorim sa avem cat mai mult timp alocat pentru etapa de gandire/cautare algoritm, iar implementarea sa fie scurta
  - daca implementare este scurta, atunci si debug faci mai usor sau ai sanse mai mari sa nu faci prostii din prima
  - STL este mai prietenos decat implementare de SD din Java
  - ai mai mult control
  - nu trebuie sa stim C++, ci doar cateva concepte de baza
  - nu trebuie sa stim tot STL, ci doar o (mica) parte din el
 
 ### De ce C++11?
   - raspunsul scurt este: NU e necesar
   - pentru compilare trebuie sa pui `-std=c++11` ca argument a lui g++
   - mentionez cateva features care iti pot face viata mai usoara
     - putem insa sa ne facem codul mai scurt/clar prin folosirea lui auto :D
		``` cpp
		    map<int, int> :: iterator f() {...}
		    // ...
		    auto it = f(); // declaratia asta este mai scurta
		                   // poate am uitat ce tip returneaza f  
		                   // (adica stiu ce este - un iterator, 
		                   // dar nu mai stiu cum se scrie)

		     map<int, int> :: iterator it  = f(); //  daca nu folosesc auto trebuie sa fac asa
		```
     - probabil ca la PA nu se va ajunge pana aici, dar pentru voi e bine sa stiti, de exemplu, ca in C++11 exista si unordered_map. 
        - functioneaza fix ca map (interfata)
        - map tine cheile sortate
           - in spate implementarea foloseste o structura arborescenta 
           - daca iterez un map obtin cheile sortate
           - pentru ca mentine aceasta proprietate, operatiile de insert/delete/find au $O(log n)$   
        - unordered_map nu tine cheile sortate 
          - chiar este un hashtable
          - daca iterez un unordered_map cheile NU sunt sortate
          - pentru ca nu se chinuie sa tina cheile sortate,    operatiile de insert/delete/find au $O(1)$ (amortizat)   

## skel
Recomandarea este sa nu folositi schelet.
  - invatati sa scrieti voi singuri de la 0
     -  cel putin la primele 6 laboratoare de PA, codul e foarte foarte scurt pentru o problema. Deci poate chiar este mai complicat sa te uiti in schelet si sa il intelegi decat sa scrii tu alea 10 linii :D.
     - ca sa sprijin asta dau un exemplu: citire & stocarea inputului in forma potrivita face parte din intelegerea problemei!
       - daca in schelet iti da un map cu cheie string si valoare o lista de int-uri, poate esti tentat sa nu te intrebi daca chiar asa e bine sa il stochezi
       - probabil tot la aceeasi declaratie si acelasi for la citire vei ajunge, dar daca il vei scrie tu nu exista nimic in acea sursa pe care nu il intelegi si din prima excluzi posibilitatea de a avea buguri/a nu sti sa faci ceva pentru ca responsabilul de schelet a gandit cumva si tu voiai sa faci in alt fel (perfect valid)
   - vedeti ca insist pe ideea de incercati sa faceti voi ca sa intelegeti mai bine! Deci ar putea fi si lucruri irelevante in unele probleme. 
     - Ex. la minimax, probabil va fi o problema cu un joc complex, in care vom scrie un cod foarte lung (e o exceptie). Acolo, daca scheletul va fi usor de inteles, evident ca este ok sa il folosim si sa implementam doar algoritmul.
     - Pentru chestiile simple insa, citirea inputului & stocarea in forma potrivita chiar va ajuta sa intelegeti
    - puteti avea insa o sursa proprie, un skelet minimal pe care il puteti folosi oricand; este un exemplu mai jos

### Standard skel
``` cpp
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
	freopen("gigel.in",  "r", stdin);   // daca las linia asta citesc din fisier
    freopen("gigel.out", "w", stdout);  // daca las linia asta afisez in fisier
    
    // acum pot folosi cin si cout sa citesc/afisez din/in fisier daca am lasat liniile
    // de mai sus decomentate
    
	cout << "pwp de la Gigel\n"; // aici am scris un mesaj in gigel.out

	return 0;
}
```
### Fancy skel :D
``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("gigel.in",  "r", stdin);   // daca las linia asta citesc din fisier
    freopen("gigel.out", "w", stdout);  // daca las linia asta afisez in fisier
    
    // acum pot folosi cin si cout sa citesc/afisez din/in fisier daca am lasat liniile
    // de mai sus decomentate
    
	cout << "pwp de la Gigel\n"; // aici am scris un mesaj in gigel.out

	return 0;
}
```          
## Makefile
Avand in vedere cele spuse mai sus, puteti sa faceti mereu un folder pentru fiecare problema (cel putin la laborator, unde recomand sa nu folositi schelet, ca sa invatati voi sa faceti).

Puteti salva urmatorul Makefile undeva in `~/utils/MakefileCpp`. Rulati comanda `cp ~/utils/MakefileCpp ./Makefile` sa il copiati unde doriti.

### Standard Makefile
``` bash
# doar linia urmatoare e nevoie sa o modificati cu sursa pe care o compilati
SRC = skel.cpp

# configurari g++
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lm

# fisiere obiect si executabile care vor fi  generate
OBJ = $(SRC:.cpp=.o)   # OBJ = inlocuiteste extensia .cpp cu .o
EXE = $(SRC:.cpp=.exe) # OBJ = inlocuiteste extensia .cpp cu .exe


build: $(SRC) 
	$(CC) $(CFLAGS) $^ -o $(EXE) $(LDFLAGS)


run: build
	./$(EXE)


.PHONY: clean
clean:
	rm -f *.o *.exe ```

# class vs struct la PA
 
# STL

## IO
### iostream
### fstream
### streams vs libc
### examples
### std vs file
### parsare
## Containters
### std::pair
``` cpp
#include <utility>
```

### std::tuple
``` cpp
#include <utility>
```
### std::vector
cppreference: [std::vector](http://en.cppreference.com/w/cpp/container/vector)
``` cpp
#include <vector>
```


### std::stack
### std::queue
### std::set
### std::map
### std::priority_queue

## Standard algorithms
``` cpp
#include <algorithm>
```

### basic (non-sequence)
#### std::min / std::max

### sorting
#### std::sort
#### std::nth_elementh

### searching
#### std::find
#### std::lower_bound
#### std::upper_bound
#### std::min_element/std::max_element

### modifying sequence
#### std::reverse
#### std::remove
#### std::fill

# Recomandari & exemple
Pe pagina fiecarei functii / structuri de date sunt niste exemple minimale.
http://www.cplusplus.com/
http://en.cppreference.com/w/

<!--stackedit_data:
eyJoaXN0b3J5IjpbMTAzMDYwMDc4Ml19
-->
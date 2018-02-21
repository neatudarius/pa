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
   - (probabil) ca n

    
## Makefile

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
eyJoaXN0b3J5IjpbLTE2Nzc3MDk3MjhdfQ==
-->
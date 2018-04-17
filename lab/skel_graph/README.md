# skel_graph


### descriere
Algoritmi pe grafuri, pusi pe categorii.

### structura
Pentru un algoritm X, repo-ul pune la dispozitie mai multe fisiere plasate undeva la pathul `.../X`.
 - `main.cpp`
   - contine implementarea propriu-zisa a algoritmului
   - in funcia `main` se poate observa ca:
      * se citeste implicit dintr-un fisier de intrare (de obicei are extensia `.in`)
      * se afiseaza implicit la stdout
      * se poate citi se la stdin/afisa la stdout prin comentarea/decomentarea celor 2 linii indicate
 - `Makefile`
   - `make build`
   - `make run`
      * compileaza sursa main.cpp si o ruleaza. Aceasta regula are ca scop rularea unui exemplu. De exemplu, puteti sa faceti asta imediat inainte de a citi codul, pentru a verifica ca ati inteles ce doreste algoritmul. Din acest motiv, output-ul este afisat implicit la stdout.
 - `in` sau `algorithm.in`
   - fisierul de intrare care poate fi folosit pentru testare
   - implicit acesta are contintul din `_example.in`
 - `_example.in` si `_example.png`
   - fisierul cu extensia `in` contine un exemplu pe care nu trebuie sa il modificati. Este primul exemplu pe care ar trebui sa il intelegi la algoritmul respectiv.
   - fisierul cu extensia `png` contine graful din `_example.in` desenat, astfel incat sa va fie usor sa intelegeti inputul si sa vedeti daca outputul corespunde cu asteptarile.
   - in caz ca ati modificat `algorithm.in`, puteti rula comanda `cp _example.in algorithm.in` ca sa faceti restore la exemplu si sa il rulati 

#### recomandari
 - clonati repoul
   - se poate clona direct cu `git clone https://github.com/neatudarius/pa.git`
   - se poate clona, daca aveti git & ssh keys configurate cu `git clone git@github.com:neatudarius/pa.git`. Pentru colaborare, trebuie a doua varianta
   - clonarea se face o singura data, de acum in colo veti lucra cu acest repo doar din folderul `pa` (rootul repoului)
 - actualizare continut
   - deoarece se vor face modificari saptamanal (uneori zilnic), prima grija pe care trebuie sa o aveti atunci cand incepeti sa lucrati/sa intelegeti algoritmul X, este sa va asigurati ca aveti ultima versiune a lui
   - `git pull` va aduce ultima versiune de pe site
 - deschidere repo in `Sublime 3`
   - in radacina repoului se ruleaza comanda `subl .`
   - se observa ca a deschid tot repoul ca pe un folder
   - partea misto este ca Sublime 3 iti poate deschide si pozele. In acest fel, poti accesa orice resursa ofera acest repo prin intermediul aceluiasi tool.
   - un tutorial de instalare Sublime se gaseste in categoria colaborare
	

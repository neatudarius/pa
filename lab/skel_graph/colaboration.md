### colaborare
 - Toate sursele vor fi facute dupa `template.cpp`. 
 - Sursa finala incarcata trebuie sa fie sub forma de tutorial: `citeste din fisier` si `afiseaza pe ecran`
un exemplu de rezultat. Totul se desfasoara prin comanda `make run`
 - Se va folosi un `Makefile` universal. Se va compila cu `C++11` folosind `gcc-7.2`.
 - Sursa se numeste `main.cpp`, fisierele de intrare/iesire sunt de forma `algorithm.in`/`algorithm.out`.
 - Fiecare algoritm clasic pe grafuri trebuie sa fie insotit de fisierele `_example.in` / `_example.png`. In fisierul in se pune un exemlu relevant care dorim sa nu se schimbe. In fisierul png vom avea desenat graful corespunzator exemplui. Pentru desenare se foloseste [graph_editor](https://csacademy.com/app/graph_editor/).
 - Se va testa pe infoarena/leetcode/hackerrank (unde se poate - speram ca se poate mereu :D).
 - Se vor folosi toolurile mentionate in `tools.md`.

### git
#### setup
 - generare key ssh
    - se va urma acest [tutorial](https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/)
 - clonare
   ```
   git clone git@github.com:neatudarius/pa.git
   ```
#### contribution
 - 1. update
   ```
   git checkout master
   git pull
   ```
 - 2. create own branch
   ```
   git checkout -b my_brach
   ```
   (please use a real name!)
 - 3. change files(s) using editors (e.g. Sublime 3)
 - 4. test changes
 - 5. add to git
   ```
   git add file1 file 2 ...
   ```
 - 6. commit (give a pretty name to this change - PLEASE USE ENGLISH in commits)
   ```
   git commit -m "this is a dummy commit name
   ```
 - 7. push
   ```
   git push origin my_branch
   ```
 - 8. repeat 3-7 until you finish  your job
 - 9. make a pull request from browser
   - go to `https://github.com/neatudarius/pa`
   - click on `New pull request`
   - base: `master`
   - compare: `my_branch`
   - on the right select for both reviewers and assignees as many people as possible (at least Darius)
   - in `Leave a comment` box try to explain with bullets what changes you did (see previous pull requests for examples)
   - click on `Create pull requeste`
 - 10. reviews
 - 11. issues
   - if issues are reported, fix them (execute 3-8)
   - any new commit in `my_branch` will be automatically appended to current pull request
 - 12. accepted
   - finally your PR is accepted
   - on the PR URL go down
   - click on `SQUASH and MERGE` (to see this option click on arrow near green `MERGE`)
   - fill the comment with the same message as `Leave comment message` (the one from top)
   - `MERGE`
 - 13. grab a beer, all changes are now in master
   ```
   git checkout master
   git pull
   ```

Rover-ul Curiosity, trimis pe Marte pentru a explora planeta, a facut o descoperire interesanta.
El a gasit o carte, demonstrand astfel ca exista extraterestri. In urma analizelor amanuntite, cercetatorii
au ajuns la concluzia ca limbajul extraterestru e ceva mai special.

Acesta contine M simboluri: s1, s2, … sm si are K restrictii. O restrictie este o pereche de 2 simboluri (si, sj), 
semnificand faptul ca simbolul sj nu se poate afla imediat dupa simbolul si intr-un cuvant (de exemplu, pentru 
restrictia (a, b), nu putem avea cuvantul ab, dar cuvintele acb si ba sunt permise).

Orice cuvant format folosind cele M simboluri si care respecta toate cele K restrictii
este un cuvant valid. Un simbol poate aparea de oricate ori intr-un cuvant.

Cerinta: Dandu-se un numar intreg N, cercetatorii se intreaba care este numarul de cuvinte de lungime N din limbajul
extraterestru? Intrucat acest numar poate fi foarte mare, se cere afisarea lui modulo 666013.

Input Format

Se va citi de la stdin.

Pe prima linie, se vor afla 3 numere intregi, N, M si K.

Vor urma K linii, fiecare continand 2 numere intregi i si j, semnificand faptul ca exista restrictia (si, sj).

Constraints

1 ≤ N ≤ 1000
1 ≤ M ≤ 100
1 ≤ K ≤ M2

Pentru toate restrictiile (si, sj), avem 1 ≤ i, j ≤ M.

Operatia a modulo b reprezinta restul impartirii lui a la b.

Operatia modulo (notata si ca %) are urmatoarele proprietati:

(a+b)%c = ((a%c) + (b%c)) % c
(a*b)%c = ((a%c) * (b%c)) % c
Timp C++: 1s; Java: 2s

Output Format

Se va afisa la stdout.

Se va afisa un singur numar intreg, reprezentand numarul de cuvinte de lungime N modulo 666013.

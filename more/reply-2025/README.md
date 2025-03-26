### Come usare il `template.cpp`

Per creare una nuova soluzione al problema:
- crea un nuovo file (con il tuo nome), e.g. "fabio.cpp", dentro la cartella "csrc/"
- aggiungi `#include "template.cpp"` in cima al file
- crea una funzione `void solve() {   }` dentro il file (usando questa signature)
- dentro tutto il file puoi usare la funzione `deb()` per scrivere cose di debug, e.g. `deb("ciao", 123, 14.6, vector<int>{1,7,6,9})`
- dentro tutto il file puoi leggere la variabile `ctrl_c` per vedere se è stato mandato un Ctrl+C al programma (e in tal caso, devi chiudere il programma!)

### Comando da usare per compilare

Per compilare in modalità debug, in cui `deb()` funziona ma il programma è lento:

```sh
g++ -Wall -Wpedantic -Wextra -march=native -fsanitize=address -g -DDEBUG NOMEFILE.cpp -o NOMEFILE.out
```

In modalità release, in cui `deb()` è silenziato:

```sh
g++ -O3 -Wall -Wpedantic -Wextra -march=native NOMEFILE.cpp -o NOMEFILE.out
```

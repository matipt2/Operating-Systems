
Mateusz Ptasik


Katalog zawiera dwa programy w języku C. Do każdego kodu dodałem komentarze, ponadto wszystkie ćwiczenia postaram się po krótce opisać poniżej.


Ćwiczenie 2: Program ten wywołuje funkcję fork trzy razy po czym wypisuje identyfikatory dla procesu macierzystego, a poźniej procesów potomnych używając przy tym funkcji wait(). 

Dodatkowy program "identyfikatory": Program ten jest wywoływany przez główny program "cw2" w celu stworzenia procesów potomnych, używając przy tym funkcji execlp().

Przy n-krotnym wywołaniu funkcji fork-exec powstanie n-procesów.





Uruchamianie programów:

W katalogu znajduje się program Makefile, który ułatwia kompilowanie i uruchamianie programów. Można wpisać w terminalu komendę "make", która wyświetli możliwe warianty poleceń, lecz podam je również poniżej.

Aby make run-cw2 działał, należy wcześniej skompilować program "cw2.c" oraz "identyfikatory.c". W przeciwnym wypadku uruchamiając program "cw2" bez kompilacji programu "identyfikatory" wystąpi błąd: ERROR: No such file or directory.

Instrukcja:

make cw2  Kompiluje program cw2"
make all          Kompiluje wszystkie programy"
make run-all      Uruchamia wszystkie programy"
make run-cw2    Uruchamia program cw2"
make clean        Usuwa pliki *.o oraz *.x"
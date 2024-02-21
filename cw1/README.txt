
Mateusz Ptasik


Katalog zawiera pięć programów w języku C. Do każdego kodu dodałem komentarze, ponadto wszystkie ćwiczenia postaram się po krótce opisać poniżej.


Ćwiczenie 1a: Program ten wypisuje identyfikatory PID, PGID, UID, GID, PPID.

Ćwiczenie 1b: Program ten wywołuje funkcję fork trzy razy po czym wypisuje identyfikatory dla procesu macierzystego, a poźniej procesów potomnych używając przy tym funkcji wait(). 

Ćwiczenie 1c: Program ten wywołuje funkcję fork trzy razy po czym wypisuje identyfikatory dla procesu macierzystego, a poźniej procesów potomnych używając przy tym funkcji sleep(). 

Ćwiczenie 1d: Program ten wywołuje funkcję fork trzy razy po czym wypisuje identyfikatory dla procesu macierzystego, a poźniej procesów potomnych. Program używa także funkcji sleep() do opóźnienia działania procesów potomnych, co powoduje, że procesy potomne są tworzone z opóźnieniem.

Ćwiczenie 1e: Ten program wywołuje funkcje fork trzy razy,  wyświetla informacje o procesie macierzystym oraz każdym procesie potomnym, w tym jego PID, UID, GID, PPID i PGID. W każdej iteracji pętli for () funkcja setpgid () jest wywoływana, aby zmienić PGID procesu potomnego na PGID procesu macierzystego. Funkcja wait () jest również wywoływana w procesie macierzystym, aby oczekiwać na zakończenie procesu potomnego.


Uruchamianie programów:

W katalogu znajduje się program Makefile, który ułatwia kompilowanie i uruchamianie programów. Można wpisać w terminalu komendę "make", która wyświetli możliwe warianty poleceń, lecz podam je również poniżej.

Instrukcja:

make compile-a  Kompiluje program a
make compile-b  Kompiluje program b
make compile-c  Kompiluje program c
make compile-d  Kompiluje program d
make compile-e  Kompiluje program e
make all        Kompiluje wszystkie programy
make run-all    Uruchamia wszystkie programy
make run-a      Uruchamia program a
make run-b      Uruchamia program b
make run-c      Uruchamia program c
make run-d      Uruchamia program d
make run-e      Uruchamia program e
make clean      Usuwa pliki *.o oraz *.x

Przy n-krotnym wywołaniu funkcji fork() powstanie (2^n)-1 procesów.
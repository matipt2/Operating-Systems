Mateusz Ptasik


Katalog zawiera dwa programy w języku C i biblioteke do tworzenia, otwierania, uzyskiwania wartości, operowania, zamykania i usuwania semafora.
Do każdego kodu dodałem komentarze, ponadto ćwiczenie  po krótce opisałem poniżej.


Program przy pomocy semaforow nazwanych standardu POSIX przedstawia problem jednoczesnego korzystania z zasobu współdzielonego przez kilka procesów. Program glowny powiela procesy za pomoca fork i exec, inicjuje i usuwa semafor w odpowiednich miejscach za pomoca funkcji atexit. Na końcu porównywany jest wynik.



    Program sklada sie z czterech modulow: 
    1) powielacz.c 
    2) wykluczanie.c
    3) library.c
    4) library.h

W pliku MAKEFILE jako argumenty zostało podane PROCESY = 3 i SEKCJE = 2. 
W katalogu znajduje się program Makefile, który ułatwia kompilowanie i uruchamianie programów. Można wpisać w terminalu komendę "make", która wyświetli możliwe warianty poleceń.

Jak uruchomić programy:

Aby uruchomić program, należy wykonać komendę:

make run6

Aby wyczyścić zawartość katalogu:

make clean

Odpowiedź na pytanie z ćwiczenia ( "Sprawdzić, jaka będzie końcowa wartość numeru bez użycia sekcji krytycznej") : Wartość tego numeru będzie mniejsza od "normalnego" uruchomienia z powodu faktu antysynchronizacji.





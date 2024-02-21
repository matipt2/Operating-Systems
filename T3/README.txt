Mateusz Ptasik


Katalog zawiera trzy programy w języku C. Do każdego kodu dodałem komentarze, ponadto wszystkie ćwiczenia postaram się po krótce opisać poniżej.


Ćwiczenie 3a: Program, który ustawia obsługę sygnału na 3 sposoby zgodnie z opcją podaną jako argument wywołania programu, a następnie czeka na sygnał (funkcja pause()). Numer sygnału jest przekazywany jako argument wywołania programu przy czym proces wypisuje na ekranie swój PID, a funkcja do własnej obsługi sygnału wypisuje jego numer i nazwę.

Ćwiczenie 3b: Program uruchamia ćw 3a przy użyciu funkcji execlp w procesie potomnym i wysyła do niego sygnaly poprzez funkcję systemową kill z procesu macierzystego. 

Ćwiczenie 3c: Program tworzacy w procesie macierzystym proces potomny, który staje sie liderem nowej grupy procesów. Nastepnie w kilku jego procesach potomnych uruchamiany jest program do obsługi sygnałów. Pierwszy proces macierzysty wysyła sygnały do całej grupy procesów potomnych po uprzednim sprawdzeniu jej istnienia. Proces będący liderem grupy procesów ignoruje sygnały i czeka na zakończenie wszystkich swoich procesów potomnych i wypisuje ich status zakończenia zwracany przez funkcje wait.

W katalogu znajduje się program Makefile, który ułatwia kompilowanie i uruchamianie programów. Można wpisać w terminalu komendę "make", która wyświetli możliwe warianty poleceń.

Aby sprawdzić działanie pierwszego programu, należy wysłać sygnał o numerze 2 do procesu o numerze PID wyświetlonym przez program.

W pliku makefile uruchamiając run-cw3x gdzie x = [a,b,c] w przykładowych argumentach podałem mode 2 i signal 2.





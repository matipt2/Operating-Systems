Mateusz Ptasik


Katalog zawiera jeden program w języku C i dwa dodatkowe pliki tekstowe. Do kodu dodałem komentarze, ponadto ćwiczenie postaram się po krótce opisać poniżej.


Ćwiczenie 4: 
Ten program realizuje komunikację między dwoma procesami za pomocą potoków w systemie operacyjnym. Proces macierzysty odczytuje dane z pliku wejściowego, dzieli je na małe fragmenty (rozmiar CHUNK_SIZE) i przesyła je przez potok do procesu potomnego. Proces potomny odbiera te dane z potoku i zapisuje je do pliku wyjściowego. Przed przesłaniem i zapisaniem każdego fragmentu procesy odczekują losową liczbę sekund (do 5 sekund). Na końcu program otwiera plik wyjściowy i wypisuje jego zawartość na ekran. 


W katalogu znajduje się program Makefile, który ułatwia kompilowanie i uruchamianie programów. Można wpisać w terminalu komendę "make", która wyświetli możliwe warianty poleceń.








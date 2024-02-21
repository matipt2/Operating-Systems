#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <signal.h>
#include "biblioteka.h"
mqd_t serwer; //deskryptor kolejki serweru
char odKlienta[30]; //tablica do przechowywania dzialania podanego od klienta
void koniec_sygnal(int signal) 
{
	printf ("Ptrzymano sygnal przerwania, usuwanie kolejki\n");
	exit(EXIT_SUCCESS);
}
void koniec(void) 
{
	zamykanie(serwer);
}
void odczytdDanych(char* odKlienta) //odcytanie danych od klienta i informacja o bezpiecznym zamnieciu konsoli gdy wszytsko co podal klient zostalo zczytane
{
    if (scanf("%s", odKlienta) == EOF) //sprawdzanie czy odczytano calosc tego co klient nam przekazal wtedy bowiem nie moglibysmy zamknac konsoli
    {
        printf("Zakonczenie odczytywania od klienta. Bezpieczne zakmniecie konsoli jest teraz mozliwe\n");
        exit(EXIT_SUCCESS);
    }
}
int main () 
{
	sleep(1);

	if (signal (SIGINT,koniec_sygnal) == SIG_ERR) 
	{
		perror("SIGNAL ERROR");
		exit(EXIT_FAILURE);
	}
	if (atexit (koniec) != 0) 
	{
		perror("ATEXIT ERROR");
		_exit(EXIT_FAILURE);
	}
	mqd_t kolejkaOdp;//przechowuje deskryptor kolejki odbierajacej odp z serwera
	char kolejkaOdpN[10]; //przechowuje nazwe kolejki ktora odbiera odpowiedz z serwera
	sprintf (kolejkaOdpN, "/%d", getpid()); 
	serwer = otwieranie(nazwaKolejki, O_WRONLY); //otwarcie kolejki serwera do zapisu
	{
		printf ("Kolejka \"%s\" zostala otworzona. Jej deskryptor to %d\n",nazwaKolejki, serwer);
		pobieranieAtrb(serwer);
	}
	srand(time(NULL));
	while (1) 
	{ 
	  printf ("Podaj dzialanie\n");
	  odczytdDanych(odKlienta); //odczytywanie danych od klienta
	  char odKlientaiPid[40];//wiekszy o 10 bo potrzebujemy miejsce na pid klienta
          sprintf(odKlientaiPid, "%d %s", getpid(), odKlienta); //dopisanie pidu klienta do wiadomosci
	  wysylanie(serwer, odKlientaiPid, 3); //wysylanie danych od klienta do kolejki serwera. Dlugosc wiadomosci wynosi jeden jest to bowiem znak
	  printf ("Twoj PID to: %s zostalo wyslane do serwera \n", odKlientaiPid);
	  sleep (rand()%3);  
	  kolejkaOdp = tworzenie(kolejkaOdpN, O_RDONLY); //nowa kolejka aby klient mogl odebrac odp z serwera
	  odbieranie(kolejkaOdp, odKlientaiPid, NULL);
          printf ("Odpowiedz z serwera na twoje dzialanie to: %s\n", odKlientaiPid);
          zamykanie(kolejkaOdp);
          usuwanie(kolejkaOdpN);
	}
       zamykanie(serwer);
	return 0;
}

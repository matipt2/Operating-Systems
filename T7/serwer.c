#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <signal.h>
#include "biblioteka.h"
void koniec_sygnal(int signal, mqd_t mq_des) 
{
	printf ("Otrzymano sygnal przerwania, usuwanie kolejki\n");
	zamykanie(mq_des);
	exit(EXIT_SUCCESS);
}
void koniec(void) 
{
	usuwanie(nazwaKolejki);
}
int main () 
{	
	if (atexit (koniec) != 0) 
	{
		perror("ATEXIT ERROR");
		exit(EXIT_FAILURE);
	}
	srand(time(NULL));  
	mqd_t des; //deskryptor kolejki
	des = tworzenie(nazwaKolejki, O_RDONLY); 
	{
		pobieranieAtrb(des);//pobieranie atrybutow kolejki i wyswietlanie ich
	}

	if (signal(SIGINT, des) == SIG_ERR)
	{
		perror("SIGNAL ERROR");
		exit(EXIT_FAILURE);
	}


	while (1)
	{
	   char wiadomosc[30]; //zmienna do odbierania komunikatu z kolejki
	   char odpWynik[30];//bufor ktory przechowuje wynik ktory zostanienie wslany do klienty
	   int a,b,wynik,pidKlient;
	   char znak; 
	   odbieranie(des,wiadomosc , NULL); //odbieranie komuniaktu z kolejki
	   sscanf(wiadomosc, "%d %d%c%d", &pidKlient, &a, &znak, &b); //odczytanie danych zawartych w wiadomosci
	   printf ("Klient z numerem PID: %d - prosi o wykonanie dzialania %d %c %d\n",pidKlient,a,znak,b);
	   switch(znak)  //wykonywanie dzialan
           {
		 case '+':
		    wynik = a+ b;
		    sprintf (odpWynik, "%d", wynik);
		    break;
		case '-':
		    wynik = a - b;
		    sprintf (odpWynik, "%d", wynik);
		    break;
		case '*':
		    wynik = a * b;
		    sprintf (odpWynik, "%d", wynik);
		    break;
		case '/':
		    wynik = a / b;
		    sprintf (odpWynik, "%d", wynik);
		    break;  
		  default: 
		  sprintf (odpWynik, "Podano bledny znak.\n");
		  break;	
           }
		sleep (rand()%3);
		sprintf (wiadomosc, "/%d", pidKlient); //nazwa kolejki odpowiedzi
		mqd_t odpowiedz;//stworzenie zmiennej  doprzechowywania deskryptora kolejki  
		odpowiedz = otwieranie(wiadomosc, O_WRONLY); //otwarcie kolejki odpowiedzi klienta
		printf ("Rownanie %s jest wysylane do procesu %d\n", odpWynik, pidKlient);
		wysylanie(odpowiedz, odpWynik, 1); //wysylanie odp do klienta, 1 to dlugosc
		zamykanie(odpowiedz);
	}
	usuwanie(nazwaKolejki);
	return 0;
}

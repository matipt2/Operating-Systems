#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "biblioteka.h"



mqd_t tworzenie(const char *name, int oflag) // tworzenie kolejki komunikatow o podanej nazwie
{
	struct mq_attr attr; //przechowywanie argumentow kolejki
	attr.mq_msgsize = 30; //max dlugosc komunikatu
	attr.mq_maxmsg = 10; //max liczba komunikatow w kolejce
	mqd_t des = mq_open(name, O_CREAT | oflag, 0644, &attr); 
	//otwieranie albo tworzenie kolejki
	if (des == -1) 
	{
		perror ("MQ_ARR ERROR");
		exit (5);
	}
	return des; // zwracanie deskryptor kolejki
}

mqd_t otwieranie(const char *name, int oflag) // otwiera istniejaca kolejke
{
	mqd_t des;
	des = mq_open(name, oflag); //otwieranie
	if (des == -1) 
	{
		perror ("MQ_OPEN ERROR");
		exit (5);
	}
	
	return des; // zwracanie deskryptor kolejki
}
void zamykanie(mqd_t mq_des) //zamyka deskryptor kolejki komunikatow
{
	if (mq_close(mq_des) == -1) 
	{
		perror ("MQ_CLOSE ERROR");
		exit (5);
	}
}

void usuwanie(const char *name) //usuwa kolejke 
{
	if (mq_unlink(name) == -1) 
	{
		perror ("MQ_UNLINK ERRR");
		exit (5);
	}
}
void wysylanie(mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio) //wysylanie wiadomosci przez kolejke
{
	if (mq_send(mq_des, msg_ptr, 30, msg_prio) == -1) 
	{
		perror ("MQ_SEND ERROR");
		exit (5);
	}
}

void odbieranie(mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio) //odbieranie wiadomosci
{
	if (mq_receive(mq_des, msg_ptr,30, msg_prio) == -1) 
	{
		perror ("MQ_RECIVE ERROR");
		exit (5);
	}
}

void pobieranieAtrb(mqd_t mq_des) //pobiera atrybuty kolejki i wyswietla informacje o nich
{
	struct mq_attr attr;
	if (mq_getattr(mq_des, &attr) == -1) 
	{
		perror ("MQ_GETATTR ERROR");
		exit (5);
	}
        printf("Ilosc komunikatow atm: %ld \n", attr.mq_curmsgs);
        printf("Wielkosc MAX komunikatow: %ld \n", attr.mq_msgsize);
        printf("MAX komunikatow: %ld \n", attr.mq_maxmsg);
        printf("Flag - %ld \n", attr.mq_flags);
 
}

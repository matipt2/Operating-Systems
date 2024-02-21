DIR = `basename $(CURDIR)`
CFLAGS = -pthread -Wall -std=c99 -pedantic -O
LFLAGS = -pthread -Wall -std=c99 -pedantic -O

NAME1 = powielacz
NAME2 = wykluczanie




EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o

LIBS1  = $(LIB1).c



CO = gcc
LD = $(CO)
ARFLAGS = rsv
AR = ar



%.o: %.c
	$(CO) $(CFLAGS) -c $<
.PHONY: help
help:
	@echo "make run6  Uruchamia program numer 6"
	@echo "make clean        Usuwa pliki *.o oraz *.x"
SYNCHRONIZUJ = 1
LIB1 = library
.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run6
PROCESY= 3
SEKCJA = 2
WEWY = numer.txt
SEMAFOR = /sem_powielacz

run6: $(EXEC1) $(EXEC2)
	clear
	./$(EXEC1) $(EXEC2) $(PROCESY) $(SEKCJA) $(WEWY) $(SEMAFOR) $(SYNCHRONIZUJ)



.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

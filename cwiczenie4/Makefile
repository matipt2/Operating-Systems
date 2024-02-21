CFLAGS = -pedantic -Wall -std=c99
LFLAGS = -pedantic -Wall -std=c99
CO = gcc
LD = $(CO)

NAME1 = cw4




OBJS1 = $(NAME1).o


EXEC1 = $(NAME1).x



.PHONY: help
help:
	@echo "make $(NAME1)  Kompiluje program $(NAME1)"
	@echo "make run-$(NAME1)    Uruchamia program $(NAME1)"
	@echo "make clean        Usuwa pliki *.o oraz *.x"


.PHONY: $(NAME1) 

$(NAME1):
	$(CO) $(CFLAGS) -c $(NAME1).c -o $(OBJS1)
	$(LD) $(LFLAGS) -o $(EXEC1) $(OBJS1)


.PHONY: all
all: $(EXEC1)

$(EXEC1): $(OBJS1)
	$(LD) $(LFLAGS) -o $@ $^




%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run-$(EXEC1)


run-$(NAME1): $(EXEC1)
	./$(EXEC1) input.txt output.txt


	
	

.PHONY: clean
clean:
	@rm *.o *.x


CFLAGS = -pedantic -Wall -std=c99
LFLAGS = -pedantic -Wall -std=c99
CO = gcc
LD = $(CO)

NAME1 = cw2
NAME2 = identyfikatory


OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x


.PHONY: help
help:
	@echo "make $(NAME1)  Kompiluje program $(NAME1)"
	@echo "make $(NAME2)  Kompiluje program $(NAME2)"
	@echo "make all          Kompiluje wszystkie programy"
	@echo "make run-all      Uruchamia wszystkie programy"
	@echo "make run-$(NAME1)    Uruchamia program $(NAME1)"
	@echo "make clean        Usuwa pliki *.o oraz *.x"


.PHONY: $(NAME1) $(NAME2) 

$(NAME1):
	$(CO) $(CFLAGS) -c $(NAME1).c -o $(OBJS1)
	$(LD) $(LFLAGS) -o $(EXEC1) $(OBJS1)

$(NAME2):
	$(CO) $(CFLAGS) -c $(NAME2).c -o $(OBJS2)
	$(LD) $(LFLAGS) -o $(EXEC2) $(OBJS2)


.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC2): $(OBJS2)
	$(LD) $(LFLAGS) -o $@ $^





%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run-$(EXEC1) run-$(EXEC2) 

run-$(NAME1): $(EXEC1)
	./$(EXEC1)

run-$(NAME2): $(EXEC2)
	./$(EXEC2)


.PHONY: run-all
run-all: $(EXEC1) $(EXEC2)
	./$(EXEC1)
	./$(EXEC2)
	

.PHONY: clean
clean:
	@rm *.o *.x

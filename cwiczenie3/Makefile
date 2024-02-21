CFLAGS = -pedantic -Wall -std=c99
LFLAGS = -pedantic -Wall -std=c99
CO = gcc
LD = $(CO)

NAME1 = cw3a
NAME2 = cw3b
NAME3 = cw3c
NAME4 = childprogram



OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x


.PHONY: help
help:
	@echo "make $(NAME1)  Kompiluje program $(NAME1)"
	@echo "make $(NAME2)  Kompiluje program $(NAME2)"
	@echo "make $(NAME3)  Kompiluje program $(NAME3)"
	@echo "make all          Kompiluje wszystkie programy"
	@echo "make run-all      Uruchamia wszystkie programy"
	@echo "make run-$(NAME1)    Uruchamia program $(NAME1)"
	@echo "make run-$(NAME2)    Uruchamia program $(NAME2)"
	@echo "make run-$(NAME3)    Uruchamia program $(NAME3)"
	@echo "make clean        Usuwa pliki *.o oraz *.x"


.PHONY: $(NAME1) $(NAME2) $(NAME3) $(NAME4) 

$(NAME1):
	$(CO) $(CFLAGS) -c $(NAME1).c -o $(OBJS1)
	$(LD) $(LFLAGS) -o $(EXEC1) $(OBJS1)

$(NAME2):
	$(CO) $(CFLAGS) -c $(NAME2).c -o $(OBJS2)
	$(LD) $(LFLAGS) -o $(EXEC2) $(OBJS2)

$(NAME3):
	$(CO) $(CFLAGS) -c $(NAME3).c -o $(OBJS3)
	$(LD) $(LFLAGS) -o $(EXEC3) $(OBJS3)

$(NAME4):
	$(CO) $(CFLAGS) -c $(NAME4).c -i $(OBJS4)
	$(LD) $(LFLAGS) -o $(EXEC4) $(OBJS4)

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

$(EXEC1): $(OBJS1)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC2): $(OBJS2)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC3): $(OBJS3)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC4): $(OBJS4)
	$(LD) $(LFLAGS) -o $@ $^



%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run-$(EXEC1) run-$(EXEC2) run-$(EXEC3) run-$(EXEC4)

run-$(NAME1): $(EXEC1)
	./$(EXEC1) 2 2

run-$(NAME2): $(EXEC2)
	./$(EXEC2) 2 2 $(EXEC1)

run-$(NAME3): $(EXEC1) $(EXEC3) $(EXEC4)
	./$(EXEC3) ./$(EXEC4) ./$(EXEC1) 2 2


.PHONY: run-all
run-all:
	make run-$(NAME1)
	make run-$(NAME2)
	make run-$(NAME3)
	

.PHONY: clean
clean:
	@rm *.o *.x

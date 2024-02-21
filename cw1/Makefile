CFLAGS = -pedantic -Wall -std=c99
LFLAGS = -pedantic -Wall -std=c99
CO = gcc
LD = $(CO)

NAME1 = a
NAME2 = b
NAME3 = c
NAME4 = d
NAME5 = e

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x

.PHONY: help
help:
	@echo "make compile-$(NAME1)  Kompiluje program $(NAME1)"
	@echo "make compile-$(NAME2)  Kompiluje program $(NAME2)"
	@echo "make compile-$(NAME3)  Kompiluje program $(NAME3)"
	@echo "make compile-$(NAME4)  Kompiluje program $(NAME4)"
	@echo "make compile-$(NAME5)  Kompiluje program $(NAME5)"
	@echo "make all          Kompiluje wszystkie programy"
	@echo "make run-all      Uruchamia wszystkie programy"
	@echo "make run-$(NAME1)    Uruchamia program $(NAME1)"
	@echo "make run-$(NAME2)    Uruchamia program $(NAME2)"
	@echo "make run-$(NAME3)    Uruchamia program $(NAME3)"
	@echo "make run-$(NAME4)    Uruchamia program $(NAME4)"
	@echo "make run-$(NAME5)    Uruchamia program $(NAME5)"
	@echo "make clean        Usuwa pliki *.o oraz *.x"


.PHONY: compile-$(NAME1) compile-$(NAME2) compile-$(NAME3) compile-$(NAME4) compile-$(NAME5)

compile-$(NAME1):
	$(CO) $(CFLAGS) -c $(NAME1).c -o $(OBJS1)
	$(LD) $(LFLAGS) -o $(EXEC1) $(OBJS1)

compile-$(NAME2):
	$(CO) $(CFLAGS) -c $(NAME2).c -o $(OBJS2)
	$(LD) $(LFLAGS) -o $(EXEC2) $(OBJS2)

compile-$(NAME3):
	$(CO) $(CFLAGS) -c $(NAME3).c -o $(OBJS3)
	$(LD) $(LFLAGS) -o $(EXEC3) $(OBJS3)

compile-$(NAME4):
	$(CO) $(CFLAGS) -c $(NAME4).c -o $(OBJS4)
	$(LD) $(LFLAGS) -o $(EXEC4) $(OBJS4)

compile-$(NAME5):
	$(CO) $(CFLAGS) -c $(NAME5).c -o $(OBJS5)
	$(LD) $(LFLAGS) -o $(EXEC5) $(OBJS5)

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

$(EXEC1): $(OBJS1)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC2): $(OBJS2)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC3): $(OBJS3)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC4): $(OBJS4)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC5): $(OBJS5)
	$(LD) $(LFLAGS) -o $@ $^



%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run-$(EXEC1) run-$(EXEC2) run-$(EXEC3) run-$(EXEC4) run-$(EXEC5)

run-$(NAME1): $(EXEC1)
	./$(EXEC1)

run-$(NAME2): $(EXEC2)
	./$(EXEC2)

run-$(NAME3): $(EXEC3)
	./$(EXEC3)

run-$(NAME4): $(EXEC4)
	./$(EXEC4)

run-$(NAME5): $(EXEC5)
	./$(EXEC5)


.PHONY: run-all
run-all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
	./$(EXEC1)
	./$(EXEC2)
	./$(EXEC3)
	./$(EXEC4)
	./$(EXEC5)

.PHONY: clean
clean:
	@rm *.o *.x



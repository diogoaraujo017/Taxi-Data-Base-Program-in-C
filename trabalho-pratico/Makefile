CC=gcc

CFLAGS=-Wall -Iincludes -g

all: programa-principal programa-testes

programa-principal: src/programa-principal.o src/drivers_structure.o src/users_structure.o src/rides_structure.o src/queries.o src/parsing.o src/func_auxiliares.o
	$(CC) $^ $(CFLAGS)  -o $@

programa-testes: src/programa-testes.o src/drivers_structure.o src/users_structure.o src/rides_structure.o src/queries.o src/parsing.o src/func_auxiliares.o
	$(CC) $^ $(CFLAGS)  -o $@

src/programa-principal.o: src/programa-principal.c

src/programa-testes.o: src/programa-testes.c

src/drivers_structure.o: src/drivers_structure.c

src/rides_structure.o: src/rides_structure.c

src/users_structure.o: src/users_structure.c

src/rides_structure.o: src/rides_structure.c

src/queries.o: src/queries.c

src/parsing.o: src/parsing.c

src/func_auxiliares.o: src/func_auxiliares.c

clean:
	rm -f programa-principal src/*.o


	rm -f programa-testes src/*.o
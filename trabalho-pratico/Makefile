CC=gcc

CFLAGS=-Wall -Iincludes -g

programa-principal: src/main.o src/drivers_structure.o src/users_structure.o src/rides_structure.o src/queries.o src/parsing.o
	$(CC) $^ $(CFLAGS)  -o $@

src/main.o: src/main.c

src/drivers_structure.o: src/drivers_structure.c

src/rides_structure.o: src/rides_structure.c

src/users_structure.o: src/users_structure.c

src/rides_structure.o: src/rides_structure.c

src/queries.o: src/queries.c

src/parsing.o: src/parsing.c

clean:
	rm -f programa-principal src/*.o
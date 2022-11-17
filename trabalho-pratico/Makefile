CC=gcc

CFLAGS=-Wall -Iincludes

program: src/main.o src/drivers_structure.o src/users_structure.o src/users_structure.o src/queries.o src/parsing_rides.o src/parsing_drivers.o src/parsing_users.o
	$(CC) $^ $(CFLAGS)  -o $@


src/main.o: src/main.c


src/drivers_structure.o: src/drivers_structure.c

src/users_structure.o: src/users_structure.c

src/rides_structure.o: src/rides_structure.c

src/queries.o: src/queries.c

src/parsing_drivers.o: src/parsing_drivers.c

src/parsing_users.o: src/parsing_users.c

src/parsing_rides.o: src/parsing_rides.c


clean:
	rm -f program src/*.o
CFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2
CC=gcc
pliki = labirinth.o input.o errors.o array.o charArray.o queue.o simulation.o

main: $(pliki)
	$(CC) $(CFLAGS) -o labirinth.exe $(pliki)

array.o: array.c array.h errors.h
charArray.o: charArray.c charArray.h errors.h input.h
errors.o: errors.c errors.h charArray.h
input.o: input.c input.h charArray.h array.h
queue.o: queue.c queue.h
simulation.o: simulation.c simulation.h charArray.h errors.h array.h queue.h input.h
labirinth.o: labirinth.c input.h simulation.h errors.h

clean:
	-rm $(pliki) labirinth.exe
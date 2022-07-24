## Korzystanie z cmake:

Musisz poprawić plik cmake, czyli dodać do niego linijkę z opcjami kompilowania, których wymaga Peczarski:

    set(CMAKE_C_FLAGS "-std=c17 -Wall -Wextra -Wno-implicit-fallthrough")

Oraz poprawić wersję cmake, na mniejszą:

    cmake_minimum_required(VERSION 3.0)

Całość u mnie wygląda tak:

    cmake_minimum_required(VERSION 3.0)
    project(untitled1 C)

    set(CMAKE_C_STANDARD 99)

    # Ustawiamy wspólne opcje kompilowania dla wszystkich wariantów projektu.
    set(CMAKE_C_FLAGS "-std=c17 -Wall -Wextra -Wno-implicit-fallthrough")

    #add_executable(untitled1 oldPr_will_be_deleted.c main.h main.c input.c input.h queue.c queue.h array.c array.h errors.c errors.h)
    add_executable(nowaWersja main.c
            input.c input.h  queue.c queue.h
            errors.c errors.h
            array.c array.h charArray.c charArray.h simulation.c simulation.h)

Teraz aby skompilować projekt musisz utworzyć nowy folder w projekcie:

    mkdir cmake-build
    cd cmake-build

Wewnątrz tego folderu wywołać funkcję:

    cmake ..
    make (lub "make nowaWersja", jak nie zadziałą)

Projekt skompiluje się do pliku "nowaWersja". Możesz poprawić ostrzeżenia.

Ale gdy drugi raz skompilujesz to nie dostaniesz ostrzeżeń, ponieważ `makefile` kompiluje tylko pliki, które zostały zmienione od ostatniej kompilacji. Musisz się zmienić datę ostatniej edycji bez zmieniania nic w plikach za pomocą komendy "touch". Komendę wywołujesz w folderze z projektem, zatem:

    cd ..
    touch *

Teraz jak wejdziesz do folderu cmake-build to będziesz miała znów ostrzeżenia.

    cd cmake-build
    make

## Plik makefile

W środku projektu, aby wygenerować zależności można wywołać polecenie

    gcc -MM plik

Czyli, aby wygenerować dla wszystkich plików .c:

    gcc -MM *.c

Ja otrzymałem coś takiego:

    array.o: array.c array.h errors.h charArray.h input.h
    charArray.o: charArray.c charArray.h errors.h array.h input.h
    errors.o: errors.c errors.h array.h charArray.h input.h
    input.o: input.c input.h array.h charArray.h errors.h simulation.h \
    queue.h
    main.o: main.c input.h array.h charArray.h simulation.h queue.h errors.h
    queue.o: queue.c queue.h
    simulation.o: simulation.c simulation.h array.h charArray.h queue.h \
    input.h errors.h

Do pliku Makefile musisz dać jeszcze linijkę o opcjach kompilacji, których wymaga Peczar i kompilatorze:

    CFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2
    CC=gcc

I teraz dodajesz polecenie do skompilowania projektu, czyli dla jakiegoś mniejszego przykładu. Projekt składa się z trzech plików: main.c, pierwszy.c, pierwszy.h, drugi.c, drugi.h:

    CFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2
    CC=gcc
    pliki = main.o pierwszy.o drugi.o

    main: $(pliki)
        $(CC) $(CFLAGS) -o main.exe $(pliki)

    pierwszy.o: pierwszy.c pierwszy.h drugi.h
    drugi.o: drugi.c drugi.h
    main.o main.c pierwszy.h drugi.h

    clean:
        -rm $(pliki) main.exe
Mamy dwa poleceni: main, do utworzenia pliku main.exe oraz clean, do usunięcia plików binarnych (to też jest wymagane)

I to jest cały makefile, korzysta się z niego wpisując make i nazwa polecenia:
    
    make main
    make clean

Musisz podmienić zależności oraz pliki .o na te z twojego projektu (i zamienić nazwę main na labyrinth).

Po skompilowaniu, aby jescze raz skompilować musisz użyć komenty touch na wszystkich plikach w projekcie:
    
    touch *
    
Która nadpisuje czas ostatniej edycji.

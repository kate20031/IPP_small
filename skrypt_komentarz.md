
## Nie korzystamy z cmake ani make

Przekazujemy ścieżkę do skompilowanego programu, tylko go odpalamy.
Czyli, jeśli ta ścieżka to pierwszy argument w programie, to warto go zapisać w zmiennej, która jasno mówi czym jest:

    program=$1
    ./$program < "input.txt" > "output.txt"

## Skrypt powinien sprawdzać, czy jest wywołany z dwoma argumentami

Jak wpiszę `./test.sh` z brakującym argumentami to powinna się pojawić jakaś informacja o błędzie i jakie argumenty trzeba podać przy włączeniu skryptu. Do sprawdzania ile argumentów się podało służy "$#", czyli na początku dać coś w stylu:

    if (($# < 2)); then
        echo "Proszę podać folder z testami ..."
        exit 1
    fi

## Program musi wypisywać wypisywać wyjście na stdout, nie do pliku

Czyli musisz zrobić program tak jak wcześniej, z getline i fprintf do stdout i stderr, tak jest w treści zadania. 

To skrypt testujący musi "przekierować" wejście z pliku i wyjście do pliku. Robi się to za pomocą "<" oraz ">", było napisane w samouczku do basha.
Czyli, aby wczytać z pliku dane i przekierować na standardowe WEJŚĆIE programu wpisujesz,
    
    ./program<"plik.in"
    
a aby przekirować WYJŚCIE do pliku,
    
    ./program 1> "plik.out"
    
a aby przekierować BŁĄÐ do pliku 

    ./program 2> "plik.err"

Możesz je napisać wszystkie jednocześnie

    ./program < "plik.in" 1> "plik.out" 2> "plik.err"

Musisz zamienić nazwy oczywiście.

Ja robię tak, że przkierowuję wyjście do jakiegoś tymczasowego pliku "tymczasowy.out" oraz "tymczasowy.err" oraz porównuję potem dwa pliki:

    diff "tymczasowy.out" "poprawny.out"

Potem je usuwam:

    rm tymczasowy.out"= tymczasowy.err

Możesz odpalić skrypt raz bez valgrinda - tak jak powyżej, a raz z valgrindem (poniżej), wtedy przekierowanie wygląda tak samo.

## Skrypt musi sprawdzać, czy exitcode jest dobry

Do sprawdzenia exitcode ostatniego polecenia służy "$?". Np.

    wojtek@wojtek-Swift-SF315-51G:~/CLionProjects/ipp-male$ ./main.exe 
    hejka
    ERROR 1
    wojtek@wojtek-Swift-SF315-51G:~/CLionProjects/ipp-male$ echo $?
    1
    wojtek@wojtek-Swift-SF315-51G:~/CLionProjects/ipp-male$ echo $?
    0

Za pierwszym razem "$?" zwróciło 1, bo to błąd programu "main.exe". Za drugim razem to exitcode polecenia "echo" z poprzedniej linijki, 0 oznacza, że zakończyło się powodzeniem.
Musisz sprawdzać, czy jak plik z błędem ma być niepusty to czy exitcode jest równy jeden (w każdym błędzie chyba ma być równy 1), a jak nie ma błędu to exitcode ma być równy 0.

## Sprawdzaj, czy valgrind się nie uda

Musisz wtedy zwrócić błąd. Ja robię tak, że najpierw odpalam bez valgrinda, żeby przekierować wejście i wyjście i je porównać, a potem z valgrindem:

      valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all "./$program" < "wejscie.in"

Ten "-error-exitcode=123" sugeruje, że jak valgrind się nie uda to zwróci exitcode równy 123, zatem trzeba sprawdzić czy takiego nie zwrócił:

      if [[ $? == 123 ]]; then echo "Błąd pamięci"; fi

## Żeby wszystkie ścieżki działały

Ja dostałem jeszcze taki komentarz:

    * Użycie "./program" zamiast samego "program" powoduje, że działają jedynie ścieżki podane względem katalogu bieżącego, natomiast nie działają te zaczynające się od / lub ~. (-0.5)

Ale nie wiem jak to naprawić, musisz spytać na grupie lub discordzie (ktoś kiedyś pisał jak to zrobić) lub poszukać w internecie.

## Nie wywołuj make w każdym obrocie pętli

Raz przed pętlą wystarczy "make", a potem tylko włączasz program.

## Na końcu posprzątaj

Wywołaj `make clean` na końcu skryptu.

## Uwaga odnośnie kodu:

Chyba możesz zrobić

    for file in $2/*in; do

Zamiast:
    
    for file in $2/*; do
        if [[ $file == *.in ]]; then

Ale najlepiej też, jeśli zapiszesz ten argument w osobnym pliku (wtedy będzie wiadomo co to jest):

    testy=$2
    
    (...)

    for file in "$testy"/*.in; do
        ...
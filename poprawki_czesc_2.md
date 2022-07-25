## input.c
- funkcji "power" z 55. linijki korzystasz tylko do podnoszenia 2 do którejś potęgi. W każdym języku programowania potęgi dwójki za wbudowane automatycznie. Wystarczy przesuwać bitowo 1 o pewną ilość miejsc, np. 1 << 6 = 2 ^ 6. Ta funkcja jest niepotrzebna
- funckja "binToHex" z 64. linijki oraz "intToHex" są wykorzystywane jedynie w pliku charArray.c. Nie powinny być w pliku input.c, tylko w charrArray.c. Możesz też dać komentarz co robi binToHex, ponieważ to nie jest oczywiste.
- osobiście bym zmienił kolejność w scanToArrayAdd (111 linijka). Przekazujesz bool afterR, żeby rozróżnić, że w jednym można wczytać zero, a w drugim nie oraz że w jednym < uint32. Może niech funkcja scanToArray tylko wczytuje numery, nie wiedząc jakie są poprawne a jakie nie. Wtedy po wczytaniu, inna funkcja sprawdzi, czy nie ma zer, tam gdzie ma ich nie być oraz inna funkcja, czy są mniejsze od uint32 po wcszytaniu wszystkiego.
- W "converRToBinary" (170. linijka) w linijce 177 clino on narzeka na zamianę unsigned long long na long long. Może da się przebudować tą pętlę, aby nie było nigdzie liczb ujemnych. Może jakiś for?
- 226 "scanAndConverte" ja bym zmienił nazwę na coś jaśniejszeg, np. scanWalls, scanHexOrR, czy coś takiego.
- 234 linjka, pętla while, gdzie w ifie masz w każdym przypadku "break". Zatem chyba ta pętla jest niepotrzebna
- 274, 286  funkcje "convertIndex" oraz "converIndexRev" nie wiem, jaki mają związek w wczytywaniem. Powinny się znaleźć w innym pliku (bardziej pasuje simulation.c)
- 308 funckja readInput zwraca bool oraz ma argument int* err. Chyba służą do tego samego, więc jedno się powtarza i jest przez to niepotrzebne

## labyrinth.c (w sumie to nic poważnego, bardziej sugestie)
- plik z programem nie musi się nazywać labyrinth.c, może być main.c, moim zdaniem to lepiej wskazuje na to, gdzie program się zaczyna
- 19 linijka, daj && które się znajduje na końcu na początek następnej linijki, lepiej widać że to jeden warunek
- 28 linijka, "checkStartEnd", ja bym dał do funkcji checkErrors, jak sprawdzać błędy to wszystkie (można w funkcji zamienić potrzebne wartości jeszcze raz)
- 32, 34, ja był dał (size_t)(-1) oraz (size_t)(-2), jest czytelniej
- 26 nie wiem czy jest sens robić dwa entery przerwy w środku funkcji

## simulation.c
- 81 tu właściwie jeszcze raz obliczasz volume, a już raz obliczyłaś, wcześniej, możesz przekazać go w funkjci
- 82 "bool" niestety ma 8 bitów w c, czyli możesz równie dobrze wykorzystać charArray, który napisałaś. Więc niestety zajmujesz 8 razy więcej miejsca niż potrzebujesz (ale może za to nie odejmują punktów). Ja i wiele osób zrobiliśmy tak, że odwiedzone zaznaczamy od razu w labiryncie, który wczytaliśmy (u Ciebie to funkcje getBit i setBit z charArray). Czyli uznajemy że ściana labiryntu to odwiedzony klocek, a jak odwiedzamy jakiś klocek to stawiamy tam ścianę, żeby nie odwiedzać go jeszcze raz. Wtedy nie potrzebujesz nowej tablicy, tylko korzystasz z getBit i setBit z charArray.
- 94 możesz też zrobić typedef, żeby nie pisać słówka struct. Warto trzymać się jednej konwencji
- 126 - 129 możesz zrobić funkcję "usuń kolejkę", która będzie to robiła

## Pozostałe uwagi
- jak masz jakiekolwiek równanie, np.(5-3)/2, to musisz dawać spacje między operatorami, czyli (5 - 3) / 2. Szczególnie to widać w charArray i getBit. Jak masz << lub & to też chyba trzeba te spacje dawać.
- nie wiem, czy sprawdzasz, żeby iloczyn wymiarów (volume) był mniejszy niż size_t. Jak jest większy to błąd danych wejściowych
- jak masz wiodące zera w wejściu 0x, to nie ma sensu trzymać ich w charArray. W ogóle tam początek labiryntu jest na końcu, czyli kostka o wymiarach (1,1,1,..) (lub o indeksie 0) jest ostatnia w tej linijce. A ponieważ za pomocą getline masz wczytaną całą linijkę, to możesz do charArray wrzucać od razu od końca, czyli mieć logiczniej w tablicy zapisany ten labirynt
- i możesz zapisywać odwiedzone (visited) w charArray, za pomocą setBit, czyli tak jakby ustawiać ścianę w labiryncie.
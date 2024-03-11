/**************************************************************************************************
    AUTOR: Szymon Kruk

    WEJSCIE:
    Na wejsciu programu jest wiersz z nieujemna liczba calkowita okreslajaca dlugosc wyprowadzenia,
    wiersze opisu L-systemu i wiersze opisu interpretacji slowa.

    Opis L-systemu sklada się z wiersza zawierającego aksjomat, po ktorym nastepuje ciag wierszy
    z regulami zastepowania. Wiersz reguly zastepowania zaczyna sie od zastepowanego symbolu,
    a po nim jest zastępujace go slowo. Alfabet L-systemu nie jest jawnie podany. Przyjmujemy,
    ze jest zbiorem symboli występujących w aksjomacie i regulach zastępowania.

    Opis interpretacji slowa zaczyna sie od ciagu wierszy prologu, po nim sa wiersze regul
    interpretacji, a po nich wiersze epilogu. Każdy z tych trzech ciagow jest poprzedzony wierszem
    pustym. Wiersz reguly interpretacji zaczyna sie od interpretowanego symbolu, a reszta wiersza
    jest tekstem, ktory dla tego symbolu nalezy wypisac na wyjscie.

    WYJSCIE:
    Wynikiem programu jest wypisanie do standardowego wyjscia bezposrednio po sobie
    w nastepujacej kolejnosci:
    - ciagu wierszy prologu
    - ciagu wierszy bedacych interpretacja wyprowadzonego slowa
    - ciagu wierszy epilogu
    Kazdy wiersz wyjscia kocnczy sie znakiem nowej linii.

    KONWENCJA:    
    W opisie funkcji oraz zmiennych 'symbol' w zaleznosci od kontekstu rozumiemy jako
    znak typu 'char' lub odpowiadajaca mu w systemie ASCII liczbe.
    Natomiast przez 'slowo' wielokrotnie rozumiemy tablice liczb, ktore w systemie ASCII
    odpowiadaja symbolom tworzacym rzeczywiste slowo.
**************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>


/**
    'liczba_wyprowadzen' - nieujemna liczba calkowita informujaca o dlugosci wyprowadzenia slowa

    'slowo' - wskaznik do tablicy zawierajacej slowo poczatkowe

    'tab' - dwuwymiarowa tablica o wymiarach 128x101. W 'k-tym' wierszu 
    tablicy znajduje sie slowo zastepujace symbol odpowiadajacy liczbie 'k' w systemie ASCII.
    Slowo zastepujace konczy sie znakiem nowej linii, a jego dlugosc jest przechowywana
    w ostatniej komorce wiersza (pod indeksem '100'). Jezeli symbol nie posiada zadnego
    wyprowadzenia to w pierwszej komorce odpowiadajacego mu wiersza znajduje sie wartosc '404'.

    Zwraca wskaznik do slowa o wyprowadzeniu dlugosci 'liczba_wyprowadzen', wyprowadzonego ze slowa
    poczatkowego 'slowo' na podstawie regul wyprowadzenia z tablicy 'tab'.

    UWAGA: Jako ze dlugosc kolejnych wyprowadzen slowa rosnie, funkcja alokuje dodatkowa pamiec
    ktora nalezy pozniej samodzielnie zwolnic!
*/
int* wyprowadz_slowo(int liczba_wyprowadzen, int* slowo, int tab[128][101])
{   
    // zmienna do iteracji po slowie zastepujacym symbol 
    int index_wyprowadzenia;
    // zmienna do iteracji po poprzednim wyprowadzeniu slowa
    int index_slowa;
    // zmienna do iteracji po wyprowadzeniu symbolu
    int index;
    // wskaznik do tablicy przechowujacej kolejne wyprowadzenie
    int *wyprowadzenie;
    /* 
        rozmiar tablicy przechowujacej kolejne wyprowadzenie, 
        uzycie typu 'unsigned long int' jest tutaj wymagane
        do poprawnej kompilacji programu
    */
    unsigned long int rozmiar;

    // wyprowadzenie slowa koncowego
    for (int x = 0; x < liczba_wyprowadzen; x++)
    {
        index_wyprowadzenia = 0;
        index_slowa = 0;
        wyprowadzenie = (int *) malloc(1 * sizeof(int));
        rozmiar = 1;

        // wyprowadzenie kolejnego slowa
        while (slowo[index_slowa] != 10)
        {
            if (tab[slowo[index_slowa]][0] != 404)
            {   
                // powiekszenie rozmiaru tablicy o rozmiar slowa zastepujacego symbol
                wyprowadzenie = realloc(wyprowadzenie, (rozmiar +
                                        (unsigned long int) tab[slowo[index_slowa]][100]) *
                                        sizeof(int));
                rozmiar += (unsigned long int) tab[slowo[index_slowa]][100];
                index = 0;

                // zastapienie symbolu odpowiadajacym mu slowem
                while (tab[slowo[index_slowa]][index] != 10)
                {
                    wyprowadzenie[index_wyprowadzenia] = tab[slowo[index_slowa]][index];
                    index_wyprowadzenia++;
                    index++;
                }
            }
            else
            {   
                // przepisanie symbolu nieposiadajacego wyprowadzenia
                wyprowadzenie = realloc(wyprowadzenie, (rozmiar + 1) * sizeof(int));
                rozmiar += 1;
                wyprowadzenie[index_wyprowadzenia] = slowo[index_slowa];
                index_wyprowadzenia++;
            }

            index_slowa++;
        }

        // dodanie znaku nowej linii na koniec wyprowadzenia slowa
        wyprowadzenie = realloc(wyprowadzenie, (rozmiar + 1) * sizeof(int));
        wyprowadzenie[index_wyprowadzenia] = 10;

        /* 
            ustawienie wskaznika poprzedniego wyprowadzenia na kolejne wyprowadzenie
            i zwolnienie pamieci poprzedniego wyprowadzenia
         */
        int *temp;
        temp = slowo;
        slowo = wyprowadzenie;
        wyprowadzenie = temp;
        free(wyprowadzenie);
    }

    // zwrot wskaznika do ostatecznego wyprowadzenia slowa
    return slowo;
}

/**
    'slowo' - wskaznik do tablicy zawierajacej wyprowadzone slowo, zakonczone znakiem nowej linii

    'reguly_intepretacji' - tablica dwuwymiarowa o wymiarach 128x100 zawierajaca reguly
    interpretacji symboli. W 'k-tym' wierszu tablicy znajduje sie slowo bedace interpretacja
    symbolu odpowiadajacego liczbie 'k' w systemie ASCII. Jezeli symbol nie posiada zadnej
    interpretacji to w pierwszej komorce odpowiadajacego mu wiersza znajduje sie wartosc '404'.

    Wypisuje w kolejnych wierszach standardowego wyjscia interpretacje kolejnych symboli
    tworzacych wyprowadzone slowo 'slowo' na podstawie regul interpretacji przekazanych
    w tablicy 'reguly_interpretacji'.
    Kazdy wypisany wiersz konczy sie znakiem nowej linii.
*/
void interpretuj_slowo(int* slowo, int reguly_interpretacji[128][100])
{   
    // zmienna do iteracji po wyprowadzonym slowie
    int index_slowa = 0;
    // zmienna do iteracji po interpretacjach symboli
    int index_interpretacji;

    while (slowo[index_slowa] != 10)
    {
        index_interpretacji = 0;

        if (reguly_interpretacji[slowo[index_slowa]][0] != 404)
        {
            while (reguly_interpretacji[slowo[index_slowa]][index_interpretacji] != 10)
            {
                putchar(reguly_interpretacji[slowo[index_slowa]][index_interpretacji]);
                index_interpretacji++;
            }
            
            putchar(10);
        }

        index_slowa++;
    }
}

/**
    'prolog_czy_epilog' - liczba decydujaca czy chcemy zczytac prolog czy epilog

    Zczytuje ze standardowego wejscia i wypisuje do standardowego wyjscia
    wszystkie wiersze prologu jezeli 'prolog_czy_epilog' ma wartosc '0'.
    Dla kazdej innej przekazanej wartosci calkowitej zczytuje ze standardowego wejscia i wypisuje
    do standardowego wyjscia wszystkie wiersze epilogu.
*/
void zczytaj_i_wyswietl_tekst(int prolog_czy_epilog)
{
    // wiersz prologu/epilogu
    char wiersz_tekstu[101];
    // zmienna iteracyjna
    int index;
    // symbol informujacy o zakonczeniu prologu/epilogu
    int warunek_koncowy;
    // pierwszy znak wiersza prologu
    int pierwszy_znak;

    if (prolog_czy_epilog == 0){
        // czyta prolog
        warunek_koncowy = 10;
    }
    else 
    {   
        // czyta epilog
        warunek_koncowy = -1;
    }

    // zczytanie i wyswietlenie wierszy prologu/epilogu
    pierwszy_znak = getchar();
    while (pierwszy_znak != warunek_koncowy)
    {
        ungetc(pierwszy_znak, stdin);
        fgets(wiersz_tekstu, 101, stdin);
        index = 0;

        while (wiersz_tekstu[index] != 10)
        {
            putchar(wiersz_tekstu[index]);
            index++;
        }

        putchar(10);

        pierwszy_znak = getchar();
    }
}

/**
    'slowo' - wskaznik do tablicy o rozmiarze conajmniej '100'

    Zczytuje slowo poczatkowe do tablicy na ktora wskazuje 'slowo' i po dodaniu
    na jego koniec znaku nowej linii zwraca do niej wskaznik.
*/
int* zczytaj_slowo_poczatkowe(int* slowo)
{
    // symbol tworzacy slowo poczatkowe
    int symbol;
    // zmienna iteracyjna
    int index = 0;

    // zczytanie slowa poczatkowego
    symbol = getchar();
    while (symbol != 10)
    {
        slowo[index] = symbol;
        symbol = getchar();
        index++;
    }
    // dodanie znaku nowej linii na koniec slowa poczatkowego
    slowo[index] = 10;
    
    return slowo;
}

/**
    'reguly_interpretacji' - dwuwymiarowa tablica o wymiarach 128x100

    Inicjalizuje pierwsza kolumne tablicy 'reguly_interpretacji' wartoscia '404'.
    Nastepnie dla kazdego wiersza interpretacji zczytuje ze standardowego wejscia i wpisuje do
    'k-tego' wiersza przekazanej tablicy regule interpretacji symbolu ktoremu w systemie ASCII
    odpowiada liczba 'k' i dodaje na jej koniec znak nowej linii.
*/
void zczytaj_reguly_interpretacji(int reguly_intepretacji[128][100])
{
    // pierwszy znak wiersza regul interpretacji
    int pierwszy_znak;
    // zmienna iteracyjna
    int index = 0;
    // kolejne symbole tworzace interpretacje symbolu slowa
    int regula;

    // inicjalizacja pierwszej kolumny wartoscia '404'
    for (int k = 0; k < 128; k++)
    {
        reguly_intepretacji[k][0] = 404;
    }

    // zczytanie regul interpretacji
    pierwszy_znak = getchar();
    while (pierwszy_znak != 10)
    {
        regula = getchar();
        index = 0;

        while (regula != 10)
        {
            reguly_intepretacji[pierwszy_znak][index] = regula;
            index++;
            regula = getchar();
        }

        reguly_intepretacji[pierwszy_znak][index] = 10;

        pierwszy_znak = getchar();
    }
}

/**
    'symbole_wyprowadzajace' - dwuwymiarowa tablica o wymiarach 128x101

    Inicjalizuje pierwsza kolumne tablicy 'symbole_wyprowadzajace' wartoscia '404', 
    Nastepnie dla kazdego wiersza wyprowadzen zczytuje do 'k-tego' wiersza wyprowadzenie
    symbolu ktoremu w systemie ASCII odpowiada liczba 'k' i dodaje na jego koniec znak nowej linii.
    W ostatniej komorce (pod indeksem '100') wiersza zawierajacego wyprowadzenie symbolu zapisuje
    dlugosc tego wyprowadzenia.
*/
void zczytaj_wyprowadzenia(int symbole_wyprowadzajace[128][101])
{
    // pierwszy znak wiersza wyprowadzen
    int pierwszy_znak;
    // zmienna iteracyjna
    int index = 0;
    // kolejne symbole wyprowadzenia
    int symbol;

    // inicjalizacja pierwszej kolumny wartoscia '404'
    for (int k = 0; k < 128; k++)
    {
        symbole_wyprowadzajace[k][0] = 404;
    }

    // zczytanie wyprowadzen symboli
    pierwszy_znak = getchar();
    while (pierwszy_znak != 10)
    {
        symbol = getchar();
        index = 0;

        while (symbol != 10)
        {
            symbole_wyprowadzajace[pierwszy_znak][index] = symbol;
            index++;
            symbol = getchar();
        }

        symbole_wyprowadzajace[pierwszy_znak][index] = 10;
        // przechowanie dlugosci wyprowadzenia dla symbolu w ostatniej komorce wiersza
        symbole_wyprowadzajace[pierwszy_znak][100] = index;

        pierwszy_znak = getchar();
    }
}

int main(void)
{   
    // liczba wyprowadzen slowa
    int liczba_wyprowadzen;
    // wskaznik do tablicy przechowujacej slowo poczatkowe
    int *slowo;
    slowo = (int*) malloc(101 * sizeof(int));
    // wyprowadzenia symboli
    int symbole_wyprowadzajace[128][101];
    // reguly intepretacji symboli
    int reguly_interpretacji[128][100];

    // zczytanie liczby wyprowadzen
    scanf("%d", &liczba_wyprowadzen);
    getchar();

    // zczytanie slowa poczatkowego
    slowo = zczytaj_slowo_poczatkowe(slowo);

    // zczytanie wyprowadzen symboli
    zczytaj_wyprowadzenia(symbole_wyprowadzajace);

    // zczytanie i wyswietlenie prologu
    zczytaj_i_wyswietl_tekst(0);

    // zczytanie interpretacji symboli
    zczytaj_reguly_interpretacji(reguly_interpretacji);

    // wyprowadzenie slowa i wyswietlenie jego interpretacji 
    slowo = wyprowadz_slowo(liczba_wyprowadzen, slowo, symbole_wyprowadzajace);
    interpretuj_slowo(slowo, reguly_interpretacji);

    // zwolnienie pamieci przechowujacej koncowe wyprowadzenie slowa
    free(slowo);

    // zczytanie i wyswietlenie epilogu
    zczytaj_i_wyswietl_tekst(1);
    
    return 0;
}
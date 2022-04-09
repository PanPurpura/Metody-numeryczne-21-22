#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

const int SIZE = 100;                           //Rozmiar wprowadzanych wektorow

void display_vector(long double vector[], int size);            //Funkcja wyswietlajaca wektor
void fill_vector(long double vector[], int size);               //Funkcja wypelniajaca wektor wartosciami podanymi w zadaniu.
long double euclidean_norm(long double vector[], int size);         //Funkcja wyliczajaca norme euklidesowa
void minus_v(long double vector1[], long double vector2[], int size, long double minus_h[]);        //Funkcja odejmujaca wektory
int jacobi_method(long double exact_x_it[], long double vector[], long double stop, int size, long double minus_h[]);       //Funkcja rozwiazujaca rownanie metoda jacobiego
void initialize_vector(long double vector[], int size, int value);          //Funkcja do inicjalizacji wektora wybrana wartoscia.
void copy_(long double v1[], long double v2[], int size);                   //Funkcja do kopiowania wartosci z wektora do wektora.
int gauss_method(long double exact_x_it_g[], long double vector[], long double stop, int size, long double minus_h[]);  //Funkcja rozwiazujaca rownanie metoda gaussa-seidela
void iteration_j(int it_j, long double j1[], long double minus_h[], long double vector[], int size);        //Dwie funkcje wyliczajace roznice wynikow w danej iteracji
void iteration_g(int it_g, long double g1[], long double minus_h[], long double vector[], int size);        //oraz wyniku dokladnego.

long double exact_x[SIZE];     //Wektor z wyliczonym metoda jacobiego x.
long double exact_x_g[SIZE];    //Wektor z wyliczonym metoda gaussa-seidela x.
long double auxiliary[SIZE];    //Pomocniczy wektor dla funkcji iteration_j oraz iteration_g.

int main()
{
    cout.precision(15);                     //Ustawiam precyzje

    //Deklaruje potrzebne wetory, wektor v jest to wektor wyrazow wolnych.
    long double v[SIZE];
    fill_vector(v, SIZE);
    display_vector(v, SIZE);
    long double exact_x_it[SIZE];
    long double minus_h[SIZE];
    long double exact_x_it_g[SIZE];
    //Wszystkie wektory inicjalizuje na 0.
    initialize_vector(exact_x_it, SIZE, 0);
    initialize_vector(exact_x, SIZE, 0);
    initialize_vector(exact_x_g, SIZE, 0);
    initialize_vector(exact_x_it_g, SIZE, 0);
    initialize_vector(minus_h, SIZE, 0);
    initialize_vector(auxiliary, SIZE, 0);
    //Ustawiam precyzje do ktorej metody maja liczyc.
    long double stop = 1e-16;
    //Zapisuje zwracane przez zmienne ilosci iteracji potrzebnych do uzyskania wektora x.
    int it_j;
    it_j = jacobi_method(exact_x_it, v, stop, SIZE, minus_h);
    int it_g;
    it_g = gauss_method(exact_x_it_g, v, stop, SIZE, minus_h);
    //Wyswietlam obliczone wektory (oba beda takie same).
    cout<<endl<<endl<<"Wektor x policzony metoda jacobiego:"<<endl<<endl;
    display_vector(exact_x, SIZE);
    cout<<endl<<"Wektor x policzony metoda gaussa:"<<endl<<endl;
    display_vector(exact_x_g, SIZE);
    //Zmieniam wartosci wektorow ponownie na 0.
    initialize_vector(exact_x_it, SIZE, 0);
    initialize_vector(exact_x_it_g, SIZE, 0);
    //Wywoluje dwie funkcje ktore policza roznice miedzy iteracjami oraz wynikiem koncowym.
    iteration_j(it_j, exact_x_it, minus_h, v, SIZE);
    iteration_g(it_g, exact_x_it_g, minus_h, v, SIZE);

    return 0;
}

void initialize_vector(long double vector[], int size, int value)   //Zainicjuj podany wektor podana wartoscia.
{
    for(int i = 0; i < size; i++)
        vector[i] = value;
}

void copy_(long double v1[], long double v2[], int size)        //Skopiuj wartosci jednego wektora do drugiego.
{
    for(int i = 0; i < size; i++)
        v1[i] = v2[i];
}

int jacobi_method(long double exact_x_it[], long double vector[], long double stop, int size, long double minus_h[])
{

    //Metoda jacobiego, obliczajaca wektor x.
    int it = 0;         //Zmienna pomocnicza do liczenia iteracji. Gdy osiagniety zostanie warunek stop, zostanie ona zwrocona przez funkcje.

    while(1)
    {

        //Korzystajac ze wzoru obliczam wyrazy wetora x. Pierwsza dwa wyrazy obliczam inaczej.
        exact_x_it[0] = (vector[0] - (1 * exact_x[1] + 0.2 * exact_x[2]))/3;
        exact_x_it[1] = (vector[1] - (1 * exact_x[0] + 1 * exact_x[2] + 0.2 * exact_x[3]))/3;


        //Pozostale wartosci obliczam z udzialem wartosci na 4 wstegach oraz wartosci na diagonali.
        int i = 2;
        int j = 0;
        while(i < size - 2)
        {
            exact_x_it[i] = (vector[i] - (0.2 * exact_x[j] + 1 * exact_x[j+1] + 1 * exact_x[j+3] + 0.2 * exact_x[j+4]))/3;
            i++;
            j++;
        }
        //Dwa ostatnie wyrazy rowniez obliczam inaczej.
        exact_x_it[size - 2] = (vector[size - 2] - (0.2 * exact_x[(size-2) - 2] + 1 * exact_x[(size-2) - 1] + 1 * exact_x[(size-2) + 1]))/3;
        exact_x_it[size - 1] = (vector[size - 1] - (0.2 * exact_x[(size-1) - 2] + 1 * exact_x[(size-1) - 1]))/3;
        //Zwiekszam licznik iteracji.
        it++;

        //Odejmuje od siebie dwa wektory, a nastepnie obliczam norme euklidesowa z wektora wynikowego i sprawdzam czy jest ona mniejsza
        //niz warunek stopu, jesli tak to zwracam ilosc iteracji.
        minus_v(exact_x_it, exact_x, size, minus_h);
        copy_(exact_x, exact_x_it, size);
        if(euclidean_norm(minus_h, size) < stop)
            return it;
    }

}

int gauss_method(long double exact_x_it_g[], long double vector[], long double stop, int size, long double minus_h[])
{
    //Metoda gaussa-seidela, obliczajaca wektor x.
    int it = 0;         //Zmienna pomocnicza do liczenia iteracji. Gdy osiagniety zostanie warunek stop, zostanie ona zwrocona przez funkcje.


    while(1)
    {
        //Korzystajac ze wzoru obliczam wyrazy wetora x. Pierwsza dwa wyrazy obliczam inaczej.
        exact_x_it_g[0] = (vector[0] - (1 * exact_x_g[1] + 0.2 * exact_x_g[2]))/3;
        exact_x_it_g[1] = (vector[1] - (1 * exact_x_it_g[0] + 1 * exact_x_g[2] + 0.2 * exact_x_g[3]))/3;

         //Pozostale wartosci obliczam z udzialem wartosci na 4 wstegach oraz wartosci na diagonali.
        int i = 2;
        int j = 0;
        while(i < size - 2)
        {
            exact_x_it_g[i] = (vector[i] - (0.2 * exact_x_it_g[j] + 1 * exact_x_it_g[j+1] + 1 * exact_x_g[j+3] + 0.2 * exact_x_g[j+4]))/3;
            i++;
            j++;
        }
        //Dwa ostatnie wyrazy rowniez obliczam inaczej.
        exact_x_it_g[size - 2] = (vector[size - 2] - (0.2 * exact_x_it_g[(size-2) - 2] + 1 * exact_x_it_g[(size-2) - 1] + 1 * exact_x_g[(size-2) + 1]))/3;
        exact_x_it_g[size - 1] = (vector[size - 1] - (0.2 * exact_x_it_g[(size-1) - 2] + 1 * exact_x_it_g[(size-1) - 1]))/3;
         //Zwiekszam licznik iteracji.
        it++;

        //Odejmuje od siebie dwa wektory, a nastepnie obliczam norme euklidesowa z wektora wynikowego i sprawdzam czy jest ona mniejsza
        //niz warunek stopu, jesli tak to zwracam ilosc iteracji.
        minus_v(exact_x_it_g, exact_x_g, size, minus_h);
        copy_(exact_x_g, exact_x_it_g, size);
        if(euclidean_norm(minus_h, size) < stop)
            return it;
    }
}

void iteration_j(int it_j, long double j1[], long double minus_h[], long double vector[], int size)
{
    ofstream jac("Data_j.txt", ios_base::app);      //Tworze zmienna typu ofstream, podajac jako argumenty nazwe pliku tekstowego do ktorego
                                                    //zapisze dane oraz polecenie dopisywania danych do konca pliku.
    //W petli obliczam kolejne iteracje uzywajac metody jacobiego.
    for(int k = 0; k < it_j; k++)
    {
        j1[0] = (vector[0] - (1 * auxiliary[1] + 0.2 * auxiliary[2]))/3;
        j1[1] = (vector[1] - (1 * auxiliary[0] + 1 * auxiliary[2] + 0.2 * auxiliary[3]))/3;

        int i = 2;
        int j = 0;
        while(i < size - 2)
        {
            j1[i] = (vector[i] - (0.2 * auxiliary[j] + 1 * auxiliary[j+1] + 1 * auxiliary[j+3] + 0.2 * auxiliary[j+4]))/3;
            i++;
            j++;
        }

        j1[size - 2] = (vector[size - 2] - (0.2 * auxiliary[(size-2) - 2] + 1 * auxiliary[(size-2) - 1] + 1 * auxiliary[(size-2) + 1]))/3;
        j1[size - 1] = (vector[size - 1] - (0.2 * auxiliary[(size-1) - 2] + 1 * auxiliary[(size-1) - 1]))/3;

        //Na koniec odejmuje wektor koncowy od wektora wyliczonego w danej iteracji.
        minus_v(j1, exact_x_g, size, minus_h);
        copy_(auxiliary, j1, size); // Zapamietuje wyliczony w danej iteracji wektor.
        //Zapisuje wyniki do pliku.
        jac << k+1 << " " << euclidean_norm(minus_h, size) << endl;
    }

    //Zamykam plik.
    jac.close();
}

void iteration_g(int it_g, long double g1[], long double minus_h[], long double vector[], int size)
{
    ofstream g("Data_g.txt", ios_base::app);        //Tworze zmienna typu ofstream, podajac jako argumenty nazwe pliku tekstowego do ktorego
                                                    //zapisze dane oraz polecenie dopisywania danych do konca pliku.
    //W petli obliczam kolejne iteracje uzywajac metody jacobiego.
    initialize_vector(auxiliary, size, 0);

    for(int k = 0; k < it_g; k++)
    {
        g1[0] = (vector[0] - (1 * auxiliary[1] + 0.2 * auxiliary[2]))/3;
        g1[1] = (vector[1] - (1 * g1[0] + 1 * auxiliary[2] + 0.2 * auxiliary[3]))/3;

        int i = 2;
        int j = 0;
        while(i < size - 2)
        {
            g1[i] = (vector[i] - (0.2 * g1[j] + 1 * g1[j+1] + 1 * auxiliary[j+3] + 0.2 * auxiliary[j+4]))/3;
            i++;
            j++;
        }

        g1[size - 2] = (vector[size - 2] - (0.2 * g1[(size-2) - 2] + 1 * g1[(size-2) - 1] + 1 * auxiliary[(size-2) + 1]))/3;
        g1[size - 1] = (vector[size - 1] - (0.2 * g1[(size-1) - 2] + 1 * g1[(size-1) - 1]))/3;

        //Na koniec odejmuje wektor koncowy od wektora wyliczonego w danej iteracji.
        minus_v(g1, exact_x_g, size, minus_h);
        copy_(auxiliary, g1, size);             // Zapamietuje wyliczony w danej iteracji wektor.
        //Zapisuje wyniki do pliku.
        g << k+1 << " " << euclidean_norm(minus_h, size) << endl;
    }

    //Zamykam plik.
    g.close();
}

//Funkcja ktora odejmuje wartosci jednego wektora poprzez drugiego w petli i operuje na pomocniczej zmiennej globalnej do ktorej
//zapisuje wyniki dzialania.
void minus_v(long double vector1[], long double vector2[], int size, long double minus_h[])
{
    for(int i = 0; i < size; i++)
    {
        minus_h[i] = vector1[i] - vector2[i];
    }
}

//Funkcja obliczajaca norme euklidesowa z podanego wektora o zadanym rozmiarze.
long double euclidean_norm(long double vector[], int size)
{
    long double suma = 0.0;
    for(int i = 0; i < size ; i++)
    {
        suma = suma + (vector[i] * vector[i]);
    }

    return sqrt(suma);
}

void display_vector(long double vector[], int size)                  //Prosta funkcja do wyswietlenia wektora.
{
    for(int i = 0; i<size; i++)
    {
        cout<<"[ ";
        cout.width(17);
        cout<<vector[i];
        cout<<" ]"<<endl;
    }
}

void fill_vector(long double vector[], int size)                  //Prosta funkcja do uzpelnienia wektora wyrazow wolnych.
{
    for(int j = 0; j<size; j++)
    {
        vector[j] = j+1;                                //Przypisuje wektorowi podane wartosci.
    }
}



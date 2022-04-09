#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void generate_nets_of_points(double vector[], double vector2[], int n);             //Funkcja generuje siatki punkt�w wed�ug podanych wzor�w.
void generate_set_of_values_fun1(double vector[], double net[], int n);             //Funkcja generuje zbi�r warto�ci funkcji pierwszej dla podanych punkt�w.
void create_data(double set_of_values[], double net[], int n, string doc_name);     //Funkcja zapisuje podane dane do pliku o podanej nazwie.
double polynomial_value(double set_of_values[], double net[], int n, double point); //Funkcja wyliczaj�ca przybli�on� warto�� wielomianu w danym punkcie.
void generate_set_of_values_fun2(double vector[], double net[], int n);             //Funkcja generuje zbi�r warto�ci funkcji drugiej dla podanych punkt�w.

const int SIZE = 10;            //Ilo�� w�z��w interpolacji, "n", a tak�e rozmiar tablic w programie.



int main()
{
    double net[SIZE+1];                 //Tablica do przechowywania punkt�w siatki pierwszej.
    double net_2[SIZE+1];               //Tablica do przechowywania punkt�w siatki drugiej
    double set_of_values_fun1[SIZE+1];  //Tablica do przchowywania zbioru warto�ci funkcji pierwszej.
    double set_of_values_fun2[SIZE+1];  //Tablica do przechowywania zbioru warto�ci funkcji drugiej.
    double polynomial_val[1000];        //Tablica przechowujaca wartosci wielomianu danego stopnia dla 1000 punkt�w jednorodnie rozlozonych
                                        //w przedzialu <-1;1>.

    generate_nets_of_points(net, net_2, SIZE);          //Wygeneruj obie siatki punkt�w

    double between[1001];               //Osobna tablica dla wybranych punkt�w znajduj�cych si� w przedziale <-1;1>
    int j = 0;
    double i = -1.0;
    //Za pomoca tej petli uzupelni� tablic� between.
    while(i <= 1)
    {
        between[j++] = i;
        i = i + 0.002;
    }
    between[1000] = 1.0;

//######################################################################################################
    //Generuje zbior wartosci dla funkcji pierwszej i siatki pierwszej.
    generate_set_of_values_fun1(set_of_values_fun1, net, SIZE);
    //Obliczam przybli�one warto�ci wielomian�w w punktach, kt�re wcze�niej zapisalem w tablicy between.
    for(int k = 0; k <= 1000; k++)
    {
        polynomial_val[k] = polynomial_value(set_of_values_fun1, net, SIZE, between[k]);
    }
    //Zapisuj� obliczone dane do pliku.
    create_data(polynomial_val, between, 1000, "fun1_a.txt");
//######################################################################################################
    //Generuje zbior wartosci dla funkcji pierwszej i siatki drugiej.
    generate_set_of_values_fun1(set_of_values_fun1, net_2, SIZE);
    //Obliczam przybli�one warto�ci wielomian�w w punktach, kt�re wcze�niej zapisalem w tablicy between.
    for(int k = 0; k <= 1000; k++)
    {
        polynomial_val[k] = polynomial_value(set_of_values_fun1, net_2, SIZE, between[k]);
    }
    //Zapisuj� obliczone dane do pliku.
    create_data(polynomial_val, between, 1000, "fun1_b.txt");
//######################################################################################################
    //Generuje zbior wartosci dla funkcji drugiej i siatki pierwszej.
    generate_set_of_values_fun2(set_of_values_fun2, net, SIZE);
     //Obliczam przybli�one warto�ci wielomian�w w punktach, kt�re wcze�niej zapisalem w tablicy between.
    for(int k = 0; k <= 1000; k++)
    {
        polynomial_val[k] = polynomial_value(set_of_values_fun2, net, SIZE, between[k]);
    }
    //Zapisuj� obliczone dane do pliku.
    create_data(polynomial_val, between, 1000, "fun2_a.txt");
//######################################################################################################
    //Generuje zbior wartosci dla funkcji drugiej i siatki drugiej.
    generate_set_of_values_fun2(set_of_values_fun2, net_2, SIZE);
     //Obliczam przybli�one warto�ci wielomian�w w punktach, kt�re wcze�niej zapisalem w tablicy between.
    for(int k = 0; k <= 1000; k++)
    {
        polynomial_val[k] = polynomial_value(set_of_values_fun2, net_2, SIZE, between[k]);
    }
    //Zapisuj� obliczone dane do pliku.
    create_data(polynomial_val, between, 1000, "fun2_b.txt");
//######################################################################################################

    return 0;
}

void generate_nets_of_points(double vector[], double vector2[], int n)  //Funkcja wyliczaj�ca punkty dla siatki pierwszej oraz drugiej.
{
    //Za pomoc� prostej p�tli oraz korzystaj�c ze wzor�w wyliczam odpowiednie punkty i zapisuje je w tablicach.
    for(int i = 0; i <= n; i++)
    {
        vector[i] = ((-1.0) + (2.0 * ((double)i/(n))));
        vector2[i] = cos(((2 * (double)i + 1) * 3.14159265359)/(2*(n+1)));
    }
}

void generate_set_of_values_fun1(double vector[], double net[], int n)  //Funkcja obliczajaca zbior wartosci dla funkcji pierwszej.
{
    for(int i = 0; i <= n; i++)
    {
        vector[i] = ((1.0)/(1.0 + (25.0 * net[i]*net[i])));
    }
}

void generate_set_of_values_fun2(double vector[], double net[], int n)  //Funkcja obliczajaca zbi�r warto�ci dla funkcji drugiej.
{
    for(int i = 0; i<=n; i++)
    {
        vector[i] = ((1.0)/(1 + net[i]*net[i]));
    }
}

void create_data(double set_of_values[], double net[], int n, string doc_name)  //Funkcja zapisujaca dane do pliku.
{
    ofstream data(doc_name, ios_base::app); // Tworze obiekt klasy ofstream
    //Za pomcoa petli zapisuje interesujace mnie dane w odpowiedniej formie do pliku o podanej nazwie.
    for(int i = 0; i <= n; i++)
    {
        data << net[i] << " " << set_of_values[i] << endl;
    }

    //Na koniec zamykam plik.
    data.close();
}

double polynomial_value(double set_of_values[], double net[], int n, double point) //Funkcja wyliczajaca przybli�one warto�ci wielomianu w danym punkcie.
{
    //Jest to implementacja wzoru interpolacyjnego Lagrange'a.
    double value = 0.0;
    double fi;
    for(int i = 0; i <= n; i++)
    {
        fi = 1.0;
        for(int j = 0; j <= n; j++)
        {
            if(i != j)
            {
                fi = fi * ((point - net[j])/(net[i] - net[j]));
            }
        }
        value += fi * set_of_values[i];
    }

    return value;
}



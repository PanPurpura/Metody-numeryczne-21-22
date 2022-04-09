#include <iostream>

using namespace std;
const int SIZE = 50;                        //Rozmiar macierzy i wektorow.

void display_matrix(double matrix[][2]);                //Funkcja wyswietlajaca macierz.
void fill_matrix(double matrix[][2]);                   //Funkcja uzupelniajaca macierz wartosciami.
void display_vector(double vector[], int size);         //Funkcja wyswietlajaca wektor.
void solve_backward(int size, double matrix[][2], double solution[], double value);     //Funkcja rozwiazujaca rownanie metoda backward substitution.
void solve_x(double z[], double zP[], double x[]);      //Funkcja wyliczajaca x z wyprowadzonego na zajeciach wzoru.

int main()
{
    double B[SIZE][2];                              //Deklaracja tablicy.
    cout.precision(8);                              //Ustawiam precyzje.
    fill_matrix(B);                                 //Uzupelniam macierz wartosciami.
    cout<<"Macierz B:"<<endl<<endl;
    display_matrix(B);
    cout<<endl<<endl;
    double z[SIZE];                                 //Deklaruje wektory w ktorych zapisze rozwiazania rownan i rozwiazanie koncowe.
    double zP[SIZE];
    double y[SIZE];
    solve_backward(SIZE, B, z, 5);                  //Rozwiazuje rownanie Bz = b.
    cout<<"Obliczony wektor z:"<<endl<<endl;
    display_vector(z, SIZE);
    cout<<endl<<endl;
    solve_backward(SIZE, B, zP, 1);                 //Rozwiazuje rownanie Bz' = u.
    cout<<"Obliczony wektor z':"<<endl<<endl;
    display_vector(zP, SIZE);
    cout<<endl<<endl;
    solve_x(z, zP, y);
    cout<<"Obliczony wektor y:"<<endl<<endl;
    display_vector(y, SIZE);

    return 0;
}

void fill_matrix(double matrix[][2])            //Funkcja uzupelniajaca macierz odpowiednimi wartosciami.
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<2; j++)
        {
            if(j == 0)
                matrix[i][j] = 9;               //Do pierwszego wiersza wstawiam same 9.
            else
            {
                if(i == SIZE-1)
                    matrix[i][j] = 0;           //Ostatnim elementem jest 0.
                else
                    matrix[i][j] = 7;           //Do drugiego wiersza macierzy wprowadzam same 7.
            }
        }
    }
}

void display_matrix(double matrix[][2])        //Prosta funkcja do wyswietlenia macierzy na ekran.
{
   for(int i = 0; i<SIZE; i++)
   {
       cout<<"[ ";
       cout.width(13);
       cout<<matrix[i][0]<<"  ";
       cout.width(13);
       cout<<matrix[i][1];
       cout<<" ]"<<endl;
   }
}

void display_vector(double vector[], int size)                  //Prosta funkcja do wyswietlenia wektora.
{
    for(int i = 0; i<size; i++)
    {
        cout<<"[ ";
        cout.width(11);
        cout<<vector[i];
        cout<<" ]"<<endl;
    }
}
//Skladowe wektorow b i u skladaja sie tylko z jednej wartosci. Wektor b z samych 5, a wektor u z samych 1. Dlatego zeby zaoszczedzic miejsca uzywam po prostu zmiennej value
//do ktorej przekazuje raz 5 raz 1 w zaleznosci ktore rownanie chce rozwiazac.
void solve_backward(int size, double matrix[][2], double solution[], double value)      //Funkcja ktora rozwiazuje rownanie metoda backward substitution.
{
    double sum;
    solution[size-1] = value/matrix[size-1][0];                                      //Ustawiam pierwszy element wektora rozwiazan na odpowiednia wartosc (ide od konca).


    for(int i = (size-2); i>=0; i--)
    {
        sum = 0;
        sum = sum + ((solution[i+1] * matrix[i][1]));         //Sumuje odpowiednie wyrazy dla danego wiersza ukladu rownan idac od konca.

        solution[i] = (value - sum) / matrix[i][0];                                      //Wykonuje dzielenie i otrzymuje nastepny wyraz wektora rozwian ktory uzwyam do dalszych obliczen.
    }


}

//Funkcja wyliczajaca wektor rozwiazan x z nastepujacego wzoru:
//          z' * (v^T * z)
// x = z - ----------------
//          1 + (v^T * z')
//Wektor v^T sklada sie z samych 1 dlatego aby zaoszczedzic pamiec uzywam po prostu wartosci 1.0
void solve_x(double z[], double zP[], double x[])
{
    double sum = 0;
    double sum1 = 0;
    for(int i = 0; i<SIZE; i++)
    {
        sum += 1.00*z[i];               //Obliczam iloczyn v^T * z ktory bedzie liczba.
        sum1 += 1.00*zP[i];             //Obliczam iloczyn v^T * z' ktory rowniez bedzie liczba
    }

    sum1++;                             //Dodaje jedynke do iloczynu v^T * z'.
    for(int j = 0; j<SIZE; j++)
    {
        x[j] = (z[j] - ((zP[j] * sum)/sum1));       //Wykonuje mnozenie z' * (v^T * z), nastepnie dziele jego wynik przez sum1 i odejmuje od wektora z otrzymujac wynik ktory zapisuje do wektora x.
    }
}

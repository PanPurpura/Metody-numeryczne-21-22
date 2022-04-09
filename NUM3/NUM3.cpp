#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const int SIZE = 100;                                                   //Ilosc kolumn
const int ROWS = 4;                                                     //Ilosc wierszy

void A_fill(double [][ROWS], int cols, int rows);                       //Funkcja do uzupelnienia macierzy A odpowiednimi wartosciami.
void display_matrix(double matrix[][ROWS], int cols);                   //Funkcja wyswietlajaca macierz na ekran
void x_fill(double vector[], int size);                                 //Funkcja wypelniajaca wektor x odpowiednimi wartosciami.
void display_vector(double vector[], int size);                         //Funkcja wyswietlajaca wektor na ekran.
void solve_forward(int size, double matrix[][ROWS], double solution[], double free[]);      //Funkcja rozwiazujaca rownanie za pomoca forward substitution.
void solve_backward(int size, double matrix[][ROWS], double solution[], double free[]);     //Funkcja rozwiazujaca rownanie za pomoca backward substitution.

int main()
{
    double A[SIZE][ROWS];                               //Deklaruje tablice dwuwymiarowa na macierz.
    double x[SIZE];                                     //Deklaruje wektor x.
    cout.precision(8);
    A_fill(A, SIZE, ROWS);                              //Uzupelniam macierz A oraz wektor x danymi.
    x_fill(x, SIZE);
    cout<<"Macierz A:"<<endl<<endl;                     //Wyswietlam macierz A i wektor x.
    display_matrix(A, SIZE);
    cout<<endl<<"Wektor x:"<<endl<<endl;
    display_vector(x, SIZE);
    cout<<endl;

    A[1][0] = (A[1][0]/A[0][1]); //L21                      //Z poczatkowych wartosci obliczam jedynie L21, poniewaz reszta sie nie zmienia.

    for(int i = 1; i<SIZE; i++)                             //Z wyprowadzonych wzorow obliczam rozklad macierzy A na LU.
    {
        A[i][1] = A[i][1] - (A[i][0]*A[i-1][2]);
        if(i<(SIZE-1))
        {
            A[i][2] = A[i][2] - (A[i][0]*A[i-1][3]);
            A[i+1][0] = (A[i+1][0]/A[i][1]);
        }

        if(i<(SIZE-2))
            A[i][3] = A[i][3];


    }

    cout<<"Macierz LU:"<<endl<<endl;
    display_matrix(A, SIZE);                    //Wyswietlam macierz LU (nadpisana macierz A)
    double b[SIZE];

    cout<<endl;
    solve_forward(SIZE, A, b, x);                       //Rozwiazuje rownania L*b=x za pomoca forward substitution.
    cout<<"Wektor b z rownania L*b=x:"<<endl<<endl;
    display_vector(b, SIZE);
    cout<<endl;
    double y[SIZE];
    solve_backward(SIZE, A, y, b);                      //Rowiazuje rownanie U*y=b za pomoca backward substitution.
    cout<<"Wektor y z rownania U*y=b:"<<endl<<endl;
    display_vector(y, SIZE);
    cout<<endl;

    double W = 1;                                       //Wyznacznik bedzie rowny iloczynowi wartosci znajdujacych sie na diagonali.
    for(int i = 0; i<SIZE; i++)
    {
        W *= A[i][1];
    }
    cout<<"Wyznacznik wynosi: "<<W<<endl;

    return 0;
}

void A_fill(double matrix[][ROWS], int cols, int rows)          //Funkcja do uzupelnienia macierzy A podanymi wartosciami.
{
    int mianownik = 1;
    int mianownik1 = 1;
    for(int i = 0; i<cols; i++)
    {
        for(int j = 0; j<rows; j++)
        {
            if(j == 0)                                  //Dla kazdej kolumny wiersza pierwszego wpisuje 0.2 z wyjatkiem kolumny o indeksie 0 do ktorej wpisuje 0.
            {                                           //Stanowi to pierwsza wstege pod diagonala.
                if(i == 0)
                {
                    matrix[i][j] = 0;
                }
                else
                {
                    matrix[i][j] = 0.2;
                }
            }
            else if(j == 1)                             //Dla kazdej kolumny wiersza drugiego wpisuje 1.2. Stanowi to diagonale macierzy.
            {
                matrix[i][j] = 1.2;
            }
            else if(j == 2)                             //Dla kazdej kolumny wiersza trzeciego wpisuje wartosc dana odpowiednim wzorem z wyjatkiem kolumny 99 ktora ustawiam na 0.
            {
                if(i == 99)
                {
                    matrix[i][j] = 0;
                }
                else
                {
                    matrix[i][j] = (0.1/mianownik);
                    mianownik++;
                }
            }
            else if(j == 3)                             //Dla kazdej kolumny wiersza czwartego wpisuje wartosc dana odpowiednim wzorem z wyjatkiem kolumn o indeksie 99 i 98,
            {                                           //ktore ustawiam na 0.
                if(i == 98 || i == 99)
                {
                    matrix[i][j] = 0;
                }
                else
                {
                    matrix[i][j] = ((0.4)/(pow(mianownik1,2)));
                    mianownik1++;
                }
            }
        }
    }
}

void x_fill(double vector[], int size)                  //Prosta funkcja do uzpelnienia wektora x.
{
    for(int j = 0; j<size; j++)
    {
        vector[j] = j+1;                                //Przypisuje wektorowi podane wartosci.
    }
}

void display_matrix(double matrix[][ROWS], int cols)        //Prosta funkcja do wyswietlenia macierzy na ekran.
{
   for(int i = 0; i<cols; i++)
   {
       cout<<"[ ";
       cout.width(13);
       cout<<matrix[i][0]<<"  ";
       cout.width(13);
       cout<<matrix[i][1]<<"  ";
       cout.width(13);
       cout<<matrix[i][2]<<"  ";
       cout.width(13);
       cout<<matrix[i][3]<<" ]"<<endl;
   }
}

void display_vector(double vector[], int size)                  //Prosta funkcja do wyswietlenia wektora.
{
    for(int i = 0; i<size; i++)
    {
        cout<<"[ ";
        cout.width(10);
        cout<<vector[i];
        cout<<" ]"<<endl;
    }
}

void solve_forward(int size, double matrix[][ROWS], double solution[], double free[])       //Funkcja ktora rozwiazuje rownanie metoda forward substitution.
{
    int i;
    double sum;
    solution[0] = free[0];                                                                  //Pierwszy wyraz wektora rozwiazan ustawiam na pierwszy wyraz wolny (pierwszy wyraz wektora x)

    for(i = 1; i<size; i++)
    {
        sum = 0;
        sum = sum + (solution[i-1]*matrix[i][0]);                                           //Sumuje odpowiednie wyrazy dla danego wiersza ukladu rownan.

        solution[i] = (free[i] - sum) / 1;                                                  //Wykonuje dzielenie i otrzymuje nastepny wyraz wektora rozwiazan, ktorego uzywam do dalszych obliczen.
    }
}

void solve_backward(int size, double matrix[][ROWS], double solution[], double free[])      //Funkcja ktora rozwiazuje rownanie metoda backward substitution.
{
    double sum;
    solution[size-1] = free[size-1]/matrix[size-1][1];                                      //Ustawiam pierwszy element wektora rozwiazan na odpowiednia wartosc tak jak poprzednio (tutaj ide od konca).


    for(int i = (size-2); i>=0; i--)
    {
        sum = 0;
        sum = sum + ((solution[i+1] * matrix[i][2])+(solution[i+2]*matrix[i][3]));         //Sumuje odpowiednie wyrazy dla danego wiersza ukladu rownan idac tym razem od konca.

        solution[i] = (free[i] - sum) / matrix[i][1];                                      //Wykonuje dzielenie i otrzymuje nastepny wyraz wektora rozwian ktory uzwyam do dalszych obliczen.
    }


}

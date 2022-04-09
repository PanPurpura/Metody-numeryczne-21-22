#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
//Prototypy funkcji wyliczajacych przyblizenie pochodnej w punkcie.
float Dh_fa(float, float);
float Dh_fb(float, float);
double Dh_da(double, double);
double Dh_db(double, double);


int main()
{
    //DANE DLA FLOAT
    float x = 0.3;                                      //Punkt w ktorym liczymy przyblizenie pochodnej
    float h2;                                           //Wartosc h dla ktorej policzymy przyblizenie
    cout<<"Enter h for float, range <10^-7; 0,1>: ";
    cin>>h2;

    float res_fa = 0, res_fb = 0;                       //Zmienne przechowujace przyblizenie pochodnej w punkcie.
    res_fa = Dh_fa(x, h2);
    res_fb = Dh_fb(x, h2);

    float error_fa = 0, error_fb = 0;                   //Zmienne przechowujące blad obliczeniowy
    error_fa = fabs(res_fa - (-sin(x)));
    error_fb = fabs(res_fb - (-sin(x)));

    cout<<"Result for float:"<<endl;                    //Wypisanie wynikow obliczen dla float.
    cout<<"a) "<<res_fa<<endl;
    cout<<"b) "<<res_fb<<endl;
    cout<<"Error for float:"<<endl;
    cout<<"a) "<<error_fa<<endl;
    cout<<"b) "<<error_fb<<endl;

    //DANE DLA DOUBLE
    cout<<"Enter h for double, range <10^-16; 0,1>: ";
    cin>>h2;

    double res_da = 0, res_db = 0;                      //Zmienne przechowujace przyblizenie pochodnej w punkcie.

    res_da = Dh_da(x, h2);
    res_db = Dh_db(x, h2);

    double error_da = 0, error_db = 0;                  //Zmienne przechowujące blad obliczeniowy
    error_da = fabs(res_da - (-sin(x)));
    error_db = fabs(res_db - (-sin(x)));

    cout<<"Result for double:"<<endl;                   //Wypisanie wynikow obliczen dla double.
    cout<<"a) "<<res_da<<endl;
    cout<<"b) "<<res_db<<endl;
    cout<<"Error for double:"<<endl;
    cout<<"a) "<<error_da<<endl;
    cout<<"b) "<<error_db<<endl;

    cout<<endl<<"*****************************************************";
    cout<<endl<<"First phase complete, results displayed above.";
    cout<<endl<<"*****************************************************";
    cout<<endl<<"Second phase in progress..."<<endl<<endl;

    float err, err1;                                            //Zmienne przechowujace blad obliczeniowy dla typu float.
    for(float h = 0.0000001; h<0.1; h=h*1.03)                   //Petla w ktorej uwzgledniajac odpowiednie h obliczam blad obliczeniowy, a wyniki zapisuje do pliku.
    {
        err = fabs(Dh_fa(x, h)-(-sin(x)));                      //Blad dla wzoru z podpunktu a)
        std::ofstream zapis("blad_fa.txt", ios_base::app);
        zapis<<h<<" "<<err<<endl;

        err1 = fabs(Dh_fb(x, h)-(-sin(x)));                     //Blad dla wzoru z podpunktu b)
        std::ofstream zapis1("blad_fb.txt", ios_base::app);
        zapis1<<h<<" "<<err1<<endl;
    }

    double err2, err3;                                          //Zmienne przechowujace blad obliczeniowy dla typu double.
    for(double h1 = 0.0000000000000001; h1<0.1; h1=h1*1.03)     //Petla w ktorej uwzgledniajac odpowiednie h obliczam blad obliczeniowy, a wyniki zapisuje do pliku.
    {
        err2 = fabs(Dh_da(x, h1)-(-sin(x)));                    //Blad dla wzoru z podpunktu a)
        std::ofstream zapis("blad_da.txt", ios_base::app);
        zapis<<h1<<" "<<err2<<endl;

        err3 = fabs(Dh_db(x, h1)-(-sin(x)));                    //Blad dla wzoru z podpunktu b)
        std::ofstream zapis1("blad_db.txt", ios_base::app);
        zapis1<<h1<<" "<<err3<<endl;
    }

    cout<<"***********************************************************";
    cout<<endl<<"Second phase complete, results saved in four files:"<<endl;
    cout<<"blad_fa.txt, blad_fb.txt, blad_da.txt, blad_db.txt"<<endl;
    cout<<"***********************************************************";

    cout<<endl<<"End of program";



    return 0;
}

//Implementacja funkcji dzieki ktorym policze przyblizenie funkcji w punkcie.
float Dh_fa(float x, float h)
{
    return ((cos(x+h) - cos(x))/h);
}

float Dh_fb(float x, float h)
{
    return ((cos(x+h) - cos(x-h))/(2*h));
}

double Dh_da(double x, double h)
{
    return ((cos(x+h) - cos(x))/h);
}

double Dh_db(double x, double h)
{
    return ((cos(x+h) - cos(x-h))/(2*h));
}


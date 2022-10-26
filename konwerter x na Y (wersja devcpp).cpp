#include <iostream>
#include <locale.h>
#include <string>
#include <cmath>
#include <ctype.h>
#include <cstdlib>
#include <sstream>
//Autorem programu Jest Norbert F zmamy szerzej jako Nubet (https://github.com/Nubet/)
using namespace std;

string to_String(int Number)// z powodu braku wsparcia kompilatora devcpp do c++ 11 odtworzyłem funkcje to_string przy pomocy biblioteki sstream 
{
     std::ostringstream ss;
     ss << Number; // wczytujemy zmienna number 
     return ss.str(); // skorzystanie z .str(); jest mozliwe tylko jesli wczesniej zadeklarowalismy ostringstreama 
}
  
int zamiana_lc(char n){
    if(toupper(n) == 'A')
        return 10;
    if(toupper(n) == 'B')
        return 11;
    if(toupper(n) == 'C')
        return 12;
    if(toupper(n) == 'D')
        return 13;
    if(toupper(n) == 'E')
        return 14;
    if(toupper(n) == 'F')
        return 15;
}
int zamiana_liczba_na_cyfre(int liczba){
	if( liczba == 10 )
        return 'A';
    if( liczba == 11)
        return 'B';
    if( liczba == 12)
        return 'C';
    if( liczba ==  13)
        return 'D';
    if( liczba == 14 )
        return 'E';
    if( liczba == 15)
        return 'F';
}
long zamiana_na_dziesietny(int systemX, string liczbaX){
    long long wynik = 0;
    int p = liczbaX.length()-1;

    for(int i = 0; i <= liczbaX.length()-1; i++){
            //cout << "i: " << i << endl;
            //cout << "\t p: " << p << endl;
            if( isalpha(liczbaX[i]) != 0){
                wynik = wynik + (zamiana_lc(liczbaX[i]) * pow(systemX, p));
            }
            else{
                wynik = wynik + ((liczbaX[i]-48) * pow(systemX, p));
            }
            p--;
    }
    return wynik; // wynik = liczbaX w systemie dziesietnym
}
int zamiana_X_na_Y(int systemY, long long wynik)
{
    int i = 0; // liczba do inkrementowania
    //int r[1]; // tablica zawierajace reszte z dzielenia liczbyX przez systemY
    int w = wynik;
    string r = "";
    while(true){
        //int * r = new int[i+1];
        //r[i] = w % systemY;
        if(w % systemY >= 10){ // dzieki takiemy zapisowy otrzymamy reszte z dzielenia liczby w przez system na jaki chcemy zamienic
			char wynik_modulo = zamiana_liczba_na_cyfre(w % systemY); // wynik_modulo przechowuje liczbe > 10 czyli taka ktora wymaga konwersji na znak
			cout << "Liczbe " << w % systemY << " zapisujemy w postaci " << wynik_modulo << endl;
			r = r + wynik_modulo; // nasze reszty przechowywane sa w jednym stringu czyli defakto tablicy jednak nie musimy znac podczas deklarowania jej wielkosci wiec w taki sposob unikamy korzystania z wskaznikow
        }
		else 
        	r = r + to_String(w % systemY);
  	
        w = w / systemY; // zmienna w to "wynik" czyli dzielnie poprzedniego wyniku przez system na jaki chcemy zamienic(warto zwrocic uwage na to ze zmienna w jest intem a wiec "koncowka" jest obcinana)
        if(w == 0) // korzystamy z nieskonczonej petli jednak przy kazdym obrocie sprawdzamy czy "W" czyl wynik nie jest rowny zeru jesli tak to znaczy ze dalej nie ma sensu juz dzielic i jestesmy w stanie z reszt odczytac liczbe po konwersji a wiec konczymy petle
            break;

        i++;
    }
    for(int j = r.length()-1; j >= 0; j--) // czytanie stringa od tylu
    	cout<< r[j];
	
   
    

}
int main()
{
    setlocale(LC_CTYPE, "Polish"); // zalaczanie polskich znakow
    int systemX, systemY;
    string liczbaX, liczbaY;

    cout << "Podaj system liczby która chcesz zamieniac " << endl;
    cin>>systemX;
    if (systemX < 2 || systemX > 16){ // konwerter zaklada dzialanie dla systemow od 2 do 16
    	cout << "Podałes bledny system(Program obsluguje konwersje od systemy 2 do 16)" << endl;
        return 0;
    }
    cout << "Podaj liczbe jaka chcesz zamieniac " << endl;
    cin>>liczbaX;

    //Walidacja podanych danych
    if(systemX <= 10)
    {
        for(int i = 0; i <= liczbaX.length()-1; i++){
            if( isalpha(liczbaX[i]) != 0){ // sprawdzanie czy i element stringu zawierajacego nasza liczbe do konwersji jest litera jesli tak znaczy to, ze uzytkownik podal bledna dana poniewaz system ktory podal nie uwzglednia wystepowania liter
                cout << "Probujesz wpisac litere w systemie " << systemX;
                return 0;
            }

            if(liczbaX[i]-48 >= systemX){ // Odejmuje 48 poniewaz wyswietlanie i elementu ciagu znakow w przypadku kiedy znakiem jest liczba program wypisze  jej wartosc w postaci ASCII. A jak wiadomo liczby w tablicy ASCII zaczynaja sie od 48 jest to sposob konwersji znaków ascii na nasz alfabet i system
                cout << "Podana liczba jest bledna, Nie jest zapisana w systemenie " << systemX << " poniewaz wystepuje tam liczba " << liczbaX[i] << endl;
                cout << "Poprawny zakres dla systemu " << systemX << " wynosi: " << "0 - " << systemX-1 << endl;
                return 0;
            }
        }
    }
    else
    {
        for(int i = 0; i <= liczbaX.length()-1; i++)
        {
            //cout << isalpha(liczba[i]) << endl;
            if( isalpha(liczbaX[i]) != 0) // funkcja isalpha sprawdza czy wyslany znak jest litera jesli tak zwraca jej odpowiednik z tablicy ascii w przypadku gdy wyslemy liczbe zwroci nam 0 stad zapis != 0
            {
                int max_systemowa = systemX; // program zapisuje porownanie 2 liter jako matematyczne porownanie 2 cyfr jedna juz mamy czyli system ktory podal nam uzytkownik 2 zas pozyskamy z wlasnej funkcji "zamiana_lc" (zamiana litera cyfra)
                if(zamiana_lc(liczbaX[i]) >= max_systemowa){
                       cout << "Podana litera " << liczbaX[i] << " nie znajduje sie w systemie jaki podales "  << endl;
                       return 0;
                }
            }
        }
    }

    cout << "Podaj system na jaki chcesz zamienia wczeoniej podana liczbe " << endl;
    cin>>systemY;


    if(systemX != 10){
        cout << liczbaX << " w systemie 10 to " << zamiana_na_dziesietny(systemX, liczbaX) << endl;
        zamiana_X_na_Y(systemY, zamiana_na_dziesietny(systemX, liczbaX)); // 2 argumentem jest to co zwroci funkcja  zamiana_na_dziesietny
    }
    else {// w przypadku gdy uzytkownik chce zamienic liczbe z systemu dziesietnego jestesmy w stanie oszczedzic moc obliczeniowa nie probojac zamieniac systemu 10 na system 10 
         long long wynik = atoi(liczbaX.c_str()); // lub stoi(liczbaX) <-- ten zapis nie dziala poniewaz zostal wprowadzony w c++ 11 a kompilator devcpp korzysta z 10
         zamiana_X_na_Y(systemX, wynik);
    }


}

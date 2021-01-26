#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Ulamek		//deklaracja klasy
{
private:
	int licznik;	//deklaracja zmiennych prywatnych 
	int mianownik;

public:
	Ulamek();			//konstruktor domyslny
	Ulamek(int, int);	//konstrukotr parametryzujacy
	Ulamek(int parametr);	//konstruktor konwertujacy
	~Ulamek();			//destruktor
	void setLicznik(int);	//gettery i settery
	void setMianownik(int);
	int getLicznik();
	int getMianownik();
	bool czyRowne(Ulamek*);  //funkcja sprawdzajaca czu ulamki sa rowne
	void wyswietl();			//funkcja wyswietlajaca pola klasy 
	operator double();			//operator konwersji zmieniajacy klase na double
};

Ulamek *dzielenie(Ulamek*, Ulamek*);		//deklaracja funkcji dzielenie zwracaja
double pierwiastek(double);					//deklaracja funkcji pierwiastek


int main()
{
	Ulamek ulamek1(2, 3);		//tworzenie instancji klasy ulamek
	Ulamek ulamek2(3, 4);
	int parametr = 5;			//inicjacja zmiennej parametr ktora zostanie zmieniona na klase ulamek konstruktorem konwertujacym
	Ulamek ulamekkonwertowany(parametr);	//zastosowanie konstrukotra konwertujacego w celu zamiany int na klase
	Ulamek ulamek_a(5, 10);
	Ulamek ulamek_b(15, 30);

	cout <<"Po dzieleniu: " << *dzielenie(&ulamek1, &ulamek2)<< endl;		//dzielenie dwoch ulamkow
	cout <<"Po dzieleniu: " << *dzielenie(&ulamek1, &ulamekkonwertowany) << endl;	//dzielenie dwoch ulamkow w tym jednego tworzonego przez konstruktor konwertujacy

	if (ulamek_a.czyRowne(&ulamek_b))	//sprawdzanie czy ulamek_a jest rownym ulamek_b
		cout << "Sa rowne" << endl;
	else
		cout << "Nie sa rowne" << endl;
	
	ulamek1.operator double();			//zamiana klasy ulamek na zmienna typu double
	cout << "Po pierwiastkowaniu: " << pierwiastek(ulamek1) << endl;	//wywolanie funckji pierwiastek obliczajacej pierwiastek z klasy zmienionej na double

	system("pause");
	return 0;
}

Ulamek::Ulamek()  //konstruktory
{
	setLicznik(1);
	setMianownik(1);
}
Ulamek::Ulamek(int licznik, int mianownik)
{
	setLicznik(licznik);
	setMianownik(mianownik);
}
Ulamek::Ulamek(int parametr)
{
	setLicznik(parametr);
	setMianownik(1);
}
Ulamek::~Ulamek()		//destruktor
{
}
void Ulamek::setLicznik(int licznik)  //settery 
{
	this->licznik = licznik;
}
void Ulamek::setMianownik(int mianownik)
{
	this->mianownik = mianownik;
}
int Ulamek::getLicznik()		//gettery
{
	return licznik;
}
int Ulamek::getMianownik()
{
	return mianownik;
}
bool Ulamek::czyRowne(Ulamek* ulamek2)		//funkcja sprawdzajaca czy ulamki sa rowne
{
	if ((this->licznik) * (ulamek2->mianownik) == (ulamek2->licznik) * (this->mianownik))  //z definicji dwa ulamki a/b i c/d sa sobie rowne gdy
		return true;																		//a/b = c/d mozna przeksztalcic ten wzor na a*d = c*b
	else// gdy warunek jest spelniony zwracana jest wrtosc true, natoimast gdy nie zwracana jest wartosc false
		return false;
}
void Ulamek::wyswietl()		//funckja wyswietlacja
{
	cout << "Licznik: " << getLicznik() << endl;
	cout << "Mianownik: " << getMianownik() << endl;
	cout << "Ulamek: " <<(double)getLicznik() / (double)getMianownik() << endl;
}
Ulamek::operator double()		//operator konwersji, zamienia on klase Ulamek na zmienna typu double
{
	return static_cast<double>((double)licznik/(double)mianownik);  
}
Ulamek* dzielenie(Ulamek* ulamek1, Ulamek* ulamek2)		//funkcja dzielaca jeden pierwiastek przez drugi
{														//w tresci zadania jest prosba o utworzenie funkcji zwracajacej obiekt, natomiast ja zrobilem funkcje z
	Ulamek* podzielony = new Ulamek();					//zwracajaca wskaznik do obiektu, poniewaz gdy probowalem zwrocic obiekt program nie dzialal poprawnie
	podzielony->setLicznik((ulamek1->getLicznik()) * (ulamek2->getMianownik()));		//dzielenie ulamkow to inaczej mnozenie ich przez odwrotnosc
	podzielony->setMianownik((ulamek1->getMianownik()) * (ulamek2->getLicznik()));
	//podzielony->wyswietl();
	
	return podzielony;			//zwracanie wskaznika do obiektu 
}
double pierwiastek(double ulamek)		//funkcja liczaca pierwiastek kwadratowy z przeslanej "klasy"
{
	double squareRoot;
	squareRoot = sqrt(ulamek);

	return squareRoot;
}
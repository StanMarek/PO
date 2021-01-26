#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#define PI 3,141592		//definicja PI jako liczby do obliczen pola kola

using namespace std;

class Prostokat; //nalezy zaznaczy na samym poczataku ze istnieje klasa Prostokat aby klasa Punkt wiedziala o niej i mogla wykorzystac w funkcji czyWspolne()

class Punkt
{
public:
	Punkt();
	~Punkt();
	void wyswietl();
	bool czyWspolne(Prostokat* prostokat);
	void setX(double);
	void setY(double);
	double getX();
	double getY();
	friend void ustawXY(Punkt*, double, double);

private:
	double x;
	double y;
};

class Prostokat
{
public:
	Prostokat();
	Prostokat(double, double, double, double);
	~Prostokat();
	double getSzer();
	double getWys();
	double getXPunktu();
	double getYPunktu();
	void setSzer(double);
	void setWys(double);

private:
	Punkt lewy_dolny;
	double szerokosc;
	double wysokosc;
};

class Kolo
{
public:
	Kolo();
	Kolo(double, double, int);
	~Kolo();
	bool czyStyczne(Kolo*);
	void setR(int);
	int getR();
	void setXSrodka(double);
	void setYSrodka(double);
	double getXSrodka();
	double getYSrodka();

private:
	Punkt srodek;
	int promien;
};
//poniezej znajduja sie deklaracje funckji
void ustawXY(Punkt*, double, double);
void pokazInfo(Prostokat*);
void pokazInfo(Kolo*);
double odlegloscPunktow(Punkt*, Punkt*); //funckja pomocnicza zwracajaca odleglosc dwoch punktow

int main()
{
	srand(time(NULL));	//dzieki temu mamy pewnosc ze ziarno bedzie inne za kazdym razem	
	Punkt p1;		//tworzenie obiektow typu Punkt
	Punkt p2;
	Punkt p3;
	ustawXY(&p1, 5, 2);	//ustawianie ich wspolrzednych
	ustawXY(&p2, -7, -7);
	ustawXY(&p3, 1.25, 2.5);
	p1.wyswietl();	//wyswietlanie wspolrzednych punktow
	p2.wyswietl();
	p3.wyswietl();

	Prostokat prost1(13, 10, -8, -6);	//tworzenie prostokata
	if (p1.czyWspolne(&prost1))		//sprawdzanie czy wszystkie punkty naleza do prostokata
		cout << "P1 Wspolne" << endl;
	if (p2.czyWspolne(&prost1))
		cout << "P2 Wspolne" << endl;
	if (p3.czyWspolne(&prost1))
		cout << "P3 Wspolne" << endl;

	Kolo k1(0, 0, 10);		//tworzenie kola
	pokazInfo(&k1);		//wypisywanie informacji o kole i prostokacie
	pokazInfo(&prost1);

	Kolo* koleczkaokraglehehe = new Kolo[1000];		//tworzenie tablicy tysiaca kol

	for (int i = 0; i < 1000; i++)		//w petli nastepuje przypisanie wartosci kazdemu kolu
	{
		koleczkaokraglehehe[i].setXSrodka((int)(rand() % 41) + (-20));
		koleczkaokraglehehe[i].setYSrodka((int)(rand() % 41) + (-20));
		koleczkaokraglehehe[i].setR((int)(rand() % 20) + 1);
	}

	int iloscStycznych = 0;		//inicjacja funkcji ilczacej ilosc kol stycznych do kola k1
	for (int i = 0; i < 1000; i++)		//w petli sprawdzany jest warunek dla kazdego kola, jesli jest styczne ilosc jest zwiekszana o 1
		if (k1.czyStyczne(&koleczkaokraglehehe[i]))
			iloscStycznych++;
			
	cout << "Ilosc kombinacji okregow stycznych: " << iloscStycznych << endl;
		

	system("pause");
	return 0;
}

Kolo::Kolo() //konstrukor domyslny
{
	srodek.setX(0);
	srodek.setY(0);
	setR(0);
} 

Kolo::Kolo(double x, double y, int r) //konstruktor parametryzujacy
{
	srodek.setX(x);
	srodek.setY(y);
	setR(r);
}

Kolo::~Kolo() //destrukor
{
}

bool Kolo::czyStyczne(Kolo* kolo)
{	//styczne wewnetrznie
	if (odlegloscPunktow(&this->srodek, &kolo->srodek) == abs(this->getR() - kolo->getR())) //kola sa styczne wewnetrznie jest odleglosc ich srodkow jest rowna wartosci bezwzglednej roznicy ich promieni
		return true;
	//styczne zewnetrznie
	else if (odlegloscPunktow(&this->srodek, &kolo->srodek) == (this->getR() + kolo->getR())) //okregi sa styczne zewnetrznie jest odleglosc ich srodkow jest rowna sumie ich promieni
		return true;
	else
		return false;
}

void Kolo::setR(int promien)
{
	this->promien = promien;
}

int Kolo::getR()
{
	return promien;
}

void Kolo::setXSrodka(double x)
{
	this->srodek.setX(x);
}

void Kolo::setYSrodka(double y)
{
	this->srodek.setY(y);
}

double Kolo::getXSrodka()
{
	return srodek.getX();
}

double Kolo::getYSrodka()
{
	return srodek.getY();
}

Prostokat::Prostokat() //konstrukor domyslny
{
	lewy_dolny.setX(0);
	lewy_dolny.setY(0);
	setSzer(5.0);
	setWys(5.0);
}

Prostokat::Prostokat(double szer, double wys, double x, double y)	//konstruktor parametryzujacy
{
	this->lewy_dolny.setX(x);
	this->lewy_dolny.setY(y);
	setSzer(szer);
	setWys(wys);
}

Prostokat::~Prostokat() //destruktor
{
}

double Prostokat::getSzer()
{
	return szerokosc;
}

double Prostokat::getWys()
{
	return wysokosc;
}

double Prostokat::getXPunktu()
{
	return lewy_dolny.getX();
}

double Prostokat::getYPunktu()
{
	return lewy_dolny.getY();
}

void Prostokat::setSzer(double szerokosc)
{
	this->szerokosc = szerokosc;
}

void Prostokat::setWys(double wysokosc)
{
	this->wysokosc = wysokosc;
}

Punkt::Punkt() //konstrukor domyslny
{
	setX(0);
	setY(0);
}

Punkt::~Punkt() //destruktor
{
}

void Punkt::wyswietl() //funkcja wyswietlajaca parametry punktu
{
	cout << "X punktu: " << getX() << endl;
	cout << "Y punktu: " << getY() << endl;
}

bool Punkt::czyWspolne(Prostokat* prostokat)
{
	//punkt nalezy do prostakata jesli jego wspolrzedna X zawiera sie w przedziale jego szerokosci a jego wpolrzedna Y zawiera sie w przedziale wysokosci wlacznie
	if ((this->getX() >= prostokat->getXPunktu()) && (this->getX() <= (prostokat->getXPunktu() + prostokat->getSzer())))
	{
		if ((this->getY() >= prostokat->getYPunktu()) && (this->getY() <= (prostokat->getYPunktu() + prostokat->getWys())))
			return true;
		else
			return false;
	}
	else
		return false;
}

void Punkt::setX(double x)
{
	this->x = x;
}

void Punkt::setY(double y)
{
	this->y = y;
}

double Punkt::getX()
{
	return x;
}

double Punkt::getY()
{
	return y;
}

void ustawXY(Punkt* punkt, double x, double y)
{
	//przekaznie przez wskazniki punktu powoduje zamiane na stale a nie do konca definicji funkcji
	punkt->setX(x);
	punkt->setY(y);
}

void pokazInfo(Prostokat* prostokat)	//wyswietlanie informacji o prostokacie
{
	cout << "X1: " << prostokat->getXPunktu() << endl;
	cout << "Y1: " << prostokat->getYPunktu() << endl;
	cout << "X2: " << prostokat->getXPunktu() + prostokat->getSzer()<< endl;
	cout << "Y2: " << prostokat->getYPunktu() << endl;
	cout << "X3: " << prostokat->getXPunktu() + prostokat->getSzer() << endl;
	cout << "Y3: " << prostokat->getYPunktu() + prostokat->getWys() << endl;
	cout << "X4: " << prostokat->getXPunktu() << endl;
	cout << "Y4: " << prostokat->getYPunktu() + prostokat->getWys() << endl;
	cout << "Pole prostokata: " << prostokat->getSzer() * prostokat->getWys() << endl;
}

void pokazInfo(Kolo* kolo)	//wyswietlanie infromacji o kole
{
	cout << "X srodka kola :" << kolo->getXSrodka() << endl;
	cout << "Y srodka kola: " << kolo->getYSrodka() << endl;
	cout << "Promien R kola: " << kolo->getR() << endl;
	cout << "Pole kola: " << PI * (kolo->getR() * kolo->getR());
	cout << endl;
}

double odlegloscPunktow(Punkt* p1, Punkt* p2)	//liczenie odleglosci dwoch punktow
{
	double d;
	double x1 = p2->getX() - p1->getX();
	double y1 = p2->getY() - p1->getY();
	d = sqrt((x1 * x1) + (y1 * y1));
	//odleglosc miedzy punktami to pierwiastek kwadratowy sumy kwadratow z roznic ich wspolrzednych
	return d;
}


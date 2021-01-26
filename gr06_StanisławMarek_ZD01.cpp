#include <iostream>	
#include <string>

using namespace std;


class Bohater
{
private:
	string pseudonim;		//zmienne prywatne
	string klasa;
	int sila_ataku;
	static int licznik;

public:
	static int counter;		//nowa zmienna statyczna dzieki ktorej mozna bez problemu pokazac licznik
	Bohater();  //konstruktor domyslny
	Bohater(string, string, int);  //konstruktor parametryzujacy
	~Bohater();		//destruktor
	void wyswietl();  //funkcja wyswietlajaca
	string getImie();  //settery i gettery
	void setImie(string);		//umozliwiaja dostep do danych prywatnych 
	string getKlasa();		//czyli tych poddanych "enkapsukacji"/"hermetyzacji"
	void setKlasa(string);
	int getSila();
	void setSila(int);
	int getID();
	static int getCounter();
};


class Ekwipunek
{
private:
	string rodzaj;			//zmienne prywatne
	string material;
	double wartosc;
	Bohater* BOHATER;		//tworzenie wskznika do klasy Bohater

public:
	Ekwipunek();		//konstruktor dokmyslny
	~Ekwipunek();		//destruktor
	Ekwipunek(string, string, double, Bohater*); //konstruktor parametryzuj�cy
	string getRodzaj();		//settery i gettery
	string getMaterial();
	double getWartosc();
	void setRodzaj(string);
	void setMaterial(string);
	void setWartosc(double);
	void wyswietl();
	void setBohater(Bohater*);
	Bohater* getBohater();
};



int main()
{
	Bohater *bohater = new Bohater("Piotr", "Magik", 2137); //dynamiczne tworzenie bohatera
	bohater->wyswietl();		//wyswietlanie pol oboiektu bohater
	bohater->setSila(1111);		//zamiana sily bohatera
	cout << endl;		
	bohater->wyswietl();		//wyswietlenie zmienionych pol obiektu bohater
	cout << endl;

	Bohater** bohaterowie = new Bohater* [2];		//tworzenie dynamicznej tablicy 2D przechowujacej bohaterow
	for (int i = 0; i < 2; ++i)						//nalezy to robic w petli tworzac nawijmy to tabele wskaznikow do obiektow
	{
		bohaterowie[i] = new Bohater[2];			//tworzenie drugiego "wymiaru" tablicy
	}
	
	(bohaterowie[0][0]).setSila(10);				//nie wiedzialem czy pola bphaterow z tablicy nalezy uzupelnic w petli czy pominac
	(bohaterowie[0][1]).setSila(11);				//wiec zdecydowalem sie na "reczne" uzupelnienie kazdego po kolei
	(bohaterowie[1][0]).setSila(12);
	(bohaterowie[1][1]).setSila(13);
	(bohaterowie[0][0]).setImie("Imie1");
	(bohaterowie[0][1]).setImie("Imie2");
	(bohaterowie[1][0]).setImie("Imie3");
	(bohaterowie[1][1]).setImie("Imie4");
	(bohaterowie[0][0]).setKlasa("Klasa1");
	(bohaterowie[0][1]).setKlasa("Klasa2");
	(bohaterowie[1][0]).setKlasa("Klasa3");
	(bohaterowie[1][1]).setKlasa("Klasa4");

	for (int i = 0; i < 2; i++)						//tutaj uzywajac petli wypisuje sile kazdego bohatera razem z jego indeksem w tabeli
	{												//oczywiscie nalezy tu uzyc petli zagniezdzonych poniewaz to tablica 2D
		for (int j = 0; j < 2; j++) 
		{
			cout << "Sila bohatera o indeksie " << i << j << ": " << bohaterowie[i][j].getSila() << endl;
		}
	}

	int suma = 0;	//zmienna suma przechowywac bedzie sume sil bohaterow, nalezy nadac jej poczatkowa wartosc rowna 0
	for (int i = 0; i < 2; i++)		//tutaj rowniez uzywamy petli zagniezdzonych ze wzgledu na wymiar tablicy
	{
		for (int j = 0; j < 2; j++)
		{
			suma += (bohaterowie[i][j]).getSila();
		}
	}
	cout << "Suma sily: " << suma << "\n\n";		//wyswietlenie sumy
	cout << "Licznik przed usunieciem: " << Bohater::getCounter();		//wyswietlenie licznika
	for (int i = 0; i < 2; i++) {					//tutaj przechodzimy do usuwania dynamicznie zadeklarowanych bohaterow z tablicy
		delete[] bohaterowie[i];					//robimy to w petli, najpierw usuwany jest jeden wymiar wskaznikow do obiektow
	}
	delete[] bohaterowie;							//a nastepnie usuwamy kolejny "rzadek" tablicy wskaznikow	
	delete bohater;			//usuawnie pierwszego obiektu, rowniez dynamicznego
	cout << "\nLicznik po usunieciu: " << Bohater::getCounter() << endl << endl; //licznik po usunieciu wszytskich obiektow

	//Ekwipunek obiekt_ekw1; //statyczne tworzenie instancji

	Ekwipunek *obiekt_ekw1 = new Ekwipunek(); //dynamiczne tworzenie instancji klasy ekwipunek
	obiekt_ekw1->wyswietl();			//wyswietlanie pol klasy
	cout << endl;
	cout << "Klasa: " << obiekt_ekw1->getBohater()->getKlasa() << endl;  //wyswietlanie klasy obiektu Bohater utworzonego w klasie Ekwipunek
	cout << endl;
	//Ekwipunek obiekt_ekw2("Luk", "Drewno", 212.50); //statyczne tworzenie instancji
	Bohater nowybohater("IMIE", "KLASA", 2000);				//tworzenie nowego bohatera aby przekazac go jako parametr konstruktora parametryzujacego 
	Ekwipunek* obiekt_ekw2 = new Ekwipunek("Luk", "Drewno", 212.50, &nowybohater); //dynamiczne tworzenie instancji, z przekazanym adresem do utworzonego bohatera
	obiekt_ekw2->wyswietl();			//wyswietlanie pol klasy
	cout << endl;
	cout << "Klasa: " << obiekt_ekw2->getBohater()->getKlasa() << endl;  //wyswietlnie klasy obiektu Bohater przekazanego jako parametr konstruktora klasy ekwipunek

	//obiekt_ekw1.~Ekwipunek(); //usuwnanie statycznej instancji klasy Ekwipunek
	//obiekt_ekw2.~Ekwipunek(); //usuwnanie statycznej instancji klasy Ekwipunek
	delete obiekt_ekw1; //usuwnanie dynamicnzej instancji klasy Ekwipunek
	delete obiekt_ekw2; //usuwnanie dynamicznej instancji klasy Ekwipunek

	system("pause");
	return 0;
}

Ekwipunek::Ekwipunek()
{
	BOHATER = new Bohater(); //tworzenie nowego obiektu Bohater
	setRodzaj("Miecz");			//przypisanie domyslnych wartosci ekwipunkowi
	setMaterial("Stal");
	setWartosc(175.99);
	//cout << "Klasa bohatera: " << bohaterekw->getKlasa() << endl;
}
Ekwipunek::~Ekwipunek()		//destruktor
{
	//cout << "destruktor" << endl;
}
Ekwipunek::Ekwipunek(string rodzaj, string material, double wartosc, Bohater* BOHATER)  //jako parametr przesylam rowniez wskaznik do klasy Bohater
{
	setRodzaj(rodzaj);		//zmiana pol Ekwipunku z domyslnych na przeslane
	setMaterial(material);
	setWartosc(wartosc);
	this->BOHATER = BOHATER;	//przypisanie przeslanego bohatera do wlasnie tego bohatera na ktorym bede operowac uzywajac instancji tej klasy utworzonej tym konstruktorem
}
string Ekwipunek::getRodzaj()		//definicje setterow i getterow
{
	return rodzaj;
}
string Ekwipunek::getMaterial()
{
	return material;
}
double Ekwipunek::getWartosc()
{
	return wartosc;
}
void Ekwipunek::setRodzaj(string rodzaj)
{
	this->rodzaj = rodzaj;
}
void Ekwipunek::setMaterial(string material)
{
	this->material = material;
}
void Ekwipunek::setWartosc(double wartosc)
{
	this->wartosc = wartosc;
}

void Ekwipunek::wyswietl()		//definicja funckji wyswietl
{
	cout << "Rodzaj: " << getRodzaj() << endl;
	cout << "Material: " << getMaterial() << endl;
	cout << "Wartosc: " <<getWartosc() << endl;
}

void Ekwipunek::setBohater(Bohater* BOHATER)	//ustwainie bohatera jako tego przeslanego
{
	this->BOHATER = BOHATER;
}

Bohater* Ekwipunek::getBohater()		//funkcja zwracajaca wskaznik do klasy Bohater 
{										//uzywana jest do wyswietlenia klasy bohatera utworzonego konstruktorem domyslnym
	return BOHATER;						//i do wyswietlenia klasy bohatera przeslanewgo jako parameter
}

Bohater::Bohater()
{
	licznik++; //przy tworzeniu kazdej instancji klasy licznik ulega zwiekszeniu o 1
	counter = licznik;	//przypisanie wartosci licznika do zmiennej counter
	setImie("JAKIESIMIE");
	setKlasa("JAKASKLASA");
	setSila(1905);
	//cout << "Konstruktor domyslny\n";
	//cout << "Licznik: " << getID() << endl;
}
Bohater::Bohater(string pseudonim, string klasa, int sila_ataku)
{
	licznik++;		//identycznie jak w konstruktorze domyslnym
	counter = licznik;
	setImie(pseudonim);		//ustawienie przeskanych wartosci jako nowych dla utworzonej instancji
	setKlasa(klasa);
	setSila(sila_ataku);
	//cout << "Konstruktor parametryzujacy" << endl;
}
Bohater::~Bohater()
{
	licznik--;		//przyusuwaniu instancji licznik ulega zmnijeszeniu o 1
	counter = licznik;
	//cout << "Destruktor\n";
	//cout << "Licznik: " << getID() << endl;
}
int Bohater::licznik = 0;		//przypisanie wartosci 0 licznikowi
string Bohater::getImie()		//ponizej znajduja sie definicje setterow i getterow
{
	return pseudonim;
}
void Bohater::setImie(string pseudonim)
{
	this->pseudonim = pseudonim;
}
string Bohater::getKlasa()
{
	return klasa;
}
void Bohater::setKlasa(string klasa)
{
	this->klasa = klasa;
}
int Bohater::getSila()
{
	return sila_ataku;
}
void Bohater::setSila(int sila_ataku)
{
	this->sila_ataku = sila_ataku;
}
void Bohater::wyswietl()	//funckja wyswietlajaca pola klasy, wykorzystuje gettery
{
	cout << "Pseudonim: " << getImie() << endl;
	cout << "Klasa: " << getKlasa() << endl;
	cout << "Sila ataku: " << getSila() << endl;
	//cout << "Licznik: " << getID() << endl;
}
int Bohater::getID()
{
	return licznik;
}
int Bohater::counter = licznik;  //przypisanie wartosci licznika do countera aby zliczal poprawnie, bez tej linijki program sie nie kompiluje
int Bohater::getCounter()
{
	return counter;
}



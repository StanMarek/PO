#include <string>
#include <iostream>

using namespace std;
class Person
{
public:
	Person();	//konstruktor domyslny
	Person(string, string, int);	//konstruktor parametryzujacy
	Person(const Person&);	//konstruktor kopiujacy
	~Person();	//destruktor
	int age();	//funkcja wiek
	void setYOB(int);	//setter roku urodzenia mozna uzyc w pkt 7
	string Name();	//zwraca imie
	friend ostream& operator<<(ostream& os, const Person& per); //przeciazenie operatora wypisujacego dane
protected:
	string name;
	string surname;
	int yearOfBirth;
private:
};

class Employee :
	public Person	//dziedziczenie publiczne
	//Osoba->Pracownik
{
public:
	Employee();	//konstruktor domyslny
	Employee(string);	//konstruktor parametryzujacy 1
	Employee(string, string, string, int);	//konstruktor parametryzujacy 2
	~Employee();	//destruktor
protected:
	string voivodeship;
	static const double minSalary; //deklaracja statycznej stalej
private:
};

class IT_Guy :
	public Employee	//dziedziczenie publiczne
	//Osoba->Pracownik->Informatyk
{
public:
	using Person::age; //zaznaczamy ze bedziemy korzystac z funkcji znajdujacej sie "2 poziomy wyzej"
	IT_Guy();	//konstruktor domyslny
	IT_Guy(string, double);	//konstruktor parametryzujacy 1
	IT_Guy(string, string, string, string, int, double);	//konstruktor parametryzujacy 2
	IT_Guy(const IT_Guy&);	//konstruktor kopiujacy
	~IT_Guy();	//destruktor
	void setVoi(string);
	friend ostream& operator<<(ostream& os, const IT_Guy& it); //przeciazony operator wypisywania danych klasy
protected:
private:
	string specialization;
	double multiplier;
	double salary;
};

class RetiredPerson :
	public Person	//dziedziczenie publczne
	//Osoba->Emeryt
{
public:
	RetiredPerson(); //konstruktor domyslny
	RetiredPerson(double);	//konstruktor parametryzujacy 1
	RetiredPerson(string, string, int, double);	//konstruktor parametryzujacy 2
	RetiredPerson(const Person&);	//konstruktor kopiujacy Obiekt klasy bazowej jako Obiekt klasy pochodnej
	~RetiredPerson();	//destruktor
	friend ostream& operator<<(ostream& os, const RetiredPerson& rp);	//przeciazony operator wypisywania
protected:
private:
	double pension;
};

RetiredPerson* createRetiredPeople(Person **, int); //deklaracja funkcji

int main()
{
	//5
	Person o1 = Person("Jakas", "Osoba", 1930);
	cout << o1 << endl;

	//6
	IT_Guy i1 = IT_Guy("Pan", "Informatyk", "MiejscePracy", "Specjalizacja", 1980, 3.14);
	cout << i1;
	cout << "Wiek: " << i1.age() << endl;
	cout << endl;

	//7
	IT_Guy i2 = IT_Guy(i1);
	cout << i2;
	cout << "Wiek: " << i2.age() << endl;
	cout << endl;

	//8
	i2.setVoi("NoweWojewodztwo");
	cout << i2 << endl;

	//9
	int arraySize = 3;
	Person** peopleArray = new Person * [arraySize]; //dynamiczna tablica wskaznikow do obiektow klasy Osoba
	peopleArray[0] = &o1;	//przypisanie pola 0
	peopleArray[1] = &i1;	//przypisanie pola 1
	peopleArray[2] = &i2;	//przypisanie pola 2
	int iterator = 0;
	while (iterator < arraySize)
	{
		cout << *peopleArray[iterator] << endl;
		iterator++;
		//w petli wypisuje kazda osobe po kolei
	}

	//10
	RetiredPerson* emerytArray = createRetiredPeople(peopleArray, arraySize);	//przypisanie wskaznika przeslanego z funkcji do zmiennej
	int iterator2 = 0;
	while (iterator2 < arraySize)
	{
		cout << emerytArray[iterator2];
		iterator2++;
		//wypisanie w petli
	}

	delete[] peopleArray;	//usuniecie pierwszej tablicy dynamicznej z pamieci
	delete[] emerytArray;	//usuaniecie przeslanej tablicy dynamicznej z pamieci

	return 0;
}

RetiredPerson* createRetiredPeople(Person **personArray, int arraySize) //definicja funkcji
{
	/*funkcja ta zwraca wskaznik do dynamicznej tablicy obiektow klasy Emeryt*/
	int n=0;
	unsigned int size=0;
	for (n; n < arraySize; n++)
	{
		if (personArray[n]->age() > 65)
			size++;
	}
	/*aby obliczyc ilosc miejsca jakie nalezy przeznaczyc na nowa tablice
	szukamy ilosc wszystkich ludzi po 65 roku zycia i zapiusujemy je do zmiennej*/
	RetiredPerson* retiredPeople = new RetiredPerson[size]; //dynamiczna tablica
	
	int i = 0;
	for (n = 0; n < arraySize; n++)
	{
		if (personArray[n]->age() > 65)
		{
			retiredPeople[i] = RetiredPerson(*personArray[n]);
			i++;
		}
	}
	/*jezeli wiek osoby jest wiekszy niz 65 to jest ona przypisywana do wolnej komorki tej tablicy*/

	return retiredPeople;
}

Person::Person() :name("defname"), surname("defsurname"), yearOfBirth(0)
{
}

Person::Person(string na, string sur, int yob) : name(na), surname(sur), yearOfBirth(yob)
{
}

Person::Person(const Person& per)
{
	name = per.name;
	surname = per.surname;
	yearOfBirth = per.yearOfBirth;
}

Person::~Person()
{
}

int Person::age()
{
	/*wiek to roznica obecnego roku i roku w ktorym osoba sie urodzila*/
	int currentYear = 2020;
	return currentYear - yearOfBirth;
}

void Person::setYOB(int yob)
{
	this->yearOfBirth = yob;	//przeslaney rok jest ustawiany jako rok urodzenia obiektu
}

string Person::Name()
{
	return string(name);
}

ostream& operator<<(ostream& os, const Person& per)
{
	os << "Imie: " << per.name << endl;	//wypisanie imienia
	os << "Nazwisko: " << per.surname << endl;	//wypisanie nazwiska
	os << "Rok urodzenia: " << per.yearOfBirth << endl;	//wypisanie roku urodzenia

	return os;
}

Employee::Employee() :voivodeship("voi"), Person()
{
	/*na liscie inicjalizacyjnej kazdego konstruktora tej klasy
	wywolywany jest konstrukor klasy bazowej
	Person() - domyslny*/
}

Employee::Employee(string voi) :voivodeship(voi), Person()
{
}

Employee::Employee(string nam, string sur, string voi, int yob) : Person(nam, sur, yob)
{
	/*Person(nam, sur, yob) - parametryzujacy */
	voivodeship = voi;
}

Employee::~Employee()
{
}

const double Employee::minSalary = 2137; //definicja statycznej stalej

IT_Guy::IT_Guy() :specialization("spec"), Employee()
{
	/*na liscie inicjalizacyjnej kazdego konstruktora tej klasy
	wywolywany jest konstrukor klasy bazowej
	Employee() - domyslny zawiera w sobie konstruktor klasy bazowej Person()
	wywolujac Employee() wywolujemy Person()*/
}

IT_Guy::IT_Guy(string spec, double multi) : specialization(spec), Employee()
{
	/*wyplata liczona jest jako iloczyn minimalnego wynagrodzenia i
	mnoznika */
	salary = minSalary * multi;
}

IT_Guy::IT_Guy(string nam, string sur, string voi, string spec, int yob, double multi) :Employee(nam, sur, voi, yob)
{
	/*Employee(nam, sur, voi, yob) - konstruktor paramteryzujacy zawiera w sobie konstrukor parametryzujacy klasy bazowej
	Person(nam, sur, yob), wywolujac Employee(nam, sur, voi, yob) wywolujemy Person(nam, sur, yob) */
	specialization = spec;
	multiplier = multi;
	salary = minSalary * multi;
}

IT_Guy::IT_Guy(const IT_Guy& copy)
{
	/*konstruktor kopiujacy zgodnie z trescia polecenia kopiuje wszytskie dane z obiektu oprocz
	imie, nazwisko i rok urodzenia*/
	voivodeship = copy.voivodeship;
	specialization = copy.specialization;
	multiplier = copy.multiplier;
	salary = copy.salary;
	/*zgodnie z trescia polecenia w tym konstruktorze nadawane sa nowe wartosci imienia, nazwiska i roku*/
	name = "NoweImie";
	surname = "NoweNazw";
	yearOfBirth = 1940;
}

IT_Guy::~IT_Guy()
{
}

void IT_Guy::setVoi(string voi)
{
	this->voivodeship = voi;
}

ostream& operator<<(ostream& os, const IT_Guy& it)
{
	//wypisywanie
	/*Imie, Nazwisko, Rok urodzenia
	specjalizacja, wojewodztwo
	wyplata*/
	os << it.name << " " << it.surname << ", " << it.yearOfBirth << endl;
	os << it.specialization << ", " << it.voivodeship << endl;
	os << "Wyplata: " << it.salary << endl;

	return os;
}

RetiredPerson::RetiredPerson() :Person(), pension(0)
{
	/*kazdy konstrukor klasy Emeryt wywoluje konstruktor klasy Osoba
	w zaleznosci od konstrukora klasy pochodnej wywolywane sa rozne konstruktory
	klasy bazowej*/
}

RetiredPerson::RetiredPerson(double pen) :pension(pen), Person()
{
}

RetiredPerson::RetiredPerson(string nam, string sur, int yob, double pen) : Person(nam, sur, yob), pension(pen)
{
}

RetiredPerson::RetiredPerson(const Person& retiring) : Person(retiring)
{
	/*konstrukor kopiujacy klasy Emeryt kopiuje dane obiektu klasy Osoba
	a pensje ustala w zaleznosci od wieku i roku urodzenia*/
	pension = (double)age() * yearOfBirth / 100;
}

RetiredPerson::~RetiredPerson()
{
}

ostream& operator<<(ostream& os, const RetiredPerson& rp)
{
	//wypisywanie
	/*Imie, Nazwisko, Rok urodzenia
	emerytura*/
	os << rp.name << " " << rp.surname << ", " << rp.yearOfBirth << endl;
	os << "Emerytura: " << rp.pension << endl;
	return os;
}
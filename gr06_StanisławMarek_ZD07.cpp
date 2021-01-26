#include<string>
#include<iostream>

using namespace std;

class Passenger
{
private:
	string name;
	string surname;
	int age;

public:
	Passenger();
	Passenger(string, string, int);
	~Passenger();
	void displayInfo();
	int getAge();
	string getName();
	string getSurname();
	friend ostream& operator<<(ostream& os, const Passenger& pass);

};

class Coach
{
private:
	string destination;
	double ticketPrice;
	const int seatsLimit;
	Passenger** passengers;

public:
	Coach();
	Coach(string, double, int);
	~Coach();
	void displayInfo();
	double getPrice();
	Coach& operator++(int);
	Coach& operator--(int);
	Coach& operator+=(Passenger&);	//metoda klasy
	friend Coach& operator-=(Coach&, Passenger&);	//zaprzyjazniona funkcja globalna
	void showPassengers();
};

void swap(Passenger*, Passenger*); //deklaracja funkcji pomocniczej

int main(void)
{
	//3
	const int amountOfPassengers = 5;
	Passenger passengers[amountOfPassengers] =
	{
		Passenger("Andrzej", "Duda", 21),
		Passenger("Stanislaw", "Zoltek", 37),
		Passenger("Krzy-Krzysztof", "Bosak", 4),
		Passenger("Major Wojciech", "Suchodolski", 20),
		Passenger("Krzysztof", "Kononowicz", 69),
	};
	for (int i = 0; i < amountOfPassengers; i++)
		cout << passengers[i];
	cout << endl;

	//4
	/*w celu segregacji wzgledem wieku uzywam algorytm sortowania bombelkowego
	wykorzystujaca pole wiek wzgledem ktorego operujemy, jezeli wiek pasazera na miesjcu jest wiekszy
	niz pasazaera na miejscu wczesnijeszym to sa oni zamieniani miejscami*/
	for (int i = 0; i < amountOfPassengers; i++)
		for (int j = amountOfPassengers - 1; j > i; j--)
		{
			if (passengers[j].getAge() > passengers[j - 1].getAge())
			{
				swap(passengers[j], passengers[j-1]);	//funkcja pomocnicza
			}
		}
	for (int i = 0; i < amountOfPassengers; i++)
		cout << passengers[i];
	cout << endl;

	//5
	Coach bus = Coach("Wybory prezydneckie 10 maja 2020", 12.5, 35);
	bus.displayInfo();
	cout << endl;

	//6
	for (int i = 0; i < 3; i++)
		bus++;
	cout << "Nowa cena: " << bus.getPrice() << endl;
	cout << endl;

	//7
	bus += passengers[0];
	bus += passengers[1];
	bus += passengers[2];
	bus += passengers[3];
	bus.showPassengers();
	cout << endl;

	//8
	bus -= passengers[2];
	bus.showPassengers();
	
	return 0;
}

void swap(Passenger* a, Passenger* b)
{
	/*funkcja pomocnicza otzrymuje w argumentach dwa wskazniki do obiekotw
	jej celem jest zamiana ich wartosci*/
	Passenger temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

Passenger::Passenger() : name("name"), surname("surname"), age(0)
{
}

Passenger::Passenger(string imie, string nazwisko, int wiek) : name(imie), surname(nazwisko), age(wiek)
{
}

Passenger::~Passenger()
{
}

void Passenger::displayInfo()
{
	cout << name << " " << surname << ", " << age << endl;
}

int Passenger::getAge()
{
	return age;
}

string Passenger::getName()
{
	return string(name);
}

string Passenger::getSurname()
{
	return string(surname);
}

ostream& operator<<(ostream& os, const Passenger& pass)
{
	/*przeciazanie operatora << to tworzenie zaprzyjaznionej funkcji globalnej zwracajacej
	referencje do obiektu klasy ostream
	uzywajac cout<<klasa kompilator wie ze chodzi nam o ta tak jakby funkcje wypisujaca

	zastosowanie tego pzeciazonego operatora jest rownowazne uzyciu w/w fukncji displayInfo()

	cout<<klasa = klasa.displayInfo()*/
	os << pass.name << " " << pass.surname << ", " << pass.age << endl;
	return os;
}

Coach::Coach() : destination("nowhere"), ticketPrice(0.), seatsLimit(1)
{
	passengers = new Passenger * [seatsLimit];
	passengers[0] = nullptr;
}

Coach::Coach(string cel, double cena, int limit) : seatsLimit(limit)
{
	this->destination = cel;
	this->ticketPrice = cena;
	/*cala tablice wypelniam nullami*/
	passengers = new Passenger * [seatsLimit];
	for (int i = 0; i < seatsLimit; i++)
	{
		passengers[i] = nullptr;
	}
}

Coach::~Coach()
{
	/*usuwanie dynamiczne alkowanej pamieci*/
	delete[] passengers;
}

void Coach::displayInfo()
{
	cout << "Cel: " << destination << endl << "Cena: " << ticketPrice << endl << "Limit mijesc: " << seatsLimit << endl;
}

double Coach::getPrice()
{
	return ticketPrice;
}

Coach& Coach::operator++(int)
{
	/*operator++ zwraca referencje a nie wskaznik*/
	ticketPrice = ticketPrice + 1;
	return *this;
}

Coach& Coach::operator--(int)
{
	/*nie bylo polecania aby to zrobic ale skoro zdefiniowany jest ++
	to postanowilem stworzyc rowniez --*/
	ticketPrice = ticketPrice - 1.0;
	return *this;
}

Coach& Coach::operator+=(Passenger& passgr)
{
	/*pasazer zostaniedodany "na miejsce w autobusie" tylko
	wtedy gdy to miejsce bedzie wolne czyli wskaznik bedzie nullem
	jesli miejsce jest "zajete" to petla sprawdza kolejne*/
	for (int i = 0; i < this->seatsLimit; i++)
	{
		if (this->passengers[i] == nullptr)
		{
			this->passengers[i] = &passgr;
			break;
		}
		else
			continue;
	}

	return *this;
}

void Coach::showPassengers()
{
	/*do wypisania pasazerow w petli uzywam wczesniej zdefionowanego
	przeciazonego operatora << nalezy jednak uzyc wskaznika do "operatora"
	inaczej bedzie to wypisywac adresy pasazerow w pamieci*/
	int i = 0;
	while (passengers[i] != nullptr)
	{
		cout << "Pasazer " << i + 1 << ": ";
		//cout << passengers[i]->getName() << endl;
		cout << *this->passengers[i];
		i++;
	}
}

Coach& operator-=(Coach& co, Passenger& pa)
{
	/*aby usunac pasazera z autobusu wszystkie jego dane osobiste
	imie, nazwisko oraz wiek musza sie zgadzac z tymi podanymi*/
	int i;
	int n;
	for (i = 0; i < co.seatsLimit; i++)
	{
		if (pa.getName() == co.passengers[i]->getName() && pa.getSurname() == co.passengers[i]->getSurname() && pa.getAge() == co.passengers[i]->getAge())
		{
			n = i;
			/*znamy poloznenie w tablicy szukanego pasazera 
			wiec przypisujemy je do zmiennej n a petle przerywamy*/
			break;
		}
	}
	/*po usunieciu pasazera ze srodka listy nalezy przesunac wszytskich o jedno miejsce aby
	nie napotkac na nulla w srodku tablicy*/
	for (n; n < co.seatsLimit - 1; n++)
	{
		co.passengers[n] = co.passengers[n + 1];
	}
	/*przez przesuniecie ostatnie miejsce jest jakas nieznan wartoscia
	dlatego ostatnie miejsce wypelaniam nullem*/
	co.passengers[co.seatsLimit - 1] = nullptr;

	return co;
}




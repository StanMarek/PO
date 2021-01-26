#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <vector>

using namespace std;

struct Movie
{
	string title;
	/*w tresci zadania jest polecenie utworzyc w struktorze tablice dwuelementowa,
	nie bylem pewny czy chodzi o tab[][] czy o tab[2], ale intuicja podpowiedziala mi
	ze chodzi o taka ktora zawiera dwa elementy czyli ma dwie komorki*/
	string mainActor[2];
	int yearOfProduction;
	int time;

	/*sekcja metod*/
	Movie(string, string, string, string, string); //w zasadzie ten konstruktor jest zbedny
	Movie(initializer_list<string>); //tylko ten jest uzywany
};

class Customer
{
private:
	string firstName;
	string lastName;
	int minutesLimit;	//limit_minut
	const int borrowedMoviesLimit = 0;	//limit_wypozyczonych_filmow
	Movie** borrowedMovies;	//wypozyczone_filmy

public:
	/*w przypadku koinstrukotrow klasy Customer jest podobnie do konstrultorw struktury Movie,
	wsytarczlby ten z numerem 1 lub 2 i ewentalnie 0, nie ma potrzeby tworzyc tego z numerem 3*/
	Customer();	//0
	Customer(initializer_list<string>);	//1
	Customer(initializer_list<string>, int);	//2
	Customer(string, string, int bml);	//3
	~Customer();
	void setFirstName(string);
	void setLastName(string);
	string getFirstName();
	string getLastName();

	void displayInfo();	//pokazInfo
	void changeData(string, string);	//zmienDane
	void borrowMovie(Movie*);	//wypozyczFilm
	void giveBackMovie(Movie*);	//zwrotFilmu

	int arraySize();
};


int main()
{
	/*funkcja main nie wumaga komentarza,
	kazdy podpunkt zadania jest podpisany,
	wydaje mi sie ze wszystko jest zrozumiale*/
	//	3
	initializer_list<string> il1 = { "tytul", "2000", "180", "name", "lastname" };
	Movie fl(il1);

	initializer_list<string> il2 = { "LoTR", "2001", "200", "name1", "lastname1" };
	initializer_list<string> il3 = { "LoTR 2", "2002", "210", "name2", "lastname2" };
	initializer_list<string> il4 = { "LoTR 3", "2003", "240", "name3", "lastname3" };
	initializer_list<string> il5 = { "Hobbit", "2014", "190", "name4", "lastname4" };
	Movie movies[4] = { il2, il3, il4, il5 };

	//	4
	initializer_list<string> customer1 = { "Pan", "Pawel", "2137", "4" };
	initializer_list<string> customer2 = { "Niezly", "Kozak", "2115", "3" };
	Customer customers[2] = { customer1, customer2 };
	customers[0].displayInfo();
	cout << endl;
	customers[1].displayInfo();
	cout << endl;

	//	5
	string newLastName;
	cout << "Podaj nowe nazwisko: ";
	getline(cin, newLastName);
	customers[1].changeData(customers[1].getFirstName(), newLastName);
	customers[1].displayInfo();
	cout << endl;

	//	6
	customers[1].borrowMovie(&fl);
	customers[1].borrowMovie(&movies[0]);
	customers[1].borrowMovie(&movies[1]);

	//	7
	customers[1].giveBackMovie(&fl);
	customers[1].displayInfo();

	system("pause");
	return 0;
}

Movie::Movie(string t, string y, string ti, string i, string n)
{
	title = t;
	/*wszystkie parametry przesylamy jako string dlatego czesc z nich nalezy zrzutowac na int
	uztylem tutaj atoi i c_str
	jednakze juz pod koniec zrozumialem swoja glupote ze rownie dobrze mozna zastosowac funkcje stoi*/
	yearOfProduction = atoi(y.c_str());
	time = atoi(ti.c_str());
	mainActor[0] = i;
	mainActor[1] = n;
}

Movie::Movie(initializer_list<string> list)
{
	/*w sumie w tym konstruktorze dzieje sie to samo co w poprzednim ale
	tu liste inicjalizatorow prtzesylamy do kontenera z ktorego przypisujemy
	wartosci polom struktury*/
	vector<string> listVec = list;

	title = listVec[0];
	yearOfProduction = atoi(listVec[1].c_str());
	time = atoi(listVec[2].c_str());
	mainActor[0] = listVec[3];
	mainActor[1] = listVec[4];
}


Customer::Customer() : borrowedMoviesLimit(0)
{
	setFirstName("Imie");
	setLastName("Nazwisko");
	borrowedMovies = new Movie * [1];	/*w kazdym konstruktorze trzeba utworzyc tablice wskaznikow na strukture z okreslona iloscia komorek (rozmiarem)*/
}
/*odnoscnie tresci zadania
nie bylem pewny czy aby utworzyc instancje klasy Customer mam uzyc konstruktora wylacznie z lista inicjalizatorow
czy moge zrobic czesciowo z lista inicjalizatorw i lista inicjalizacyjna
wlasiciwie to jedno nie wyklucza drugiego ale to taka mala niescislosc
ostatecznie wybralem chyba trudniejsza wersje korzystajaca wylacznie z listy inicjalizatorw aby uniknac nieporozumien
ale inny konstruktor rowniez jest zdefiniowany*/
Customer::Customer(initializer_list<string> list)
{
	/*sytuacja podobna do struktury Movie*/
	vector<string> listVec = list;

	setFirstName(listVec[0]);
	setLastName(listVec[1]);
	minutesLimit = atoi(listVec[2].c_str());
	/*aby wlasiwie przypisac zmiennej stalej jakas wartosci nie korzystajac z listy inicjalizacyjnej
	skorzystalem z "castowania", tworzac zmienna wskaznikowa, a nastepnie przypisujac do niej przeslana wartosc zrzutowana na int*/
	int* borrowedMoviesLimes = const_cast<int*> (&borrowedMoviesLimit);
	*borrowedMoviesLimes = atoi(listVec[3].c_str());
	borrowedMovies = new Movie * [borrowedMoviesLimit];
	/*w kazdym konstruktorze nalezy zapelnic tablice pozyczonych filmow nullami aby pozbyc sie tych wszystkich "smieciowych" wartosci
	umozliwi to pozniej sprawne funkcjonowanie innych funkcji*/
	for (int i = 0; i < borrowedMoviesLimit; i++)
	{
		borrowedMovies[i] = nullptr;
	}
}

Customer::Customer(initializer_list<string> list, int bml) : borrowedMoviesLimit(bml)
{
	vector<string> listVec = list;

	setFirstName(listVec[0]);
	setLastName(listVec[1]);
	minutesLimit = atoi(listVec[2].c_str());
	for (int i = 0; i < borrowedMoviesLimit; i++)
	{
		borrowedMovies[i] = nullptr;
	}
}

Customer::Customer(string fN, string lN, int bml) : borrowedMoviesLimit(bml)
{
	setFirstName(fN);
	setLastName(lN);
	borrowedMovies = new Movie * [bml];
	for (int i = 0; i < borrowedMoviesLimit; i++)
	{
		borrowedMovies[i] = nullptr;
	}
}

Customer::~Customer()
{
	// destruktor musi dealokowac pamiec dynamicznie zaalokowana
	delete[] borrowedMovies;
}

void Customer::setFirstName(string fN)
{
	this->firstName = fN;
}

void Customer::setLastName(string lN)
{
	this->lastName = lN;
}

string Customer::getFirstName()
{
	return string(firstName);
}

string Customer::getLastName()
{
	return string(lastName);
}

void Customer::displayInfo()
{
	cout << "Imie: " << getFirstName() << endl;
	cout << "Nazwisko: " << getLastName() << endl;
	cout << "Wypozyczone filmy " << arraySize() << ": " << endl;
	/*zwykle wypisyanie tytulow filmow w petli*/
	for (int i = 0; i < arraySize(); i++)
	{
		cout << "- " << borrowedMovies[i]->title << endl;
	}
}

void Customer::changeData(string fN, string lN)
{
	setFirstName(fN);
	setLastName(lN);
}

void Customer::borrowMovie(Movie* movie)
{
	/*aby klient mogl wypozyczyc film musi spelnic kilka warunkow, limit minut nie moze zostac przekroczony
	oraz limit filmow nie moze zostac przekroczony
	aby sprawdzic limit minut wypozyczonych dotychczasowo tworzmy zmienna o wartosci 0 i w petli dodajemy do niej czas
	trwania pozyczonych filmow
	nastepnie sprawdzamy czy aktualna ilosc minut + czas trwania wypozyczonego filmu nie bedzie wieksze od limitu
	nastepnie trzeba jeszcze sprawdzic czy laczna ilosc wypozyczonych filmow + 1 (ktory chcemy pozyczyc) nie przekorczy limitu
	jesli oba warunki sa spelnione nastepuje wypozyczenie*/
	int summaryTime = 0;
	int summaryMovies = 0;
	for (int i = 0; i < arraySize(); i++)
	{
		summaryTime += borrowedMovies[i]->time;
	}
	for (int i = 0; i < arraySize(); i++)
	{
		if (borrowedMovies[i] != nullptr)
			summaryMovies++;
	}

	if (minutesLimit >= summaryTime + movie->time && arraySize() + 1 <= borrowedMoviesLimit)
		borrowedMovies[arraySize()] = movie;
	else
		cout << "Przekroczono limit minut" << endl;
}

void Customer::giveBackMovie(Movie* movie)
{
	/*gdy klient oddaje film to z tablicy pozyczonych filmow zostaje usuniety film o podanym tytule i roku produkcji(porownywanie calych klas nie ma sensu
	jesli tytul i rok produkcji jest identyczny)
	jesli film zostanie znaleziony w bazie danych wykorzystujac petle to film jest usuwany a petla sie konczy
	nalezy jeszcze pozniej przesunac cala tablice filmow aby nie doszlo do sytuacji:
	film - null - film - film*/
	int n = arraySize();
	int i;
	for (i = 0; i < n; i++)
	{
		if (borrowedMovies[i]->title == movie->title && borrowedMovies[i]->yearOfProduction == movie->yearOfProduction)
		{
			break;
		}
	}

	for (i; i < borrowedMoviesLimit - 1; i++)
	{
		borrowedMovies[i] = borrowedMovies[i + 1];
	}

	borrowedMovies[borrowedMoviesLimit - 1] = nullptr;
}

int Customer::arraySize()
{
	/*pomocnicza funkcja stworzona przeze mnie do obslugi metod powyzej
	funkcja .size() zwracajaca dlugosc tablicy (ilosc komorek) nie dzialala
	wiec zostalem zmuszony do stworzenia swojej
	zwraca ona ilosc komorek w tablicy pozyczonych filomow*/
	int n = 0;
	int i = 0;
	while (borrowedMovies[i] != nullptr && n < borrowedMoviesLimit)
	{
		i++;
		n++;
	}
	return n;
}
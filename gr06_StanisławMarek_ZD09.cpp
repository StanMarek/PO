#include <iostream>
#include <string>

using namespace std;

class Sweets
{
private:
	string name;
	double price;
	int quantity; //ilosc sztuk

public:
	Sweets(string, double, int);
	~Sweets();
	string getName();
	double getPrice();
	int getQuantity();
};

class Fruits
{
private:
	string name;
	double price;
	double mass;	//masa

public:
	Fruits(string, double, double);
	~Fruits();
	string getName();
	double getPrice();
	double getMass();
};

ostream& operator<<(ostream& os, Sweets& s);	//deklaracja przeciazonego operatora<< dla klasy Sweets
ostream& operator<<(ostream& os, Fruits& f);	//deklaracja przeciazonego operatora<< dla klasy Fruits

template<typename Type>
void printArray(Type* array, int arraySize)
{
	/*szablon funkcji wypisujacej tablice w zaleznosci od jej typu i rozmiaru*/
	for (int i = 0; i < arraySize; i++)
		cout << array[i];
}

template <typename Type>
void swap(Type* a, Type* b)
{
	/*szablon funkcji zmieniajcej miejscami w pamieci dwie zmienne w zaleznosci od typu
	jest to funkcja pomocnicza wykorzystywana przy sortowaniu*/
	Type temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

template <typename Type> 
void sortByAlphabet(Type* array, int arraySize)
{
	/*alogorytm sortowania bombelkowego wykorzystywany do sortowania tablicy 
	zmiennych przeslanego typu*/
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize - 1; j++)
		{
			if (array[j].getName() > array[j + 1].getName())
			{
				swap(array[j], array[j + 1]);	//w/w funkcja pomocnicza
			}
		}
	}
}

template <int basketSize, typename Type>
class Basket
{
	/*szablon klasy*/
private:
	string basketName;
	Type* productArrayPointer[basketSize];	//tablica wskaznikow to przeslanego typu

public:
	Basket(string, Type*); //konstruktor parametryzujacy
	~Basket();
	double basketValue();	//wartosc koszyka
	template <int Size, typename T>
	friend ostream& operator<<(ostream& os, Basket<Size, T>& refBasket);	//przeciazony operator<< tym razem jako szablonowa funkcja zaprzyjazniona
};

template<int basketSize, typename Type>
inline Basket<basketSize, Type>::Basket(string name, Type* typeArray) :basketName(name)
{
	/*w konstruktorze parametryzujacym jako argument dostajemy tablice wskanzikow do obiektow
	sa one przypisywane do tablicy w szablonie klasy*/
	for (int i = 0; i < basketSize; i++)
	{
		productArrayPointer[i] = &typeArray[i];
	}
}

template<int basketSize, typename Type>
inline Basket<basketSize, Type>::~Basket()
{
}

template<int basketSize, typename Type>
inline double Basket<basketSize, Type>::basketValue()
{
	/*koszt poczatkowy wynosi 0
	z kazdym dodanym produktem/produktem znajdujacym sie w koszyku
	calkowita wartosc wzrata o ilosc sztuk pomnozona o cene jednej sztuki*/
	double totalValue = 0;
	for (int i = 0; i < basketSize; i++)
	{
		if (productArrayPointer[i] != nullptr)
		{
			totalValue += ((productArrayPointer[i]->getPrice()) * (productArrayPointer[i]->getQuantity()));
		}
	}
	return totalValue;
}

template<int Size, typename T>
inline ostream& operator<<(ostream& os, Basket<Size, T>& refBasket)
{
	/*przeciazony operator dziala raczej tylko dla jednego typu argumentu i jest to typ Sweets
	aby dla wiekszej ilosci typow byl poprawny nalezy tworzyc specjalizacje klasy*/
	os << refBasket.basketName << endl;
	for (int i = 0; i < basketSize2; i++)
	{
		if (refBasket.productArrayPointer[i] != nullptr)
		{
			os << "Produkt: " << refBasket.productArrayPointer[i]->getName() << endl;
		}
	}
	os << "Wartosc: " << refBasket.basketValue();
	return os;
}

template <int basketSize>
class Basket <basketSize, Fruits>
{
	/*szablon klasy specjalizowany gdyby jako parametr przeslana zostala klasa Fruits
	metody i operatory dzialaja wtedy inaczej*/
private:
	string basketName;
	Fruits* productPointerArray[basketSize];

public:
	Basket(string);
	double basketValue();
	template <int Size>
	friend ostream& operator<<(ostream& os, Basket<Size, Fruits>& refFruitsBasket);
	void addFruitToBasket(Fruits*);
};

template <int basketSize>
Basket<basketSize, Fruits>::Basket(string name) :basketName(name)
{
	/*ze wzgledu na posiadanie metody dodajacej owoce(wskzaniki do obiektow) 
	do tablicy wskaznikow, cala tablica musi zostac wypelniona nullami w konstruktorze*/
	for (int i = 0; i < basketSize; i++)
	{
		productPointerArray[i] = nullptr;
	}
}

template <int basketSize>
double Basket<basketSize, Fruits>::basketValue()
{	
	/*zasada dzialania identyczna jak w poprzendim przypadku z tym ze w tym 
	mnozymy cene przez mase*/
	double totalValue = 0;
	for (int i = 0; i < basketSize; i++)
	{
		if (productPointerArray[i] != nullptr)
		{
			totalValue += productPointerArray[i]->getPrice() * productPointerArray[i]->getMass();
		}
	}
	return totalValue;
}

template <int basketSize>
void Basket<basketSize, Fruits>::addFruitToBasket(Fruits* fruit)
{
	/*ady dodac produkt do koszyka musi byc w nim miejsce,
	dlatego sprawdzamy czy wszytskie miejsca sa zajete, jezeli jakies jest wolne
	owoc jest dodawany w to miejsce a petla przerywa dzialanie
	w argumencie funkcji przkazywny jest wskaznik do obiektu ktory chcemy dodac
	jesli warunek jest spelniony zostaje on dodany na miejsce i tablicy*/
	for (int i = 0; i < basketSize; i++)
	{
		if (productPointerArray[i] == nullptr)
		{
			productPointerArray[i] = fruit;
			break;
		}
	}
}

template <int Size>
ostream& operator<<(ostream& os, Basket<Size, Fruits>& refBasket)
{
	/*specjalizowny przeciazony operator<< do dzialania jesli parametrem jest klasa Fruits*/
	os << refBasket.basketName << endl;
	for (int i = 0; i < basketSize; i++)
	{
		if (refBasket.productPointerArray[i] != nullptr)
		{
			os << "Produkt: " << refBasket.productPointerArray[i]->getName() << endl;
		}
		else
			break;
	}

	os << "Wartosc: " << refBasket.basketValue();
	return os;
}

int main()
{
	//4
	const int sweets = 2;
	Sweets slodycze_tab[sweets] = {
		Sweets("Czekolada", 6.66, 3),
		Sweets("Cukierki", 0.75, 36)
	};	
	printArray(slodycze_tab, sweets);	//wypisywanie
	cout << endl;

	//5
	const int fruits = 3;
	Fruits owoce_tab[fruits] = {
		Fruits("Jablko", 2.37, 1.25),
		Fruits("Wisnia", 9.99, 2.48),
		Fruits("Maliny", 8.93, 1.77)
	};
	printArray(owoce_tab, fruits);	//wypisywanie
	cout << endl;

	//6
	Basket<2, Sweets> basket_1("Koszyk slodyczy", slodycze_tab);

	//7
	cout << basket_1 << endl << endl;

	//9
	Basket<3, Fruits> basket_2("Koszyk owocow");
	basket_2.addFruitToBasket(&owoce_tab[0]);	//przekazanie adresu jako argument
	basket_2.addFruitToBasket(&owoce_tab[2]);	//przekazanie adresu jako argument
	cout << basket_2 << endl << endl;
	
	//10
	sortByAlphabet(slodycze_tab, sweets);	//sortowanie
	sortByAlphabet(owoce_tab, fruits);	//sortowanie
	cout << "Posortowane slodycze" << endl;
	printArray(slodycze_tab, sweets);	//wypisywanie
	cout << "Posortowane owoce" << endl;
	printArray(owoce_tab, fruits);	//wypisywanie
	

	return 0;
}

ostream& operator<<(ostream& os, Sweets& s)
{
	/*przeciazony operator jako funkcja globalna nie zaprzyjazniona*/
	os << s.getName() << endl;
	os << "Cena: " << s.getPrice() << " " << "Ilosc: " << s.getQuantity() << endl;
	return os;
}

ostream& operator<<(ostream& os, Fruits& f)
{
	/*przeciazony operator jako funkcja nie zaprzyjazniona*/
	os << f.getName() << endl;
	os << "Cena: " << f.getPrice() << " " << "Masa: " << f.getMass() << endl;
	return os;
}

Sweets::Sweets(string nam = "", double pr = 0., int qua = 0) :name(nam), price(pr), quantity(qua)
{
	/*jednoczsnie konstruktor domyslny i parametryzujacy*/
}

Sweets::~Sweets()
{
}

string Sweets::getName()
{
	return string(name);
}

double Sweets::getPrice()
{
	return price;
}

int Sweets::getQuantity()
{
	return quantity;
}

Fruits::Fruits(string nam = "", double pr = 0., double ma = 0.) :name(nam), price(pr), mass(ma)
{
	/*jednoczsnie konstruktor domyslny i parametryzujacy*/
}

Fruits::~Fruits()
{
}

string Fruits::getName()
{
	return string(name);
}

double Fruits::getPrice()
{
	return price;
}

double Fruits::getMass()
{
	return mass;
}


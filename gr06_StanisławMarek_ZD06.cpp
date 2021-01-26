#include <iostream>
#include <string>
using namespace std;

struct Product
{
	string name;
	string brand;
	double price;
	double mass;
	double carbohydratesPart;
	double proteinPart;
	double fatPart;

	Product(string, string, double, double, double, double, double);
	double calories();
	void displayInfo();
};

class ShoppingList
{
public:
	ShoppingList();
	ShoppingList(string, double);
	~ShoppingList();
	void displayInfo();
	friend void addProduct(ShoppingList*, Product*);
	friend void displayList(ShoppingList*);


private:
	string listName;
	const double availableBudget;
	Product* productPointer[4];

};

int main()
{
	//3
	const int amount = 5;
	Product* products = new Product[amount]
	{
		Product{ "nazwa1", "marka1", 35, 109.99, 69.5, 19.5, 11 },
		Product{ "nazwa2", "marka2", 90, 49.99, 40.33, 30, 30.64 },
		Product{ "nazwa3", "marka3", 20, 52.17, 60, 29.83, 10.17 },
		Product{ "nazwa4", "marka4", 15, 75.75, 50.5, 39.5, 10 },
		Product{ "nazwa5", "marka5", 40, 83.14, 20, 66.66, 13.34 },
	};
	for (int i = 0; i < 5; i++)
	{
		products[i].displayInfo();
		cout << endl;
	}

	//4
	string Product::* namePtr;
	namePtr = &Product::name;
	double (Product:: * functionPtr)();
	functionPtr = &Product::calories;
	cout << "Nazwa ostatniego produktu: " << products[amount - 1].*namePtr << endl;
	cout << "Kalorycznosc ostatniego produktu: " << (products[amount - 1].*functionPtr)() << endl;
	cout << endl;

	//5
	ShoppingList shoppinglist = ShoppingList();
	shoppinglist.displayInfo();
	ShoppingList shoppingList2 = ShoppingList("Lista zakupow", 213.7);
	shoppingList2.displayInfo();
	cout << endl;

	//6
	for (int i = 0; i < 4; i++)
	{
		addProduct(&shoppingList2, &products[i]);
	}
	cout << endl;

	//7
	displayList(&shoppingList2);
	
	delete[] products;
	system("pause");
	return 0;
}

Product::Product(string n, string m, double ma, double c, double wu, double bu, double tu)
{
	this->name = n;
	this->brand = m;
	this->price = c;
	this->mass = ma;
	this->carbohydratesPart = wu;
	this->proteinPart = bu;
	this->fatPart = tu;
}

double Product::calories()
{
	double weight = this->mass;
	double summaryCalories = 0;
	/*dzielenie przez 100 aby z procentow zrobic ulamek
	np. 71% = 0.71*/
	double carbohydratesMass = weight * carbohydratesPart / 100;
	double proteinMass = weight * proteinPart / 100;
	double fatMass = weight * fatPart / 100;

	summaryCalories = carbohydratesMass * 4 + proteinMass * 4 + fatMass * 9;

	return summaryCalories;
}

void Product::displayInfo()
{
	cout << "Nazwa produktu: " << name << endl;
	cout << "Marka: " << brand << endl;
	cout << "Cena: " << price << endl;
	cout << "Masa: " << mass << endl;
	cout << "Kalorycznosc: " << calories() << endl;
}

ShoppingList::ShoppingList() : availableBudget(0)
{
	/*w kazdym konstruktorze zapelniam tablice nullami zeby
	w komorkach nie bylo zadnych "smieciowych" wartosci
	bo uniemozliwi to poprawne dzialanie funkcji addProduct()

	konstruktor domyslny ustawia nazwe listy na default i budzet 0*/
	this->listName = "Default";

	for (int i = 0; i < 4; i++)
		productPointer[i] = nullptr;
}

ShoppingList::ShoppingList(string paramName, double maxbudged) : availableBudget(maxbudged)
{
	/*tu rowniez tablica zostaje zapelniona nullami*/
	this->listName = paramName;

	for (int i = 0; i < 4; i++)
		productPointer[i] = nullptr;
}

ShoppingList::~ShoppingList()
{
}

void ShoppingList::displayInfo()
{
	cout << listName << endl;
	cout << "Budzet: " << availableBudget << endl;
}

void addProduct(ShoppingList* list, Product* someProduct)
{
	/*aby dodac produkt do listy trzeba uwzglednic posiadany budzet
	w pierwszej petli liczona jest aktualna wartosc zakupow, jesli komorka jest pusta(null)
	to petla zostaje przerwana aby nie liczyc dalej
	w kolejnej petli nastepuje porownanie wartosci i budzetu, jezeli suma aktualnej wartosci zakupow
	i dodawanego produktu jest mniejsza lub rowna dostepnemu budzetowi produkt zostaje dodany jezeli jest spelniony
	rowniez warunek ze na liscie jest dostepne miejsce czyli jakas komorka jest nullem
	jesli budzet jest przekroczony petla przerywa dzialanie, jak w przypadku gdy budzet jest przekroczony i nie ma mijesca*/
	double sum = 0;
	double totalCost = 0;


	for (int i = 0; i < 4; i++)
	{
		if (list->productPointer[i] != nullptr)
			sum += list->productPointer[i]->price;
		else
			break;
	}

	for (int i = 0; i < 4; i++)
	{
		if (list->productPointer[i] == nullptr && sum + someProduct->price <= list->availableBudget)
		{
			list->productPointer[i] = someProduct;
			totalCost = sum + someProduct->price;
			cout << "Dodano produkt" << endl;
			cout << "Wartosc zakupow: " << totalCost << endl;
			break;
		}
		else if (sum + someProduct->price > list->availableBudget)
		{
			totalCost = sum;
			cout << "Budzet przekroczony!" << endl;
			cout << "Wartosc zakupow: " << totalCost << endl;
			break;
		}

	}

}

void displayList(ShoppingList* list)
{
	int i = 0;
	string Product::* productPtr[2];	//tablica wskaznikow to typu string
	productPtr[0] = &Product::name;	//0 komorka w tablicy przyjmuje wskaznik do pola name struktury
	productPtr[1] = &Product::brand;	//1 komorka w tablicy przyjmuje wskaznik do pola brand struktury

	/*petla wypisujaca liste wykonuje sie do czasu az ktoras komorka jest pusta*/
	while (list->productPointer[i] != nullptr)
	{
		cout << "Nazwa: " << *list->productPointer[i].*productPtr[0] << endl;
		cout << "Marka: " << *list->productPointer[i].*productPtr[1] << endl;
		i++;
	}

}

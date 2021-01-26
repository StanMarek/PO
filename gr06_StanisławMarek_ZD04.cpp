#include <iostream>
#include <string>

/*deklaracje wszytskich przestrzeni nazw, klas i struktur
oraz ich skladowych takich jak konstruktory, akcesory metody
oraz funkcje poza "klasowe" */
namespace first
{
	namespace second
	{
		class Biblioteka
		{
		public:
			struct Ksiazka
			{
				std::string title;
				std::string author;
				int amountOfPages;
				static int counter;
				Ksiazka();
				Ksiazka(std::string, std::string, int);
				void setTitle(std::string);
				void setAuthor(std::string);
				void setAmountOfPages(int);
				std::string getTitle();
				std::string getAuthor();
				int getAmountOfPages();
				/*ze wzgledu ze w strukturze wszystko jest publiczne mozna zrezygnowac z tworzenia akcesorow
				ale ja postanowilem je zrobic dla popraiwienia czytelnosci kodu i ulatwienia sobie pracy*/
			};

			Biblioteka(std::string, char*);
			~Biblioteka();
			Ksiazka showTheMostPages(Ksiazka*, int); //wypiszNajwiecejStron
			void setName(std::string);
			void setCity(char*);
			std::string getName();

		private:
			std::string name;
			char city[100];
		};
	}

	class Czytelnik
	{
	public:
		Czytelnik();
		Czytelnik(std::string, std::string, int);
		~Czytelnik();
		void setAOBB(int);
		void setFirstName(std::string);
		void setLastName(std::string);
		void setBorrowedBooks(second::Biblioteka::Ksiazka*, int);
		std::string getFirtsName();
		std::string getLastName();
		int getAOBB();
		friend void showBorrowed(Czytelnik*);

	private:
		std::string firstName;
		std::string lastName;
		int amountOfBorrowedBooks;
		second::Biblioteka::Ksiazka* borrowedBooks = new second::Biblioteka::Ksiazka[10000];
	};
	int bookCounter();
	void showBorrowed(Czytelnik*);

}

int main()
{
	/*aby skrocic zapis urzywam specyfikatora typedef do kazdego typu obiektu*/
	typedef first::second::Biblioteka Library;
	typedef first::second::Biblioteka::Ksiazka Book;
	typedef first::Czytelnik Reader;

	Library library(std::string("Biblioteka"), new char[7]{ "Miasto" });	//tworzenie obiektu biblioteka
	std::cout << std::endl;
	/*czteroelementowa tablica obiektow ksiazek z zainicjowanymi wartosciami pol*/
	Book books[4] = {
		{std::string("Pan Taduesz"), std::string("Adam Mickiewicz"), 344},
		{std::string("Kordian"), std::string("Juliusz Slowacki"), 111},
		{std::string("Zbrodnia i kara"), std::string("Fiodor Dostojewski"), 513 },
		{std::string("Makbet"), std::string("William Szekspir"), 256} };

	std::cout << std::endl;
	std::cout << std::endl;

	Reader reader1("Jan", "Kowalski", 3);	//tworzenie czytelnika
	reader1.setBorrowedBooks(books, reader1.getAOBB());	//przypisywanie stworzonemu czytelnikowi ksiazek z tablicy wyzej
	first::showBorrowed(&reader1);	//wyswietlanie pozyczonych przez czytelnika ksiazek
	std::cout << std::endl;
	/*do tymczasowego obiektu typu ksiazka przypisywana jest jedna instancja struktury ksiazka
	ktora zostaje ustalona przez funkcje znajdujaca w tablicy ksiazke o najwiekszej ilosci stron
	ponizej nastepuje wypisanie autora, tytulu i ilosci stron*/
	Book temp = library.showTheMostPages(books, books->counter);	
	std::cout << "Ksiazka z najwieksza iloscia stron:" << std::endl;
	std::cout << temp.getAuthor() << std::endl;
	std::cout << temp.getTitle() << std::endl;
	std::cout << temp.getAmountOfPages() << std::endl;
	std::cout << std::endl;

	std::cout << "Licznik ksiazek: " << first::bookCounter() << std::endl;	//ilosc utworzonych ksiazek


	system("pause");
	return 0;
}

//definicje wszytskiego z przestrzeni first

	first::second::Biblioteka::Biblioteka(std::string name, char* city)	//konstruktor
	{
		setName(name);
		setCity(city);
		std::cout << "Nazwa biblioteki: " << getName() << std::endl;
		std::cout << "Lokalizacja: " << city << std::endl;
	}

	first::second::Biblioteka::~Biblioteka()
	{
	}

	first::second::Biblioteka::Ksiazka first::second::Biblioteka::showTheMostPages(Ksiazka * books, int counter)
	{
		/*funkcja porownuje w petli ilosc stron kazdej z ksiazek
		przeslanych w tablicy jako argument funkcji.
		gdy ilosc stron jest wieksza od max nastepuje zamiana
		max na ilosc stron, gdy ilosc stron ksiazki z nastpnej iteracji
		jest wieksza od nowego max to znowu nastepuje zamiana itd.
		zwracana jest ksiazka z najwieksza iloscia stron*/
		int max = 0;
		int j = 0;
		for (int i = 0; i < counter; i++)
		{
			if (books[i].getAmountOfPages() > max)
			{
				max = books[i].getAmountOfPages();
				j = i;
			}
		}
		Ksiazka book = books[j];

		return book;
	}

	void first::second::Biblioteka::setName(std::string name)
	{
		this->name = name;
	}

	void first::second::Biblioteka::setCity(char* city)
	{
		*(this->city) = *city;
	}

	std::string first::second::Biblioteka::getName()
	{
		return std::string(name);
	}

	first::second::Biblioteka::Ksiazka::Ksiazka()
	{

	}

	first::second::Biblioteka::Ksiazka::Ksiazka(std::string title, std::string author, int amountofpages)
	{
		/*przy tworzeniu nowej ksiazki trzeba pamietac aby zwiekszyc licznik ksiazek o 1*/
		counter++;
		setAuthor(author);
		setAmountOfPages(amountofpages);
		setTitle(title);
		std::cout << "Tytul: " << getTitle() << std::endl;
		std::cout << "Autor: " << getAuthor() << std::endl;
		std::cout << "Liczba stron: " << getAmountOfPages() << std::endl;

		/*alternatywnie*/

		/*std::cout << "Tytul: " << title << std::endl;
		std::cout << "Autor: " << author << std::endl;
		std::cout << "Liczba stron: " << amountOfPages << std::endl;*/
	}

	void first::second::Biblioteka::Ksiazka::setTitle(std::string title)
	{
		this->title = title;
	}

	void first::second::Biblioteka::Ksiazka::setAuthor(std::string author)
	{
		this->author = author;
	}

	void first::second::Biblioteka::Ksiazka::setAmountOfPages(int amount)
	{
		this->amountOfPages = amount;
	}

	std::string first::second::Biblioteka::Ksiazka::getTitle()
	{
		return std::string(title);
	}

	std::string first::second::Biblioteka::Ksiazka::getAuthor()
	{
		return std::string(author);
	}

	int first::second::Biblioteka::Ksiazka::getAmountOfPages()
	{
		return amountOfPages;
	}

	first::Czytelnik::Czytelnik()
	{
		std::cout << "Imie: " << getFirtsName();
		std::cout << "Nazwisko: " << getLastName();
	}

	first::Czytelnik::Czytelnik(std::string firstName, std::string lastName, int amountOfBorrowedBooks)
	{
		setFirstName(firstName);
		setLastName(lastName);
		setAOBB(amountOfBorrowedBooks);
		std::cout << "Imie: " << getFirtsName() << std::endl;
		std::cout << "Nazwisko: " << getLastName() << std::endl;
		std::cout << "Ilosc pozyczonych: " << getAOBB() << std::endl;
	}

	first::Czytelnik::~Czytelnik()
	{
		/*destruktor klasy czytelnik usuwa sam obiekt klasy czytelnik
		oraz dynamiczna tablice ksiazek ktore wypozyczyl ten czytelnik*/
		delete[] borrowedBooks;
	}

	void first::Czytelnik::setAOBB(int aobb)
	{
		this->amountOfBorrowedBooks = aobb;
	}

	void first::Czytelnik::setFirstName(std::string name)
	{
		this->firstName = name;
	}

	void first::Czytelnik::setLastName(std::string surname)
	{
		this->lastName = surname;
	}

	void first::Czytelnik::setBorrowedBooks(second::Biblioteka::Ksiazka * ksiazki, int amount)
	{
		/*w petli wyknujacej sie tyle razy ile czytelnik ma wypozyczonych ksiazek
		przypisujemy do ksiazek wypozyczonych przez uzytkownika
		ksiazki z tablicy utworzonej na poczatku*/
		for (int i = 0; i < amount; i++)
		{
			this->borrowedBooks[i] = ksiazki[i];
		}
	}

	std::string first::Czytelnik::getFirtsName()
	{
		return std::string(firstName);
	}

	std::string first::Czytelnik::getLastName()
	{
		return std::string(lastName);
	}

	int first::Czytelnik::getAOBB()
	{
		return amountOfBorrowedBooks;
	}

	int first::second::Biblioteka::Ksiazka::counter = 0;

	int first::bookCounter()
	{
		int counter = second::Biblioteka::Ksiazka::counter;
		return counter;
	}

	void first::showBorrowed(Czytelnik * reader)
	{
		/*w petli wypisuje tytuly wypozyczonych przez czytelnika ksiazek
		pobierajac je z dynamicznej tablicy
		funkcja ma zadeklarowana przyjazn aby ograniczyc tworzenie nowego akcesora
		do tejze tablicy*/
		int x = reader->amountOfBorrowedBooks;
		//std::cout << "Liczba wypozyczonych ksiazek: " << x << std::endl;
		for (int i = 0; i < x; i++)
		{
			std::cout << "Tytul wypozyczonej ksiazki: " << reader->borrowedBooks[i].getTitle() << std::endl;
		}
	}

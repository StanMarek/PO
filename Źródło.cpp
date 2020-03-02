#include <iostream>
#include "Osoba.h"
#include "Samochod.h"

using namespace std;

int main()
{
	Osoba osoba1;
	Osoba osoba2("Jurij", "Owsienko", 180, 2137);
	Osoba osoba3(osoba1, "Bogdan");
	Samochod auto1("VW", "Golf IV", 2001, &osoba2);

	osoba2.imie = "NoweImie";
	osoba2.nazwisko = "NoweNazwisko";
	osoba2.wzrost = 156;
	//osoba2.rok_urodzenia = 2000;

	osoba2.wyswietl();

	auto1.wyswietl();

	system("pause");
	return 0;
}
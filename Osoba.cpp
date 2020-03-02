#include "Osoba.h"

Osoba::Osoba() : rok_urodzenia(1990)
{
	this->imie = "Jan";
	this->nazwisko = "Nowak";
	this->wzrost = 176.5;

	this->wyswietl();
	this->zapisz();
}Osoba::Osoba(string imie, string nazwisko, double wzrost, int _rok_urodzenia) : rok_urodzenia(_rok_urodzenia)
{
	this->imie = imie;
	this->nazwisko = nazwisko;
	this->wzrost = wzrost;

	this->wyswietl();
	this->zapisz();
}
Osoba::Osoba(const Osoba& copy, string imie) : rok_urodzenia(copy.rok_urodzenia)
{
	this->imie = imie;
	this->nazwisko = copy.nazwisko;
	this->wzrost = copy.wzrost;

	this->wyswietl();
	this->zapisz();
}

Osoba::~Osoba()
{
	cout << "Zniszczono obiekt" << endl;
}
void Osoba::wyswietl()
{
	cout << imie << " " << nazwisko << endl;
	cout << "Wzrost: " << wzrost << endl;
	cout << "Rok urodzenia: " << rok_urodzenia << endl << endl;
}
void Osoba::zapisz()
{
	ofstream file;
	file.open("dane_osob.txt", ofstream::app);
	file << imie << " " << nazwisko << endl
		<< "Wzrost: " << wzrost << endl
		<< "Rok urodzenia: " << rok_urodzenia << endl;
	file.close();
}
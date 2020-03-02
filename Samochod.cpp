#include "Samochod.h"

Samochod::Samochod(string marka, string kolor, int rocznik, Osoba* osoba)
{
	cout << "Utworzone obiekt klasy Samochod" << endl;

	this->marka = marka;
	this->kolor = kolor;
	this->rocznik = rocznik;
	this->wlasciciel = osoba;
}
void Samochod::wyswietl()
{
	cout << marka << " " << kolor << " " << rocznik << " " << wlasciciel->imie << endl;
}


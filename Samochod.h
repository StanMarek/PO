#pragma once
#include <iostream>
#include <string>
#include "Osoba.h"

using namespace std;

class Samochod
{
public:
	Samochod(string marka, string kolor, int rocznik, Osoba* osoba);
	void wyswietl();
	string marka;
	string kolor;
	int rocznik;
	Osoba* wlasciciel;

private:
};


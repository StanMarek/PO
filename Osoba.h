#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Osoba
{
	public:
		Osoba();
		Osoba(string, string, double, int);
		Osoba(const Osoba &copy, string);
		
		~Osoba();


		void zapisz();
		void wyswietl();

		string imie;
		string nazwisko;
		double wzrost;
		const int rok_urodzenia;

	private:
};


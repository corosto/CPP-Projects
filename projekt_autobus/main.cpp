#include <iostream>
#include <string>
#include "funkcje.h"


int main(int argc, char* argv[])
{
	std::string poczatek = "";
	std::string koniec = "";
	std::string godzina = "";
	std::string plik_trasy = "";
	std::string plik_rozklad = "";
	std::string plik_wynikowy = "";

	if (argc == 1)
	{
		std::cout << "-t pliki wejsciowe z opisem tras" << std::endl << "-k plik wyjsciowy z kursami autobusow" 
			<< std::endl << "-p miasto poczatkowe" << std::endl << "-d miasto docelowe" << std::endl << "-g godzina odjazdu" << std::endl << "-w nazwa pliku wynikowego";
	}
	else if (argc == 13)
	{
		for (int i = 0; i < argc; i++)
		{
			std::string string_value = argv[i];

			if (string_value == "-t")
			{
				plik_trasy = argv[i + 1];
			}
			else if (string_value == "-k")
			{
				plik_rozklad = argv[i + 1];
			}
			else if (string_value == "-p")
			{
				poczatek = argv[i + 1];
			}
			else if (string_value == "-d")
			{
				koniec = argv[i + 1];
			}
			else if (string_value == "-g")
			{
				godzina = argv[i + 1];
			}
			else if (string_value == "-w")
			{
				plik_wynikowy = argv[i + 1];
			}
		}

		std::vector <std::vector<std::vector<std::string>>> trasy = wczytywanie_trasy(plik_trasy);
		std::vector<std::vector<float>> rozklad_godziny = wczytywanie_godzin(plik_rozklad);

		wypisanie_koncowych_tras(trasy, rozklad_godziny, plik_wynikowy, poczatek, koniec, godzina_na_float(godzina));

	}
	else
	{
		std::cout << "Podaj wlasciwa ilosc argumentow";
	}

	return 0;
}
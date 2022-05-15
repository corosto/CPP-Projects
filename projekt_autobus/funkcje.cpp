#include <iostream>
#include "funkcje.h"
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <sstream>


std::vector <std::vector<std::vector<std::string>>> wczytywanie_trasy(std::string filename)
{
	std::vector <std::vector<std::vector<std::string>>> trasy;
	std::string line;
	std::ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			trasy.push_back(odczyt_trasy(line + " "));
		}
		myfile.close();
	}
	else
	{
		std::cout << "Nie da sie otworzyc pliku." << std::endl;
	}
	return trasy;
}


std::vector<std::vector<std::string>> odczyt_trasy(std::string line)
{
	int licznik = 0;
	std::vector <std::vector<std::string>> gotowa_trasa;
	std::vector <std::string> trasa;
	std::string slowo = "";
	for (auto x : line)
	{
		if ((x == '(') || (x == ')'))
		{
			continue;
		}
		if (x == ' ')
		{
			if (licznik == 0)
			{
				trasa.push_back(slowo);
				gotowa_trasa.push_back(trasa);
				trasa.clear();
				slowo = "";
			}

			else if (licznik == 1)
			{
				trasa.push_back(slowo);
				slowo = "";
				++licznik;
				continue;
			}

			else if (licznik % 3 == 0)
			{
				trasa.push_back(slowo);
				slowo = "";
			}

			else if (licznik % 3 == 1)
			{
				trasa.push_back(slowo);
				gotowa_trasa.push_back(trasa);
				trasa.clear();
				trasa.push_back(slowo);
				slowo = "";
			}

			else if (licznik % 3 == 2)
			{
				trasa.push_back(slowo);
				slowo = "";
			}

			++licznik;
		}
		else
		{
			slowo += x;
		}
	}
	return gotowa_trasa;
}


std::vector<std::vector<float>> wczytywanie_godzin(std::string filename)
{
	std::vector<std::vector<float>> rozklad;
	std::string line;
	std::ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			rozklad.push_back(odczyt_godzin(line + " "));
		}
		myfile.close();
	}
	else
	{
		std::cout << "Nie da sie otworzyc pliku." << std::endl;
	}
	return rozklad;
}


std::vector<float> odczyt_godzin(std::string line)
{
	std::vector <float> rozklad_gotowy;
	int licznik = 0;
	std::string slowo = "";

	for (auto x : line)
	{
		if (x == ' ')
		{
			if (licznik == 0)
			{
				++licznik;
				slowo = "";
				continue;
			}
			else if (licznik == 1)
			{
				rozklad_gotowy.push_back(stof(slowo));
				slowo = "";
				++licznik;
			}
			else 
			{
				rozklad_gotowy.push_back(godzina_na_float(slowo));
				slowo = "";
			}
		}
		else
		{
			slowo += x;
		}
	}
	return rozklad_gotowy;
}


float godzina_na_float(std::string h)
{
	std::string slowo = "";
	std::string godzina;
	std::string minuta;

	float godzina_odjazdu;
	float minuta_odjazdu;
	float polaczone;

	bool a = true;

	for (auto x : h)
	{
		if (x == ':')
		{
			a = false;
			godzina = slowo;
			slowo = "";
			continue;
		}
		if (a == true)
		{
			slowo += x;
		}
		else if (a == false)
		{
			slowo += x;
		}
	}
	minuta = slowo;

	godzina_odjazdu = stof(godzina);
	minuta_odjazdu = stof(minuta);

	polaczone = godzina_odjazdu + (minuta_odjazdu / 60);

	godzina_na_string(polaczone);

	return polaczone;
}


std::string godzina_na_string(float godzina)
{
	std::string czas;
	int hour = floor(godzina);
	float minutes = godzina - hour;
	minutes = round(minutes * 60);
	int m = minutes;

	if (m < 10)
	{
		czas = std::to_string(hour) + ":" + "0" + std::to_string(m);
	}
	else
	{
		czas = std::to_string(hour) + ":" + std::to_string(m);
	}

	return czas;
}


std::string porownanie_godzin(float godz_uzytkow, std::vector<std::vector<float>> rozklad, float numer_trasy)
{
	float najblizsza = 10000;
	float godzina_odjazdu = 0;


	for (int i = 0; i < rozklad.size(); i++)
	{
		for (int j = 1; j < rozklad[i].size(); j++)
		{
			if (numer_trasy == rozklad[i][0])
			{
				auto a = rozklad[i][j] - godz_uzytkow;

				if (a > 0)
				{
					if (a < najblizsza)
					{
						najblizsza = a;
						godzina_odjazdu = rozklad[i][j];
					}
				}
			}
		}
	}
	if (najblizsza == 10000)
	{
		godz_uzytkow = 0;

		for (int i = 0; i < rozklad.size(); i++)
		{
			for (int j = 1; j < rozklad[i].size(); j++)
			{
				if (numer_trasy == rozklad[i][0])
				{
					auto a = rozklad[i][j] - godz_uzytkow;
					if (a > 0)
					{
						if (a < najblizsza)
						{
							najblizsza = a;
							godzina_odjazdu = rozklad[i][j];
						}
					}
				}
			}
		}
	}

	 std::string godz = godzina_na_string(godzina_odjazdu);

	 return godz;
}


std::string przybycie(float odleglosc, std::string godzina)
{
	auto h = godzina_na_float(godzina);

	auto przyjazd = h + (odleglosc / 54);

	std::string przyjechanie = godzina_na_string(przyjazd);

	return przyjechanie;
}


std::string float_to_string_with_prec(float liczba, int precision)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << liczba;
	std::string gotowe = ss.str();

	return gotowe;
}


void wypisanie_koncowych_tras(std::vector<std::vector<std::vector<std::string>>> trasy, std::vector<std::vector<float>> rozklad,
	std::string plik_wynikowy, std::string poczatek, std::string koniec, float godzina_wyjazdu)
{
	float numer_trasy;
	int a = 0;
	std::vector<std::string> miasta;
	std::string godzina;
	std::string output_string = "";

	for (int i = 0; i < trasy.size(); i++)
	{
		for (int j = 1; j < trasy[i].size(); j++)
		{
			bool powtarza_sie0 = false;
			bool powtarza_sie1 = false;

			for (auto miasto : miasta)
			{
				if (trasy[i][j][0] == miasto)
				{
					powtarza_sie0 = true;
				}

				if (trasy[i][j][3] == miasto)
				{
					powtarza_sie1 = true;
				}
			}
			if (!powtarza_sie0)
			{
				miasta.push_back(trasy[i][j][0]);
			}

			if (!powtarza_sie1)
			{
				miasta.push_back(trasy[i][j][3]);
			}
		}
	}

	for (int m = 0; m < trasy.size(); m++)
	{
		a += trasy[m].size() - 1;
	}
	graf g(a);

	for (int i = 0; i < trasy.size(); i++)
	{
		for (int j = 1; j < trasy[i].size(); j++)
		{
				auto it0 = find(miasta.begin(), miasta.end(), trasy[i][j][0]);
				auto index0 = distance(miasta.begin(), it0);

				auto it1 = find(miasta.begin(), miasta.end(), trasy[i][j][3]);
				auto index1 = distance(miasta.begin(), it1);

				g.dodaj_sciezke(index0, index1);
				g.dodaj_cene_odleglosc_nr_trasy(index0, index1, stoi(trasy[i][0][0]), stof(trasy[i][j][2]), stof(trasy[i][j][1]));
		}
	}
	auto it_poczatek = find(miasta.begin(), miasta.end(), poczatek);
	auto index_poczatek = distance(miasta.begin(), it_poczatek);

	auto it_koniec = find(miasta.begin(), miasta.end(), koniec);
	auto index_koniec = distance(miasta.begin(), it_koniec);

	g.znajdz_sciezki(index_poczatek, index_koniec);

	if (g.znalezione.size() == 0)
	{
		output_string = "Nie da sie znalezc trasy";
	}
	else
	{
		for (int i = 0; i < g.znalezione.size(); i++)
		{
			int numer = -1;
			float cala_cena = 0;
			float cala_odleglosc = 0;

			for (int j = 0; j < g.znalezione[i].size() - 1; j++)
			{
				if (numer == -1)
				{
					output_string += std::to_string(g.nr_trasy[g.znalezione[i][j]][g.znalezione[i][j + 1]]) + ". ";
					numer_trasy = g.nr_trasy[g.znalezione[i][j]][g.znalezione[i][j + 1]];
					output_string += miasta[g.znalezione[i][j]] + " ";
					godzina = porownanie_godzin(godzina_wyjazdu, rozklad, numer_trasy);
					output_string += godzina + " ";
					cala_cena += g.cena[g.znalezione[i][j]][g.znalezione[i][j + 1]];
					cala_odleglosc += g.odleglosc[g.znalezione[i][j]][g.znalezione[i][j + 1]];
				}
				else if (numer == g.nr_trasy[g.znalezione[i][j]][g.znalezione[i][j + 1]])
				{
					cala_cena += g.cena[g.znalezione[i][j]][g.znalezione[i][j + 1]];
					cala_odleglosc += g.odleglosc[g.znalezione[i][j]][g.znalezione[i][j + 1]];
				}
				else
				{
					output_string += miasta[g.znalezione[i][j]];
					std::string dojazd = przybycie(cala_odleglosc, godzina);
					output_string += " " + dojazd;
					output_string += " " + float_to_string_with_prec(cala_odleglosc, 2) + "km ";
					output_string += float_to_string_with_prec(cala_cena, 2) + "zl " + "\n";
					output_string += std::to_string(g.nr_trasy[g.znalezione[i][j]][g.znalezione[i][j + 1]]) + ". ";
					numer_trasy = g.nr_trasy[g.znalezione[i][j]][g.znalezione[i][j + 1]];
					output_string += miasta[g.znalezione[i][j]];
					godzina = porownanie_godzin(godzina_na_float(dojazd), rozklad, numer_trasy);
					output_string += " " + godzina + " ";
					cala_cena = g.cena[g.znalezione[i][j]][g.znalezione[i][j + 1]];
					cala_odleglosc = g.odleglosc[g.znalezione[i][j]][g.znalezione[i][j + 1]];
				}
				 
				if (j == g.znalezione[i].size() - 2)
				{
					output_string += miasta[g.znalezione[i][g.znalezione[i].size() - 1]];
					std::string dojazd = przybycie(cala_odleglosc, godzina);
					output_string += " " + dojazd;
					output_string += " " + float_to_string_with_prec(cala_odleglosc, 2) + "km ";
					output_string += float_to_string_with_prec(cala_cena, 2) + "zl " + "\n";
				}
				numer = g.nr_trasy[g.znalezione[i][j]][g.znalezione[i][j + 1]];
			}
			output_string += "\n";
		}
		std::ofstream zapisywanie;
		zapisywanie.open(plik_wynikowy);
		zapisywanie << output_string;
		std::cout << output_string;
		zapisywanie.close();
	}
}



graf::graf(int n)
{
	this->n = n;
	adj = new std::list<int>[n];
	std::vector<int> zero;
	std::vector<float> float_zero;
	zero.resize(n, 0);
	float_zero.resize(n, 0);
	nr_trasy.resize(n, zero);
	cena.resize(n, float_zero);
	odleglosc.resize(n, float_zero);
}


void graf::dodaj_cene_odleglosc_nr_trasy(int v, int u, int t, float c, float o)
{
	nr_trasy[v][u] = t;
	cena[v][u] = c;
	odleglosc[v][u] = o;
}


void graf::dodaj_sciezke(int v, int u)
{
	adj[v].push_back(u);
}


void graf::znajdz_sciezki(int s, int d)
{
	bool* visited = new bool[n];
	int* path = new int[n];
	int path_index = 0; 

	for (int i = 0; i < n; i++)
	{
		visited[i] = false;
	}

	znajdz_sciezki_rek(s, d, visited, path, path_index);
}


void graf::znajdz_sciezki_rek(int u, int d, bool visited[], int path[], int& path_index )
{
	visited[u] = true;
	path[path_index] = u;
	path_index++;

	if (u == d) 
	{
		std::vector<int> sciezka;
		for (int i = 0; i < path_index; i++)
		{
			sciezka.push_back(path[i]);
		}
		znalezione.push_back(sciezka);
	}
	else
	{
		std::list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (!visited[*i])
			{
				znajdz_sciezki_rek(*i, d, visited, path, path_index);
			}
		}
	}
	path_index--;
	visited[u] = false;
}
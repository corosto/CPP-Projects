/**\file*/

#include <vector>
#include <list>
#include <string>
#ifndef FUNKCJE_H
#define FUNKCJE_H


/// Funkcja, ktora otwiera plik z trasami i zapisuje je do wektora trasy, jezeli operacja sie nie powiedzie to wypisze stosowna informacje.
/// @param filename Nazwa pliku z trasami.
/// @return Zwraca trasy, odleglosc miedzy miastami oraz koszt przejazdu zapisane jako odpowiedni wektor.
std::vector <std::vector<std::vector<std::string>>> wczytywanie_trasy(std::string filename);


/// Funkcja, porzadkuje wczytana linijke pliku tekstowego i zapisuje ja do wektora.
/// @param line Pojedyncza linijka odczytana z pliku.
/// @return Zwraca 2D wektor zawierajacy uporzadkowane parametry danej trasy.
std::vector<std::vector<std::string>> odczyt_trasy(std::string line);


/// Funkcja, ktora otwiera plik z rozkladem i zapisuje je do wektora rozklad, jezeli operacja sie nie powiedzie to wypisze stosowna informacje.
/// @param filename Nazwa pliku z rozkladem.
/// @return Zwraca rozklad autobusowy zapisany jako odpowiedni wektor.
std::vector<std::vector<float>> wczytywanie_godzin(std::string filename);


/// Funkcja, ktora usuwa numer porzadkowy i zapisuje godziny w wektorze.
/// @param line Pojedyncza linijka odczytana z pliku.
/// @return Zwraca wektor w ktorym znajduja sie godziny odjazdu oraz numer trasy.
std::vector<float> odczyt_godzin(std::string line);


/// Funkcja, ktora usuwa dwukropki w rozkladzie i zamienia go na wektor float'owy.
/// @param h Godzina odjazdu lub godzina uzytkownika w potaci string(hh:mm).
/// @return Zwraca godzine zamieniona na float.
float godzina_na_float(std::string h);


/// Funkcja zamieniajaca wartosci float'owe godzina z powrotem na string.
/// @param godzina Godzina jako wartosc float np.(10:12 => 10.2).
/// @return Zwraca godzine zamieniona na string.
std::string godzina_na_string(float godzina);


/// Funkcja porownuje godzine ktora wprowadzil uzytkownik z godzinami z rokzladu i wybiera najblizsza mozliwa godzine odjazdu.
/// @param godzina_uzytkow Godzina od ktorej program zacznie szukac mozliwych polaczen.
/// @param rozklad Rozklad autobusowy w postaci float.
/// @param numer_trasy Numer trasy kursu autobusu.
/// @return Zwraca godzine odjazdu autobusu.
std::string porownanie_godzin(float godz_uzytkow, std::vector<std::vector<float>> rozklad, float numer_trasy);


/// Funkcja oblicza czas przyjazdu na podstawie odleglosci.
/// @param odleglosc Odleglosc pomiedzy miastem poczatkowym a docelowym.
/// @param godzina Godzina wyjazdu autobusu.
/// @return Zwraca godzine dojazdu.
std::string przybycie(float odleglosc, std::string godzina);


/// Funkcja ktora zamienia liczbe typu float na string z odpowiednia precyzja.
/// @param liczba Liczba ktora funkcja ma zaokraglic.
/// @param precision Liczba miejsc po przecinku zaokraglenia.
/// @return Zwraca string z okreslona precyzja.
std::string float_to_string_with_prec(float liczba, int precision);


/// Funkcja wypisuje do konsoli oraz pliku znalezione polaczenia.
/// @param trasy Wektor przechowujacy dane tras.
/// @param rozklad Wektor przechowujacy dane rozkladu.
/// @param plik_wynikowy Nazwa pliku wynikowego.
/// @param poczatek Nazwa miasta poczatkowego wybranego przez uzytkownika.
/// @param koniec Nazwa miasta koncowego wybranego przez uzytkownika.
/// @param godzina_wyjazdu Godzina wyjazdu wybrana przez uzytkownika.
void wypisanie_koncowych_tras(std::vector <std::vector<std::vector<std::string>>> trasy, std::vector<std::vector<float>> rozklad,
	std::string plik_wynikowy, std::string poczatek, std::string koniec, float godzina_wyjazdu);


class graf /// Klasa przechowujaca metody i pola potrzebne do zapisu i edycji grafu.
{
	int n; ///< Maksymalna wielkosc zapamietywanych sciezek.
	std::list<int>* adj; ///< Lista w ktorej prechowywane sa wszytskie sciezki.


	///Funkcja 
	/// @param u Aktualny wezel.
	/// @param d Koncowy wezel.
	/// @param visited[] Sprawdza czy wezel byl juz odwiedzany.
	/// @param path[] Przechowuje aktualne wierzcholki.
	/// @param path_index Przechowuje aktualny numer sciezki.
	void znajdz_sciezki_rek(int u, int d, bool visited[], int path[], int& path_index);


public:
	std::vector< std::vector<int>> znalezione;  ///< Wektor z znalezionymi polaczeniami.
	std::vector< std::vector<int>> nr_trasy;	///< Wektor przechowywujacy numery tras.
	std::vector< std::vector<float>> cena;		///< Wektor przechowywujacy ceny przejazdu.
	std::vector< std::vector<float>> odleglosc;	///< Wektor przechowywujacy odleglosci pomiedzy miastami.


	/// Konstruktor z parametrem okreslajacym maksymalna wielkosc grafu.
	/// @param n Maksymalna wielkosc zapamietywanych sciezek.
	graf(int n);


	/// Funkcja dodajaca sciezki
	/// @param v Poczatek sciezki.
	/// @param u Koniec sciezki.
	void dodaj_sciezke(int v, int u);


	/// Funkcja, ktora zapisuje w polach klasy pozadane parametry.
	/// @param v Poczatek sciezki.
	/// @param u Koniec sciezki.
	/// @param nr_trasy Numer trasy danej sciezki.
	/// @param cena Cena danej sciezki.
	/// @param odleglosc Odleglosc danej sciezki.
	void dodaj_cene_odleglosc_nr_trasy(int v, int u, int nr_trasy, float cena, float odleglosc);


	/// Fukcja znajdujaca wszyskie mozliwe sciezki.
	/// @param s Poczatkowy wezel.
	/// @param d Koncowy wezel.
	void znajdz_sciezki(int s, int d);
};

#endif
#include "SFML/Graphics.hpp"
#include "Przycisk.h"
#include "Macierze.h"
#include "Instrukcja.h"
#include <Windows.h>

using namespace std;
using namespace sf;

class Mapa
{

	bool moge = false, moge2 = false, klikniety = false;
	bool zamknac = false;

	int licznik = 0, kolumny = 15, wiersze = 15;

	string textKolumny = "15", textWiersze = "15", licznikStr = "0";

	Przycisk przyciski[30][30], pod, pod2;
	Przycisk menu[7], menuBiblioteka[8];

	Macierze mapV;

	Instrukcja inst;

	RenderWindow biblioteka;

	Event event2;

	void InicjowanieMacierzy();
	void Krok();
	void DodajLicznik();
	void Animacja();

	void TworzenieBiblioteki();
	void Zamknij();
	void WyswietlBiblioteke();
	void BibliotekaPrzyciski();
	void BibliotekaPrzyciskiWyswietl();
	void BibliotekaPrzyciskiWcisniecie(RenderWindow& okno, Event eve);
	void BibliotekaZmana();
	void KrokBezKroku();

public:
	Mapa();
	void TworzenieMapy();
	void TworzenieMenu();
	void TworzenieTextBox();
	void WyswietlMape(RenderWindow& okno);
	void WyswietlMenu(RenderWindow& okno);
	void WyswietlTextBox(RenderWindow& okno);
	void Klikniecie(RenderWindow& okno, Event eve);
};
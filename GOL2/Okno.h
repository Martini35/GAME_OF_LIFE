#include <SFML/Graphics.hpp>
#include "Mapa.h"

using namespace sf;

class Okno
{
	RenderWindow okno;
	Mapa MapaGry;
	Event event;

	bool zamknij = false;

	void TworzenieOkna();
	void Eventy();
	void Rysuj();
	void TworzenieMapy();

public:
	void OknoStart();
};
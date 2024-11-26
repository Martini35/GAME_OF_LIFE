#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Instrukcja
{
	RenderWindow instrukcja;
	Text napis;
	Font font;
	Event event;

	bool zamknac = false;

	void Zamknij();
	void TworzenieInstrukcji();
	void Napisy();
	void RysujNapis();

public:
	void WyswietlInstrukcje();
};
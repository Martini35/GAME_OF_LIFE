#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

class Przycisk
{
	RectangleShape shape;
	Text napis;
	Font font;

	int index = -1;
	float xn = 0, yn = 0;

public:
	Przycisk();
	Przycisk(float x, float y, float sx, float sy, int R, int G, int B, float obwodka);
	bool CzyMyszNadPrzyciskiem(Vector2f myszPoz);
	void DodajNapis(string nap);
	void RysujPrzycisk(RenderWindow& okno);
	void ZmienKolor(int r, int g, int b);
	void SetIndex(int index);
	int GetIndex();
	void ZmienNapis(string nap);
};
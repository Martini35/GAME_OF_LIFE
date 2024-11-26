#include "Przycisk.h"


Przycisk::Przycisk(){
	
}

Przycisk::Przycisk(float x, float y, float sx, float sy, int R, int G, int B, float obwodka) {

	shape.setSize(Vector2f(sx, sy));
	shape.setPosition(x, y);
	shape.setFillColor(Color(R, G, B));
	shape.setOutlineThickness(obwodka);
	shape.setOutlineColor(Color::Black);

	xn = x;
	yn = y;
}

bool Przycisk::CzyMyszNadPrzyciskiem(Vector2f myszPoz) {

	return shape.getGlobalBounds().contains(myszPoz);
}

void Przycisk::DodajNapis(string nap){

	font.loadFromFile("Pixel Emulator.ttf");
	napis.setFont(font);
	napis.setCharacterSize(35); 
	napis.setFillColor(Color::White);
	napis.setOutlineColor(Color::Black);
	napis.setOutlineThickness(3);
	napis.setPosition(xn + 20, yn + 2);
	napis.setString(nap);
}

void Przycisk::RysujPrzycisk(RenderWindow& okno){

	okno.draw(shape);
	okno.draw(napis);
}

void Przycisk::ZmienKolor(int r, int g, int b) {

	shape.setFillColor(Color(r, g, b));
}

void Przycisk::SetIndex(int index){

	this->index = index;
}

int Przycisk::GetIndex() {

	return index;
}

void Przycisk::ZmienNapis(string nap){
	napis.setString(nap);
}
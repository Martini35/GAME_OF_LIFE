#include "Instrukcja.h"

void Instrukcja::TworzenieInstrukcji(){

	instrukcja.create(VideoMode(920, 270), "Instrukcja");
	instrukcja.setFramerateLimit(60);
}

void Instrukcja::Zamknij() {

	while (instrukcja.pollEvent(event)) {
		if (event.type == Event::Closed) {
			zamknac = true;
			instrukcja.close();
		}
	}
}

void Instrukcja::Napisy() {

	font.loadFromFile("Pixel Emulator.ttf");
	napis.setFont(font);
	napis.setCharacterSize(15);
	napis.setFillColor(Color::White);
	napis.setPosition(20, 20);
	napis.setString("Gra w zycie ( Life, The game of life ) jeden z pierwszych i najbardziej znanych \nprzykladow automatu komorkowego, wymyslony w roku 1970 przez brytyjskiego \nmatematyka Johna Conwaya. \n\n\nZASADY:\n\nZywa komurak z mniejsza iloscia sasiadow niz 2 umiera.\n\nZywa komurka z 2 lub 3 zywymi sasiadami pozostaje nadal zywa.\n\nZywa komurka z 4 lub wieksza iloscia zywych sasiadow umiera z 'zatloczenia'");
}

void Instrukcja::RysujNapis() {
	instrukcja.draw(napis);
}

void Instrukcja::WyswietlInstrukcje(){

	TworzenieInstrukcji();

	Napisy();

	while (true) {
		instrukcja.clear();
		Zamknij();
		RysujNapis();
		instrukcja.display();

		if (zamknac) {
			zamknac = false;
			break;
		}
	}
}
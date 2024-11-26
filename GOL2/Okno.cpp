#include "Okno.h"

void Okno::TworzenieOkna() {
	okno.create(VideoMode(1275, 920), "Game of life");
	okno.setFramerateLimit(60);
}

void Okno::Eventy() {

	while (okno.pollEvent(event)) {
		if (event.type == Event::Closed) {
			okno.close();
			zamknij = true;
		}
		MapaGry.Klikniecie(okno, event);
	}
}

void Okno::TworzenieMapy() {

	MapaGry.TworzenieMapy();
	MapaGry.TworzenieMenu();
	MapaGry.TworzenieTextBox();
}

void Okno::Rysuj() {

	okno.clear();
	MapaGry.WyswietlMape(okno);
	MapaGry.WyswietlMenu(okno);
	MapaGry.WyswietlTextBox(okno);
	okno.display();
}

void Okno::OknoStart() {

	TworzenieOkna();
	TworzenieMapy();
	while (true) {
		Eventy();
		Rysuj();
		if (zamknij) {
			break;
		}
	}
}
#include "Mapa.h"


Mapa::Mapa()
{
}

void Mapa::TworzenieMapy(){

	float startX = 350.0f;
	float startY = 10.0f;
	//TODO zmieniæ na dynamiczn¹ siatke przycisków (masz to ju¿)
	for (int i = 0; i < wiersze; ++i) {
		for (int j = 0; j < kolumny; ++j) {
			float posX = startX + j * 30.f;
			float posY = startY + i * 30.f;

			przyciski[i][j] = Przycisk(posX, posY, 29.0f, 29.0f, 0, 255, 0, 0);
		}
	}

	InicjowanieMacierzy();
}

void Mapa::TworzenieMenu(){

	menu[0] = Przycisk(10, 10, 310, 50, 255, 0, 0, 1);
	menu[1] = Przycisk(10, 70, 310, 50, 255, 0, 0, 1);
	menu[2] = Przycisk(10, 130, 310, 50, 255, 0, 0, 1);
	menu[3] = Przycisk(10, 190, 310, 50, 255, 0, 0, 1);
	menu[4] = Przycisk(10, 250, 310, 50, 255, 0, 0, 1);
	menu[5] = Przycisk(10, 430, 310, 50, 255, 0, 0, 1);
	menu[6] = Przycisk(10, 550, 310, 50, 255, 0, 0, 1);

	menu[0].DodajNapis("START");
	menu[1].DodajNapis("KROK");
	menu[2].DodajNapis("RESET");
	menu[3].DodajNapis("BIBLIOTEKA");
	menu[4].DodajNapis("INSTRUKCJA");
	menu[5].DodajNapis("ZMIEN");
	menu[6].DodajNapis("KROK: 0");
}

void Mapa::TworzenieTextBox() {

	pod = Przycisk(10, 370, 150, 50, 255, 0, 0, 1);
	pod.DodajNapis(textKolumny);

	pod2 = Przycisk(170, 370, 150, 50, 255, 0, 0, 1);
	pod2.DodajNapis(textWiersze);
}

void Mapa::WyswietlMape(RenderWindow& okno){

	for (int j = 0; j < kolumny; ++j) {
		for (int i = 0; i < wiersze; ++i) {
			przyciski[i][j].RysujPrzycisk(okno);
		}
	}
	if(klikniety){
		Animacja();
	}
}

void Mapa::WyswietlMenu(RenderWindow& okno) {

	for (int k = 0; k < 7; k++) {
		menu[k].RysujPrzycisk(okno);
	}
}

void Mapa::WyswietlTextBox(RenderWindow& okno) {

	pod.RysujPrzycisk(okno);
	pod2.RysujPrzycisk(okno);
}

void Mapa::Klikniecie(RenderWindow& okno, Event eve){

	Vector2i mousePosition = Mouse::getPosition(okno);
	Vector2f mousePositionFloat(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

	//Klikniêcie nad siatk¹
	for (int j = 0; j < wiersze; j++) {
		for (int i = 0; i < kolumny; i++) {
			if (przyciski[j][i].CzyMyszNadPrzyciskiem(mousePositionFloat)) {
				// Myszka jest nad przyciskiem
				if (eve.type == Event::MouseButtonPressed && eve.mouseButton.button == Mouse::Left) {

					if(przyciski[j][i].GetIndex() == -1){
						przyciski[j][i].ZmienKolor(0, 0, 255);
						przyciski[j][i].SetIndex(1);
					}
					else {
						przyciski[j][i].ZmienKolor(0, 255, 0);
						przyciski[j][i].SetIndex(-1);
					}

					mapV.ZmnienMacierz(i, j);

					moge = false;
					moge2 = false;
				}
			}
		}
	}

	//Klikniêcie menu
	for (int k = 0; k < 6; k++) {
		if (menu[k].CzyMyszNadPrzyciskiem(mousePositionFloat)) {
			if (eve.type == Event::MouseButtonPressed && eve.mouseButton.button == Mouse::Left) {

				switch (k) {
				case 0:
					if (klikniety) {
						klikniety = false;
						menu[0].ZmienNapis("START");
					}
					else {
						klikniety = true;
						menu[0].ZmienNapis("STOP");
					}
					break;

				case 1:
					if(!klikniety){
						Krok();
						DodajLicznik();
					}
					break;

				case 2:
					if (!klikniety) {
						for (int i = 0; i < kolumny; ++i) {
							for (int j = 0; j < wiersze; ++j) {
								przyciski[j][i].ZmienKolor(0, 255, 0);
								przyciski[j][i].SetIndex(-1);
							}
						}
						mapV.Zeruj();
						menu[6].ZmienNapis("KROK: 0");
						licznik = 0;
					}
					break;

				case 3:
					if (!klikniety) {
						WyswietlBiblioteke();
					}
					break;

				case 4:
					if (!klikniety) {
						inst.WyswietlInstrukcje();
					}
					break;

				case 5:
					if (!klikniety) {
						kolumny = stoi(textKolumny);
						wiersze = stoi(textWiersze);

						//Zabezpieczenie przed niechcianymi wartoœciami
						if (kolumny == 0) {
							textKolumny = "1";
							kolumny = 1;
						}
						if (kolumny > 30) {
							textKolumny = "30";
							kolumny = 30;
						}

						if (wiersze == 0) {
							textWiersze = "1";
							wiersze = 1;
						}
						if (wiersze > 30) {
							textWiersze = "30";
							wiersze = 30;
						}

						licznik = 0;
						menu[6].ZmienNapis("KROK: 0");
						TworzenieMapy();
						InicjowanieMacierzy();
					}
					break;
				}

				moge = false;
				moge2 = false;
			}
		}
	}

	//TextBox Kolumny
	if (pod.CzyMyszNadPrzyciskiem(mousePositionFloat)) {
		if (eve.type == Event::MouseButtonPressed && eve.mouseButton.button == Mouse::Left) {
			moge = true;
			moge2 = false;
		}
	}
	if (eve.type == Event::TextEntered && moge == true) {
		//Usuwanie cyfr
		if (eve.text.unicode == 8) {
			if (!textKolumny.empty()) {
				textKolumny.pop_back();
			}
		}
		//Sprawdzenie czy s¹ to cyfry
		else if (eve.text.unicode >= 48 && eve.text.unicode <= 57) {
			//ograniczenie do 2 cyfr
			if (textKolumny.length() < 2)
				textKolumny += static_cast<char>(eve.text.unicode);
		}
	}
	pod.ZmienNapis(textKolumny);

	//TextBox Wiersze
	if (pod2.CzyMyszNadPrzyciskiem(mousePositionFloat)) {
		if (eve.type == Event::MouseButtonPressed && eve.mouseButton.button == Mouse::Left) {
			moge = false;
			moge2 = true;
		}
	}
	if (eve.type == Event::TextEntered && moge2 == true) {
		//Usuwanie cyfr
		if (eve.text.unicode == 8) {
			if (!textWiersze.empty()) {
				textWiersze.pop_back();
			}
		}
		//Sprawdzenie czy s¹ to cyfry
		else if (eve.text.unicode >= 48 && eve.text.unicode <= 57) {
			//ograniczenie do 2 cyfr
			if (textWiersze.length() < 2)
				textWiersze += static_cast<char>(eve.text.unicode);
		}
	}
	pod2.ZmienNapis(textWiersze);

	
}

void Mapa::InicjowanieMacierzy(){

	mapV = Macierze(kolumny, wiersze);
}

void Mapa::Krok(){

	mapV.KrokM();

	for (int i = 0; i < kolumny; i++) {
		for (int j = 0; j < wiersze; j++) {
			if (mapV.GetMiejsce(i, j) == 1) {
				przyciski[j][i].ZmienKolor(0, 0, 255);
				przyciski[j][i].SetIndex(1);
			}
			else {
				przyciski[j][i].ZmienKolor(0, 255, 0);
				przyciski[j][i].SetIndex(-1);
			}
		}
	}
}

void Mapa::DodajLicznik(){

	licznik += 1;
	licznikStr = to_string(licznik);
	menu[6].ZmienNapis("KROK: " + licznikStr);
}

void Mapa::Animacja(){

	Krok();
	Sleep(350);
	DodajLicznik();
}

//Biblioteka
void Mapa::TworzenieBiblioteki() {

	biblioteka.create(VideoMode(330, 490), "Biblioteka");
	biblioteka.setFramerateLimit(60);
}

void Mapa::Zamknij() {

	while (biblioteka.pollEvent(event2)) {
		if (event2.type == Event::Closed) {
			zamknac = true;
			biblioteka.close();
		}
		BibliotekaPrzyciskiWcisniecie(biblioteka, event2);
	}
}

void Mapa::WyswietlBiblioteke() {

	TworzenieBiblioteki();
	BibliotekaPrzyciski();

	while (true) {
		biblioteka.clear();
		BibliotekaPrzyciskiWyswietl();
		Zamknij();
		biblioteka.display();

		if (zamknac) {
			zamknac = false;
			break;
		}
	}
}

void Mapa::BibliotekaPrzyciski() {

	float odleglosc = 10;
	for (int i = 0; i < 8; i++) {
		menuBiblioteka[i] = Przycisk(10, odleglosc, 310, 50, 255, 0, 0, 1);
		odleglosc += 60;
	}

	menuBiblioteka[0].DodajNapis("STANDARD");
	menuBiblioteka[1].DodajNapis("NANOMINO");
	menuBiblioteka[2].DodajNapis("ACORN");
	menuBiblioteka[3].DodajNapis("ANVIL");
	menuBiblioteka[4].DodajNapis("KICKBACK");
	menuBiblioteka[5].DodajNapis("GLIDER MESS");
	menuBiblioteka[6].DodajNapis("ACHIM'S P16");
	menuBiblioteka[7].DodajNapis("ACHIM'S P4");
}

void Mapa::BibliotekaPrzyciskiWyswietl() {

	for (int i = 0; i < 8; i++) {
		menuBiblioteka[i].RysujPrzycisk(biblioteka);
	}
}

void Mapa::BibliotekaZmana() {

	zamknac = true;
	kolumny = 30;
	wiersze = 30;
	textKolumny = "30";
	textWiersze = "30";
	TworzenieMapy();
	InicjowanieMacierzy();
	mapV.Zeruj();
	pod.ZmienNapis("30");
	pod2.ZmienNapis("30");
	Krok();
	licznik = 0;
	menu[6].ZmienNapis("KROK: 0");
}

void Mapa::KrokBezKroku() {
		
	for (int i = 0; i < kolumny; i++) {
		for (int j = 0; j < wiersze; j++) {
			if (mapV.GetMiejsce(i, j) == 1) {
				przyciski[j][i].ZmienKolor(0, 0, 255);
				przyciski[j][i].SetIndex(1);
			}
			else {
				przyciski[j][i].ZmienKolor(0, 255, 0);
				przyciski[j][i].SetIndex(-1);
			}
		}
	}
}

void Mapa::BibliotekaPrzyciskiWcisniecie(RenderWindow& okno, Event eve) {

	Vector2i mousePosition = Mouse::getPosition(okno);
	Vector2f mousePositionFloat(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

	for (int i = 0; i < 8; i++) {
		if (menuBiblioteka[i].CzyMyszNadPrzyciskiem(mousePositionFloat)) {
			if (eve.type == Event::MouseButtonPressed && eve.mouseButton.button == Mouse::Left) {
				switch (i)
				{
				case 0:
					BibliotekaZmana();
					
					mapV.ZmnienMacierz(15, 14);
					mapV.ZmnienMacierz(16, 15);
					mapV.ZmnienMacierz(16, 16);
					mapV.ZmnienMacierz(15, 16);
					mapV.ZmnienMacierz(14, 16);

					KrokBezKroku();
					biblioteka.close();
					break;
				case 1:
					BibliotekaZmana();

					mapV.ZmnienMacierz(13, 14);
					mapV.ZmnienMacierz(14, 14);
					mapV.ZmnienMacierz(15, 14);
					mapV.ZmnienMacierz(15, 15);
					mapV.ZmnienMacierz(15, 16);
					mapV.ZmnienMacierz(16, 16);
					mapV.ZmnienMacierz(17, 15);
					mapV.ZmnienMacierz(17, 16);
					mapV.ZmnienMacierz(18, 16);

					KrokBezKroku();
					biblioteka.close();
					break;
				case 2:
					BibliotekaZmana();

					mapV.ZmnienMacierz(13, 14);
					mapV.ZmnienMacierz(12, 16);
					mapV.ZmnienMacierz(13, 16);
					mapV.ZmnienMacierz(15, 15);
					mapV.ZmnienMacierz(16, 16);
					mapV.ZmnienMacierz(17, 16);
					mapV.ZmnienMacierz(18, 16);

					KrokBezKroku();
					biblioteka.close();
					break;
				case 3:
					BibliotekaZmana();

					mapV.ZmnienMacierz(13, 13);
					mapV.ZmnienMacierz(14, 13);
					mapV.ZmnienMacierz(15, 13);
					mapV.ZmnienMacierz(16, 13);
					mapV.ZmnienMacierz(12, 14);
					mapV.ZmnienMacierz(17, 14);
					mapV.ZmnienMacierz(13, 15);
					mapV.ZmnienMacierz(14, 15);
					mapV.ZmnienMacierz(15, 15);
					mapV.ZmnienMacierz(17, 15);
					mapV.ZmnienMacierz(15, 16);
					mapV.ZmnienMacierz(17, 16);
					mapV.ZmnienMacierz(18, 16);

					KrokBezKroku();
					biblioteka.close();
					break;
				case 4:
					BibliotekaZmana();

					mapV.ZmnienMacierz(15, 11);
					mapV.ZmnienMacierz(14, 12);
					mapV.ZmnienMacierz(14, 13);
					mapV.ZmnienMacierz(15, 13);
					mapV.ZmnienMacierz(16, 13);
					mapV.ZmnienMacierz(15, 16);
					mapV.ZmnienMacierz(16, 16);
					mapV.ZmnienMacierz(14, 17);
					mapV.ZmnienMacierz(16, 17);
					mapV.ZmnienMacierz(16, 18);

					KrokBezKroku();
					biblioteka.close();
					break;
				case 5:
					BibliotekaZmana();

					mapV.ZmnienMacierz(12, 12);
					mapV.ZmnienMacierz(10, 13);
					mapV.ZmnienMacierz(12, 13);
					mapV.ZmnienMacierz(11, 14);
					mapV.ZmnienMacierz(12, 14);
					mapV.ZmnienMacierz(21, 15);
					mapV.ZmnienMacierz(19, 16);
					mapV.ZmnienMacierz(20, 16);
					mapV.ZmnienMacierz(20, 17);
					mapV.ZmnienMacierz(21, 17);

					KrokBezKroku();
					biblioteka.close();
					break;
				case 6:
					BibliotekaZmana();

					mapV.ZmnienMacierz(16, 9);
					mapV.ZmnienMacierz(17, 9);
					mapV.ZmnienMacierz(16, 10);
					mapV.ZmnienMacierz(18, 10);
					mapV.ZmnienMacierz(11, 11);
					mapV.ZmnienMacierz(16, 11);
					mapV.ZmnienMacierz(18, 11);
					mapV.ZmnienMacierz(19, 11);
					mapV.ZmnienMacierz(10, 12);
					mapV.ZmnienMacierz(11, 12);
					mapV.ZmnienMacierz(17, 12);
					mapV.ZmnienMacierz(9, 13);
					mapV.ZmnienMacierz(12, 13);
					mapV.ZmnienMacierz(9, 14);
					mapV.ZmnienMacierz(10, 14);
					mapV.ZmnienMacierz(11, 14);
					mapV.ZmnienMacierz(19, 16);
					mapV.ZmnienMacierz(20, 16);
					mapV.ZmnienMacierz(21, 16);
					mapV.ZmnienMacierz(18, 17);
					mapV.ZmnienMacierz(21, 17);
					mapV.ZmnienMacierz(13, 18);
					mapV.ZmnienMacierz(19, 18);
					mapV.ZmnienMacierz(20, 18);
					mapV.ZmnienMacierz(11, 19);
					mapV.ZmnienMacierz(12, 19);
					mapV.ZmnienMacierz(14, 19);
					mapV.ZmnienMacierz(19, 19);
					mapV.ZmnienMacierz(12, 20);
					mapV.ZmnienMacierz(14, 20);
					mapV.ZmnienMacierz(13, 21);
					mapV.ZmnienMacierz(14, 21);

					KrokBezKroku();
					biblioteka.close();
					break;
				case 7:
					BibliotekaZmana();

					mapV.ZmnienMacierz(12, 11);
					mapV.ZmnienMacierz(13, 11);
					mapV.ZmnienMacierz(17, 11);
					mapV.ZmnienMacierz(18, 11);
					mapV.ZmnienMacierz(11, 12);
					mapV.ZmnienMacierz(14, 12);
					mapV.ZmnienMacierz(16, 12);
					mapV.ZmnienMacierz(19, 12);
					mapV.ZmnienMacierz(11, 13);
					mapV.ZmnienMacierz(13, 13);
					mapV.ZmnienMacierz(14, 13);
					mapV.ZmnienMacierz(16, 13);
					mapV.ZmnienMacierz(17, 13);
					mapV.ZmnienMacierz(19, 13);
					mapV.ZmnienMacierz(10, 14);
					mapV.ZmnienMacierz(11, 14);
					mapV.ZmnienMacierz(19, 14);
					mapV.ZmnienMacierz(20, 14);
					mapV.ZmnienMacierz(12, 15);
					mapV.ZmnienMacierz(14, 15);
					mapV.ZmnienMacierz(16, 15);
					mapV.ZmnienMacierz(18, 15);
					mapV.ZmnienMacierz(10, 16);
					mapV.ZmnienMacierz(11, 16);
					mapV.ZmnienMacierz(19, 16);
					mapV.ZmnienMacierz(20, 16);
					mapV.ZmnienMacierz(11, 17);
					mapV.ZmnienMacierz(13, 17);
					mapV.ZmnienMacierz(14, 17);
					mapV.ZmnienMacierz(16, 17);
					mapV.ZmnienMacierz(17, 17);
					mapV.ZmnienMacierz(19, 17);
					mapV.ZmnienMacierz(11, 18);
					mapV.ZmnienMacierz(14, 18);
					mapV.ZmnienMacierz(16, 18);
					mapV.ZmnienMacierz(19, 18);
					mapV.ZmnienMacierz(12, 19);
					mapV.ZmnienMacierz(13, 19);
					mapV.ZmnienMacierz(17, 19);
					mapV.ZmnienMacierz(18, 19);

					KrokBezKroku();
					biblioteka.close();
					break;
				default:
					break;
				}
			}
		}
	}
}
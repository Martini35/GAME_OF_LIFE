#include "Macierze.h"

Macierze::Macierze() {

    kolumny = 0;
    wiersze = 0;
}

Macierze::Macierze(int wie, int kol) {

	kolumny = kol;
	wiersze = wie;

	for (int j = 0; j < 31; j++) {
		for (int i = 0; i < 31; i++) {
			macierz[j][i] = 0;
		}
	}
}

void Macierze::ZmnienMacierz(int x, int y) {

	if(macierz[y][x] == 0){
		macierz[y][x] = 1;
    }
	else {
		macierz[y][x] = 0;
	}
}

int Macierze::GetMiejsce(int x, int y){

	return macierz[y][x];
}

void Macierze::KrokM() {

    int licznik = 0;
    int pomoc[32][32];
    
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            pomoc[i][j] = macierz[i][j];
        }
    }

    for (int i = 0; i < kolumny; i++) {                  //obliczanie miejsc w wektorze bez zewnêtrznych miejsc 
        for (int j = 0; j < wiersze; j++) {
            licznik = 0;

            if (pomoc[i - 1][j - 1] == 1) {       //sprawdzanie wokól punktu
                licznik++;
            }
            if (pomoc[i][j - 1] == 1) {
                licznik++;
            }
            if (pomoc[i + 1][j - 1] == 1) {
                licznik++;
            }
            if (pomoc[i - 1][j] == 1) {
                licznik++;
            }
            if (pomoc[i + 1][j] == 1) {
                licznik++;
            }
            if (pomoc[i - 1][j + 1] == 1) {
                licznik++;
            }
            if (pomoc[i][j + 1] == 1) {
                licznik++;
            }
            if (pomoc[i + 1][j + 1] == 1) {
                licznik++;
            }

            switch (licznik) {                              //ustawianie punktów
            case 2:
                if (pomoc[i][j] == 0) {
                    macierz[i][j] = 0;
                }
                if (pomoc[i][j] == 1) {
                    macierz[i][j] = 1;
                }
                break;
            case 3:
                macierz[i][j] = 1;
                break;
            default:
                macierz[i][j] = 0;
                break;
            }
        }
    }
}

void Macierze::Zeruj(){

    for (int i = 0; i < kolumny; i++) {
        for (int j = 0; j < wiersze; j++) {
            macierz[i][j] = 0;
        }
    }
}
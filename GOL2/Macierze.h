#include <string>
#include <iostream>

using namespace std;

class Macierze
{
	int kolumny, wiersze;

	int macierz[32][32];

public:
	Macierze();
	Macierze(int wie, int kol);
	void ZmnienMacierz(int x, int y);
	int GetMiejsce(int x, int y);
	void KrokM();
	void Zeruj();
};
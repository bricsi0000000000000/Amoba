#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>
#define MAXHOSSZ 7
#define MENNYIT 5

using namespace std;

enum Iranyok { FEL, BALRA, LE, JOBBRA };

#pragma region FUGGVENYEK
void TengelyekRajzol(int x, int y);
void KiirandoSorok(int x, int y);
void SugoKiir();
void PalyaMozgatasa(Iranyok irany, int mennyi);
void JatekosCsere();
bool RakhatokE(int x, int y);
bool Vizsgal();
void MelyikJatekosKovetkezikKiir();
void JatekMehet();
void JatekVege();
void LepesBekerese();
void KiirandoSorokNullazasa();
void PalyaKeretSzinAllit();
void MozgasBekerese(string bekert);
void Kilep();
#pragma endregion

#pragma region SZINEK
HANDLE szinezes = GetStdHandle(STD_OUTPUT_HANDLE);
int sotetKek = 1;
int sotetZold = 2;
int sotetCyan = 3;
int sotetPiros = 4;
int sotetRozsaszin = 5;
int sotetSarga = 6;
int sotetFeher = 7;
int szurke = 8;
int kek = 9;
int zold = 10;
int cyan = 11;
int piros = 12;
int rozsaszin = 13;
int sarga = 14;
int feher = 15;
#pragma endregion

int vizszintesKoordinata = 0;
int fuggolegesKoordinata = 0;

char jatekosEgySzimbolum = 'X';
char jatekosKettoSzimbolum = 'O';

struct elem {
	int x_koordinata;
	int y_koordinata;
	char karakter;
};

int elemek_hossz = 0;
elem* elemek;
int index = 0;

const int kiirHossz = MAXHOSSZ * 2 + 1;
string kiirando_sorok[kiirHossz];

int melyikJatekos = 1;

bool jatekVege = false;
bool jatekEleje = true;

#pragma region KARAKTEREK
char fuggolegesCsik = (char)179;
char vizszintesCsik = (char)196;
char kereszt = (char)197;
char forditottT = (char)193;
char balraT = (char)180;
char jobbraT = (char)195;
char allitottT = (char)194;
char jobbFelsoSarok = (char)191;
char balAlsoSarok = (char)192;
char jobbAlsoSarok = (char)217;
char balFelsoSarok = (char)218;
char duplaFuggolegesCsik = (char)186;

char also = (char)220;
char felso = (char)223;
char egesz = (char)219;
#pragma endregion

int main()
{
	JatekMehet();
}

void KiirandoSorokNullazasa() {
	for (int i = 0; i < kiirHossz; i++)
	{
		kiirando_sorok[i] = "";
		for (int j = 0; j < kiirHossz; j++)
		{
			kiirando_sorok[i] += ' ';
		}
	}
}

void MozgasBekerese(string bekert) {
	char merre = bekert[0];
	string mennyivel = "";

	for (int i = 1; i <= bekert.length(); i++)
	{
		mennyivel += bekert[i];
	}

	int mennyi = atoi(mennyivel.c_str());
	if (bekert.length() == 1) {
		mennyi = 1;
	}

	if (merre == 'a') {
		PalyaMozgatasa(Iranyok::BALRA, mennyi);
	}
	else if (merre == 'd') {
		PalyaMozgatasa(Iranyok::JOBBRA, mennyi);
	}
	else if (merre == 'w') {
		PalyaMozgatasa(Iranyok::FEL, mennyi);
	}
	else if (merre == 's') {
		PalyaMozgatasa(Iranyok::LE, mennyi);
	}
}

void LepesBekerese() {
#pragma region KOORDINATAK BEKERESE
	do {
		string x, y, bekert = "";
		bool elso = false;
		do {
			MelyikJatekosKovetkezikKiir();
			x = y = bekert = "";
			while (bekert == "") {
				getline(cin, bekert);
			}
			MozgasBekerese(bekert);
			for (int i = 0; i < bekert.length(); i++)
			{
				if (bekert[i] == ' ') {
					elso = true;
					i++;
				}
				if (!elso) {
					x += bekert[i];
				}
				else {
					y += bekert[i];
				}
			}
		} while (y == "" || x == "");

		vizszintesKoordinata = atoi(x.c_str());
		fuggolegesKoordinata = atoi(y.c_str());

	} while (!RakhatokE(vizszintesKoordinata, fuggolegesKoordinata));
#pragma endregion

#pragma region PALYA ELEMEK
	elem * uj_elemek = new elem[elemek_hossz + 1];

	for (int i = 0; i < elemek_hossz; i++)
	{
		uj_elemek[i].karakter = elemek[i].karakter;
		uj_elemek[i].x_koordinata = elemek[i].x_koordinata;
		uj_elemek[i].y_koordinata = elemek[i].y_koordinata;
	}
	elemek_hossz++;

	if (melyikJatekos == 1) {
		uj_elemek[index].karakter = jatekosEgySzimbolum;
	}
	else if (melyikJatekos == 2) {
		uj_elemek[index].karakter = jatekosKettoSzimbolum;
	}
	uj_elemek[index].x_koordinata = vizszintesKoordinata;
	uj_elemek[index].y_koordinata = fuggolegesKoordinata;

	delete[] elemek;
	elemek = uj_elemek;

	index++;
#pragma endregion

	if (!jatekVege) {
		if (Vizsgal()) {
			JatekVege();
		}
	}

	JatekosCsere();
	TengelyekRajzol(vizszintesKoordinata, fuggolegesKoordinata);
}

void JatekMehet() {
	SetConsoleTextAttribute(szinezes, feher);

	jatekVege = false;
	melyikJatekos = 1;
	elemek_hossz = 0;
	vizszintesKoordinata = 0;
	fuggolegesKoordinata = 0;
	index = 0;

	elem * uj_elemek = new elem[elemek_hossz];

	delete[] elemek;
	elemek = uj_elemek;

	KiirandoSorokNullazasa();
	TengelyekRajzol(vizszintesKoordinata, fuggolegesKoordinata);
}

void JatekVege() {
	jatekVege = true;
	TengelyekRajzol(vizszintesKoordinata, fuggolegesKoordinata);
	while (true) {

		string bekert;
		SetConsoleTextAttribute(szinezes, sarga);
		cout << "\t        NYERT: ";
		if (melyikJatekos == 1) {
			SetConsoleTextAttribute(szinezes, cyan);
			cout << "EGYES JATEKOS" << endl;
		}
		else {
			SetConsoleTextAttribute(szinezes, rozsaszin);
			cout << "KETTES JATEKOS" << endl;
		}

		SetConsoleTextAttribute(szinezes, zold);
		cout << endl << "\t        kilepes 'k' | ujrakezdes 'u' | mozgatas(wasd): ";
		cin >> bekert;

		MozgasBekerese(bekert);

		SetConsoleTextAttribute(szinezes, sotetFeher);

		if (bekert == "u") {
			JatekMehet();
		}
		if (bekert == "k") {
			Kilep();
		}
	}
}

bool Vizsgal() {
#pragma region STRING TABLA ELKESZITESE
	int sor;
	int oszlop;

	int minSor = elemek[0].y_koordinata;
	int maxSor = elemek[0].y_koordinata;

	int minOszlop = elemek[0].x_koordinata;
	int maxOszlop = elemek[0].x_koordinata;
	for (int i = 0; i < elemek_hossz; i++)
	{
		if (elemek[i].y_koordinata < minSor) {
			minSor = elemek[i].y_koordinata;
		}
		if (elemek[i].y_koordinata > maxSor) {
			maxSor = elemek[i].y_koordinata;
		}

		if (elemek[i].x_koordinata < minOszlop) {
			minOszlop = elemek[i].x_koordinata;
		}
		if (elemek[i].x_koordinata > maxOszlop) {
			maxOszlop = elemek[i].x_koordinata;
		}
	}

	sor = abs(maxSor - minSor) + 1;
	oszlop = abs(maxOszlop - minOszlop) + 1;

	string* tabla = new string[sor];

	for (int i = 0; i < sor; i++)
	{
		tabla[i] = "";
		for (int j = 0; j < oszlop; j++)
		{
			tabla[i] += ".";
		}
	}

	for (int i = 0; i < elemek_hossz; i++)
	{
		int sorIndex = 0;
		for (int j = minSor; j <= maxSor; j++)
		{
			int oszlopIndex = 0;
			for (int u = minOszlop; u <= maxOszlop; u++) {
				if (elemek[i].x_koordinata == u && elemek[i].y_koordinata == j) {
					tabla[sorIndex][oszlopIndex] = elemek[i].karakter;
				}
				oszlopIndex++;
			}
			sorIndex++;
		}
	}
#pragma endregion

	int ot = 0;
#pragma region VIZSZINTESEN -> X TENGELYEN
	if (oszlop >= 5) {
#pragma region JATEKOS EGY
		ot = 0;
		for (int i = 0; i < sor; i++) {
			for (int j = 0; j < oszlop; j++) {
				if (tabla[i][j] == jatekosEgySzimbolum) {
					ot++;
					if (ot >= MENNYIT) {
						//JatekVege();
						return true;
					}
				}
				else {
					ot = 0;
				}
			}
			ot = 0;
		}
#pragma endregion
#pragma region JATEKOS KETTO
		ot = 0;
		for (int i = 0; i < sor; i++) {
			for (int j = 0; j < oszlop; j++) {
				if (tabla[i][j] == jatekosKettoSzimbolum) {
					ot++;
					if (ot >= MENNYIT) {
						//JatekVege();
						return true;
					}
				}
				else {
					ot = 0;
				}
			}
			ot = 0;
		}
#pragma endregion
	}
#pragma endregion

#pragma region FUGGOLEGESEN -> Y TENGELYEN
	if (sor >= 5) {
#pragma region JATEKOS EGY
		ot = 0;
		for (int i = 0; i < sor; i++) {
			for (int j = 0; j < oszlop; j++) {
				if (tabla[i][j] == jatekosEgySzimbolum) {
					ot = 0;
					for (int u = i; u < sor; u++)
					{
						if (tabla[u][j] == jatekosEgySzimbolum) {
							ot++;
							if (ot >= MENNYIT) {
								//JatekVege();
								return true;
							}
						}
						else {
							ot = 0;
						}
					}
				}
				ot = 0;
			}
		}
#pragma endregion
#pragma region JATEKOS KETTO
		ot = 0;
		for (int i = 0; i < sor; i++) {
			for (int j = 0; j < oszlop; j++) {
				if (tabla[i][j] == jatekosKettoSzimbolum) {
					ot = 0;
					for (int u = i; u < sor; u++)
					{
						if (tabla[u][j] == jatekosKettoSzimbolum) {
							ot++;
							if (ot >= MENNYIT) {
								//JatekVege();
								return true;
							}
						}
						else {
							ot = 0;
						}
					}
				}
				ot = 0;
			}
		}
#pragma endregion
	}
#pragma endregion

	if (sor >= 5 && oszlop >= 5) {
#pragma region ATLO BALFELUL -> JOBB ALUL
#pragma region JATEKOS EGY
		for (int i = 0; i < sor; i++) {
			for (int j = 0; j < oszlop; j++) {
				if (tabla[i][j] == jatekosEgySzimbolum) {
					ot = 0;
					int index = 0;
					for (int u = i; u < sor; u++)
					{
						if (tabla[u][j + index] == jatekosEgySzimbolum) {
							ot++;
							if (ot >= 5) {
								jatekVege = true;
								return true;
							}
						}
						else {
							ot = 0;
							index = 0;
						}
						index++;
					}
				}
			}
		}
#pragma endregion
#pragma region JATEKOS KETTO
		for (int i = 0; i < sor; i++) {
			for (int j = 0; j < oszlop; j++) {
				if (tabla[i][j] == jatekosKettoSzimbolum) {
					ot = 0;
					int index = 0;
					for (int u = i; u < sor; u++)
					{
						if (tabla[u][j + index] == jatekosKettoSzimbolum) {
							ot++;
							if (ot >= 5) {
								jatekVege = true;
								return true;
							}
						}
						else {
							ot = 0;
							index = 0;
						}
						index++;
					}
				}
			}
		}
#pragma endregion
#pragma endregion

#pragma region ATLO JOBBFELUL -> BAL ALUL
#pragma region JATEKOS EGY
		for (int i = 0; i < sor; i++) {
			for (int j = 0; j < oszlop; j++) {
				if (tabla[i][j] == jatekosEgySzimbolum) {
					ot = 0;
					int index = 0;
					for (int u = i; u < sor; u++)
					{
						if (j - index >= 0) {
							if (tabla[u][j - index] == jatekosEgySzimbolum) {
								ot++;
								if (ot >= MENNYIT) {
									//JatekVege();
									return true;
								}
							}
							else {
								ot = 0;
								index = 0;
							}
						}
						index++;
					}
				}
			}
		}
#pragma endregion
#pragma region JATEKOS KETTO
		for (int i = 0; i < sor; i++) {
			for (int j = 0; j < oszlop; j++) {
				if (tabla[i][j] == jatekosKettoSzimbolum) {
					ot = 0;
					int index = 0;
					for (int u = i; u < sor; u++)
					{
						if (j - index >= 0) {
							if (tabla[u][j - index] == jatekosKettoSzimbolum) {
								ot++;
								if (ot >= MENNYIT) {
									//JatekVege();
									return true;
								}
							}
							else {
								ot = 0;
								index = 0;
							}
						}
						index++;
					}
				}
			}
		}
#pragma endregion
#pragma endregion
	}

	delete[] tabla;
	return false;
}

bool RakhatokE(int x, int y) {
	for (int i = 0; i < elemek_hossz; i++)
	{
		if (elemek[i].x_koordinata == x && elemek[i].y_koordinata == y) {
			return false;
		}
	}
	return true;
}

void KiirandoSorok(int x, int y)
{
	KiirandoSorokNullazasa();

	for (int i = 0; i < elemek_hossz; i++)
	{
		int sorIndex = 0;
		for (int sor = x - MAXHOSSZ; sor <= x + MAXHOSSZ; sor++)
		{
			int oszlopIndex = 0;
			for (int oszlop = y - MAXHOSSZ; oszlop <= y + MAXHOSSZ; oszlop++) {
				if (elemek[i].x_koordinata == sor && elemek[i].y_koordinata == oszlop) {
					kiirando_sorok[oszlopIndex][sorIndex] = elemek[i].karakter;
				}
				oszlopIndex++;
			}
			sorIndex++;
		}
	}
}

void PalyaMozgatasa(Iranyok irany, int mennyi) {

	for (int i = 0; i < mennyi; i++)
	{
		switch (irany)
		{
		case FEL:
			fuggolegesKoordinata -= 1;
			break;
		case BALRA:
			vizszintesKoordinata -= 1;
			break;
		case LE:
			fuggolegesKoordinata += 1;
			break;
		case JOBBRA:
			vizszintesKoordinata += 1;
			break;
		}
	}

	TengelyekRajzol(vizszintesKoordinata, fuggolegesKoordinata);
}

void PalyaKeretSzinAllit() {
	SetConsoleTextAttribute(szinezes, sotetFeher);
}

void TengelyekRajzol(int vizszintes, int fuggoleges) {
	system("cls");

	KiirandoSorok(vizszintes, fuggoleges);
	jatekEleje = false;

	cout << endl;

	cout << "\t";
	int felsoHossz = to_string(fuggoleges - MAXHOSSZ).length();
	int alsoHossz = to_string(fuggoleges + MAXHOSSZ).length();
	int sorSzelesseg;
	if (felsoHossz > alsoHossz) {
		sorSzelesseg = felsoHossz;
	}
	else {
		sorSzelesseg = alsoHossz;
	}
	for (int i = 0; i < sorSzelesseg; i++)
	{
		cout << " ";
	}

	int oszlopSzelesseg = 0;
	int oszlopKiirSzelesseg = 0;
	int sorIndex = fuggoleges - MAXHOSSZ;
	int sorKiirIndex = 0;
	int oszlopKiirIndex = 0;
	int sorI = 0;
	sorSzelesseg = to_string(fuggoleges).length();
	for (int sor = fuggoleges - MAXHOSSZ * 2; sor <= fuggoleges + MAXHOSSZ * 2 + 3; sor++)
	{
		oszlopKiirIndex = 0;
		for (int oszlop = vizszintes - MAXHOSSZ; oszlop <= vizszintes + MAXHOSSZ + 2; oszlop++)
		{
			PalyaKeretSzinAllit();

			oszlopSzelesseg = to_string(oszlop - 1).length() + 2;
			oszlopKiirSzelesseg = to_string(oszlop - 2).length() + 2;
			felsoHossz = to_string(fuggoleges - MAXHOSSZ).length();
			alsoHossz = to_string(fuggoleges + MAXHOSSZ).length();
			int kulonbseg;
			if (felsoHossz >= alsoHossz) {
				kulonbseg = felsoHossz - to_string(sorIndex).length();
			}
			else if (felsoHossz < alsoHossz) {
				kulonbseg = alsoHossz - to_string(sorIndex).length();
			}

			if (sor == fuggoleges - MAXHOSSZ * 2) {
				kulonbseg = felsoHossz - to_string(sorIndex).length();
				if (oszlop == vizszintes - MAXHOSSZ) {

					for (int i = 0; i < kulonbseg + 8; i++)
					{
						cout << " ";
					}
				}
				if (oszlop <= vizszintes + MAXHOSSZ) {
					if (oszlop == vizszintes - MAXHOSSZ) {
						cout << " ";
					}
					else {
						cout << fuggolegesCsik;
					}
					if (oszlop == vizszintes - MAXHOSSZ) {
						cout << "  ";
					}
					else {
						cout << " ";
					}
					SetConsoleTextAttribute(szinezes, feher);
					cout << oszlop << " ";
					PalyaKeretSzinAllit();
				}
			}
			else if (oszlop == vizszintes - MAXHOSSZ) {
				cout << endl;

				SetConsoleTextAttribute(szinezes, sarga);
#pragma region A
				if (sorI == 7) {
					cout << "    " << " " << also << egesz << egesz << egesz << egesz << egesz << "\t";
				}
				else if (sorI == 8) {
					cout << "    " << egesz << felso << " " << " " << egesz << " " << " " << "\t";
				}
				else if (sorI == 9) {
					cout << "    " << felso << egesz << also << also << egesz << also << also << "\t";
				}
				else if (sorI == 10) {
					cout << "    " << " " << " " << felso << felso << felso << felso << felso << "\t";
				}
#pragma endregion
#pragma region B
				else if (sorI == 11) {
					cout << "    " << also << egesz << egesz << also << egesz << egesz << also << "\t";
				}
				else if (sorI == 12) {
					cout << "    " << egesz << " " << " " << egesz << " " << " " << egesz << "\t";
				}
				else if (sorI == 13) {
					cout << "    " << egesz << also << also << egesz << also << also << egesz << "\t";
				}
				else if (sorI == 14) {
					cout << "    " << felso << felso << felso << felso << felso << felso << felso << "\t";
				}
#pragma endregion
#pragma region O
				else if (sorI == 15) {
					cout << " " << also << "  " << also << egesz << egesz << egesz << egesz << egesz << also << "\t";
				}
				else if (sorI == 16) {
					cout << " " << also << felso << " " << egesz << " " << " " << " " << " " << " " << egesz << "\t";
				}
				else if (sorI == 17) {
					cout << " " << " " << felso << " " << egesz << also << also << also << also << also << egesz << "\t";
				}
				else if (sorI == 18) {
					cout << "    " << " " << felso << felso << felso << felso << felso << " " << "\t";
				}
#pragma endregion
#pragma region M
				else if (sorI == 19) {
					cout << "    " << egesz << egesz << egesz << egesz << egesz << egesz << egesz << "\t";
				}
				else if (sorI == 20) {
					cout << "    " << " " << felso << egesz << egesz << also << " " << " " << "\t";
				}
				else if (sorI == 21) {
					cout << "    " << also << egesz << egesz << egesz << also << also << also << "\t";
				}
				else if (sorI == 22) {
					cout << "    " << felso << felso << felso << felso << felso << felso << felso << "\t";
				}
#pragma endregion
#pragma region A
				else if (sorI == 23) {
					cout << "    " << " " << also << egesz << egesz << egesz << egesz << egesz << "\t";
				}
				else if (sorI == 24) {
					cout << "    " << egesz << felso << " " << " " << egesz << " " << " " << "\t";
				}
				else if (sorI == 25) {
					cout << "    " << felso << egesz << also << also << egesz << also << also << "\t";
				}
				else if (sorI == 26) {
					cout << "    " << " " << " " << felso << felso << felso << felso << felso << "\t";
				}
#pragma endregion

				else {
					for (int i = 0; i < 14; i++)
					{
						cout << " ";
					}
					cout << "\t";
				}

				if (sorI % 2 == 0) {
					for (int i = 0; i < kulonbseg; i++)
					{
						cout << " ";
					}
					SetConsoleTextAttribute(szinezes, feher);
					cout << sorIndex;
					PalyaKeretSzinAllit();

					sorIndex++;
					sorKiirIndex++;
					cout << " ";
				}
				else {
					PalyaKeretSzinAllit();

					for (int i = 0; i < felsoHossz; i++)
					{
						if (sor > fuggoleges - MAXHOSSZ * 2 + 1 && sor < fuggoleges + MAXHOSSZ * 2 + 2) {
							cout << vizszintesCsik;
						}
						else {
							cout << " ";
						}
					}
					if (sor > fuggoleges - MAXHOSSZ * 2 + 1 && sor < fuggoleges + MAXHOSSZ * 2 + 2) {
						cout << vizszintesCsik;
					}
					else {
						cout << " ";
					}
				}
			}
			else {
				if (sorI % 2 != 0) {
					if (alsoHossz > felsoHossz && oszlop == vizszintes - MAXHOSSZ + 1) {
						cout << " ";
					}
					if (sor == fuggoleges - MAXHOSSZ * 2 + 1) {
						if (oszlop == vizszintes - MAXHOSSZ + 1) {
							cout << balFelsoSarok;
						}
						else {
							if (oszlop < vizszintes + MAXHOSSZ + 2) {
								cout << allitottT;
							}
							else {
								cout << jobbFelsoSarok;
							}
						}
					}
					else if (oszlop == vizszintes - MAXHOSSZ + 1) {
						if (sor < fuggoleges + MAXHOSSZ * 2 + 3) {
							cout << jobbraT;
						}
						else {
							cout << balAlsoSarok;
						}
					}
					else {
						if (oszlop < vizszintes + MAXHOSSZ + 2) {
							if (sor < fuggoleges + MAXHOSSZ * 2 + 3) {
								cout << kereszt;
							}
							else {
								cout << forditottT;
							}
						}
						else {
							if (sor < fuggoleges + MAXHOSSZ * 2 + 3) {
								cout << balraT;
							}
							else {
								cout << jobbAlsoSarok;
							}
						}
					}
					if (oszlop < vizszintes + MAXHOSSZ + 2) {
						for (int j = 0; j < oszlopSzelesseg; j++)
						{
							cout << vizszintesCsik;
						}
					}
				}
				else {
					if (oszlop == vizszintes - MAXHOSSZ + 1) {
						cout << fuggolegesCsik;
					}
					else {
						for (int i = 0; i < oszlopKiirSzelesseg; i++)
						{
							if (i == oszlopKiirSzelesseg / 2) {
								if (kiirando_sorok[sorKiirIndex - 1][oszlopKiirIndex] == jatekosEgySzimbolum) {
									SetConsoleTextAttribute(szinezes, cyan);
								}
								else if (kiirando_sorok[sorKiirIndex - 1][oszlopKiirIndex] == jatekosKettoSzimbolum) {
									SetConsoleTextAttribute(szinezes, rozsaszin);
								}
								cout << kiirando_sorok[sorKiirIndex - 1][oszlopKiirIndex];
								PalyaKeretSzinAllit();
							}
							else {
								cout << " ";
							}
						}
						cout << fuggolegesCsik;
					}
				}
			}
			if (oszlop > vizszintes - MAXHOSSZ + 1) {
				oszlopKiirIndex++;
			}
		}
		sorI++;
	}

	cout << endl;

	SugoKiir();

	if (!jatekVege) {
		LepesBekerese();
	}
}

void SugoKiir() {
	SetConsoleTextAttribute(szinezes, szurke);
	cout << "\t        Palya mozgatasa: 'w' fel | 'a' balra | 's' le | 'd' jobbra" << endl;
	cout << "\t        Ha egy szamot is beirsz rogton utana akkor annyit fog arrebb menni." << endl << endl;
	cout << "\t        Koordinata beirasa szokozzel elvalasztva." << endl;
	cout << "\t        Eloszor vizszintes majd fuggoleges." << endl << endl;
	SetConsoleTextAttribute(szinezes, feher);
}

void JatekosCsere() {
	if (melyikJatekos == 1) {
		melyikJatekos = 2;
	}
	else if (melyikJatekos == 2) {
		melyikJatekos = 1;
	}
}

void MelyikJatekosKovetkezikKiir() {
	cout << "\t        ";
	if (melyikJatekos == 1) {
		SetConsoleTextAttribute(szinezes, cyan);
		cout << "Elso jatekos kovetkezik: ";
		SetConsoleTextAttribute(szinezes, feher);
	}
	else if (melyikJatekos == 2) {
		SetConsoleTextAttribute(szinezes, rozsaszin);
		cout << "Masodik jatekos kovetkezik: ";
		SetConsoleTextAttribute(szinezes, feher);
	}
}

void Kilep() {
	exit(0);
}
#pragma once

#include "ConstEnum.h"
#include "Lag.h"

class Resultat
{
private:
	char dato[9];
	int  hjemmemaal;
	int  bortemaal;
	bool normalTid;
	int  bortescorere[MAXMAAL];
	int  hjemmescorere[MAXMAAL];
public:
	Resultat(std::ifstream& fil, char _dato[]);
	Resultat(Lag* hjemmelag, Lag* bortelag);
    bool sameDate(char* date);
	char* kortDato();
	char* langDato();
    void skrivResultatTilSkjerm();
    void skrivResultatTilFil(std::ofstream & utfil);
	int getHjemmemaal();
	int getBortemaal();
	bool getNormalTid();
	void besteSpillereHjemmeScor(int spiller[]) {
		for (int i = 0; i < hjemmemaal; i++) {
			spiller[hjemmescorere[i]-1]++;//Minus 1 fordi spiller nr 1 ligger i index 0
		}
	}
	void besteSpillereBorteScor(int spiller[]) {
		for (int i = 0; i < bortemaal; i++) {
			spiller[bortescorere[i]-1]++;//Minus 1 fordi spiller nr 1 ligger i index 0
		}
	}
};
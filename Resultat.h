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
	void besteSpillereHjemmeScor(int spiller[]);
	void besteSpillereBorteScor(int spiller[]);
};
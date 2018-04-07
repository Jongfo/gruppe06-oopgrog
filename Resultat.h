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
	Resultat(Lag* hjemmelag, Lag* bortelag);
	char* kortDato();
	char* langDato();
	void  skrivTilFil(std::ofstream& fil);
};
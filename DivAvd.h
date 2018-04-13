#pragma once

#include "ListTool2B.h"
#include "Lag.h"
#include "Resultat.h"
#include "ConstEnum.h"

class DivAvd : TextElement
{
private:
	int antLag;
	Lag* lag[MAXLAG];
	Resultat* resultat[MAXLAG][MAXLAG];

public:
	DivAvd(char* navn);
	DivAvd(std::ifstream& inn, char* navn);
	void  skrivTilFil(std::ofstream& ut);
	void  nyeLag();
	void  display();
	Lag*  getLag();
	Lag*  getLag(char* s);
	void  fjernSpillerNr(int n);
	char* hentNavn();
	void  visTabell();
	void  skrivTabellTilFil(char* navn);
	void  skrivTerminliste();
    bool  resultaterTilSkjerm(char* date);
    bool  resultaterTilFil(char* fileName, char* date);
	char* lesResultat(std::ifstream& fil);
	int   finnLagIndeks(char* navn);
	~DivAvd();
};

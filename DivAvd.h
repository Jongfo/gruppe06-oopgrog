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

	char* terminlisteFil;	// namnet p� fila der terminlista ligg

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
	void  visTabell(char* tabell);
	void  skrivTabellTilFil(char* navn, char* tabell);
	void  skrivTerminliste();
    bool  resultaterTilSkjerm(char* date);
    bool  resultaterTilFil(std::ofstream &utfil, char* date);
	char* lesResultat(std::ifstream& fil, bool& feil);
	int   finnLagIndeks(char* navn);
	bool  harSpilt(Lag* hjemmeLag, Lag* borteLag, char* dato);
	void  fjernResultat();
	bool dataTilTabell(char* tabell, int poeng[], int vunnet[], int uavgjort[], int tapt[]);
	void sorteringTilTabell(int poeng[], int vunnet[], int uavgjort[], int tapt[], Lag* sorter[]);
	~DivAvd();
};

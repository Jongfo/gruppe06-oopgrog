#pragma once

#include "ListTool2B.h"
#include "Lag.h"
#include "Resultat.h"
#include "ConstEnum.h"
#include "Spillere.h"

class DivAvd : TextElement
{
private:
	int antLag;
	Lag* lag[MAXLAG];
	Resultat* resultat[MAXLAG][MAXLAG];
	char* divFilPos;

public:
	DivAvd(std::ifstream& inn, char* navn, char* divFil);
	void skrivTilFil();
	void nyeLag();
	void display();
	Lag* getLag();
	Lag* getLag(char* s);
	void fjernSpillerNr(int n);
	char* hentNavn();
	void visTabell(char* tabell);
	void skrivTabellTilFil(std::ofstream &utfil, char* tabell);
	void skrivTerminliste();
    bool resultaterTilSkjerm(char* date);
    bool resultaterTilFil(std::ofstream &utfil, char* date);
	char* lesResultat(std::ifstream& fil, bool& feil);
	int finnLagIndeks(char* navn);
	bool harSpilt(Lag* hjemmeLag, Lag* borteLag, char* dato);
	void fjernResultat();
	bool dataTilTabell(char* tabell, int poeng[], int vunnet[], int uavgjort[], int tapt[]);
	void sorteringTilTabell(int poeng[], int vunnet[], int uavgjort[], int tapt[], Lag* sorter[]);
	void finnTopScorer();
	void sorteringTilScorer(int s[], int pos[]);
	void skrivScorerTilFil(std::ofstream& tsf, int s[], int pos[]);
	void skrivScorerTilSkjerm(int s[], int pos[]);
	void finnBesteSpillere(int s[]);
	void finnBesteSpillereiLag(int s[], int lagNr);
	char* getDivFilPos();
	~DivAvd();
};

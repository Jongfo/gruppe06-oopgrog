#pragma once

#include "RobustIO.h"
#include "Spiller.h"

extern RobustIO rIO;

class Spillere
{
private:
    int sisteNr;        //Antall spillere(?)
    List* spillere;     //Liste med spillere(sorted)

public:
    Spillere();
	void lesSpillereFraFil();
	void skrivTilFil();
	void nySpiller();
	void fjernSpiller();
	void visSpiller();
	void visSpiller(char* s);
	void visSpiller(int nr);
    char* getSpillerNavn(int nr);
	int getSisteNr();
	bool finsSpiller(int n);
    ~Spillere();
};

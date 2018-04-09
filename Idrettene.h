#pragma once

#include "Idrett.h"
#include "RobustIO.h"

extern RobustIO rIO;

class Idrettene
{
private:
	List* idretter;

public:
	Idrettene();
	void nyIdrett();
	void nyDivisjon();
	void visIdrett();
	void visIdrett(char* s);
	Idrett* getIdrett();
	Idrett* getIdrett(char* s);
	void lesInnIdrettFraFil();
	void skrivTilFil();
	void fjernSpillerNr(int n);
	void fjernIdrett();
	void skrivTabell();
	void lesResultat();
	~Idrettene();
};
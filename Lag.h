#pragma once

#include "RobustIO.h"
#include "ConstEnum.h"

extern RobustIO rIO;

class Lag
{
private:
	char* navn;             //Navn på leget
	char* postadresse;      //Adressen til laget
	int antSpillere;        //Antall spillere i laget
	int spillere[MAXSPILLERE];  //ID til spillere
public:
	Lag();
	~Lag();
};
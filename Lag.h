#pragma once

#include "ConstEnum.h"

class Lag
{
private:
	char* navn;
	char* postadresse;
	int antSpillere;
	int spillere[MAXSPILLERE];
public:
	Lag();
	~Lag();
};
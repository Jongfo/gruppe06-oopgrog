#pragma once

#include "RobustIO.h"
extern RobustIO rIO;
class Lag
{
private:
	char* navn;
	char* postadresse;
	int antSpillere;
	int spillere[50];
public:
	Lag();
	~Lag();
};
#pragma once

#include "RobustIO.h"
#include "ConstEnum.h"

extern RobustIO rIO;

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
	void display();
};
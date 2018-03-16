#pragma once

#include "ConstEnum.h"

class Resultat
{
private:
	char dato[9];
	int hjemmemaal;
	int bortemaal;
	bool normalTid;
	int bortescorere[MAXSPILLERE];
	int hjemmescorere[MAXSPILLERE];
public:
	Resultat();
};
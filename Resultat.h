#pragma once

#include "ConstEnum.h"
#include "Lag.h"

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
	Resultat(Lag* hjemmelag, Lag* bortelag);
};
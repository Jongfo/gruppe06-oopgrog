#pragma once

#include "ListTool2B.h"
#include "Lag.h"
#include "Resultat.h"

class DivAvd : TextElement
{
private:
	int antLag;
	Lag* lag[30];
	Resultat* resultat[30][30];

public:
	DivAvd(char* navn);
	~DivAvd();
};

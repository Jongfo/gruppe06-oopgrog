#pragma once

#include "ListTool2B.h"
#include "Lag.h"
#include "Resultat.h"
#include "ConstEnum.h"

class DivAvd : TextElement
{
private:
	int antLag;
	Lag* lag[MAXLAG];
	Resultat* resultat[MAXLAG][MAXLAG];

public:
	DivAvd(char* navn);
	void nyeLag();
	void display();
	~DivAvd();
};

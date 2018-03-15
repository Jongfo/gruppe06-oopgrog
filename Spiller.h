#pragma once
#include "ListTool2B.h"
#include "RobustIO.h"


extern RobustIO t;

class Spiller : public NumElement
{
private:
    char* navn;
    char* adresse;
public:
	Spiller();
    Spiller(int nr);
	virtual void display();
	int spillerNr();
	bool sameNavn(char* n);
    ~Spiller();
};

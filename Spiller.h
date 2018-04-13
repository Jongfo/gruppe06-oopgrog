#pragma once
#include "ListTool2B.h"
#include "RobustIO.h"

extern RobustIO rIO;


class Spiller : public NumElement
{
private:
    //int spillerNR er lagret som NumElement::number.
    char* navn;
    char* adresse;
public:
	Spiller();
    Spiller(int nr);
	Spiller(std::ifstream& inn, int num);
	void skrivTilFil(std::ofstream& ut);
	virtual void display();
	int spillerNr();
    char* spillerNavn();
	bool sammeNavn(char* n);
    ~Spiller();
};

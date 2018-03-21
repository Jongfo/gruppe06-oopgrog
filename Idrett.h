#pragma once
#include "ListTool2B.h"
#include "ConstEnum.h"
#include "RobustIO.h"
#include "DivAvd.h"

extern RobustIO rIO;
class Idrett : TextElement
{
private:
	List* divisjoner;
	char* tabelltype;

public:
	Idrett(char* navn);
	Idrett(std::ifstream& inn, char* navn);
	void skrivTilFil(std::ofstream& ut);
    void endreSpillere(char* idrettNavn, char* divNavn, char* lagNavn);
	void nyDivisjon();
	void display();
	DivAvd* getDivAvd(char* s);
	~Idrett();
};
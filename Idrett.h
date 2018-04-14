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
	void skrivTilFil(std::ofstream& idrettFil);
    bool resultatDatoTilSkjerm(char* date, DivAvd* div);
    bool resultatDatoTilFil(std::ofstream &utfil, char* date, DivAvd* div);
	void fjernSpillerNr(int n);
	void nyDivisjon();
	void fjernDivAvd();
	void visTabell();
	void display();
	DivAvd* getDivAvd();
	DivAvd* getDivAvd(char* s);
	void finnTopScorer();
	~Idrett();
};
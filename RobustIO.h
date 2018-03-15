#pragma once
#include <iostream>
#include <fstream>
class RobustIO
{
public:
	void lesInnICharPointer(const char* utskrift, char*& intast); //skriv ut til skjermen, leser inn tekst fra bruker
	void lesCharPointerFraFil(std::ifstream &inn, char*& t); //Brukes til å lese inn i pointer fra fil 
	char* lesNyttNavn(char* t);
	char* lesNyAdr(char* t);
	bool  okNavn(char* s);
	bool  okAdr(char* s); 
	int   tall(char* t, const int MIN, const int MAX); //Tekst til bruker og mellom hvilkne tall bruker kan taste
	char  lesInTilStor();//Leser in en kommand/Gjør til stor bokstav
	char* strip(char* s);
};
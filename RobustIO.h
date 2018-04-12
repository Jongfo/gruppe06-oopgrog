#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 
#include <iostream>
#include <fstream>
#include <cstring>          //  strcpy, strlen, strncmp
#include  <cstdlib>          //  ctoi
#include "ConstEnum.h"
class RobustIO
{
public:
	void  lesInnICharPointer(const char* utskrift, char*& inntast); //skriv ut til skjermen, leser inn tekst fra bruker
	void  lesCharPointerFraFil(std::ifstream &inn, char*& t); //Brukes til å lese inn i pointer fra fil 
	char* lesNyttNavn(const char* t);
	char* lesNyAdr(const char* t);
	char* lesTabelltype(const char* t);
	bool  finnesTabellen(char* tabelltype);
	bool  okNavn(char* s);
	bool  okAdr(char* s); 
	int   lesTall(const char* t, const int MIN, const int MAX); //Tekst til bruker og mellom hvilkne tall bruker kan taste
	char  lesInnTilStor();  //Leser in en kommand/Gjør til stor bokstav
	char* strip(char* s);   // Fjerner blanke fra s og returnerer det
	void lesDato(const char* t, char s[]);
	bool okDato(char* s);
	char* finnPlassOgLeggeFil(char* customname, char* id, const char* prefix);
	void fjernTegn(char* s, bool spesialtegn = true,
		           bool mellomrom = false, bool bokstaver = false,
		           bool tall = false);
	bool yn(); //Skriver ja eller nei
};
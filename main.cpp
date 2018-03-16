
//#include <iostream>
#include "ConstEnum.h"
#include "DivAvd.h"
#include "Idrett.h"
#include "Idrettene.h"
#include "Lag.h"
#include "ListTool2B.h"
#include "Resultat.h"
#include "RobustIO.h"
#include "Spiller.h"
#include "Spillere.h"

//Globale Variabler
RobustIO t;
Spillere spillere;
Idrettene idrettene;
//Funksjon deklaration
void skrivMeny();
void valgMeny();
void nySID();
void charNrTekst();

int main()
{
	skrivMeny();
	valgMeny();
}

void skrivMeny()
{ 
	std::cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:";
	std::cout << "\t\nS og A | nr | navn - (S)kriver (A)lle spillern eller alle med nr/navn";
	std::cout << "\t\nI og A | navn - (S)kriver (A)lle idrettene eller idretten med navn";
	std::cout << "\t\nN og S | I | D - (N)y (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\t\nF og S | I | D - (F)jern (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\t\nL - Skriv termin(L)iste for en gitt divisjon/avdeling til skjerm eller fil";
	std::cout << "\t\nK - Skriv alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil";
	std::cout << "\t\nT - Skriv (T)abell for en hel idrett eller en divisjon/avdeling til skjerm eller fil";
	std::cout << "\t\nR - Lese (R)esultatliste inn fra fil";
	std::cout << "\t\nD - (D)ata om alle spillerne på et lag";
	std::cout << "\t\nE - (E)ndre/redigere spillerne på et lag";
	std::cout << "\t\nC - Skriv 10-på-topp liste av topps(C)orerne for en gitt divisjon/avdeling eller et gitt lag til skjerm eller fil";
	std::cout << "\t\nQ = Quit/Avslutt";
}

void valgMeny() 
{
	char kommando = t.lesInTilStor(); // Leser brukerens ›nske/valg.
	while (kommando != 'Q') 
	{
		switch (kommando) 
		{
		case 'S': charNrTekst(); break;
		case 'I': break; 
		case 'N': nySID();  break;
		case 'F': break; 
		case 'L': break; 
		case 'K': break; 
		case 'T': break; 
		case 'R': break;
		case 'D': break;
		case 'E': break;
		case 'C': break;
		default: skrivMeny(); break; //Skriver meny
		}
		kommando = t.lesInTilStor(); // Leser brukerens ønske/valg.
	};
}
void nySID()
{
	char k = t.lesInTilStor();
	switch (k)
	{
	case 'S': spillere.nySpiller(); break;
	case 'I': break;
	case 'D': break;
	default:
		std::cout << "Ugyldig kommando";
		break;
	}
}

void charNrTekst()
{
	char temp[MAXTEKST];//Lager midlertidig char-array
	std::cin.getline(temp, MAXTEKST);//henter input fra bruker
	temp[0] = toupper(temp[0]);
	if (atoi(temp)) 
	{
		spillere.visSpiller(atoi(temp));
	}
	else if (strlen(temp) > 1)
	{
		spillere.visSpiller(temp);
	}
	else if (temp[0] == 'A') {
		spillere.visSpiller();
	}
	else 
	{
		std::cout << "\n\nUgyldig kommando";
	}

}
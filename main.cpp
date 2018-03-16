
//#include <iostream>
#include "ConstEnum.h"
#include "Idrettene.h"
#include "ListTool2B.h"
#include "RobustIO.h"
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
void lesFraFil();


int main()
{
	lesFraFil();
	skrivMeny();
	valgMeny();
}

void skrivMeny()
{ 
	std::cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:";
	std::cout << "\n\tS og A | nr | navn - (S)kriver (A)lle spillern eller alle med nr/navn";
	std::cout << "\n\tI og A | navn - (S)kriver (A)lle idrettene eller idretten med navn";
	std::cout << "\n\tN og S | I | D - (N)y (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\n\tF og S | I | D - (F)jern (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\n\tL - Skriv termin(L)iste for en gitt divisjon/avdeling til skjerm eller fil";
	std::cout << "\n\tK - Skriv alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil";
	std::cout << "\n\tT - Skriv (T)abell for en hel idrett eller en divisjon/avdeling til skjerm eller fil";
	std::cout << "\n\tR - Lese (R)esultatliste inn fra fil";
	std::cout << "\n\tD - (D)ata om alle spillerne på et lag";
	std::cout << "\n\tE - (E)ndre/redigere spillerne på et lag";
	std::cout << "\n\tC - Skriv 10-på-topp liste av topps(C)orerne for en gitt divisjon/avdeling eller et gitt lag til skjerm eller fil";
	std::cout << "\n\tQ = Quit/Avslutt";
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
void lesFraFil() 
{
	std::ifstream inn("gruppe06-ooprog/SPILLERE.DTA");
	if (inn) 
	{
		spillere.lesInn(inn);
	}
	else 
	{
		std::cout << "Finner ikke SPILLERE.DTA\n";
	}
}

//#include <iostream>
#include "ConstEnum.h"
#include "Idrettene.h"
#include "ListTool2B.h"
#include "RobustIO.h"
#include "Spillere.h"

//Globale Variabler
RobustIO rIO;
Spillere spillere;
Idrettene idrettene;

//Funksjon deklarasjoner
void skrivMeny();
void valgMeny();
void nySID();
void visSpiller();
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
	std::cout << "\n\tS A | nr | navn - (S)kriver (A)lle spillern eller alle med nr/navn";
	std::cout << "\n\tI A | navn - skr(I)ver (A)lle idrettene eller idretten med navn";
	std::cout << "\n\tN S | I | D - (N)y (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\n\tF S | I | D - (F)jern (S)piller,(I)drett eller (D)ivisjon/avdeling";
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
	char kommando = rIO.lesInTilStor(); // Leser brukerens ›nske/valg.

	while (kommando != 'Q') 
	{
		switch (kommando) 
		{
		case 'S': visSpiller(); break;
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
		kommando = rIO.lesInTilStor(); // Leser brukerens ønske/valg.
	};
}

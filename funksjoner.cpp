#include "RobustIO.h"
#include "Spillere.h"
#include "Idrettene.h"

extern RobustIO rIO;
extern Spillere spillere;
extern Idrettene idrettene;

// legg til ny spelar, idrett, divisjon
void nySID()
{
	char k = rIO.lesInTilStor();

	switch (k)
	{
	case 'S': spillere.nySpiller(); break;
	case 'I': idrettene.nyIdrett(); break;
	case 'D': break;
	default:
		std::cout << "Ugyldig kommando";
		break;
	}
}

// Viser ein spelar
void visSpiller() //Kan flytte denne inn i spillere � gj�re som frode
{
	char temp[MAXTEKST];				//Lager midlertidig char-array
	std::cin.getline(temp, MAXTEKST);	//henter input fra bruker
	temp[0] = toupper(temp[0]);			//F�rste bokstav skal v�re stor uansett
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

// les all data fr� fil
void lesFraFil()
{
	std::ifstream inn("gruppe06-ooprog/SPILLERE.DTA");
	if (inn)
	{
		spillere.lesFraFil(inn);
	}
	else
	{
		std::cout << "Finner ikke SPILLERE.DTA\n";
	}
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
	std::cout << "\n\tD - (D)ata om alle spillerne p� et lag";
	std::cout << "\n\tE - (E)ndre/redigere spillerne p� et lag";
	std::cout << "\n\tC - Skriv 10-p�-topp liste av topps(C)orerne for en gitt divisjon/avdeling eller et gitt lag til skjerm eller fil";
	std::cout << "\n\tQ = Quit/Avslutt";
}

void valgMeny()
{
	char kommando = rIO.lesInTilStor(); // Leser brukerens �nske/valg.

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
		kommando = rIO.lesInTilStor(); // Leser brukerens �nske/valg.
	};
}

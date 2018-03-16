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
void visSpiller() //Kan flytte denne inn i spillere å gjøre som frode
{
	char temp[MAXTEKST];				//Lager midlertidig char-array
	std::cin.getline(temp, MAXTEKST);	//henter input fra bruker
	temp[0] = toupper(temp[0]);			//Første bokstav skal være stor uansett
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

// les all data frå fil
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
#include "Resultat.h"
#include "RobustIO.h"
#include "Spillere.h"

extern RobustIO rIO;
extern Spillere spillere;

// les info om resultat frå fil
Resultat::Resultat(std::ifstream& fil, char _dato[])
{
	for (int i = 0; i < DATOLEN; i++)
	{
		dato[i] = _dato[i];
	}
	// DEBUG
	std::cout << "Resultat::lesFraFil\n";

	// DEBUG (std::cout)
	fil >> hjemmemaal;
	std::cout << '\t' << hjemmemaal << " - ";
	fil >> bortemaal;
	std::cout << bortemaal << "\t\t";
	fil >> normalTid;
	std::cout << (!normalTid ? "Ikkje " : "") << "normal tid!\n";

	std::cout << "\tHS: ";
	for (int i = 0; i < hjemmemaal; i++)
	{
		fil >> hjemmescorere[i];
		// DEBUG
		std::cout << ' ' << hjemmescorere[i];
	}

	std::cout << "\n\tBS: ";
	for (int i = 0; i < bortemaal; i++)
	{
		fil >> bortescorere[i];
		// DEBUG
		std::cout << ' ' << bortescorere[i];
	}
	std::cout << '\n';

	fil.ignore();
}

Resultat::Resultat(Lag* hjemmelag, Lag* bortelag)
{
	rIO.lesDato("Dato", dato);

	/*
	// les inn antal mål
	std::cout << "Maal:\n";
	hjemmemaal = rIO.lesTall(hjemmelag->getNavn(), 0, MAXMAAL);
	bortemaal = rIO.lesTall(bortelag->getNavn(), 0, MAXMAAL);

	// spør om kampen blei ferdig til normal tid
	std::cout << "Ble kampen ferdig paa normal tid? (y/n) ";
	normalTid = rIO.lesInnTilStor() == 'Y';

	// les inn målscorarar for alle måla
	
	// heimemål
	if (hjemmemaal > 0)
	{
		std::cout << "Maalscorere (" << hjemmelag->getNavn() << "):\n";
		for (int i = 0; i < hjemmemaal; i++)
		{
			// TODO: List opp spelarane på laget for brukarvennlegheit
			do
			{
				hjemmescorere[i] = rIO.lesTall("Spillerens nummer",
					0, spillere.getSisteNr());

				if (!hjemmelag->spillerILag(hjemmescorere[i]))
				{
					std::cout << hjemmescorere[i] << " spiller ikke for "
						<< hjemmelag->getNavn() << "!\n";
				}
			} while (!hjemmelag->spillerILag(hjemmescorere[i]));
		}
	}

	// bortemål
	if (bortemaal > 0)
	{
		std::cout << "Maalscorere (" << bortelag->getNavn() << "):\n";
		for (int i = 0; i < bortemaal; i++)
		{
			// TODO: List opp spelarane på laget for brukarvennlegheit
			do
			{
				bortescorere[i] = rIO.lesTall("Spillerens nummer",
					0, spillere.getSisteNr());

				if (!bortelag->spillerILag(bortescorere[i]))
				{
					std::cout << bortescorere[i] << " spiller ikke for "
						<< bortelag->getNavn() << "!\n";
				}
			} while (!bortelag->spillerILag(bortescorere[i]));
		}
	}
	*/
}

bool Resultat::sameDate(char* date)
{
    return !strcmp(date, dato);
}

// returnerer datoen i "dd/mm"-form
char* Resultat::kortDato()
{
	char* kortDato = new char[6];
	kortDato[0] = dato[6];
	kortDato[1] = dato[7];
	kortDato[2] = '/';
	kortDato[3] = dato[4];
	kortDato[4] = dato[5];
	kortDato[5] = '\0';
	return kortDato;
}

char* Resultat::langDato()
{
	return dato;
}
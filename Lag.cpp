#include "Lag.h"
#include "Spillere.h"
#include <algorithm>
extern Spillere spillere;

Lag::Lag()
{
	rIO.lesInnICharPointer("Navn paa lag?", navn);
	postadresse = rIO.lesNyAdr("Postadressa til laget?");
	int spillereAaLeggeTil = rIO.lesTall("Antall spillere på laget", 0,
									  std::min(spillere.getSisteNr(), MAXLAG));

	for (int i = 0; i < spillereAaLeggeTil; i++)
	{
		int nr;	// nr som brukaren tastar inn
		do
		{
			nr = rIO.lesTall("Nr til spiller", 1, spillere.getSisteNr());
			if (spillerILag(nr))
			{
				std::cout << "\nFins allerede i laget.\n";
			}
			if (!spillere.finsSpiller(nr))
			{
				std::cout << "\nSpiller fins ikke.\n";
			}
		} while (spillerILag(nr) || !spillere.finsSpiller(nr));
		spillerNr[antSpillere++] = nr;
	}
}
Lag::Lag(std::ifstream& inn) 
{
	rIO.lesCharPointerFraFil(inn, navn);
	rIO.lesCharPointerFraFil(inn, postadresse);
	int spillerePaaLaget; inn >> spillerePaaLaget;
	for (int i = 0; i < spillerePaaLaget; i++)
	{
		int nr; inn >> nr;
		spillerNr[antSpillere++] = nr;
	}
	inn.ignore();
	
}

Lag::~Lag()
{
	delete[] navn;
	delete[] postadresse;
}

// skriv info om laget til fil
void Lag::skrivTilFil(std::ofstream& ut)
{
	ut << navn << '\n'
		<< postadresse << '\n'
		<< antSpillere << '\n';

	for (int i = 0; i < antSpillere; i++)
	{
		ut << spillerNr[i] << ' ';
	}

	ut << '\n';
}

// returner true dersom spiller n finst i lager.
bool Lag::spillerILag(int n)
{
	for (int i = 0; i < antSpillere; i++)
	{
		if (spillerNr[i] == n)
		{
			return true;
		}
	}
	return false;
}

char* Lag::getNavn()
{
	return navn;
}

void Lag::displaySpillere()
{
	for (int i = 0; i < antSpillere; i++)
	{
		spillere.visSpiller(spillerNr[i]);
	}
}

void Lag::display()
{
	std::cout << "Lag: " << navn << '\n'
		<< "Adresse: " << postadresse << '\n'
		<< "Antall spillere: " << antSpillere << '\n';
}

// fjernar spillerNr n frå lag
void Lag::fjernSpillerNr(int n)
{
	for (int i = 0; i < antSpillere; i++)
	{
		if (spillerNr[i] == n)
		{
			spillerNr[i] = 0;

			// flytt alle over ned
			for (int j = i; j < antSpillere; j++)
			{
				spillerNr[j] = spillerNr[j + 1];
			}
			spillerNr[antSpillere - 1] = 0;
			break;
		}
	}
}
#include "Lag.h"
#include "Spillere.h"
#include <algorithm>
extern Spillere spillere;

Lag::Lag()
{
	rIO.lesInnICharPointer("Navn paa lag?", navn);
	rIO.lesInnICharPointer("Adresse til laget?", postadresse);
	int spillereAaLeggeTil = rIO.tall("Antall spillere p� laget", 0,
									  std::min(spillere.getSisteNr(), MAXLAG));

	for (int i = 0; i < spillereAaLeggeTil; i++)
	{
		int nr;	// nr som brukaren tastar inn
		do
		{
			nr = rIO.tall("Nr til spiller", 1, spillere.getSisteNr());
			if (spillerILag(nr))
			{
				std::cout << "\nFins allerede i laget.\n";
			}
		} while (spillerILag(nr));
		spillerNr[antSpillere++] = nr;
	}
}

Lag::~Lag()
{

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
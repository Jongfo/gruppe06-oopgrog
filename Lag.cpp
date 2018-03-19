#include "Lag.h"
#include "Spillere.h"
#include <algorithm>
extern Spillere spillere;

Lag::Lag()
{
	rIO.lesInnICharPointer("Navn paa lag?", navn);
	rIO.lesInnICharPointer("Adresse til laget?", postadresse);
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

void Lag::display()
{
	std::cout << "Lag: " << navn << '\n'
		<< "Adresse: " << postadresse << '\n'
		<< "Antall spillere: " << antSpillere << '\n';
}
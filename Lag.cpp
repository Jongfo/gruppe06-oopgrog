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
		} while (spillerILag(nr));
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
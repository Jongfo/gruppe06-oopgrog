#include "Spiller.h"

Spiller::Spiller() 
{
	std::cout << "\n\nWE ARE NOT SUPPOSED TO BE HERE\n\n";
}

Spiller::Spiller(int nr) : NumElement(nr)
{
	navn = rIO.lesNyttNavn("Navn paa spiller?");
	adresse = rIO.lesNyAdr("Adressen til spiller?");
}

Spiller::Spiller(std::ifstream& inn, int num) : NumElement(num)
{
	rIO.lesCharPointerFraFil(inn, navn);
	rIO.lesCharPointerFraFil(inn, adresse);
}

// skriv data om spelaren til fil
void Spiller::skrivTilFil(std::ofstream& ut)
{
	ut	<< number << '\n'
		<< navn << '\n'
		<< adresse << '\n';
}

void Spiller::display() 
{
	std::cout << "\nID: " << number << std::endl;
	std::cout << "Navn: " << navn << std::endl;
	std::cout << "Adressen: " << adresse << std::endl;
}

int Spiller::spillerNr() 
{
	return number;
}

char* Spiller::spillerNavn()
{
    return navn;
}

bool Spiller::sammeNavn(char* n)
{
	if (!strcmp(n, navn))
	{
		return true;
	}
	return false;
}

Spiller::~Spiller()
{
    delete[] navn;
    delete[] adresse;
}

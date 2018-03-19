#include "Lag.h"

Lag::Lag()
{
	rIO.lesInnICharPointer("Navn paa lag?", navn);
	rIO.lesInnICharPointer("Adresse til laget?", postadresse);
	//TODO: Les inn spelarar
}

Lag::~Lag()
{

}

void Lag::display()
{
	std::cout << "Lag: " << navn << '\n'
		<< "Adresse: " << postadresse << '\n'
		<< "Antall spillere: " << antSpillere << '\n';
}
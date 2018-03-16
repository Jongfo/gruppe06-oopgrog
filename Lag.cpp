#include "Lag.h"

Lag::Lag()
{
	rIO.lesInnICharPointer("Navn paa lag?", navn);
	rIO.lesInnICharPointer("Adresse til laget?", postadresse);
}

Lag::~Lag()
{

}
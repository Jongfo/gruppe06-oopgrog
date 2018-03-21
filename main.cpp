#include "Idrettene.h"
#include "RobustIO.h"
#include "Spillere.h"
#include "funksjoner.h"

//Globale Variabler
RobustIO rIO;
Spillere spillere;
Idrettene idrettene;

int main()
{
	lesFraFil();
	skrivMeny();
	valgMeny();

	spillere.skrivTilFil();
}

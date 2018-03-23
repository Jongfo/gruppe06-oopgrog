#include "Resultat.h"
#include "RobustIO.h"

extern RobustIO rIO;

Resultat::Resultat(Lag* hjemmelag, Lag* bortelag)
{
	rIO.lesDato("Dato", dato);
}
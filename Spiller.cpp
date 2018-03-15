#include "Spiller.h"
#include <iostream>

Spiller::Spiller(int nr) : NumElement(nr)
{
    // les inn namn
    // les inn adresse
}

Spiller::~Spiller()
{
    delete[] navn;
    delete[] adresse;
}

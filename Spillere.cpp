#include "Spillere.h"
#include "Spiller.h"

Spillere::Spillere()
{
    spillere = new List(Sorted);
}

Spillere::~Spillere()
{
    delete spillere;
}

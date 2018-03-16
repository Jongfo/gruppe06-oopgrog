#include "Idrettene.h"

Idrettene::Idrettene()
{
	idretter = new List(Sorted);
}
void Idrettene::nyIdrett() 
{
	char* t;
	rIO.lesInnICharPointer("Navn paa Idrett?", t);
	idretter->add((TextElement*)new Idrett(t));
}
Idrettene::~Idrettene()
{
	delete idretter;
}
#include "Idrettene.h"

Idrettene::Idrettene()
{
	idretter = new List(Sorted);
}

Idrettene::~Idrettene()
{
	delete idretter;
}

// legg til ny idrett i lista
void Idrettene::nyIdrett() 
{
	char* t;
	rIO.lesInnICharPointer("Navn paa Idrett?", t);

	// sjekk at idretten ikkje allereie finst
	if (!idretter->inList(t))
	{
		idretter->add((TextElement*)(new Idrett(t)));
	}
	else
	{
		std::cout << "En idrett med dette navnet fins allerede!\n";
	}
}
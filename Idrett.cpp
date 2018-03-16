#include "Idrett.h"

Idrett::Idrett(char* navn) : TextElement(navn)
{
	char* t;
	rIO.lesInnICharPointer("Navn paa Divisjon/Avdeling?", t);
	divisjoner->add((TextElement*)new DivAvd(t)); 
}

Idrett::~Idrett()
{
	delete divisjoner;
}
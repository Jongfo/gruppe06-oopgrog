#include "Idrett.h"

Idrett::Idrett(char* navn) : TextElement(navn)
{
	divisjoner = new List(Sorted);
	nyDivisjon();
	tabelltype = rIO.lesTabelltype("Tabelltype: ");
	
}
void Idrett::nyDivisjon() {
	char* t;
	rIO.lesInnICharPointer("Navn paa Divisjon/Avdeling?", t);
	if (!divisjoner->inList(t)) {
		divisjoner->add((TextElement*)new DivAvd(t));
	}
	else
	{
		std::cout << "Denne divisjonen finner allerede i listen"
	}
}
Idrett::~Idrett()
{
	delete divisjoner;
}

void Idrett::display()
{
	std::cout << text << '\n'
		<< "Tabelltype: " << tabelltype << '\n';
}
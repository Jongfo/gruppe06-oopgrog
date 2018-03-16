#include "Idrett.h"

Idrett::Idrett(char* navn) : TextElement(navn)
{
	divisjoner = new List(Sorted);
	char* t;
	rIO.lesInnICharPointer("Navn paa Divisjon/Avdeling?", t);
	tabelltype = rIO.lesTabelltype("Tabelltype: ");
	divisjoner->add((TextElement*)new DivAvd(t)); 
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
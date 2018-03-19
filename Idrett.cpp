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
		std::cout << "Denne divisjonen finner allerede i listen";
	}
}
Idrett::~Idrett()
{
	delete divisjoner;
}

// returnerer div/avd med namn s
DivAvd* Idrett::getDivAvd(char* s)
{
	if (divisjoner->inList(s))
	{
		DivAvd* divisjon = (DivAvd*)divisjoner->remove(s);
		divisjoner->add((TextElement*)divisjon);
		return divisjon;
	}
	else
	{
		std::cout << "Divisjon/Avdeling eksisterer ikke.\n";
		return nullptr;
	}
}

void Idrett::display()
{
	std::cout << text << '\n'
		<< "Tabelltype: " << tabelltype << '\n'
		<< "Antall divisjoner: " << divisjoner->noOfElements() << '\n';
	divisjoner->displayList();
}
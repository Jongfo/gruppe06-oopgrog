#include "Idrett.h"
Idrett::Idrett(char* navn) : TextElement(navn)
{
	tabelltype = rIO.lesTabelltype("Tabelltype: ");
	divisjoner = new List(Sorted);
	nyDivisjon();
	
}
Idrett::Idrett(std::ifstream&inn, char* navn) : TextElement(navn) 
{
	char* tabelltemp;
	rIO.lesCharPointerFraFil(inn, tabelltemp);
	if (rIO.finnesTabellen(tabelltemp)) 
	{
		tabelltype = tabelltemp;
	}
	else 
	{
		tabelltype = (char*)"DOES NOT EXIST";
	}
	divisjoner = new List(Sorted);
	std::ifstream innDiv("gruppe06-ooprog/NY_DIV.DTA");
	if (innDiv) 
	{
		while (innDiv.good()) 
		{
			char* temp; rIO.lesCharPointerFraFil(innDiv, temp);
			if (!strcmp(temp,navn)) 
			{
				int n; innDiv >> n; innDiv.ignore();
				for (int i = 0; i < n; i++) 
				{
					char* temp2;  rIO.lesCharPointerFraFil(innDiv, temp2);
					divisjoner->add((TextElement*)new DivAvd(innDiv,temp2));
				}
			}
		}
	}
	else 
	{
		std::cout << "\nFinner ikke NY_DIV.DTA";
	}
}

// skriv data om idrett og divisjonar til fil
void Idrett::skrivTilFil(std::ofstream& idrettFil, std::ofstream& divAvdFil)
{
	// skriv data
	idrettFil << text << '\n'
			  << tabelltype << '\n';

	divAvdFil << text << '\n'
			  << divisjoner->noOfElements() << '\n';
	
	// skriv divisjonar
	for (int i = 1; i <= divisjoner->noOfElements(); i++)
	{
		DivAvd* divisjon = (DivAvd*)divisjoner->removeNo(i);
		divisjoner->add((TextElement*)divisjon);
		divisjon->skrivTilFil(divAvdFil);
	}
}

void Idrett::nyDivisjon()
{
	char* t;
	rIO.lesInnICharPointer("Navn paa Divisjon/Avdeling?", t);
	if (!divisjoner->inList(t))
	{
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

// les namn paa og returnerer div/avd
DivAvd* Idrett::getDivAvd()
{
	// les namn paa div/avd
	char* divNavn;
	rIO.lesInnICharPointer("Divisjon/Avdeling", divNavn);
	DivAvd* divisjon = getDivAvd(divNavn);
	return divisjon;
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
	std::cout << '\n' << text << '\n'
		<< "Tabelltype: " << tabelltype << '\n'
		<< "Antall divisjoner: " << divisjoner->noOfElements() << '\n';
	divisjoner->displayList();
}

// fjernar spillerNr n frå alle lag i alle divisjonane
void Idrett::fjernSpillerNr(int n)
{
	for (int i = 1; i <= divisjoner->noOfElements(); i++)
	{
		DivAvd* divisjon = (DivAvd*)divisjoner->removeNo(i);
		divisjon->fjernSpillerNr(n);
		divisjoner->add((TextElement*)divisjon);
	}
}

// fjernar ein divisjon
void Idrett::fjernDivAvd()
{
	char* divisjonNavn;
	rIO.lesInnICharPointer("Divisjon/Avdeling aa fjerne", divisjonNavn);
	if (divisjoner->inList(divisjonNavn))
	{
		DivAvd* divisjon = (DivAvd*)divisjoner->remove(divisjonNavn);
		delete divisjon;
	}
	else
	{
		std::cout << "Divisjon fins ikke!\n";
	}
}
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
	int antDiv; inn >> antDiv; inn.ignore();
	for (int i = 0; i < antDiv; i++) {
		char* divNavn;  rIO.lesCharPointerFraFil(inn, divNavn);
		//Finner hvor filen ligger
		char filPlass[MAXTEKST]; char tekst[] = "gruppe06-ooprog/Div_i_"; char type[] = ".DTA";
		strcpy(filPlass, tekst); strcat(filPlass, navn); strcat(filPlass, divNavn); strcat(filPlass, type);
		std::ifstream innDiv(filPlass);//Åpner filen
		if (innDiv) {
			divisjoner->add((TextElement*)new DivAvd(innDiv, divNavn));
		}
		else {
			std::cout <<"FINNER IKKE: " << filPlass << '\n';
		}

	}
}

// skriv data om idrett og divisjonar til fil
void Idrett::skrivTilFil(std::ofstream& idrettFil)
{
	// skriv data
	idrettFil << text << '\n'
			  << tabelltype << '\n';
	idrettFil << divisjoner->noOfElements() << '\n';

	// skriv divisjonar
	for (int i = 1; i <= divisjoner->noOfElements(); i++)
	{
		DivAvd* divisjon = (DivAvd*)divisjoner->removeNo(i);
		idrettFil << divisjon->hentNavn() << '\n';
		//Finner ut hvor filen skal legges
		char filPlass[MAXTEKST]; char tekst[] = "gruppe06-ooprog/Div_i_"; char type[] = ".DTA";
		strcpy(filPlass, tekst); strcat(filPlass, text); strcat(filPlass, divisjon->hentNavn()); strcat(filPlass, type);
		std::ofstream divAvdFil(filPlass); //Legger file der

		divisjon->skrivTilFil(divAvdFil);
		divisjoner->add((TextElement*)divisjon);
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
		std::cout << "Vil du virkelig fjerne " << divisjonNavn << "? (y/n)";
		if (rIO.lesInnTilStor() == 'Y')
		{
			DivAvd* divisjon = (DivAvd*)divisjoner->remove(divisjonNavn);
			delete divisjon;
		}
	}
	else
	{
		std::cout << "Divisjon fins ikke!\n";
	}
}
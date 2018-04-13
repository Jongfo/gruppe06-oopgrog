#include "Idrett.h"
#include <fstream>
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
		char* filPlass = rIO.finnPlassOgLeggeFil(navn, divNavn, "Div/");
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
		char* filPlass = rIO.finnPlassOgLeggeFil(text, divisjon->hentNavn(), "Div/");
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
	else if (toupper(*s) == 'Q')
	{ 
		return nullptr;
	}
    //std::cout << "Divisjon/Avdeling eksisterer ikke.\n";
    return nullptr;
}

// Skriver alle kampene i alle divisjonene med gitt dato til fil
void Idrett::alleKampeneTilFil(char* fileName, char* date, DivAvd* div)
{
    std::ifstream innfil("RESULTAT.DTA"); //sjekk navn!


    if (div)
    {

    }
    else
    {
        for (int i = 1; i <= divisjoner->noOfElements(); i++)
        {
            DivAvd* tempDiv = (DivAvd*)divisjoner->removeNo(i);
            divisjoner->add((TextElement*)tempDiv);
            tempDiv->kamperTilFil(fileName, date);
        }
    }
}

// Skriver alle kapene i all divisjonene med gitt dato til skjerm
void Idrett::alleKampeneTilSkjerm(char* date, DivAvd* div)
{
    for (int i = 1; i <= divisjoner->noOfElements(); i++)
    {
        DivAvd* tempDiv = (DivAvd*)divisjoner->removeNo(i);
        divisjoner->add((TextElement*)tempDiv);
        tempDiv->kamperTilSkjerm(date);
    }
}

void Idrett::display()
{
	std::cout << '\n' << text << '\n'
			  << "Tabelltype: " << tabelltype << '\n'
			  << "Antall divisjoner: " << divisjoner->noOfElements() << '\n';
	divisjoner->displayList();
	std::cout << '\n';
	for (int i = 0; i < 20; i++) { std::cout << '-'; };
	std::cout << '\n';
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
		std::cout << "Vil du virkelig fjerne " << divisjonNavn << '?'; 
		if (rIO.yn())
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
//Viser tabell til divisjonen
void Idrett::visTabell() {
	char* divNavn; rIO.lesInnICharPointer("Navn paa divisjonen (blank for alle)", divNavn);
	char* filNavn; rIO.lesInnICharPointer("Fil navn på Divisjonen (blankt kun til skjerm", filNavn);
	if (!strlen(divNavn)) 
	{

			//Skriver alle tabeller til skjerm eller fil
		for (int i = 1; i <= divisjoner->noOfElements(); i++) {
			DivAvd* divisjon = (DivAvd*)divisjoner->removeNo(i);
			if (strlen(filNavn)) {
				divisjon->skrivTabellTilFil(filNavn);
			}
			else {
				divisjon->visTabell();
			}
			divisjoner->add((TextElement*)divisjon);
		}
	}
	else if (divisjoner->inList(divNavn))
	{
		//Skriver spesefikk tabell til sjerm eller fil
		DivAvd* divisjon = (DivAvd*)divisjoner->remove(divNavn);
		if (strlen(filNavn)) {
			divisjon->skrivTabellTilFil(filNavn);
		}
		else {
			divisjon->visTabell();
		}
		divisjoner->add((TextElement*)divisjon);
	}
	else 
	{
		std::cout << "Fant ikke Divisjonen\n\n";
	}
}
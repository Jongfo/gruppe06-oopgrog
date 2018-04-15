#include "Idrett.h"
#include <fstream>


Idrett::Idrett(char* navn) : TextElement(navn)
{
	// les inn tabelltype
	for (int i = 1; i < ANTTABELLTYPER; i++) {
		std::cout << '\t' <<  i << ". " << rIO.getTabelltype(i)<< "\n";
	}
	tabelltype = rIO.getTabelltype(rIO.lesTall("Tabelltype",1,ANTTABELLTYPER-1));
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
		char* filPlass; rIO.lesCharPointerFraFil(inn, filPlass);
		std::ifstream innDiv(filPlass);//Åpner filen
		if (innDiv) {
			divisjoner->add((TextElement*)new DivAvd(innDiv, divNavn, filPlass));
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
		idrettFil << divisjon->getDivFilPos() << '\n';
		//Finner ut hvor filen skal legges
		std::ofstream divAvdFil(divisjon->getDivFilPos()); //Legger file der

		divisjon->skrivTilFil();
		divisjoner->add((TextElement*)divisjon);
	}
}

void Idrett::nyDivisjon()
{
	char* t = nullptr;
	do
	{
		delete[] t;
		rIO.lesInnICharPointer("Navn paa Divisjon/Avdeling?", t);
	} while (strlen(t) == 1);

	if (strlen(t) > 1)
	{
		if (!divisjoner->inList(t))
		{
			//Finne en fil å lese data fra!
			bool fantPlass = false; bool utAvLoop = false;
			do {
				char* filPlass;
				rIO.lesInnICharPointer("Hva heter filen til Divisjonen? (husk fil type '.dta'/'.txt')", filPlass);
				char lok[MAXTEKST] = "gruppe06-ooprog/Div/";  strcat(lok, filPlass);
				std::ifstream nyDiv(lok);
				if (nyDiv) {
					filPlass = new char[strlen(lok) + 1]; strcpy(filPlass, lok);
					divisjoner->add((TextElement*)new DivAvd(nyDiv, t, filPlass));
					fantPlass = true; std::cout << "Lest fra filen" << filPlass << '\n';
				}
				else {
					std::cout << "Fant ikke filen, skrive in paa nytt?\n";
					utAvLoop = !rIO.yn(); delete[] filPlass;
				}
			} while (!fantPlass && !utAvLoop );
		}
		else
		{
			std::cout << "Denne divisjonen finnes allerede i listen";
		}
	}
	else
	{
		std::cout << "Ingen divisjon laga.\n";
	}
	
	delete[] t;
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
	rIO.lesInnICharPointer("Divisjon/Avdeling:", divNavn);
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
bool Idrett::resultatDatoTilFil(std::ofstream &utfil, char* date, DivAvd* div)
{
    bool found = false;
    utfil << "Resultater for " << TextElement::text << ' ' << date << ":\n";
    if (div)
    {
        found = div->resultaterTilFil(utfil, date);
    }
    else
    {
        for (int i = 1; i <= divisjoner->noOfElements(); i++)
        {
            DivAvd* tempDiv = (DivAvd*)divisjoner->removeNo(i);
            divisjoner->add((TextElement*)tempDiv);
            if (tempDiv->resultaterTilFil(utfil, date))
                found = true;
        }
    }
    return found;
}

// Skriver alle kapene i all divisjonene med gitt dato til skjerm
bool Idrett::resultatDatoTilSkjerm(char* date, DivAvd* div)
{
    bool found = false;
    std::cout << "\n\n\tResultater for " << TextElement::text << ' ' << date << ":\n";
    if (div)
    {
        found = div->resultaterTilSkjerm(date);
    }
    else
    {
        for (int i = 1; i <= divisjoner->noOfElements(); i++)
        {
            DivAvd* tempDiv = (DivAvd*)divisjoner->removeNo(i);
            divisjoner->add((TextElement*)tempDiv);
            if (tempDiv->resultaterTilSkjerm(date))
                found = true;
        }
    }
    return found;
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
			std::cout << divisjonNavn << " fjernet.\n";
		}
		else
		{
			std::cout << divisjonNavn << " ikke fjernet.\n";
		}
	}
	else
	{
		std::cout << "Divisjon fins ikke!\n";
	}

	delete[] divisjonNavn;
}
//Viser tabell til divisjonen
void Idrett::visTabell() {
	char* divNavn; rIO.lesInnICharPointer("Navn paa divisjonen (blank for alle)", divNavn);
	char* filNavn; 
	if (!strlen(divNavn)) 
	{
        rIO.lesInnICharPointer("Skriv fil navn hvis onsket aa skrve til fil (blankt kun til skjerm)", filNavn);
			//Skriver alle tabeller til skjerm eller fil
        if (strlen(filNavn))
        {
            char* filPlass = rIO.finnPlassOgLeggeFil(filNavn, "", "Tabell/");
            std::ofstream tabellFil(filPlass);
            // skriver idrett navn først i fila.
            tabellFil << "Idrett: " << TextElement::text << '\n'; 

            for (int i = 1; i <= divisjoner->noOfElements(); i++)
            {
                DivAvd* divisjon = (DivAvd*)divisjoner->removeNo(i);
                divisjon->skrivTabellTilFil(tabellFil, tabelltype);
                divisjoner->add((TextElement*)divisjon);
            }
            delete[] filPlass;
        }
		else 
        {
            for (int i = 1; i <= divisjoner->noOfElements(); i++)
            {
                DivAvd* divisjon = (DivAvd*)divisjoner->removeNo(i);
				divisjon->visTabell(tabelltype);
			    divisjoner->add((TextElement*)divisjon);
			}
		}
        delete[] filNavn;
	}
	else if (divisjoner->inList(divNavn))
	{
        rIO.lesInnICharPointer("Skriv fil navn hvis onsket aa skrve til fil (blankt kun til skjerm)", filNavn);
		//Skriver spesefikk tabell til sjerm eller fil
		DivAvd* divisjon = (DivAvd*)divisjoner->remove(divNavn);
		if (strlen(filNavn)) {
            char* filPlass = rIO.finnPlassOgLeggeFil(filNavn, "", "Tabell/");
            std::ofstream tabellFil(filPlass);
            // skriver idrett navn først i fila.
            tabellFil << "Idrett: " << TextElement::text << '\n';
			divisjon->skrivTabellTilFil(tabellFil, tabelltype);
            delete[] filPlass;
		}
		else {
			divisjon->visTabell(tabelltype);
		}
		divisjoner->add((TextElement*)divisjon);
        delete[] filNavn;
	}
	else 
	{
		std::cout << "Fant ikke Divisjonen\n\n";
	}
    delete[] divNavn;
}

void Idrett::finnTopScorer() {
	char* divisjonNavn;
	rIO.lesInnICharPointer("I hvilken divisjon vil du finne toppScorer?", divisjonNavn);
	if (divisjoner->inList(divisjonNavn)) {
		DivAvd* divisjon = (DivAvd*)divisjoner->remove(divisjonNavn);
		divisjon->finnTopScorer();
		divisjoner->add((TextElement*)divisjon);
	}
	else {
		std::cout << "Fant ikke divisjonen\n";
	}
}
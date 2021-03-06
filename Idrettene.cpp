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
	do {
		rIO.lesInnICharPointer("Navn paa Idrett?", t);
	} while (strlen(t) < 1);//S�rge for at den ikke er forkort

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

void Idrettene::nyDivisjon() 
{
	char* t;
	rIO.lesInnICharPointer("Navn paa Idrett?", t);

	// 
	if (idretter->inList(t))
	{
		Idrett* temp = (Idrett*)idretter->remove(t);
		temp->nyDivisjon();
		idretter->add((TextElement*)temp);
		
	}
	else
	{
		std::cout << "Finner ikke idrett\n";
	}
}

// viser alle idrettar
void Idrettene::visIdrett()
{
	idretter->displayList();
}

// sp�r om namn paa og returnerar idrett
Idrett* Idrettene::getIdrett()
{
	char* idrettNavn;
	rIO.lesInnICharPointer("Idrett:", idrettNavn);
	Idrett* idrett = getIdrett(idrettNavn);
	return idrett;
}

// returnerer idrett med eit gitt namn
Idrett* Idrettene::getIdrett(char* s)
{
	if (idretter->inList(s))
	{
		Idrett* idrett = (Idrett*)idretter->remove(s);
		idretter->add((TextElement*)idrett);
		return idrett;
	}
	else
	{
		//std::cout << "Idrett fins ikke!\n";
		return nullptr;
	}
}

// viser idrett med namn s
void Idrettene::visIdrett(char* s)
{
	if (idretter->inList(s))
	{
		idretter->displayElement(s);
	}
	else
	{
		std::cout << "Idrett eksisterer ikke.\n";
	}
}

void Idrettene::lesInnIdrettFraFil()
{
	std::ifstream inn("gruppe06-ooprog/IDRETTENE.DTA");
	if (inn) 
	{
		int antIdrett; inn >> antIdrett; inn.ignore();
		for (int i = 0; i < antIdrett; i++) 
		{
			char* t; rIO.lesCharPointerFraFil(inn, t);
			idretter->add((TextElement*)(new Idrett(inn,t)));
		}
	}
	else 
	{
		std::cout << "Finner ikke IDRETTENE.DTA";
	}
}

// skriv alle idrettane og divisjomame til fil
void Idrettene::skrivTilFil()
{
	std::ofstream idrettFil("gruppe06-ooprog/IDRETTENE.DTA");
	
	idrettFil << idretter->noOfElements() << '\n';
	
	for (int i = 1; i <= idretter->noOfElements(); i++)
	{
		Idrett* idrett = (Idrett*)idretter->removeNo(i);
		idrett->skrivTilFil(idrettFil);
		idretter->add((TextElement*)idrett);
	}
}

// fjernar spelarar med nr n fr� alle lag i alle idrettane
void Idrettene::fjernSpillerNr(int n)
{
	// g� gjennom alle idrettar
	for (int i = 1; i <= idretter->noOfElements(); i++)
	{
		Idrett* idrett = (Idrett*)idretter->removeNo(i);
		idrett->fjernSpillerNr(n);
		idretter->add((TextElement*)idrett);
	}
}

// fjernar ein idrett
void Idrettene::fjernIdrett()
{
	char* idrettNavn;
	rIO.lesInnICharPointer("Idrett aa fjerne:", idrettNavn);
	if (idretter->inList(idrettNavn))
	{
		std::cout << "Vil du virkelig fjerne " << idrettNavn << '?';
		if (rIO.yn())
		{
			Idrett* idrett = (Idrett*)idretter->remove(idrettNavn);
			delete idrett;
			std::cout << idrettNavn << " fjernet.\n";
		}
		else
		{
			std::cout << idrettNavn << " ikke fjernet.\n";
		}
	}

	delete[] idrettNavn;
}
// h�nterer skrive ut tabbeler
void Idrettene::skrivTabell() 
{
	//Vis resultat liste ikke finnes skal ikke dette kj�re
	char* idrNavn; rIO.lesInnICharPointer("Navn paa Idretten?", idrNavn);
	if (idretter->inList(idrNavn))
	{
		Idrett* idr = (Idrett*)idretter->remove(idrNavn);
		idr->visTabell();
		idretter->add((TextElement*)idr);
	}
	else
	{
		std::cout << "Fant ikke idretten \n\n";
	}
}

// les alle resultata fr� fil
bool Idrettene::lesResultat()
{
	std::ifstream fil("gruppe06-ooprog/RESULTAT.DTA");
	bool feil = false;	// true dersom feil i fila

	while (fil.good() && !feil)
	{
		
		// finn idrett
		char* idrettNavn;
		rIO.lesCharPointerFraFil(fil, idrettNavn);
		Idrett* idrett = getIdrett(idrettNavn);

		if (idrett != nullptr)
		{
			delete[] idrettNavn;

			char* divisjonNavn;
			rIO.lesCharPointerFraFil(fil, divisjonNavn);

			do	// les resultat i ein divisjon til vi f�r eit tomt namn
			{
				// finn div/avd
				DivAvd* divisjon = idrett->getDivAvd(divisjonNavn);

				if (divisjon != nullptr)
				{
					delete[] divisjonNavn;
					divisjonNavn = divisjon->lesResultat(fil, feil);
				}
				else
				{
					std::cout << "Ugyldig divisjon/avdeling '"
							  << divisjonNavn << "'.\n";
					feil = true;
				}

			} while (strlen(divisjonNavn) > 0 && !feil);
			delete[] divisjonNavn;
		}
		else
		{
			std::cout << "Ugyldig idrett '" << idrettNavn << "'.\n";
			delete[] idrettNavn;
			feil = true;
		}
	}

	if (!feil)
	{
		std::cout << "\nInnlesing av resultat vellykket.\n";
	}
	return feil;
}
void Idrettene::finnToppScorer() {
	char* idrNavn; rIO.lesInnICharPointer("Navn paa Idretten?", idrNavn);
	if (idretter->inList(idrNavn)) {
		Idrett* idr = (Idrett*)idretter->remove(idrNavn);
		idr->finnTopScorer();
		idretter->add((TextElement*)idr);
	}
	else {
		std::cout << "Fant ikke idretten \n\n";
	}
}
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

void Idrettene::nyDivisjon() 
{
	char* t;
	rIO.lesInnICharPointer("Navn paa Idrett?", t);

	// 
	if (idretter->inList(t)) {
		Idrett* temp = (Idrett*)idretter->remove(t);
		temp->nyDivisjon();
		idretter->add((TextElement*)temp);
		
	}
	else {
		std::cout << "Finner ikke idrett\n";
	}
}

// viser alle idrettar
void Idrettene::visIdrett()
{
	for (int i = 1; i <= idretter->noOfElements(); i++)
	{
		Idrett* idrett = (Idrett*)idretter->removeNo(i);
		idrett->display();
		idretter->add((TextElement*)idrett);
	}
}

// sp�r om namn paa og returnerar idrett
Idrett* Idrettene::getIdrett()
{
	char* idrettNavn;
	rIO.lesInnICharPointer("Idrett", idrettNavn);
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
		std::cout << "Idrett fins ikke!\n";
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
		int n; inn >> n; inn.ignore();
		for (size_t i = 0; i < n; i++) 
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
	//std::ofstream divAvdFil("gruppe06-ooprog/NY_DIV.DTA");

	idrettFil << idretter->noOfElements() << '\n';
	
	for (int i = 1; i <= idretter->noOfElements(); i++)
	{
		Idrett* idrett = (Idrett*)idretter->removeNo(i);
		idretter->add((TextElement*)idrett);
		idrett->skrivTilFil(idrettFil);
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
	rIO.lesInnICharPointer("Idrett aa fjerne", idrettNavn);
	if (idretter->inList(idrettNavn))
	{
		std::cout << "Vil du virkelig fjerne " << idrettNavn << "? (y/n)";
		if (rIO.lesInnTilStor() == 'Y')
		{
			Idrett* idrett = (Idrett*)idretter->remove(idrettNavn);
			delete idrett;
		}
	}
}

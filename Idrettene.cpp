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
		std::cout << "Idrett eksisterer ikke.\n";
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
		for (size_t i = 0; i < n; i++) {
			char* t; rIO.lesCharPointerFraFil(inn, t);
			idretter->add((TextElement*)(new Idrett(inn,t)));
		}
	}
	else 
	{
		std::cout << "Finner ikke IDRETTENE.DTA";
	}
}
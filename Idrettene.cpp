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
		idretter->add((TextElement*)t);
		
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

// viser idrett med namn s
void Idrettene::visIdrett(char* s)
{

}
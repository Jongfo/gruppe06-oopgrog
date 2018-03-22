#include "Spillere.h"
#include "Spiller.h"
#include "Idrettene.h"
#include "RobustIO.h"

extern RobustIO rIO;
extern Idrettene idrettene;

Spillere::Spillere()
{
    spillere = new List(Sorted);
}
void Spillere::lesSpillereFraFil()
{
	std::ifstream inn("gruppe06-ooprog/SPILLERE.DTA");
	if (inn) {
		inn >> sisteNr;
		for (int i = 0; i < sisteNr; i++) {
			int num;
			inn >> num; inn.ignore();
			Spiller* temp = new Spiller(inn, num);
			spillere->add(temp);
		}
	}
	else {
		std::cout << "Finner ikke SPILLERE.DTA\n";
	}
	
}

// skriv data om alle spelarane til fil
void Spillere::skrivTilFil()
{
	std::ofstream utfil("gruppe06-ooprog/SPILLERE.DTA");

	utfil << sisteNr << '\n';

	for (int i = 1; i <= spillere->noOfElements(); i++)
	{
		Spiller* spiller = (Spiller*)spillere->removeNo(i);
		spillere->add(spiller);
		spiller->skrivTilFil(utfil);
	}
}

void Spillere::nySpiller()
{
	int n;
	// finn fyrste ledige spelarnummer
	for (int i = 1; i <= sisteNr + 1; i++)
	{
		// "tom" plass i lista
		if (!spillere->inList(i))
		{
			n = i ;
		}
		// alt er fyllt frå før
		else if (i == sisteNr + 1)
		{
			n = sisteNr;
		}
	}
	spillere->add(new Spiller(n));
	sisteNr++;
}

void Spillere::fjernSpiller()
{
	int n = rIO.lesTall("Spillerens nummer?", 1, sisteNr);
	Spiller* spiller = (Spiller*)spillere->removeNo(n);
	delete spiller;

	idrettene.fjernSpillerNr(n);
}

void  Spillere::visSpiller() 
{
	for (int i = 1; i <= spillere->noOfElements(); i++) 
	{
		Spiller* temp = (Spiller*)spillere->removeNo(i);
		temp->display();
		spillere->add(temp);
	}
}

void  Spillere::visSpiller(char* s) 
{
	for (int i = 1; i <= spillere->noOfElements(); i++) 
	{
		Spiller* temp = (Spiller*)spillere->removeNo(i);
		if (temp->sammeNavn(s)) 
		{
			temp->display();
		}
		spillere->add(temp);
	}
}
void  Spillere::visSpiller(int nr) 
{
	for (int i = 1; i <= spillere->noOfElements(); i++) 
	{
		Spiller* temp = (Spiller*)spillere->removeNo(i);
		if (temp->spillerNr() == nr) {
			temp->display();
		}
		spillere->add(temp);
	}
}

int Spillere::getSisteNr()
{
	return sisteNr;
}

Spillere::~Spillere()
{
    delete spillere;
}

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

// les alle spelarane inn frå fil
void Spillere::lesSpillereFraFil()
{
	std::ifstream inn("gruppe06-ooprog/SPILLERE.DTA");
	if (inn)
	{
		inn >> sisteNr;
		while (inn.good())
		{
			int num;
			inn >> num;
			inn.ignore();
			if (!inn.fail())
			{
				Spiller* spiller = new Spiller(inn, num);
				spillere->add(spiller);
			}
		}
	}
	else
	{
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
	std::cout << "Spilleren faar nummeret " << ++sisteNr << '\n';
	spillere->add(new Spiller(sisteNr));
}

// fjernar ein spelar fraa lista
void Spillere::fjernSpiller()
{
	int n = rIO.lesTall("Spillerens nummer? (-1 for å avbryte)", 1, sisteNr, true);
	if (n != -1)
	{
		for (int i = 1; i <= spillere->noOfElements(); i++)
		{
			Spiller* spiller = (Spiller*)spillere->removeNo(i);
			if (spiller->spillerNr() == n)
			{
				delete spiller;
			}
			else
			{
				spillere->add(spiller);
			}
		}
		idrettene.fjernSpillerNr(n);
		std::cout << "\nSpiller nr. " << n << " fjernet.\n";
	}
	else
	{
		std::cout << "Ingen spillere fjernet.\n";
	}
}
//Viser alle spillere
void  Spillere::visSpiller() 
{
	spillere->displayList();
}
//Viser Spiller med navn s
void  Spillere::visSpiller(char* s) 
{
	bool fantS = false;
	for (int i = 1; i <= spillere->noOfElements(); i++) 
	{
		Spiller* temp = (Spiller*)spillere->removeNo(i);
		if (temp->sammeNavn(s)) 
		{
			temp->display(); fantS = true;
		}
		spillere->add(temp);
	}
	if (!fantS) {
		std::cout << "Fant ikke spiller " << s << "\n\n";
	}
}
//Viser spiller med nummer nr
void  Spillere::visSpiller(int nr) 
{
	bool fantNr = false;
	for (int i = 1; i <= spillere->noOfElements(); i++) 
	{
		Spiller* temp = (Spiller*)spillere->removeNo(i);
		if (temp->spillerNr() == nr) {
			temp->display(); fantNr = true;
		}
		spillere->add(temp);
	}
	if (!fantNr) {
		std::cout << "Fant ikke spiller nr." << nr << "\n\n";
	}
}

char* Spillere::getSpillerNavn(int nr)
{
    char* name = nullptr;
    for (int i = 1; i <= spillere->noOfElements(); i++)
    {
        Spiller* temp = (Spiller*)spillere->removeNo(i);
        if (temp->spillerNr() == nr)
        {
            name = temp->spillerNavn();
        }
        spillere->add(temp);
    }
    return name;
}

int Spillere::getSisteNr()
{
	return sisteNr;
}

Spillere::~Spillere()
{
    delete spillere;
}

// returnerar true dersom spelar finst
bool Spillere::finsSpiller(int n)
{
	if (spillere->inList(n))
	{
		return true;
	}
	else
	{
		return false;
	}
}
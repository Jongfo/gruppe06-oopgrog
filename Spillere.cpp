#include "Spillere.h"
#include "Spiller.h"
#include "RobustIO.h"

extern RobustIO rIO;


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
void Spillere::nySpiller()
{
	spillere->add(new Spiller(++sisteNr));
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
Spillere::~Spillere()
{
    delete spillere;
}

#include "Spillere.h"

Spillere::Spillere()
{
    spillere = new List(Sorted);
}
void Spillere::lesInn(std::ifstream & inn)
{
	int n;
	inn >> n;
	for (int i = 0; i < n; i++) {
		int num;
		inn >> num; inn.ignore();
		Spiller* temp = new Spiller(inn, num);
		spillere->add(temp);
	}
}
void Spillere::nySpiller()
{
	Spiller* temp = new Spiller(++sisteNr);
	spillere->add(temp);
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
		if (temp->sameNavn(s)) 
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

#include "DivAvd.h"

DivAvd::DivAvd(char* navn) : TextElement(navn)
{
	antLag = 0;
	DivAvd::nyeLag();
}

// legg til 0 eller fleire nye lag, og hvis det gjør legg til det laget
//TODO Vinne om lageet finnes fra før
void DivAvd::nyeLag() 
{
	char t[] = "Hvor mange lag oensker du aa legge til?";
	int l = rIO.lesTall(t, 0, MAXLAG - antLag);
	for (int i = antLag; i < antLag + l; i++) {
		lag[i] = new Lag();
	}
	antLag += l;
}

DivAvd::~DivAvd()
{
	for (int i = 0; i < MAXLAG; i++)
	{
		delete lag[i];
	}
	for (int i = 0; i < MAXLAG; i++)
	{
		for (int j = 0; j < MAXLAG; j++)
		{
			delete resultat[i][j];
		}
	}
}

void DivAvd::display()
{
	std::cout << text << ":\n"
		<< "Antall lag: " << antLag << '\n';
	for (int i = 0; i < antLag; i++)
	{
		lag[i]->display();
	}
}
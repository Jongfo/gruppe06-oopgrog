#include "DivAvd.h"

DivAvd::DivAvd(char* navn) : TextElement(navn)
{
	antLag = 0;

	DivAvd::nyeLag();
}

void DivAvd::nyeLag() 
{
	char t[] = "Hvor mange lag oensker du aa legge til?";
	int l = rIO.tall(t, 1, MAXLAG - antLag);
	for (int i = antLag; i < antLag + l; i++) {
		lag[i] = new Lag();
	}
	antLag += l;
}

DivAvd::~DivAvd()
{
}
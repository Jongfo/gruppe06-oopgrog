#include "DivAvd.h"

DivAvd::DivAvd(char* navn) : TextElement(navn)
{
	antLag = 0;
	DivAvd::nyeLag();
}

// legg til 0 eller fleire nye lag
void DivAvd::nyeLag() 
{
	char t[] = "Hvor mange lag oensker du aa legge til?";
	int l = rIO.tall(t, 0, MAXLAG - antLag);
	for (int i = antLag; i < antLag + l; i++) {
		lag[i] = new Lag();
	}
	antLag += l;
}

DivAvd::~DivAvd()
{
}
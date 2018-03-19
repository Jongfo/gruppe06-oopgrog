#pragma once

#include "Idrett.h"
#include "RobustIO.h"

extern RobustIO rIO;

class Idrettene
{
private:
	List* idretter;

public:
	Idrettene();
	void nyIdrett();
	void nyDivisjon();
	void visIdrett();
	void visIdrett(char* s);
	Idrett* getIdrett(char* s);
	void lesInnIdrettFraFil();
	~Idrettene();
};
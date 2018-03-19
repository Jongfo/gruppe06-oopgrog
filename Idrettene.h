#pragma once

#include "Idrett.h"

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
	~Idrettene();
};
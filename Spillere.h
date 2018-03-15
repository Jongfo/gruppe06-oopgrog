#pragma once

#include "ListTool2B.h"

class Spillere
{
private:
    int sisteNr;
    List* spillere;

public:
    Spillere();
	void nySpiller();
	void visSpiller();
	void visSpiller(char* s);
	void visSpiller(int nr);
    ~Spillere();
};

#pragma once

#include "RobustIO.h"
#include "ListTool2B.h"

class Spillere
{
private:
    int sisteNr;
    List* spillere;

public:
    Spillere();
	void lesFraFil(std::ifstream & inn);
	void nySpiller();
	void visSpiller();
	void visSpiller(char* s);
	void visSpiller(int nr);
    ~Spillere();
};

#pragma once

#include "ListTool2B.h"

class Spiller : public NumElement
{
private:
    char* navn;
    char* adresse;
public:
    Spiller(int nr);
    ~Spiller();
};

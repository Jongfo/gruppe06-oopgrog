#pragma once

class Lag
{
private:
	char* navn;
	char* postadresse;
	int antSpillere;
	int spillere[50];
public:
	Lag();
	~Lag();
};
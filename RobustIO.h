#pragma once

class RobustIO
{
public:
	char* lesNyttNavn(char* t);
	char* lesNyAdr(char* t);
	bool  okNavn(char* s);
	bool  okAdr(char* s);
	int   tall(char* t, const int MIN, const int MAX);
	char  tilStor(char ch);
	char* strip(char* s);
};
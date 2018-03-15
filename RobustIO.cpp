#include "RobustIO.h"


void RobustIO::lesInnICharPointer(const char* utskrift, char*& intast)
{
	std::cout << utskrift << std::endl;
	char temp[MAXTEKST];//Lager midlertidig char-array
	std::cin.getline(temp, MAXTEKST);//Bruker skriver inn i temp
	intast = new char[strlen(temp) + 1];//Gjør t akkurat temp langt
	strcpy(intast, temp); //Kopierer temp over til t
}
void RobustIO::lesCharPointerFraFil(std::ifstream &inn, char*& t)
{
	char temp[MAXTEKST];//Lager midlertidig char-array
	inn.getline(temp, MAXTEKST);//henter fra filen inn i temp
	t = new char[strlen(temp) + 1];//Gjør t akkurat temp langt
	strcpy(t, temp); //Kopierer temp over til t
}
char* RobustIO::lesNyttNavn(char* t)
{
	// TODO
	return nullptr;
}

char* RobustIO::lesNyAdr(char* t)
{
	// TODO
	return nullptr;
}

bool RobustIO::okNavn(char* s)
{
	// TODO
	return true;
}

bool RobustIO::okAdr(char* s)
{
	// TODO
	return true;
}

int RobustIO::tall(char* t, const int MIN, const int MAX)
{
	int tall;
	do {
		std::cout << '\t' << t << " (" << MIN << '-' << MAX << "): ";
		std::cin >> tall; std::cin.ignore();
	} while (tall < MIN || tall > MAX);
	return tall;
}

char RobustIO::lesInTilStor()
{
	char ch;
	std::cout << "\n\nKommando: ";
	std::cin >> ch; std::cin.ignore();
	return (toupper(ch));
}

char* RobustIO::strip(char* s)
{
	// TODO
	return nullptr;
}
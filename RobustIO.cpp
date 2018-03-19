#include "RobustIO.h"

const int ANTTABELLTYPER = 3;

// inneheld namna på tabelltypane
const char* TABELLTYPER[ANTTABELLTYPER] = {
	"2-1-0",
	"3-1-0",
	"3-2-1-0"
};

void RobustIO::lesInnICharPointer(const char* utskrift, char*& intast)
{
	std::cout << utskrift << std::endl;
	char temp[MAXTEKST];//Lager midlertidig char-array
	std::cin.getline(temp, MAXTEKST);//Bruker skriver inn i temp
	while (strlen(temp) <= 1) {
		std::cout << "For kort\n";
		std::cin.getline(temp, MAXTEKST);//Bruker skriver inn i temp
	}
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

// handterar innlesing av tabelltype
char* RobustIO::lesTabelltype(const char* t)
{
	while (true)
	{
		char* tabelltype;
		lesInnICharPointer(t, tabelltype);
		return lesTabelltypeFraFil(tabelltype);
	}
}
char* RobustIO::lesTabelltypeFraFil(char* tabelltype) 
{
	for (int i = 0; i < ANTTABELLTYPER; i++) 
	{
		if (!strcmp(tabelltype, TABELLTYPER[i])) 
		{
			// gyldig tabelltype
			return tabelltype;
		}
	}
	std::cout << "\nFinner ikke tabeltypen\n";
	delete[] tabelltype;
}

// returnerer true dersom berre bokstavar, mellomrom, bindestrek
bool RobustIO::okNavn(char* s)
{
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z') ||
			(s[i] >= 'a' && s[i] <= 'z') ||
			s[i] == '-' || s[i] == ' '))
		{
			return false;
		}
	}
	return true;
}

// returnerer true dersom inneheld berre bokstavar, mellomrom, bindestrek og tal
bool RobustIO::okAdr(char* s)
{
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z') ||
			  (s[i] >= 'a' && s[i] <= 'z') ||
			  (s[i] >= '0' && s[i] <= '9') ||
			   s[i] == '-' || s[i] == ' '))
		{
			return false;
		}
	}
	return true;
}

int RobustIO::lesTall(const char* t, const int MIN, const int MAX)
{
	int tall;
	do {
		std::cout << '\t' << t << " (" << MIN << '-' << MAX << "): ";
		std::cin >> tall; std::cin.ignore();
	} while (tall < MIN || tall > MAX);
	return tall;
}

char RobustIO::lesInnTilStor()
{
	char ch;
	std::cout << "\n\nKommando: ";
	std::cin >> ch; std::cin.ignore();
	return (toupper(ch));
}

// tek vekk blanke paa starten og slutten av teksta
char* RobustIO::strip(char* s)
{
	// strip fraa start
	while (s[0] == ' ')
	{
		// flytt alt ned
		for (int i = 0; i < strlen(s); i++)
		{
			s[i] = s[i + 1];
		}
	}
	// strip fraa enden
	while (s[strlen(s) - 1] == ' ')
	{
		s[strlen(s) - 1] = s[strlen(s)];
	}
	return s;
}
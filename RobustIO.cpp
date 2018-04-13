#include "RobustIO.h"

const int ANTTABELLTYPER = 4;

// inneheld namna på tabelltypane
const char* TABELLTYPER[ANTTABELLTYPER] = {
	"DOES NOT EXIST",
	"2-1-0",
	"3-1-0",
	"3-2-1-0"
};

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

// les inn eit gyldig namn
char* RobustIO::lesNyttNavn(const char* t)
{
	char* nyttNavn;
	do
	{
		lesInnICharPointer(t, nyttNavn);
		if (!okNavn(nyttNavn))
		{
			std::cout << "Ugyldig navn\n";
			delete[] nyttNavn;
			nyttNavn = nullptr;
		}
	} while (nyttNavn == nullptr);
	return nyttNavn;
}

// les inn ein gyldig adresse
char* RobustIO::lesNyAdr(const char* t)
{
	char* nyAdr;
	do
	{
		lesInnICharPointer(t, nyAdr);
		if (!okAdr(nyAdr))
		{
			std::cout << "Ugyldig adresse\n";
			delete[] nyAdr;
			nyAdr = nullptr;
		}
	} while (nyAdr == nullptr);
	return nyAdr;
}
// handterar innlesing av tabelltype
char* RobustIO::lesTabelltype(const char* t)
{
	while (true)
	{
		char* tabelltype;
		lesInnICharPointer(t, tabelltype);
		if (finnesTabellen(tabelltype)) 
		{
			return tabelltype;
		}
		else 
		{
			delete tabelltype;
		}
	}
}
bool RobustIO::finnesTabellen(char* tabelltype) 
{
	for (int i = 0; i < ANTTABELLTYPER; i++) 
	{
		if (!strcmp(tabelltype, TABELLTYPER[i])) 
		{
			// gyldig tabelltype
			return true;
		}
	}
	return false;
}

// returnerer true dersom berre bokstavar, mellomrom, bindestrek
bool RobustIO::okNavn(char* s)
{
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z') ||
			(s[i] >= 'a' && s[i] <= 'z') ||
			s[i] == '-' || s[i] == ' ') ||
			strlen(s) <= 1 )
		{
			return false;
		}
		// TODO: sjekk at ting ikkje står heilt jalla
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
			   s[i] == '-' || s[i] == ' ') ||
			   strlen(s) <= 1)
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
		std::cin >> tall; 
		if (std::cin.fail()) 
		{
			std::cin.clear();
			std::cin.ignore(MAXTEKST, '\n');
		}
		std::cin.ignore();
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

// les dato inn i s paa formatet aaaammdd
void RobustIO::lesDato(const char* t, char s[])
{
	char temp[MAXTEKST];
	do
	{
		std::cout << t << ": ";
		std::cin.getline(temp, MAXTEKST);
		fjernTegn(temp, true, true, true); // fjernar alt som ikkje er tal
	} while (!okDato(temp));
	strcpy(s, temp);
}

// fjerner spesifiserte tegn fra teksta s
void RobustIO::fjernTegn(char* s, bool spesialtegn, bool mellomrom,
						 bool bokstaver, bool tall)
{
	// fjern spesialteikn
	if (spesialtegn)
	{
		for (int i = 0; i < strlen(s); i++)
		{
			if (!((s[i] >= 'A' && s[i] <= 'Z') ||
				(s[i] >= 'a' && s[i] <= 'z') ||
				(s[i] >= '0' && s[i] <= '9') || s[i] == ' '))
			{
				// flytt alt etter ned
				for (int j = i; j < strlen(s); j++)
				{
					s[j] = s[j + 1];
				}
				i--;
			}
		}
	}

	// fjern mellomrom
	if (mellomrom)
	{
		strip(s);
		for (int i = 0; i < strlen(s); i++)
		{
			if (s[i] == ' ')
			{
				// flytt alt etter ned
				for (int j = i; j < strlen(s); j++)
				{
					s[j] = s[j + 1];
				}
				i--;
			}
		}
	}

	// fjern bokstavar
	if (bokstaver)
	{
		strip(s);
		for (int i = 0; i < strlen(s); i++)
		{
			if (s[i] >= 'A' && s[i] <= 'Z')
			{
				// flytt alt etter ned
				for (int j = i; j < strlen(s); j++)
				{
					s[j] = s[j + 1];
				}
				i--;
			}
		}
	}

	// fjern tal
	if (tall)
	{
		strip(s);
		for (int i = 0; i < strlen(s); i++)
		{
			if (s[i] >= '0' && s[i] <= '9')
			{
				// flytt alt etter ned
				for (int j = i; j < strlen(s); j++)
				{
					s[j] = s[j + 1];
				}
				i--;
			}
		}
	}


}

// returnerar true dersom gyldig dato paa format aaaammdd
bool RobustIO::okDato(char* s)
{
	if (strlen(s) != 8)
	{
		// ikkje rett lengd til aa vere dato
		return false;
	}
	else if (s[4] > '1' || (s[4] == '1' && s[5] > '2'))
	{
		// månaden er feil
		return false;
	}
	else if (s[6] > '3' || (s[6] == '3' && s[7] > '1'))
	{
		// dagen er feil
		// TODO: Sjekk ulike tillete dagar for ulike månadar
		return false;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (s[i] < '0' || s[i] > '9')
			{
				// ikkje alle symbola er tal
				return false;
			}
		}
	}

	return true;
}

char* RobustIO::finnPlassOgLeggeFil(char* customname, char* id, const char* prefix) 
{
	char filPlass[MAXTEKST]; char tekst[] = "gruppe06-ooprog/"; char type[] = ".DTA";
	char space[] = "_"; 
	strcpy(filPlass, tekst); strcat(filPlass, prefix); strcat(filPlass, customname);
	strcat(filPlass, space);  strcat(filPlass, id); strcat(filPlass, type);
	char* f; f = new char[strlen(filPlass) + 1];
	return strcpy(f, filPlass);
}
bool RobustIO::yn() {
	char konfirmation;
	do {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
		}
		std::cout << " (y/n): ";
		std::cin >> konfirmation;
		konfirmation = toupper(konfirmation);
	} while (std::cin.fail() || (konfirmation != 'Y' && konfirmation != 'N') );
	if (konfirmation == 'Y') {
		return true;
	}
	return false;
}

void RobustIO::setArrayTilNull(int a[], const int SIZE) {
	for (int i = 0; i < SIZE; i++) {
		a[i] = 0;
	}
}
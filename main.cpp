#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include "ListTool2B.h"
//#include <iostream>
//Globale Variable HUSK Å FLYTT DISSE TIL FILEN DE SKAL TIL
const int MAXTEKST = 100;

//Funksjon deklaration
char les(); //Leser in en kommand
//Vi bør ha en les til som ser om det er en char, en tekst eller et nr
int les(const char* txt, int min, int max); //Tekst til bruker og mellom hvilkne tall bruker kan taste
void les(const char* txt, char*& t);//Tekst til bruker, og hvor teksten skal hen
//void les(std::ifstream &inn, char*& t); //Brukes til å lese in i pointer fra fil 
void skrivMeny();
void valgMeny();

int main()
{
	skrivMeny();
	valgMeny();
}
char les() 
{
	char ch;
	std::cout << "\n\nKommando: ";
	std::cin >> ch; std::cin.ignore();
	return (toupper(ch));
}
int les(const char* txt, int min, int max) 
{
	int tall;
	do 
	{
		std::cout << '\t' << txt << " (" << min << '-' << max << "): ";
		std::cin >> tall; std::cin.ignore();
	} while (tall < min || tall > max);
	return tall;
}
void les(const char* txt, char*& t) 
{
	std::cout << txt << std::endl;
	char temp[MAXTEKST];//Lager midlertidig char-array
	std::cin.getline(temp, MAXTEKST);//Bruker skriver inn i temp
	t = new char[strlen(temp) + 1];//Gjør t akkurat temp langt
	strcpy(t, temp); //Kopierer temp over til t
}
/*
void les(std::ifstream &inn, char*& t) 
{
	char temp[MAXTEKST];//Lager midlertidig char-array
	inn.getline(temp, MAXTEKST);//henter fra filen inn i temp
	t = new char[strlen(temp) + 1];//Gjør t akkurat temp langt
	strcpy(t, temp); //Kopierer temp over til t
}
*/

void skrivMeny()
{ 
	std::cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:";
	std::cout << "\t\nS og A | nr | navn - (S)kriver (A)lle spillern eller alle med nr/navn";
	std::cout << "\t\nI og A | navn - (S)kriver (A)lle idrettene eller idretten mend navn";
	std::cout << "\t\nN og S | I | D - (N)y (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\t\nF og S | I | D - (F)jern (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\t\nL - Skriv termin(L)iste for en gitt divisjon/avdeling til skjerm eller fil";
	std::cout << "\t\nK - Skriv alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil";
	std::cout << "\t\nT - Skriv (T)abell for en hel idrett eller en divisjon/avdeling til skjerm eller fil";
	std::cout << "\t\nR - Lese (R)esultatlidte inn fra fil";
	std::cout << "\t\nD - (D)ata om alle spillerne på et lag";
	std::cout << "\t\nE - (E)ndre/redigere spillerne på et lag";
	std::cout << "\t\nC - Skriv 10-på-topp liste av topps(C)orerne for en gitt divisjon/avdeling eller et gitt lag til skjerm eller fil";
	std::cout << "\t\nQ = Quit/Avslutt";
}

void valgMeny() 
{
	char kommando = les(); // Leser brukerens ›nske/valg.
	while (kommando != 'Q') 
	{
		switch (kommando) 
		{
		case 'S': break; 
		case 'I': break; 
		case 'N': break; 
		case 'F': break; 
		case 'L': break; 
		case 'K': break; 
		case 'T': break; 
		case 'R': break;
		case 'D': break;
		case 'E': break;
		case 'C': break;
		default: skrivMeny(); break; //Skriver meny
		}
		kommando = les(); // Leser brukerens ønske/valg.
	};
}
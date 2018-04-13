#include "DivAvd.h"
#include <iomanip>
#include <iostream>

DivAvd::DivAvd(char* navn) : TextElement(navn)
{
	antLag = 0;
	DivAvd::nyeLag();

	// lag terminlista
	for (int i = 0; i < antLag; i++)
	{
		for (int j = 0; j < antLag; j++)
		{
			if (i != j)
			{
				std::cout << lag[i]->getNavn() << " (hjemme) - "
						  << lag[j]->getNavn() << " (borte):\n";
				resultat[i][j] = new Resultat(lag[i], lag[j]);
			}
		}
	}
}

DivAvd::DivAvd(std::ifstream& inn, char* navn) : TextElement(navn)
{
	inn >> antLag; inn.ignore();
	for (int i = 0; i < antLag; i++) 
	{
		lag[i] = new Lag(inn);
	}
}

// skriv data om divisjon/avdeling til fil
void DivAvd::skrivTilFil(std::ofstream& ut)
{
	// skriv data
	ut << antLag << '\n';

	// skriv laga
	for (int i = 0; i < antLag; i++)
	{
		lag[i]->skrivTilFil(ut);
	}
}

// legg til 0 eller fleire nye lag, og hvis det gj�r legg til det laget
//TODO Vinne om lageet finnes fra f�r
void DivAvd::nyeLag() 
{
	char t[] = "Hvor mange lag oensker du aa legge til?";
	int l = rIO.lesTall(t, 0, MAXLAG - antLag);
	for (int i = antLag; i < antLag + l; i++) {
		lag[i] = new Lag();
	}
	antLag += l;
}

DivAvd::~DivAvd()
{
	for (int i = 0; i < MAXLAG; i++)
	{
		delete lag[i];
	}
	for (int i = 0; i < MAXLAG; i++)
	{
		for (int j = 0; j < MAXLAG; j++)
		{
			delete resultat[i][j];
		}
	}
}

// les namn paa og returnerar lag
Lag* DivAvd::getLag()
{
	char* lagNavn;
	rIO.lesInnICharPointer("Lag", lagNavn);
	Lag* lag = getLag(lagNavn);
	return lag;
}

// returnerer eit lag i divisjonen
Lag* DivAvd::getLag(char* s)
{
	for (int i = 0; i < antLag; i++)
	{
		if (!strcmp(lag[i]->getNavn(), s)  )
		{
			return lag[i];
		}
	}
    if (toupper(*s) != 'Q')
	    std::cout << "Lag fins ikke!\n";
	return nullptr;
}

void DivAvd::display()
{
	std::cout << '\n' << text << ":\n"
			  << "Antall lag: " << antLag << '\n';

	for (int i = 0; i < antLag; i++)
	{
		lag[i]->display();
	}
	std::cout << '\n';
}

// fjernar spillerNr n fr� alle lag i divisjonen
void DivAvd::fjernSpillerNr(int n)
{
	for (int i = 0; i < antLag; i++)
	{
		lag[i]->fjernSpillerNr(n);
	}
}

char* DivAvd::hentNavn() 	
{
	return text;
}
void DivAvd::visTabell()
{
	//TODO display Tabell
	std::cout << "FAKE TABEL FOR " << text << "\n\n";
}
void DivAvd::skrivTabellTilFil(char* navn) 
{
	//TODO skrive tabellen til fil
	char* filPlass = rIO.finnPlassOgLeggeFil(navn, text, "Tabell/");
	std::ofstream divAvdFil(filPlass);
	//skrivTilFil(divAvdFil); //ONLY TEMP FOR TESTING
	std::cout << "FAKE WRITE OUT FOR " << text << "\n\n";
}

// skriv terminlista til fil eller til skjerm
void DivAvd::skrivTerminliste()
{
	std::ostream stream(nullptr);
	std::ofstream fil;
	char* filnavn;					// namnet p� fila � skriva til
	int kolonneStorrelse = 5;		// st�rrelsen p� ei kolonne

	// sett kolonnestorleik til st�rste lagnamn
	for (int i = 0; i < antLag; i++)
	{
		if (strlen(lag[i]->getNavn()) > kolonneStorrelse)
		{
			kolonneStorrelse = strlen(lag[i]->getNavn());
		}
	}

	rIO.lesInnICharPointer("Filnavn:", filnavn);

	if (strlen(filnavn) == 0)
	{
		// filnamn tomt; skriv til cout
		stream.rdbuf(std::cout.rdbuf());
	}
	else
	{
		// skriv til fil
		char* plass = rIO.finnPlassOgLeggeFil(filnavn, text, "TerminListe/");
		fil = std::ofstream(plass);
		stream.rdbuf(fil.rdbuf());
	}

	stream << "TERMINLISTE FOR " << text << '\n';

	for (int i = 0; i < kolonneStorrelse; i++)
	{
		stream << ' ';
	}

	// skriv namn p� toppen
	for (int i = 0; i < antLag; i++)
	{
		stream << std::setw(kolonneStorrelse) << lag[i]->getNavn() << ' ';
	}

	stream << '\n';

	// skriv datoane
	for (int i = 0; i < antLag; i++)
	{
		stream << std::setw(kolonneStorrelse) << lag[i]->getNavn() << ' ';
		for (int j = 0; j < antLag; j++)
		{
			stream << std::setw(kolonneStorrelse);
			if (i != j)
			{
				stream << resultat[i][j]->kortDato() << ' ';
			}
			else
			{
				stream << "----- ";
			}
		}
		stream << '\n';
	}

	delete[] filnavn;
}


// Leser alle 
bool DivAvd::resultaterTilSkjerm(char* date)
{
    bool found = false;
    for (int i = 0; i < MAXLAG; i++)
    {
        for (int j = 0; j < MAXLAG; j++)
        {
            if (resultat[i][j]->sameDate(date))
            {
                std::cout << "H: " << lag[i]->getNavn() << " vs. B: " << lag[j]->getNavn() << '\n';
                resultat[i][j]->skrivResultatTilSkjerm();
                found = true;
            }
        }
    }
    return found;
}

bool DivAvd::resultaterTilFil(char* fileName, char* date)
{
    bool found = false;
    std::ofstream utfil(fileName);


    for (int i = 0; i < MAXLAG; i++)
    {
        for (int j = 0; j < MAXLAG; j++)
        {
            if (resultat[i][j]->sameDate(date))
            {
                utfil << "H: " << lag[i]->getNavn() << " vs. B: " << lag[j]->getNavn() << '\n';
                resultat[i][j]->skrivResultatTilFil(utfil);
                found = true;
            }
        }
    }
    return found;
}

// les resultat for denne avdelinga inn i terminlista
// returnerer den andre linje etter siste resultat
// i ein divisjon.
// Dersom ho er tom, har vi ein ny idrett,
// dersom ikkje, har vi ein ny divisjon
char* DivAvd::lesResultat(std::ifstream& fil)
{
	// TODO: Sjekk at innlesinga er logisk gyldig

	char* dato;
	char* hjemmeLag;
	char* borteLag;

	int hjemmeLagIndeks;
	int borteLagIndeks;

	// dei to neste linjene etter innlesing av eit resultat
	char* l1;
	char* l2;

	// les dato og namna p� laga
	rIO.lesCharPointerFraFil(fil, dato);
	std::cout << dato << '\n';
	rIO.lesCharPointerFraFil(fil, hjemmeLag);
	rIO.lesCharPointerFraFil(fil, borteLag);

	// finn ideksar
	hjemmeLagIndeks = finnLagIndeks(hjemmeLag);
	borteLagIndeks  = finnLagIndeks(borteLag);

	delete[] hjemmeLag;
	delete[] borteLag;

	while (fil.good())
	{
		// DEBUG
		std::cout << hjemmeLagIndeks << " - " << borteLagIndeks << '\n';


		// les inn resultat for denne kampen
		resultat[hjemmeLagIndeks][borteLagIndeks] = new Resultat(fil, dato);


		// dei to neste linjene i fila
		rIO.lesCharPointerFraFil(fil, l1);
		rIO.lesCharPointerFraFil(fil, l2);

		// DEBUG
		std::cout << "l1: '" << l1 << "'\n";
		std::cout << "l2: '" << l2 << "'\n";

		// Dersom 1 er blank og 2 er blank, eller slutten av fila
		// ny idrett
		if ((strlen(l1) < 1 && strlen(l2) < 1) || !fil.good())
		{
			std::cout << "\nA\n\n";
			if (!fil.good()) { std::cout << "\nSLUTT\n\n"; }
			delete[] l1;
			return l2;
		}

		// Dersom 1 er blank og 1 ikkje er blank
		// ny divisjon
		else if (strlen(l1) < 1 && strlen(l2) > 0)
		{
			std::cout << "\nB\n\n";
			delete[] l1;
			return l2;
		}

		// Dersom 1 er dato og 2 er lag (2 m� vere lag, ellers er fila feil),
		// er 2 lag1 og lag2 m� lesast inn
		else if (rIO.okDato(l1) && strlen(l2) > 0)
		{
			std::cout << "\nC\n\n";
			delete[] dato;
			dato = new char[strlen(l1) + 1];
			strcpy(dato, l1);

			hjemmeLagIndeks = finnLagIndeks(l2);
			rIO.lesCharPointerFraFil(fil, borteLag);
			borteLagIndeks = finnLagIndeks(borteLag);
			delete[] borteLag;
		}

		// dersom 1 ikkje er dato, og 2 ikkje er dato,
		// er 1 lag1 2 lag2
		else if (!rIO.okDato(l1) && !rIO.okDato(l2))
		{
			std::cout << "\nD\n\n";
			hjemmeLagIndeks = finnLagIndeks(l1);
			hjemmeLagIndeks = finnLagIndeks(l2);
		}

		delete[] l1;
		delete[] l2;
	}
}

// finn indeks til laget med gitt namn
int DivAvd::finnLagIndeks(char* navn)
{
	for (int i = 0; i < MAXLAG; i++)
	{
		if (!strcmp(navn, lag[i]->getNavn()))
		{
			// fant laget med namn navn
			return i;
		}
	}

	// fant ingen lag med dette namnet !
	return 0;
}
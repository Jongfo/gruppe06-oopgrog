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

// legg til 0 eller fleire nye lag, og hvis det gjør legg til det laget
//TODO Vinne om lageet finnes fra før
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

// fjernar spillerNr n frå alle lag i divisjonen
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
	char* filnavn;					// namnet på fila å skriva til
	int kolonneStorrelse = 5;		// størrelsen på ei kolonne

	// sett kolonnestorleik til største lagnamn
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

	// skriv namn på toppen
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
void DivAvd::kamperTilSkjerm(char* date)
{

}

void DivAvd::kamperTilFil(char* fileName, char* date)
{

}

// les resultat for denne avdelinga inn i terminlista
void DivAvd::lesResultat(std::ifstream& fil)
{
	// TODO: Sjekk at innlesinga er logisk gyldig
	char* dato;

	rIO.lesCharPointerFraFil(fil, dato);
	while (rIO.okDato(dato))
	{
		// finn lagindeksar
		char* hjemmeLag;
		char* borteLag;
		int hjemmeLagIndeks;
		int borteLagIndeks;
		rIO.lesCharPointerFraFil(fil, hjemmeLag);
		rIO.lesCharPointerFraFil(fil, borteLag);
		hjemmeLagIndeks = finnLagIndeks(hjemmeLag);
		borteLagIndeks = finnLagIndeks(borteLag);
		// DEBUG
		std::cout << hjemmeLag << " - " << borteLag << '\n';
		// les inn resultat for denne kampen
		resultat[hjemmeLagIndeks][borteLagIndeks]->lesFraFil(fil);

		delete[] dato;
		rIO.lesCharPointerFraFil(fil, dato);

		delete[] hjemmeLag;
		delete[] borteLag;
	}

	delete[] dato;
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
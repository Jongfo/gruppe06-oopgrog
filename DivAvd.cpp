#include "DivAvd.h"
#include <iomanip>
#include <iostream>

/*DivAvd::DivAvd(char* navn) : TextElement(navn)
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
}*/

DivAvd::DivAvd(std::ifstream& inn, char* navn) : TextElement(navn)
{
	inn >> antLag; inn.ignore();
	for (int i = 0; i < antLag; i++) 
	{
		lag[i] = new Lag(inn);
	}
	rIO.lesCharPointerFraFil(inn, terminlisteFil);
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

	// namn på terminlistefila
	if (terminlisteFil != nullptr)
	{
		ut << terminlisteFil << '\n';
	}
}

// legg til 0 eller fleire nye lag, og hvis det gjør legg til det laget
//TODO Vinne om lageet finnes fra før
void DivAvd::nyeLag() 
{
	int l = rIO.lesTall("Hvor mange lag oensker du aa legge til?", 0, MAXLAG - antLag);
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
void DivAvd::visTabell(char* tabell)
{
	int vunnet[MAXLAG]; int tapt[MAXLAG]; int uavgjort[MAXLAG];
	int lagPoeng[MAXLAG];
	rIO.setArrayTilNull(vunnet, MAXLAG); rIO.setArrayTilNull(tapt, MAXLAG);
	rIO.setArrayTilNull(uavgjort, MAXLAG); rIO.setArrayTilNull(lagPoeng, MAXLAG);
	//Setter poeng til de forskjellige lagene
	if (dataTilTabell(tabell, lagPoeng, vunnet, uavgjort, tapt)) {
		//Lager en sotert lag basert på poeng
		Lag* sotert[MAXLAG];
		//Setter den lik lag
		for (int i = 0; i < MAXLAG; i++) {
			sotert[i] = lag[i];
		}
		sorteringTilTabell(lagPoeng, vunnet, uavgjort, tapt, sotert);
		std::cout << "TABELL FOR: " << text << "\n\n";
		std::cout << "Lag Navn \t Vunnet \t Uavgjort \t Tapt \t\t Poeng \n\n";
		for (int i = antLag - 1; i >= 0; i--) {
			if (sotert[i] != nullptr) {
				std::cout << sotert[i]->getNavn() << "\t\t" << vunnet[i] << "\t\t" << uavgjort[i]
					<< "\t\t" << tapt[i] << "\t\t" << lagPoeng[i] << '\n';
			}
		}

	}
	else {
		std::cout << "\nFant ingen lag med resultater i " << text << "\n";
	}
}
void DivAvd::skrivTabellTilFil(std::ofstream &utfil, char* tabell) 
{
	
	int vunnet[MAXLAG]; int tapt[MAXLAG]; int uavgjort[MAXLAG];
	int lagPoeng[MAXLAG];
	rIO.setArrayTilNull(vunnet, MAXLAG); rIO.setArrayTilNull(tapt, MAXLAG);
	rIO.setArrayTilNull(uavgjort, MAXLAG); rIO.setArrayTilNull(lagPoeng, MAXLAG);
	//Setter poeng til de forskjellige lagene
	if (dataTilTabell(tabell, lagPoeng, vunnet, uavgjort, tapt)) {
		//Lager en sotert lag basert på poeng
		Lag* sotert[MAXLAG];
		//Setter den lik lag
		for (int i = 0; i < MAXLAG; i++) {
			sotert[i] = lag[i];
		}
		sorteringTilTabell(lagPoeng, vunnet, uavgjort, tapt, sotert);
		utfil << "Divisjon: " << TextElement::text 
              << "\nLag Navn \tVunnet \tUavgjort \tTapt \tPoeng \n\n";
		for (int i = antLag - 1; i >= 0; i--) {
			if (sotert[i] != nullptr) {
				utfil << sotert[i]->getNavn() << "\t\t" << vunnet[i] << "\t\t" << uavgjort[i]
					<< "\t\t\t" << tapt[i] << "\t\t" << lagPoeng[i] << '\n';
			}
		}
        utfil << '\n'; // ny linje før neste div.
		std::cout << "Velykket skrevet " << text << " tabell til fil\n\n";
	}
	else {
		std::cout << "\nFant ingen lag med resultater i " << text << "\n";
	}
}

// skriv terminlista til fil eller til skjerm
void DivAvd::skrivTerminliste()
{
	char filPlassering[MAXTEKST] = "gruppe06-ooprog/TerminListe/";

	if (terminlisteFil != nullptr)
	{
		for (int i = 0; i < strlen(terminlisteFil); i++)
		{
			filPlassering[strlen(filPlassering)] = terminlisteFil[i];
			filPlassering[strlen(filPlassering) + 1] = '\0';
		}
	}

	std::ostream stream(nullptr);
	std::ofstream fil;
	int kolonneStorrelse = 5;		// størrelsen på ei kolonne

	// sett kolonnestorleik til største lagnamn
	for (int i = 0; i < antLag; i++)
	{
		if (strlen(lag[i]->getNavn()) > kolonneStorrelse)
		{
			kolonneStorrelse = strlen(lag[i]->getNavn());
		}
	}

	char* filnavn;
	rIO.lesInnICharPointer("Filnavn:", filnavn);

	if (strlen(filnavn) == 0)
	{
		// filnamn tomt; skriv til cout
		stream.rdbuf(std::cout.rdbuf());
	}
	else
	{
		delete[] terminlisteFil;
		terminlisteFil = new char[strlen(filnavn) + 1];
		strcpy(terminlisteFil, filnavn);
		// skriv til fil

		// legg til brukarbestemt namn til filnamn
		for (int i = 0; i < strlen(terminlisteFil); i++)
		{
			filPlassering[strlen(filPlassering)] = terminlisteFil[i];
			filPlassering[strlen(filPlassering) + 1] = '\0';
		}
		fil = std::ofstream(filPlassering);
		stream.rdbuf(fil.rdbuf());
	}

	if (terminlisteFil != nullptr && strlen(filnavn) == 0)
	{
		std::ifstream innfil(filPlassering);
		char buffer[MAXTEKST];
		while (innfil.good())
		{
			innfil.getline(buffer, MAXTEKST);
			stream << buffer << '\n';
		}
	}
	else if (!(antLag > 1 && resultat[0][1] == nullptr))
	{
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
	}
	else
	{
		std::cout << "Kunne ikke skrive ut tabell.\n";
	}
	delete[] filnavn;
}


// K: Skriver denne divisjonens resultater til skjerm
bool DivAvd::resultaterTilSkjerm(char* date)
{
    bool found = false,
         first = true;
    for (int i = 0; i < MAXLAG; i++)
    {
        for (int j = 0; j < MAXLAG; j++)
        {
            if (resultat[i][j]) // sjekk om resultat eksisterer.
            {
                if (resultat[i][j]->sameDate(date))
                {
                    found = true;
                    if (first)
                    {
                        std::cout << "Divisjon/Avd: " << TextElement::text << '\n';
                        first = false;
                    }
                    std::cout << "H: " << lag[i]->getNavn() << " vs. B: " << lag[j]->getNavn() << '\n';
                    resultat[i][j]->skrivResultatTilSkjerm();
                    std::cout << std::endl;
                }
            }
        }
    }
    return found;
}

// K: fører denne divisjonens resultater til fil.
bool DivAvd::resultaterTilFil(std::ofstream &utfil, char* date)
{
    bool found = false, 
         first = true;
    

    for (int i = 0; i < MAXLAG; i++)
    {
        for (int j = 0; j < MAXLAG; j++)
        {
            if (resultat[i][j]) // sjekk om resultat eksisterer.
            {
                if (resultat[i][j]->sameDate(date))
                {
                    found = true;
                    if (first)
                    {
                        utfil << "Divisjon/Avd: " << TextElement::text << '\n';
                        first = false;
                    }
                    utfil << "H: " << lag[i]->getNavn() << " vs. B: " << lag[j]->getNavn() << '\n';
                    resultat[i][j]->skrivResultatTilFil(utfil);
                    utfil << '\n';
                }
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
char* DivAvd::lesResultat(std::ifstream& fil, bool& feil)
{
	char* dato;
	char* hjemmeLag;
	char* borteLag;

	int hjemmeLagIndeks;
	int borteLagIndeks;

	// dei to neste linjene etter innlesing av eit resultat
	char* l1;
	char* l2;

	// les dato og namna på laga
	rIO.lesCharPointerFraFil(fil, dato);
	rIO.lesCharPointerFraFil(fil, hjemmeLag);
	rIO.lesCharPointerFraFil(fil, borteLag);

	// finn indeksar
	hjemmeLagIndeks = finnLagIndeks(hjemmeLag);
	borteLagIndeks  = finnLagIndeks(borteLag);


	while (fil.good())
	{
		// Lag finst ikkje
		if (hjemmeLagIndeks == -1 || borteLagIndeks == -1)
		{
			if (hjemmeLagIndeks == -1)
			{
				std::cout << "Ugyldig lag '" << hjemmeLag << "'.\n";
			}

			if (borteLagIndeks == -1)
			{
				std::cout << "Ugyldig lag '" << borteLag << "'.\n";
			}

			delete[] hjemmeLag;
			delete[] borteLag;
			delete[] dato;

			feil = true;
			l2 = new char[1];
			l2[0] = '\0';
			return l2;
		}

		// allereie lese resultat for denne kampen
		if (resultat[hjemmeLagIndeks][borteLagIndeks] != nullptr)
		{
			std::cout << "Allerede lest resultat for "
				<< lag[hjemmeLagIndeks]->getNavn() << " - "
				<< lag[borteLagIndeks]->getNavn() << '\n';

			delete[] dato;
			feil = true;
			l2 = new char[1];
			l2[0] = '\0';
			return l2;
		}

		// laga har ikkje spelt mot kvarandre denne dagen
		if (!harSpilt(lag[hjemmeLagIndeks], lag[borteLagIndeks], dato))
		{
			std::cout << hjemmeLagIndeks << " - " << borteLagIndeks
					  << " har ikke spilt " << dato << '\n';
			delete[] hjemmeLag;
			delete[] borteLag;
			delete[] dato;
			feil = true;
			l2 = new char[1];
			l2[0] = '\0';
			return l2;
		}

		// les inn resultat for denne kampen
		resultat[hjemmeLagIndeks][borteLagIndeks] = new Resultat(fil, dato);

		// dei to neste linjene i fila
		rIO.lesCharPointerFraFil(fil, l1);
		rIO.lesCharPointerFraFil(fil, l2);

		// Dersom 1 er blank og 2 er blank, eller slutten av fila
		// ny idrett
		if ((strlen(l1) < 1 && strlen(l2) < 1) || !fil.good())
		{
			delete[] l1;
			return l2;
		}

		// Dersom 1 er blank og 1 ikkje er blank
		// ny divisjon
		else if (strlen(l1) < 1 && strlen(l2) > 0)
		{
			delete[] l1;
			return l2;
		}

		// Dersom 1 er dato og 2 er lag (2 må vere lag, ellers er fila feil),
		// er 2 lag1 og lag2 må lesast inn
		else if (rIO.okDato(l1) && strlen(l2) > 0)
		{
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
			hjemmeLagIndeks = finnLagIndeks(l1);
			borteLagIndeks = finnLagIndeks(l2);
		}

		delete[] l1;
		delete[] l2;
	}
}

// finn indeks til laget med gitt namn
int DivAvd::finnLagIndeks(char* navn)
{
	for (int i = 0; i < antLag; i++)
	{
		if (!strcmp(navn, lag[i]->getNavn()))
		{
			// fant laget med namn navn
			return i;
		}
	}

	// fant ingen lag med dette namnet !
	return -1;
}

// returnerer true dersom hjemmeLag har spilt mot borteLag
// (SOM henholdsvid heime- og bortelag) denne dagen
bool DivAvd::harSpilt(Lag* hjemmeLag, Lag* borteLag, char* dato)
{
	char filPlassering[MAXTEKST] = "gruppe06-ooprog/TerminListe/";
	char kortDato[6] = {
		dato[6], dato[7],
		'/',
		dato[4], dato[5],
		'\0'
	};


	// legg til brukarbestemt namn
	for (int i = 0; i < strlen(terminlisteFil); i++)
	{
		filPlassering[strlen(filPlassering)] = terminlisteFil[i];
		filPlassering[strlen(filPlassering) + 1] = '\0';
	}

	std::ifstream fil(filPlassering);
	char buffer[MAXTEKST];
	fil.getline(buffer, MAXTEKST);		// les gjennom lagnamna på toppen

	// les til heimelaget
	for (int i = 0; i < finnLagIndeks(hjemmeLag->getNavn()); i++)
	{
		fil.getline(buffer, MAXTEKST);
	}

	// les forbi namnet på heimelaget
	int it = 0;
	while (strcmp(buffer, hjemmeLag->getNavn()))
	{
		buffer[it++] = fil.get();
		buffer[it] = '\0';
	}

	// les til datoen
	for (int i = 0; i < finnLagIndeks(borteLag->getNavn()); i++)
	{
		fil >> buffer;
	}

	char faktiskDato[6];
	fil >> faktiskDato;

	if (!strcmp(kortDato, faktiskDato))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// fjernar alle resultat frå divisjonen/avdelinga
void DivAvd::fjernResultat()
{
	for (int i = 0; i < antLag; i++)
	{
		for (int j = 0; j < antLag; j++)
		{
			if (resultat[i][j] != nullptr)
			{
				delete resultat[i][j];
				resultat[i][j] = nullptr;
			}
		}
	}
}

bool DivAvd::dataTilTabell(char* tabell, int poeng[], int vunnet[], int uavgjort[], int tapt[]) {
	int poengForVinn, poengForTap, poengForUavgjot, poengForVinnUt, poengForTapUt;
	bool harUavgjort = true; bool lestData = false;
	//Finner Tabelltypen
	if (!strcmp(tabell, rIO.getTabelltype(1))) {
		poengForVinn = 2; poengForTap = 0; poengForUavgjot = 1;
		poengForTapUt = poengForTap; poengForVinnUt = poengForVinn;
	}
	else if (!strcmp(tabell, rIO.getTabelltype(2))) {
		poengForVinn = 3; poengForTap = 0; poengForUavgjot = 1;
		poengForTapUt = poengForTap; poengForVinnUt = poengForVinn;
	}
	else if (!strcmp(tabell, rIO.getTabelltype(3))) {
		poengForVinn = 3; poengForTap = 0;
		poengForTapUt = 1; poengForVinnUt = 2;
		harUavgjort = false;
	}
	for (int i = 0; i < antLag; i++) {
		for (int j = 0; j < antLag; j++) {
			if (i != j && resultat[i][j] != nullptr) {
				lestData = true;
				if (resultat[i][j]->getHjemmemaal() > resultat[i][j]->getBortemaal() && resultat[i][j]->getNormalTid()) {
					//Normaltid og hjemme laget vant
					vunnet[i]++; tapt[j]++;
					poeng[i] += poengForVinn;
					poeng[j] += poengForTap;
				}
				else if (resultat[i][j]->getHjemmemaal() > resultat[i][j]->getBortemaal()) {
					//Hvis ikke normal tid og hjemme laget vant
					vunnet[i]++; tapt[j]++;
					poeng[i] += poengForVinnUt; vunnet[i]++;
					poeng[j] += poengForTapUt;
				}
				else if (resultat[i][j]->getHjemmemaal() < resultat[i][j]->getBortemaal() && resultat[i][j]->getNormalTid()) {
					//Normaltid og borte laget vant
					vunnet[j]++; tapt[i]++;
					poeng[i] += poengForTap;
					poeng[j] += poengForVinn;
				}
				else if (resultat[i][j]->getHjemmemaal() < resultat[i][j]->getBortemaal()) {
					//Hvis ikke normal tid og borte laget vant
					vunnet[j]++; tapt[i]++;
					poeng[i] += poengForTapUt;
					poeng[j] += poengForVinnUt;
				}
				else if (harUavgjort) {
					//Uavgjort
					uavgjort[i]++; uavgjort[j]++;
					poeng[i] += poengForUavgjot;
					poeng[j] += poengForUavgjot;
				}
			}
		}
	}
	return lestData;
}
void DivAvd::sorteringTilTabell(int poeng[], int vunnet[], int uavgjort[], int tapt[], Lag* sorter[]) {
	int counter = 0;
	//Går å soterer listen
	do {
		for (int i = antLag - 1; i > 0; i--) {
			//Hvis den finner noe foran den som er høyere bytter de plass
			if (poeng[i - 1] > poeng[i]) {
				//Soterer poengene
				int temp = poeng[i - 1];
				poeng[i - 1] = poeng[i];
				poeng[i] = temp;
				//Sorterer Vunnet kamper
				int temp2 = vunnet[i - 1];
				vunnet[i - 1] = vunnet[i];
				vunnet[i] = temp2;
				//Sorterer Uavgjorte kamper
				int temp3 = uavgjort[i - 1];
				uavgjort[i - 1] = uavgjort[i];
				uavgjort[i] = temp3;
				//Sorterer tapte kamper
				int temp4 = tapt[i - 1];
				tapt[i - 1] = tapt[i];
				tapt[i] = temp4;
				//Soteret lagene
				Lag* tempLag = sorter[i - 1];
				sorter[i - 1] = sorter[i];
				sorter[i] = tempLag;
			}
		}
		counter++;
	} while (counter <= antLag);\
}
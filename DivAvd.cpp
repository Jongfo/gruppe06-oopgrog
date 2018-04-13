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

	// namn p� terminlistefila
	if (terminlisteFil != nullptr)
	{
		ut << terminlisteFil << '\n';
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
void DivAvd::visTabell(char* tabell)
{
	int vunnet[MAXLAG]; int tapt[MAXLAG]; int uavgjort[MAXLAG];
	int lagPoeng[MAXLAG];
	rIO.setArrayTilNull(vunnet, MAXLAG); rIO.setArrayTilNull(tapt, MAXLAG);
	rIO.setArrayTilNull(uavgjort, MAXLAG); rIO.setArrayTilNull(lagPoeng, MAXLAG);
	//Setter poeng til de forskjellige lagene
	if (dataTilTabell(tabell, lagPoeng, vunnet, uavgjort, tapt)) {
		//Lager en sotert lag basert p� poeng
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
void DivAvd::skrivTabellTilFil(char* navn, char* tabell) 
{
	char* filPlass = rIO.finnPlassOgLeggeFil(navn, text, "Tabell/");
	std::ofstream tabellFil(filPlass);
	int vunnet[MAXLAG]; int tapt[MAXLAG]; int uavgjort[MAXLAG];
	int lagPoeng[MAXLAG];
	rIO.setArrayTilNull(vunnet, MAXLAG); rIO.setArrayTilNull(tapt, MAXLAG);
	rIO.setArrayTilNull(uavgjort, MAXLAG); rIO.setArrayTilNull(lagPoeng, MAXLAG);
	//Setter poeng til de forskjellige lagene
	if (dataTilTabell(tabell, lagPoeng, vunnet, uavgjort, tapt)) {
		//Lager en sotert lag basert p� poeng
		Lag* sotert[MAXLAG];
		//Setter den lik lag
		for (int i = 0; i < MAXLAG; i++) {
			sotert[i] = lag[i];
		}
		sorteringTilTabell(lagPoeng, vunnet, uavgjort, tapt, sotert);
		tabellFil << "Lag Navn \t Vunnet \t Uavgjort \t Tapt \t\t Poeng \n\n";
		for (int i = antLag - 1; i >= 0; i--) {
			if (sotert[i] != nullptr) {
				tabellFil << sotert[i]->getNavn() << "\t\t" << vunnet[i] << "\t\t" << uavgjort[i]
					<< "\t\t" << tapt[i] << "\t\t" << lagPoeng[i] << '\n';
			}
		}

	}
	else {
		std::cout << "\nFant ingen lag med resultater i " << text << "\n";
	}
	//skrivTilFil(divAvdFil); //ONLY TEMP FOR TESTING
	std::cout << "FAKE WRITE OUT FOR " << text << "\n\n";
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
	int kolonneStorrelse = 5;		// st�rrelsen p� ei kolonne

	// sett kolonnestorleik til st�rste lagnamn
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
	else
	{
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

	// les dato og namna p� laga
	rIO.lesCharPointerFraFil(fil, dato);
	std::cout << dato << '\n';
	rIO.lesCharPointerFraFil(fil, hjemmeLag);
	rIO.lesCharPointerFraFil(fil, borteLag);

	// finn indeksar
	hjemmeLagIndeks = finnLagIndeks(hjemmeLag);
	borteLagIndeks  = finnLagIndeks(borteLag);


	while (fil.good())
	{
		// DEBUG
		std::cout << hjemmeLagIndeks << " - " << borteLagIndeks << '\n';

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

		// laga har ikkje spelt mor kvarandre denne dagen
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
			std::cout << "\n\'" << navn << "\' :: "
				<< i << '\n';
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
	std::cout << "\nharSpilt(" << hjemmeLag->getNavn() << ", "
		<< borteLag->getNavn() << ", " << dato << ")\n\n";
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
	fil.getline(buffer, MAXTEKST);		// les gjennom lagnamna p� toppen

	// les til heimelaget
	for (int i = 0; i < finnLagIndeks(hjemmeLag->getNavn()); i++)
	{
		fil.getline(buffer, MAXTEKST);
	}

	// les forbi namnet p� heimelaget
	int it = 0;
	while (strcmp(buffer, hjemmeLag->getNavn()))
	{
		buffer[it++] = fil.get();
		buffer[it] = '\0';
		std::cout << '\'' << buffer << "\' - '" << hjemmeLag->getNavn() << "\'\n";
	}

	// les til datoen
	for (int i = 0; i < finnLagIndeks(borteLag->getNavn()); i++)
	{
		fil >> buffer;
		std::cout << '\'' << buffer << "\'\n";
	}

	char faktiskDato[6];
	fil >> faktiskDato;

	std::cout << '\n' << kortDato << ' ' << faktiskDato << '\n';

	if (!strcmp(kortDato, faktiskDato))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// fjernar alle resultat fr� divisjonen/avdelinga
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
	//G�r � soterer listen
	do {
		for (int i = antLag - 1; i > 0; i--) {
			//Hvis den finner noe foran den som er h�yere bytter de plass
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
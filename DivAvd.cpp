#include "DivAvd.h"
#include <iomanip>
#include <iostream>

extern Spillere spillere;

DivAvd::DivAvd(std::ifstream& inn, char* navn, char* divFil) : TextElement(navn)
{
	divFilPos = divFil;
	inn >> antLag; inn.ignore();
	for (int i = 0; i < antLag; i++) 
	{
		lag[i] = new Lag(inn);
	}

	// les inn datoane for kampane
	for (int i = 0; i < antLag; i++)
	{
		for (int j = 0; j < antLag; j++)
		{
			if (i != j)
			{
				char dato[DATOLEN];
				inn >> dato;
				resultat[i][j] = new Resultat(dato);
			}
		}
	}

	inn.ignore();
}

// skriv data om divisjon/avdeling til fil
void DivAvd::skrivTilFil()
{
	std::ofstream ut(divFilPos);
	// skriv data
	ut << antLag << '\n';

	// skriv laga
	for (int i = 0; i < antLag; i++)
	{
		lag[i]->skrivTilFil(ut);
	}

	for (int i = 0; i < antLag; i++)
	{
		for (int j = 0; j < antLag; j++)
		{
			if (i != j)
			{
				ut << resultat[i][j]->langDato() << '\n';
			}
		}
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
		utfil << "Divisjon: " << TextElement::text << '\n'
              << std::setw(15) << std::left << "Lag Navn" 
              << std::setw(10) << "Vunnet" << std::setw(10) << "Uavgjort" 
              << std::setw(10) << "Tapt"   << std::setw(10) << "Poeng" << '\n';
		for (int i = antLag - 1; i >= 0; i--) {
			if (sotert[i] != nullptr) {
				utfil << std::setw(17) << std::left << sotert[i]->getNavn() 
                      << std::setw(10) << vunnet[i] 
                      << std::setw(10) << uavgjort[i] << std::setw(10) << tapt[i] 
                      << std::setw(10) << lagPoeng[i] << '\n';
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

	std::ostream stream(nullptr);
	//std::ofstream fil;
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
	rIO.lesInnICharPointer("Filnavn (Blank for skjerm):", filnavn);

	if (strlen(filnavn) == 0)
	{
		// filnamn tomt; skriv til cout
		stream.rdbuf(std::cout.rdbuf());
	}
	else
	{
		std::ofstream fil(filPlassering);
		stream.rdbuf(fil.rdbuf());
	}

	for (int i = 0; i <= kolonneStorrelse; i++)
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
				std::cout << "Ugyldig lag '"
						  << hjemmeLag << "'.\n";
			}

			if (borteLagIndeks == -1)
			{
				std::cout << "Ugyldig lag '"
						  << borteLag << "'.\n";
			}

			delete[] borteLag;
			delete[] hjemmeLag;
			delete[] dato;

			feil = true;
			l2 = new char[1];
			l2[0] = '\0';
			return l2;
		}

		// laga har ikkje spelt mot kvarandre denne dagen
		if (strcmp(dato, resultat[hjemmeLagIndeks][borteLagIndeks]->langDato()))
		{
			std::cout << hjemmeLag << " - "
					  << borteLag
					  << " har ikke spilt " << dato << '\n';

			delete[] borteLag;
			delete[] hjemmeLag;
			delete[] dato;
			feil = true;
			l2 = new char[1];
			l2[0] = '\0';
			return l2;
		}



		// allereie lese resultat for denne kampen
		if (resultat[hjemmeLagIndeks][borteLagIndeks]->getHjemmemaal() != -1)
		{
			std::cout << "Allerede lest resultat for "
				<< hjemmeLag << " - "
				<< borteLag << '\n';

			Resultat(fil, dato); // hopp til neste
		}
		else
		{
			// les inn resultat for denne kampen
			resultat[hjemmeLagIndeks][borteLagIndeks] = new Resultat(fil, dato);
		}

		// dei to neste linjene i fila
		rIO.lesCharPointerFraFil(fil, l1);
		rIO.lesCharPointerFraFil(fil, l2);

		// Dersom 1 er blank og 2 er blank, eller slutten av fila
		// ny idrett
		if ((strlen(l1) < 1 && strlen(l2) < 1) || !fil.good())
		{
			delete[] borteLag;
			delete[] hjemmeLag;
			delete[] dato;
			delete[] l1;
			return l2;
		}

		// Dersom 1 er blank og 1 ikkje er blank
		// ny divisjon
		else if (strlen(l1) < 1 && strlen(l2) > 0)
		{
			delete[] borteLag;
			delete[] hjemmeLag;
			delete[] dato;
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

			delete[] hjemmeLag;
			hjemmeLag = new char[strlen(l2) + 1];
			strcpy(hjemmeLag, l2);
			hjemmeLagIndeks = finnLagIndeks(hjemmeLag);

			delete[] borteLag;
			rIO.lesCharPointerFraFil(fil, borteLag);
			borteLagIndeks = finnLagIndeks(borteLag);
		}

		// dersom 1 ikkje er dato, og 2 ikkje er dato,
		// er 1 lag1 2 lag2
		else if (!rIO.okDato(l1) && !rIO.okDato(l2))
		{
			delete[] hjemmeLag;
			hjemmeLag = new char[strlen(l1) + 1];
			strcpy(hjemmeLag, l1);
			hjemmeLagIndeks = finnLagIndeks(hjemmeLag);

			delete[] borteLag;
			borteLag = new char[strlen(l2) + 1];
			strcpy(borteLag, l2);
			borteLagIndeks = finnLagIndeks(borteLag);
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

/*
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
*/

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
	//Finner Tabelltypen detter er hardkodet
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
	} while (counter <= antLag);
}
void DivAvd::finnTopScorer() {
	char* lagNavn; rIO.lesInnICharPointer("Navn paa laget (blank for alle)", lagNavn);
	int alleSpillere[MAXSPILLERE]; int spillerPos[MAXSPILLERE + 1];
	rIO.setArrayTilNull(alleSpillere, MAXSPILLERE);
	for (int i = 1; i <= MAXSPILLERE; i++) {
		spillerPos[i-1] = i; //Setter SpillerPos til å være ID'en til Spillerne
	}
	if (!strlen(lagNavn)) {
		char* filNavn; rIO.lesInnICharPointer("Skriv fil navn hvis onsket aa skrve til fil (blankt kun til skjerm)", filNavn);
		finnBesteSpillere(alleSpillere);
		sorteringTilScorer(alleSpillere, spillerPos);
		//Skriver topscorer til fil
		if (strlen(filNavn)) {
			char* filPlass = rIO.finnPlassOgLeggeFil(filNavn, "", "TopScorer_");
			std::ofstream topScorerFil(filPlass);
			// skriver idrett navn først i fila.
			topScorerFil << "Divisjon: " << text << '\n';
			skrivScorerTilFil(topScorerFil, alleSpillere, spillerPos);
			std::cout << "Filen " << filPlass << " har blitt laget\n";
			delete[] filPlass; 
		}
		//Skriver topscorer til skjerm
		else {
			std::cout << "Divisjon: " << text << '\n';
			skrivScorerTilSkjerm(alleSpillere, spillerPos);
		}
		delete[] filNavn;
	}
	else {
		bool fantLag = false; int indexLag;
		for (int i = 0; i < antLag; i++) {
			if (!strcmp(lagNavn, lag[i]->getNavn())) {
				fantLag = true; indexLag = i;
			}
			
		}
		if (fantLag) {
			char* filNavn; rIO.lesInnICharPointer("Skriv fil navn hvis onsket aa skrve til fil (blankt kun til skjerm)", filNavn);
			finnBesteSpillereiLag(alleSpillere, indexLag);
			sorteringTilScorer(alleSpillere, spillerPos);
			//Skriver spesefikk lag top scorer til skjerm eller fil
			if (strlen(filNavn)) { // Til fil
				char* filPlass = rIO.finnPlassOgLeggeFil(filNavn, "", "TopScorer_");
				std::ofstream topScorerFil(filPlass);
				// skriver idrett navn først i fila.
				topScorerFil << "Divisjon: " << text << '\n';
				skrivScorerTilFil(topScorerFil, alleSpillere, spillerPos);
				std::cout << "Filen " << filPlass << " har blitt laget\n";
				delete[] filPlass; 	delete[] filNavn;
			}
			else {//Til Skjerm
				std::cout << "Divisjon: " << text << '\n';
				skrivScorerTilSkjerm(alleSpillere, spillerPos);
			}
		}
		else {
			std::cout << "Fant ikke Laget\n\n";
		}
	}

	delete[] lagNavn;
}
void DivAvd::sorteringTilScorer(int s[], int pos[]) {
	int counter = 0;
	do {
		for (int i = MAXSPILLERE - 1; i > 0; i--) {
			//Hvis den finner noe før den som er høyere bytter de plass
			if (s[i - 1] < s[i]) {
				//Soterer spiller scorere
				int temp = s[i];
				s[i] = s[i - 1];
				s[i - 1] = temp;
				//Sorter positionen på spillerene til å være lik topscorer
				int temp2 = pos[i];
				pos[i] = pos[i - 1];
				pos[i - 1] = temp2;

			}
		}
		counter++;
	} while (counter <= MAXSPILLERE);
}
void DivAvd::skrivScorerTilFil(std::ofstream& tsf, int s[], int pos[]) {
	for (int i = 0; i < 10; i++) {
		if (spillere.finsSpiller(pos[i]) && s[i] > 0) {
			tsf << spillere.getSpillerNavn(pos[i]) << " - " << s[i] << " maal" << '\n';
		}
	}
}
void DivAvd::skrivScorerTilSkjerm(int s[], int pos[]) {
	for (int i = 0; i < 10; i++) {
		if (spillere.finsSpiller(pos[i]) && s[i] > 0) {
			std::cout << spillere.getSpillerNavn(pos[i]) << " - " << s[i] << " maal" << '\n';
		}
	}
}
void DivAvd::finnBesteSpillere(int s[]) {
	for (int i = 0; i <= antLag; i++) {
		for (int j = 0; j < antLag; j++) {
			if (i != j && resultat[i][j] != nullptr) {
				resultat[i][j]->besteSpillereHjemmeScor(s);
				resultat[i][j]->besteSpillereBorteScor(s);
				
			}
		}
	}
}
void DivAvd::finnBesteSpillereiLag(int s[], int lagNr) {
	for (int i = 0; i < antLag; i++) {
		if (lagNr != i) {
			resultat[lagNr][i]->besteSpillereHjemmeScor(s);//Alle hjemme kamper for lagNr
			resultat[i][lagNr]->besteSpillereBorteScor(s);//Alle borte kamoer for lagNr
		}
	}
}
char* DivAvd::getDivFilPos() {
	return divFilPos;
}
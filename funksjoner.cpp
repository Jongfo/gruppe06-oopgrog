#include "RobustIO.h"
#include "Spillere.h"
#include "Idrettene.h"
#include "funksjoner.h"

extern RobustIO rIO;
extern Spillere spillere;
extern Idrettene idrettene;

// legg til ny spelar, idrett, divisjon
void nySID()
{
	char k = rIO.lesInnTilStor();

	switch (k)
	{
	case 'S': spillere.nySpiller();   break;
	case 'I': idrettene.nyIdrett();	  break;
	case 'D': idrettene.nyDivisjon(); break;
	default:
		std::cout << "Ugyldig kommando";
		break;
	}
}

// fjern spelar, idrett eller div/avd
void fjernSID()
{
	char k = rIO.lesInnTilStor();

	switch (k)
	{
	case 'S': spillere.fjernSpiller(); break;
	case 'I': idrettene.fjernIdrett(); break;
	case 'D': // fjern divisjon/avdeling
	{
		Idrett* idrett = idrettene.getIdrett();
		if (idrett != nullptr)
		{
			idrett->fjernDivAvd();
		}
		break;
	}
	default:
		std::cout << "Ugyldig kommando";
		break;
	}
}

// Viser ein spelar eller alle spelarar
void visSpiller() //Kan flytte denne inn i spillere Egjøre som frode
{
	char temp[MAXTEKST];				//Lager midlertidig char-array
	std::cin.getline(temp, MAXTEKST);	//henter input fra bruker
	temp[0] = toupper(temp[0]);			//Første bokstav skal være stor uansett
	if (atoi(temp))
	{
		spillere.visSpiller(atoi(temp));
	}
	else if (strlen(temp) > 1)
	{
		spillere.visSpiller(temp);
	}
	else if (temp[0] == 'A') {
		spillere.visSpiller();
	}
	else
	{
		std::cout << "\n\nUgyldig kommando";
	}
}

// viser ein eller alle idrettar
void visIdrett()
{
	char temp[MAXTEKST];				//Lager midlertidig char-array
	std::cin.getline(temp, MAXTEKST);	//henter input fra bruker
	temp[0] = toupper(temp[0]);			//Første bokstav skal være stor uansett
	if (strlen(temp) > 1)
	{
		idrettene.visIdrett(temp);
	}
	else if (temp[0] == 'A') {
		idrettene.visIdrett();
	}
	else
	{
		std::cout << "\n\nUgyldig kommando";
	}
}

// les all data frEfil
void lesFraFil()
{
	spillere.lesSpillereFraFil();
	idrettene.lesInnIdrettFraFil();
}

// E: Endrer data om spillere paa et lag.
void redigerSpillere()
{
    char* idrettNavn, * divNavn, * lagNavn;
	char kommando;
	int spillerID;
	Idrett* idretten;
	DivAvd* avdelingen;
	Lag* laget;


    // finn idrett
    rIO.lesInnICharPointer("Skriv inn navn paa idrett:", idrettNavn);
	idretten = idrettene.getIdrett(idrettNavn);
	if (idretten)
	{
		// finn Divisjon
        do
        {
		    rIO.lesInnICharPointer("skriv inn navn paa divisjon/avdeling.", divNavn);
		    avdelingen = idretten->getDivAvd(divNavn);
            if (!avdelingen && toupper(*divNavn) != 'Q')
                std::cout << "Skriv \"Q\" om du onsker aa avslutte.\n";
        } while (!avdelingen && toupper(*divNavn) != 'Q');
		if (avdelingen)
		{
			// finn Lag
            do
            {
			    rIO.lesInnICharPointer("skriv inn navn paa lag.", lagNavn);
			    laget = avdelingen->getLag(lagNavn);
                if(!laget && toupper(*lagNavn) != 'Q')
                    std::cout << "Skriv \"Q\" om du onsker aa avslutte.\n";
            } while (!laget && toupper(*lagNavn) != 'Q');
			if (laget)
			{
				do
				{
					std::cout << "\n\tOnsker du aa [F]jerne, [L]egge til en spiller?";
					kommando = rIO.lesInnTilStor();
					switch (kommando)
					{
					case 'F':
						spillerID = rIO.lesTall("Oppgi ID nummer paa spiller som skal fjernes fra laget.", 1, spillere.getSisteNr()); //Spiller ID knyttet til MAXSPILLERE?
                        if (laget->spillerILag(spillerID))
                        {
							laget->fjernSpillerNr(spillerID);
                            std::cout << "\nSpiller er fjernet.";
                        }
						else
							std::cout << "\nFant ikke spiller ID";
						break;
					case 'L':
						spillerID = rIO.lesTall("Oppgi ID nummer paa spiller som skal legges til laget.", 1, spillere.getSisteNr());
						laget->leggTilSpiller(spillerID);
						break;
					case 'Q': break;	//gjør ingen ting om bruker vil avslutte.
					default:
						std::cout << "\n\n\tUkjent kommando.\n\tF: fjern spiller.\n\tL: Legg til spiller.\n\tQ: avslutt.";
						break;
					}
				} while (kommando != 'Q');
			}
		}
	}
    else
    {
        std::cout << "Fant ikke idrett. Gaar tilbake til hovedmeny.";
    }
}

// K: skriv resultat av kamper i gitt dato
void resultatAvKamper()
{
    char* idrettNavn, *filNavn, *divNavn;
    char dato[9];
    Idrett* idretten;
    DivAvd* divisjonen;

    rIO.lesInnICharPointer("Skriv navn paa idrett:", idrettNavn);
    idretten = idrettene.getIdrett(idrettNavn);
    if (idretten)
    {
        do
        {   // bruker må skrive inn en idrett eller ingen ting for å gå videre
            rIO.lesInnICharPointer("Skriv navn paa divisjon/avdeling, eller blank:", divNavn);
            divisjonen = idretten->getDivAvd(divNavn);

        } while (!divisjonen && strlen(divNavn) != 0);

        // ber bruker omm å skrive inn filnavn og dato.
        rIO.lesInnICharPointer("Skriv inn navn paa fil, eller blank:", filNavn);
        rIO.lesDato("Skriv inn en dato på kampene:", dato);
        
        if (strlen(filNavn) > 0)
        {
            char* filNavnKode = rIO.finnPlassOgLeggeFil(filNavn, "resultater", "");
            std::ofstream utfil(filNavnKode);

            bool found = idretten->resultatDatoTilFil(utfil, dato, divisjonen);


            if (!found)
            {
                std::cout << "\n\tFant ingen resultater.\n";
                if (std::remove(filNavnKode))
                {
                    std::cout << "\tOps! dummy fil ble laget!: " << filNavnKode << std::endl;
                }
            }
            else
            {
                std::cout << "\n\tFil lagret som \"" << filNavnKode << "\".\n";
            }
            delete[] filNavnKode;
        }
        else
        {
            bool found = idretten->resultatDatoTilSkjerm(dato, divisjonen); 
        }
    }
    else
    {
        std::cout << "Fant ikke idrett. Gaar tilbake til hovedmeny.";
    }
}

// viser menyen til brukaren
void skrivMeny()
{
	std::cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:";
	std::cout << "\n\tS A | nr | navn - (S)kriver (A)lle spillern eller alle med nr/navn";
	std::cout << "\n\tI A | navn - skr(I)ver (A)lle idrettene eller idretten med navn";
	std::cout << "\n\tN S | I | D - (N)y (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\n\tF S | I | D - (F)jern (S)piller,(I)drett eller (D)ivisjon/avdeling";
	std::cout << "\n\tL - Skriv termin(L)iste for en gitt divisjon/avdeling til skjerm eller fil";
	std::cout << "\n\tK - Skriv alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil";
	std::cout << "\n\tT - Skriv (T)abell for en hel idrett eller en divisjon/avdeling til skjerm eller fil";
	std::cout << "\n\tR - Lese (R)esultatliste inn fra fil";
	std::cout << "\n\tD - (D)ata om alle spillerne pEet lag";
	std::cout << "\n\tE - (E)ndre/redigere spillerne pEet lag";
	std::cout << "\n\tC - Skriv 10-pEtopp liste av topps(C)orerne for en gitt divisjon/avdeling eller et gitt lag til skjerm eller fil";
	std::cout << "\n\tQ = Quit/Avslutt";
}

// skriv data om alle spelarar pEeit lag
void skrivSpillerePaaLag()
{
	Idrett* idrett = idrettene.getIdrett();
	if (idrett != nullptr)
	{
		DivAvd* divisjon = idrett->getDivAvd();
		if (divisjon != nullptr)
		{
			Lag* lag = divisjon->getLag();
			if (lag != nullptr)
			{
				lag->displaySpillere();
			}
		}
	}
}

// skriv terminlista til ein divisjon/avdeling
void skrivTerminliste()
{
	Idrett* idrett = idrettene.getIdrett();
	if (idrett != nullptr)
	{
		DivAvd* divisjon = idrett->getDivAvd();
		if (divisjon != nullptr)
		{
			divisjon->skrivTerminliste();
		}
	}
}

// handterar kommando-input
void valgMeny()
{
	// Leser brukerens ›nske/valg.
	char kommando = rIO.lesInnTilStor("\n\nKommando: ");

	while (kommando != 'Q')
	{
		switch (kommando)
		{
		case 'S': visSpiller();				break;
		case 'I': visIdrett();				break;
		case 'N': nySID();					break;
		case 'F': fjernSID();				break;
		case 'L': skrivTerminliste();		break;
        case 'K': resultatAvKamper();       break;  // ikke fulført!
		case 'T': idrettene.skrivTabell();	break;
		case 'R': idrettene.lesResultat();	break;
		case 'D': skrivSpillerePaaLag();	break;
        case 'E': redigerSpillere();        break;
		case 'C': break;
		default: skrivMeny();				break; //Skriver meny
		}
		kommando = rIO.lesInnTilStor(); // Leser brukerens ønske/valg.
	};
}

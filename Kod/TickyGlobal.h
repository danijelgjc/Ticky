#ifndef _TickyGlobal_h_
#define _TickyGlobal_h_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct Admin {

	char accountName[30];
	char accountPass[30];
	int numberOfLogIns;
};

struct Info {

	int allowedNumber;
	int firstTime;
};

struct Client {

	char accName[30];
	char accPass[30];
	int numOfLogIns;
	char accState[30];		// Suspended | Activated
	char accCondition[30]; 	// Deleted | Active
};

struct User {

	char accName[30];
	char accPass[30];
	int numOfLogIns;
	char accState[30];
	char accCondition[30];
	double accBalance;
};

void createEnvironment();

int compareAccountName(char*);

struct Admin* getAdmins(int*);

struct Client* getClients(int*);

struct User* getUsers(int*);

// Funkcija koja preko pokazivaca
// daje informaciju o broju dozvoljenih
// prijava a vraca da li je prijava za
// admina izvrsena prvi put
struct Info readNumberOfLogIns();

// Funkcija sluzi da se provjeri
// da li je unijeti karakter jednak
// '1', ako nije vraca 0 u suprotnom
// vraca 1. Koristi se zbog preglednosti
// koda.
int checkFirstCharacter(char*);

// Genericko za ostale
int checkSecondCharacter(char*);

int checkThirdCharacter(char*);

int checkFourthCharacter(char*);

int checkFifthCharacter(char*);

// Isto kao i ostali samo provjera
// za izlazak iz petlje preko '0'
int checkExitCharacter(char*);

// Funkcija sluzi da se izbrise
// "newline" character u procitanom
// stringu, tako sto pomocu
// strcspn pronadje indeks na kojem
// je "\n" i zamjeni ga sa '\0'
void modifyCharacter(char*, int, FILE*);

// Funkcija prima string koji se
// provjerava da li je uneseno
// ime naloga zadovoljavajuce
// ono zadovoljava ako se sastoji
// od karaktera (slova i brojeva)
// i ima min. 5 karaktera a max 20
int checkAccountName(char*);		// TODO

int changeAccountPass(char*, int, FILE*);

int checkCredentials(char*);

#endif

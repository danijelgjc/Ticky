#ifndef _TickyGlobal_h_
#define _TickyGlobal_h_
#define _CRT_SECURE_NO_WARNINGS

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
	char accCondition[30]; 		// Deleted | Active
};

struct User {
	
	char realName[30];
	char realSurName[30];
	char accName[30];
	char accPass[30];
	int numOfLogIns;
	char accState[30];
	char accCondition[30];
	double accBalance;
};
struct Date
{
	int dd;
	int mm;
	int yy;
};
struct Event
{
	char eventCode[7];
	char eventName[30];
	char eventPlace[30];
	struct Date date;
};
struct Ticket
{
	char eventCode[7];
	double prise;

};
struct soldTickets
{
	struct Ticket ticket;
	int howMany;
	char accName[30];
};

int validationPass(char*);

// Funkcija koja stvara pocetne datoteke
// admin.txt i client.txt za sada
//
void createEnvironment();

// Funkcija koja provjerava da li
// unijeti string (ime naloga) postoji
// u ostalim nalozima. Sluzi kod stvaranja
// naloga da se pronadju podudarnosti
int compareAccountName(char*);

// Naredne tri funkcije sluze za
// dohvatanje admina, klijenata i
// korisnika pri cemu im se kao 
// parametar prosledjuje adresa
// preko koje se moze dobiti broj tih 
// naloga
struct Admin* getAdmins(int*);

struct Client* getClients(int*);
struct User* getUsers(int*);
struct Event* getEvents(int*);//DONE
struct Ticket* getTickets(int*);//TODO
void printEvents();
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
// provjerava da li je unesena
// akreditacija zadovoljavajuca
// ona zadovoljava ako se sastoji
// od karaktera (slova i brojeva)
// i ima min. 5 karaktera a max 20.
// Akreditacija moze biti sifra ili 
// ime naloga
int changeAccountCredentials(char*, int, FILE*);

// Provjerava akreditaciju, poziva
// je funkcija changeAccountCrede...
int checkCredentials(char*);

void printClients();

void printUsers();

void writeUsers(struct User*, int);

#endif

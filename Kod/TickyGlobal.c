#include "TickyGlobal.h"

void createEnvironment() {

	FILE* stream;

	if((stream = fopen("../Baza_podataka/admin.txt", "w")) != NULL) {

		fprintf(stream, "%d\n", 1);
		fprintf(stream, "%s %s %d\n", "admin", "admin", 0);
		
		fclose(stream);
	}

	if((stream = fopen("../Baza_podataka/client.txt", "w")) != NULL) {

		fprintf(stream, "%d\n", 0);
		fclose(stream);
	}

	if((stream = fopen("../Baza_podataka/user.txt", "w")) != NULL) {

		fprintf(stream, "%d\n", 0);
		fclose(stream);
	}
}

struct Admin* getAdmins(int* numberOfAdmins) {

	struct Admin* admins = NULL;
	FILE* stream;
	int numberOfAccounts;


	if((stream = fopen("../Baza_podataka/admin.txt", "r")) != NULL) {

		fscanf(stream, "%d\n", &numberOfAccounts);
		*numberOfAdmins = numberOfAccounts;

		admins = calloc(numberOfAccounts, sizeof(struct Admin));

		for(int i = 0; i < numberOfAccounts; i++)
			fscanf(stream, "%s %s %d\n", admins[i].accountName, admins[i].accountPass, &admins[i].numberOfLogIns);

		fclose(stream);
	}
	return admins;
}

int compareAccountName(char* string) {

	int numberOfAdmins = 0;
	struct Admin* admins = getAdmins(&numberOfAdmins);

	int numberOfClients = 0;
	struct Client* clients = getClients(&numberOfClients);

	int numberOfUsers = 0;
	struct User* users = getUsers(&numberOfUsers);

	for(int i = 0; i < numberOfAdmins; i++)
		if(strcmp(string, admins[i].accountName) == 0) {
			
			printf("Ime naloga vec postoji. ");
			free(admins);
			free(clients);
			free(users);
			return 0;
		}

	for(int i = 0; i < numberOfClients; i++)
		if(strcmp(string, clients[i].accName) == 0) {
			
			printf("Ime naloga vec postoji. ");
			free(admins);
			free(clients);
			free(users);
			return 0;
		}

	for(int i = 0; i < numberOfUsers; i++)
		if(strcmp(string, users[i].accName) == 0) { 
			
			printf("Ime naloga vec postoji. ");
			free(admins);
			free(clients);
			free(users);
			return 0;
		}

	free(admins);
	free(clients);
	free(users);
	
	return 1;
}

struct Client* getClients(int* numberOfClients) {

	struct Client* clients = NULL;
	FILE* stream;
	
	if((stream = fopen("../Baza_podataka/client.txt", "r")) != NULL) {

		fscanf(stream, "%d\n", numberOfClients);
		
		if(*numberOfClients == 0) {

			fclose(stream);
			return clients;
		}

		clients = calloc(*numberOfClients, sizeof(struct Client));

		for(int i = 0; i < *numberOfClients; i++)
			fscanf(stream, "%s %s %d %s %s\n", clients[i].accName, clients[i].accPass, &clients[i].numOfLogIns, clients[i].accState, clients[i].accCondition);
		
		fclose(stream);
	}
	return clients;
}

struct User* getUsers(int* numberOfUsers) {

	struct User* users = NULL;
	FILE* stream;

	if((stream = fopen("../Baza_podataka/user.txt", "r")) != NULL) {

		fscanf(stream, "%d\n", numberOfUsers);

		if(*numberOfUsers == 0) {

			fclose(stream);
			return users;
		}

		users = calloc(*numberOfUsers, sizeof(struct User));

		for(int i = 0; i < *numberOfUsers; i++)
			fscanf(stream, "%s %s %s %s %d %s %s %lf\n", users[i].realName, users[i].realSurName, users[i].accName, users[i].accPass, &users[i].numOfLogIns, users[i].accState, users[i].accCondition, &users[i].accBalance);

		fclose(stream);
	}
	return users;
}
/*struct Event* getEvents(int* numberOfEvents)
{
	struct Event* events = NULL;
	FILE* stream;
	if ((stream = fopen("../Baza_podataka/event.txt", "r")) != NULL) {
		fscanf(stream, "%d\n", numberOfEvents);
		if (*numberOfEvents == 0) {
			fclose(stream);
			return events;
		};
		struct Event* eventss = calloc(numberOfEvents, sizeof(struct Event));
		for (int i = 0; i < *numberOfEvents; i++)
			fscanf(stream, "%s %s %s %d %d %d\n", events[i].eventCode, events[i].eventName, events[i].eventPlace, events[i].date.dd, events[i].date.mm, events[i].date.yy);
		fclose(stream);
	}
	return events;
}
struct Ticket* getTickets(int* numberOfTickets)
{
	struct Ticket* tickets = NULL;
	FILE* stream;
	if ((stream = fopen("../Baza_podataka/ticket.txt", "r")) != NULL) {
		fscanf(stream, "%d\n", numberOfTickets);
		if (*numberOfTickets == 0) {
			fclose(stream);
			return tickets;
		};
		struct Event* eventss = calloc(numberOfTickets, sizeof(struct Event));
		for (int i = 0; i < *numberOfTickets; i++)
			fscanf(stream, "%s %lf\n", tickets[i].eventCode, tickets[i].prise);
		fclose(stream);
	}
	return tickets;
}
void printEvents()
{
	int numOfEvents = 0;
	struct Event* events = getEvents(&numOfEvents);
	for (int i = 0; i < numOfEvents; i++) {
		fprint("%s %s %s %d.%d.%d\n", events[i].eventCode, events[i].eventName, events[i].eventPlace, events[i].date.dd, events[i].date.mm, events[i].date.mm, events[i].date.yy);
	}
}*/

struct Info readNumberOfLogIns() {

	FILE* stream;
	struct Info info;
	if((stream = fopen("../Baza_podataka/info.txt", "r")) != NULL) {

		fscanf(stream, "%d\n", &info.allowedNumber);
		fscanf(stream, "%d\n", &info.firstTime);
		fclose(stream);
	}
	return info;
}

int checkFirstCharacter(char* string) {

	// Pise u dokumentaciji sta funkcija radi
	if(string[0] == '1' && string[1] == '\0') return 1;
	else return 0;
}

int checkSecondCharacter(char* string) {

	// Isto samo za '2'
	if(string[0] == '2' && string[1] == '\0') return 1;
	else return 0;
}

int checkThirdCharacter(char* string) {

	// Isto samo za '3'	
	if(string[0] == '3' && string[1] == '\0') return 1;
	else return 0;
}


int checkFourthCharacter(char* string) {

	// Isto samo za '4'	
	if(string[0] == '4' && string[1] == '\0') return 1;
	else return 0;
}


int checkFifthCharacter(char* string) {

	// Isto samo za '5'	
	if(string[0] == '5' && string[1] == '\0') return 1;
	else return 0;
}

int checkExitCharacter(char* string) {

	// Pise u dokumentaciji
	if(string[0] == '0' && string[1] == '\0') return 1;
	else return 0;
}

void modifyCharacter(char* string, int size, FILE* stream) {

	// Pise u dokumentaciji sta funkcija radi
	fgets(string, size, stream);
	string[strcspn(string, "\n")] = '\0';
}



int changeAccountCredentials(char* string, int size, FILE* stream) {

	printf("Potrebna promjena sifre! ");
	do {

		modifyCharacter(string, size, stream);
	}while(checkCredentials(string) == 0);

	return 1;
}

int checkCredentials(char* string) {

	if(strlen(string) > 20 || strlen(string) < 5) {

		printf("Akreditacija treba biti duzine [5-20] karaktera sa slovima ili brojevima: ");
		return 0;
	}
	for(int i = 0; i < strlen(string); i++)
		if(!isalpha(string[i]) && !isdigit(string[i])) {
	
			printf("Akreditacija treba biti duzine [5-20] karaktera sa slovima ili brojevima: ");
			return 0;
		}
	return 1;
}

void printClients() {

	int numberOfClients = 0;
	struct Client* clients = getClients(&numberOfClients);

	for(int i = 0; i < numberOfClients; i++)
		printf("%s\n", clients[i].accName);

	free(clients);
}

void printUsers() {

	int numberOfUsers = 0;
	struct User* users = getUsers(&numberOfUsers);

	for(int i = 0; i < numberOfUsers; i++)
		printf("%s\n", users[i].accName);

	free(users);
}

void writeUsers(struct User* users, int numberOfUsers) {

	FILE* stream;

	if((stream = fopen("../Baza_podataka/user.txt", "w")) != NULL) {

		fprintf(stream, "%d\n", numberOfUsers);
		for(int i = 0; i < numberOfUsers; i++)
			fprintf(stream, "%s %s %s %s %d %s %s %lf\n", users[i].realName, users[i].realSurName, users[i].accName, users[i].accPass, users[i].numOfLogIns, users[i].accState, users[i].accCondition, users[i].accBalance);

		fclose(stream);
	}
}

int validationPass(char* string) {

	if(strlen(string) > 30 || strlen(string) < 5) {

		printf("Ime nije zadovoljavajuce duzine: ");
		return 1;
	}
	for(int i = 0; i < strlen(string); i++)
		if(!isalpha(string[i])) {

			printf("Karakter %c nije dozvoljen. ", string[i]);
			return 1;
		}
	return 0;
}

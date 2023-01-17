#include "TickyClient.h"
#include "TickyGlobal.h"

void clientOption(struct Info* info, FILE* stream) {

	char loggedClient[30] = { '\0' };
	if (clientLogIn(info, stream, loggedClient)) {
		
		int checkShouldIRun = 1;
		do {
		
			printf("Obrada dogadjaja [1], Izvjestaji [2], Kraj [0]: ");

			char character[15] = { '\0' };
			modifyCharacter(character, 15, stream);
			if (checkFirstCharacter(character)) {
		
				int checkShouldIRun1 = 1;
				do {
				
					char character1[15] = { '\0' };
					printf("Kreiranje dogadjaja [1], Brisanje dogadjaja [2], Kraj [0]: ");
					modifyCharacter(character1, 15, stream);
				
					if(checkFirstCharacter(character1)) {
						
						createEvent(stream);
					}
					else if(checkSecondCharacter(character1)) {
						
						// deleteEvent(stream, loggedClient);
					}
					else if(checkExitCharacter(character1)) checkShouldIRun1 = 0;					
					else printf("Greska. Unesite ponovo!\n");

				} while(checkShouldIRun1);
			}
			else if(checkSecondCharacter(character)) {

				int checkShouldIRun1 = 1;
				do
				{
					char character1[15] = { '\0' };
					printf("Pregled prodanih ulaznica [1], Izvjestaj o prodaji[2], Kraj[0]: ");
					modifyCharacter(character1, 15, stream);
					
					if(checkFirstCharacter(character1)) {
						// checkSoldTickets(stream);
					}
					else if(checkSecondCharacter(character1)) {
						// checkSales(stream);
					}
					else if (checkExitCharacter(character1)) checkShouldIRun1 = 0;
					else printf("Greska. Unesite ponovo!\n");

				} while(checkShouldIRun1);
			}
			//else if (checkThirdCharacter())
			else if (checkExitCharacter(character)) checkShouldIRun = 0;
			else printf("Greska. Unesite ponovo!\n");
		} while (checkShouldIRun);
	}
}

int clientLogIn(struct Info* info, FILE* stream, char* string) {

	struct Client client;
	int shouldIRun = 1;

	do {

		printf("Unesite ime naloga: ");
		modifyCharacter(client.accName, 30, stream);

		printf("Unesite lozinku naloga: ");
		modifyCharacter(client.accPass, 30, stream);

		int clientNumber = 0;
		if (checkClientLogInInfo(client, &clientNumber)) {

			int numberOfClient = 0;
			struct Client* clients = getClients(&numberOfClient);
			if (++clients[clientNumber].numOfLogIns == info->allowedNumber) {

				char newClientPass[30] = { '\0' };
				changeAccountCredentials(newClientPass, 30, stream);

				strcpy(clients[clientNumber].accPass, newClientPass);
				clients[clientNumber].numOfLogIns = 0;
			}
			writeClients(clients, numberOfClient);
			shouldIRun = 0;
			free(clients);
		}

	} while(shouldIRun);

	strcpy(string, client.accName);

	return 1;
}

int checkClientLogInInfo(struct Client client, int* clientNumber) {

	int numberOfClients = 0;
	struct Client* clients = getClients(&numberOfClients);
	for(int i = 0; i < numberOfClients; i++) {

		if(strcmp(clients[i].accName, client.accName) == 0 && strcmp(clients[i].accPass, client.accPass) == 0) {

			*clientNumber = i;
			free(clients);
			return 1;
		}
	}
	free(clients);
	printf("Pogresno uneseni podaci!\n");
	return 0;
}	

void writeEvent(struct Event* events, int numberOfEvents) {

	FILE* stream;
	int j = numberOfEvents;

	if ((stream = fopen("../Baza_podataka/event.txt", "w")) != NULL) {
		
		fprintf(stream, "%d\n", j);
		for(int i = 0; i < j; i++) {
		
			fprintf(stream, "%d %s %s %s %d %s %s %lf\n", events[i].eventCode, events[i].accName, events[i].eventName, events[i].eventPlace, events[i].numTickets, events[i].date, events[i].time, events[i].ticketPrice);

			FILE* stream_1;

			char newFile[50] = { '\0' };
			strcat(newFile, "../Baza_podataka/");

			char dump[50] = { '\0' };
			sprintf(dump, "%d", events[i].eventCode);

			strcat(newFile, dump);
			strcat(newFile, ".txt");

			if((stream_1 = fopen(newFile, "w")) != NULL) {

				if(events[i].soldTickets != NULL) {
					for(int k = 0; k < events[i].numTickets; k++) {
						fprintf(stream, "%d\n", events[i].soldTickets[k]);
					}
				}
				fclose(stream_1);
			}
		}
		fclose(stream);
	}
}

int generateEventCode() {

	int newEventCode = 0;

	int numberOfEvents = 0;
	struct Event* events = getEvents(&numberOfEvents);

	int shouldIRun = 1;
	srand(time(NULL));

	do {
		shouldIRun = 0;
		int newID = 1000 + rand() % 9000;

		for(int i = 0; i < numberOfEvents; i++) 
			if(newID == events[i].eventCode)
				shouldIRun = 1;
		
		if(shouldIRun == 0)
			newEventCode = newID;

	} while(shouldIRun);

	free(events);

	return newEventCode;
}

void createEvent(FILE* stream) {

	int newEventCode = generateEventCode();

	char eventName[30] = { '\0' };
	printf("Unesite ime dogadjaja: ");
	modifyCharacter(eventName, 30, stream);

	printf("Unesite datum odrzavanja: ");
	printf("\nDan, mjesec i godina: ");
	char date[30] = { '\0' };
	modifyCharacter(date, 30, stream);

	printf("Unesite mjesto odrzavanja: ");
	char eventPlace[30] = { '\0' };
	modifyCharacter(eventPlace, 30, stream);

	printf("Unesite vrijeme odrzavanja: ");
	printf("\nSati i minute: ");
	char time[30] = { '\0' };
	modifyCharacter(time, 30, stream);

	printf("Unesite cijenu ulaznica: ");
	double price;
	char ticketPrice[30] = { '\0' };
	modifyCharacter(ticketPrice, 30, stream);
	price = atof(ticketPrice);

	int numberOfEvents = 0;
	struct Event* events = getEvents(&numberOfEvents);

	events = realloc(events, (numberOfEvents + 1) * sizeof(struct Event));

	int i = numberOfEvents;

	events[i].eventCode = newEventCode;

	strcpy(events[i].eventName, eventName);
	strcpy(events[i].eventPlace, eventPlace);

	events[i].numTickets = 0;
	events[i].ticketPrice = price;

	strcpy(events[i].date, date);
	strcpy(events[i].time, time);

	events[i].soldTickets = NULL;

	writeEvent(events, ++i);

	free(events);
}

/*
void freeEvent(struct Event* event)
{
	free(event->eventCode);
	free(event->eventName);
	free(event->eventPlace);
	free(event->date.dd);
	free(event->date.mm);
	free(event->date.yy);
}


void deleteEvent(FILE* stream, char* loggedClient) {

	int numberOfEvents = 0;
	int find = 0;
	struct Event* events = getEvents(&numberOfEvents);
	struct Event* nodeToDelete;
	int i=0;
	for (i = 0; i< numberOfEvents; i++)
	{
		if(find && (i!=(numberOfEvents-1)))
		{
			events[i] = events[i + 1];
		}

		else if (find && (i == (numberOfEvents - 1))) {

		}
		else if (!strcmp(eventCode, events[i].eventCode))
		{
			freeEvent(events+i);
			events[i] = events[i + 1];
			find=1;
		}
	}
	if (find) {
		freeEvent(events + i);
		printf("Cvor uspjesno obrisan!\n");
		writeEvent(events, numberOfEvents - 1);
	}
	else printf("Cvor nije pronadjen!\n");
}
*/

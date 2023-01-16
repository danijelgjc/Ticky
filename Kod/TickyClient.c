#include "TickyClient.h"
void clientOption(struct Info* info, FILE* stream)
{
	if (clientLogin(info, stream)) {
		int checkShouldIRun = 1;
		do
		{
			printf("Upravljanje dogadjajima [1], Izvjestaji i pregledi[2], Kraj [0]: ");
			// TODO: Opcija tri, ako postoji
			char character[15] = { '\0' };
			modifyCharacter(character, 15, stream);
			if (checkFirstCharacter(character)) {
				int checkShouldIRun = 1;
				do
				{
					char character1[15] = { '\0' };
					printf("Kreiranje dogadjaja [1], Brisanje dogadjaja [2], Kraj [0]: ");
					modifyCharacter(character1, 15, stream);
					if (checkFirstCharacter(character1))
					{
						createEvent(stream);
					}
					if (checkSecondCharacter(character1))
					{
						deleteEvent(stream);
					}
					else if (checkExitCharacter(character1)) checkShouldIRun = 0;
					else printf("Greska. Unesite ponovo!\n");
				} while (checkShouldIRun);
			}
			else if (checkSecondCharacter(character))
				do
				{
					int checkSouldIRun = 1;
					char character1[15] = { '\0' };
					printf("Pregled prodanih ulaznica [1], Izvjestaj o prodaji[2], Kraj[0]: ");
					modifyCharacter(character1, 15, stream);
					if (ckeckFirstCharacter(character1))
					{
						checkSoldTickets(stream);
					}
					else if (checksecondCharacter(character1))
					{
						checkSales(stream);
					}
					else if (checkExitCharacter(character1)) checkShouldIRun = 0;
					else printf("Greska. Unesite ponovo!\n");
				} while (checkShouldIRun);
					//else if (checkThirdCharacter())
			else if (checkExitCharacter(character)) checkShouldIRun = 0;
			else printf("Greska. Unesite ponovo!\n");
		} while (checkShouldIRun);
	}
}
int clientLogIn(struct Info* info, FILE* stream) {

	struct Client client;
	int shouldIRun = 1;

	do {

		/*if (info->firstTime == 0) {

			printf("Unesite ime naloga: ");
			modifyCharacter(client.accountName, 30, stream);
			if (strcmp("client", client.accountName) != 0) {

				printf("Pogresno ime: \n");
				continue;
			}

			printf("Unesite lozinku naloga: ");
			modifyCharacter(client.accountPass, 30, stream);
			if (strcmp("client", client.accountPass) != 0) {

				printf("Pogresna lozinka: \n");
				continue;
			}
			else {

				char newClientPass[30] = { '\0' };
				changeAccountCredentials(newClientPass, 30, stream);

				int numberOfClients = 0;
				struct Client* clients = getClients(&numberOfClients);

				strcpy(clients[0].accountPass, newClientPass);
				writeClients(clients, numberOfClientss);

				info->firstTime = 1;
				shouldIRun = 0;
				free(clients);
			}
		}*/
		//else {

			printf("Unesite ime naloga: ");
			modifyCharacter(client.accName, 30, stream);

			printf("Unesite lozinku naloga: ");
			modifyCharacter(client.accPass, 30, stream);

			int clientNumber = 0;
			if (checkClientLogInInfo(client, &clientNumber)) {

				int numberOfClient = 0;
				struct Client* clients = getClients(&numberOfClient);
				/*if (++clients[numberOfClient].numberOfLogIns == info->allowedNumber) {// Mozda nesto ne valja sa numberOfClients

					char newClientPass[30] = { '\0' };
					changeAccountCredentials(newClientPass, 30, stream);

					strcpy(clients[clientNumber].accountPass, newClientPass);
					clients[clientNumber].numberOfLogIns = 0;
				}*/
				writeClients(clients, numberOfClient);
				shouldIRun = 0;
				free(clients);
			}
		//}

	} while (shouldIRun);

	writeInfo(info);

	return 1;
}
void writeEvent(struct Event* events, int numberOfEvent) {

	FILE* stream;

	if ((stream = fopen("../Baza_podataka/event.txt", "w")) != NULL) {
		fprintf(stream, "%d\n", numberOfEvent);
		for(int i=0;i<numberOfEvent;i++)
		fprintf(stream, "%s %s %s %d %d %d\n",events[i].eventCode, events[i].eventName, events[i].eventPlace, events[i].date.dd,events[i].date.dd,events[i].date.mm,events[i].date.yy);
		fclose(stream);
	}
}

int checkClientLogInInfo(struct Client client, int* clientNumber) {

	int numberOfClients = 0;
	struct Client* clients = getClients(&numberOfClients);
	for (int i = 0; i < numberOfClients; i++)
	{
		if (strcmp(clients[i].accName, client.accName) == 0 &&
			strcmp(clients[i].accPass, client.accPass) == 0) {

			*clientNumber = i;
			free(clients);
			return 1;
		}
	}
	free(clients);
	printf("Pogresno uneseni podaci!\n");
	return 0;
}

void createEvent(stream)
{
	struct Event event;
	int numberOfEvents = 0;
	struct Event* events = getEvents(&numberOfEvents);
	//do {
		printf("Unesite ime dogadjaja: ");
		modifyCharacter(event.eventName, 30, stream);
		printf("Unesite mjesto dogadjaja: ");
		modifyCharacter(event.eventPlace, 30, stream);
		printf("Unesite sifru dogadjaja: ");
		modifyCharacter(event.eventCode, 7, stream);
		printf("Unesite datum (dd.mm.yyyy): ");
		scanf("%d.%d.%d", event.date.dd, event.date.mm, event.date.yy);
	//}while(1); Koji je uslov da se ovo odradi
	events = realloc(events, (numberOfEvents + 1) * sizeof(struct Client));
	strcpy(events[numberOfEvents].eventCode, event.eventCode);
	strcpy(events[numberOfEvents].eventName, event.eventName);
	strcpy(events[numberOfEvents].eventPlace, event.eventPlace);
	events[numberOfEvents].date.dd = event.date.dd;
	events[numberOfEvents].date.mm = event.date.mm;
	events[numberOfEvents].date.yy = event.date.yy;
	writeEvents(events, ++numberOfEvents);
	free(events);
}
void freeEvent(struct Event* event)
{
	free(event->eventCode);
	free(event->eventName);
	free(event->eventPlace);
	free(event->date.dd);
	free(event->date.mm);
	free(event->date.yy);
}
void deleteEvent(char** eventCode)
{
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
		writeEvents(events, numberOfEvents - 1);
	}
	else printf("Cvor nije pronadjen!\n");
}
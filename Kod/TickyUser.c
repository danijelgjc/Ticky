#include "TickyUser.h"

void userOption(struct Info info, FILE* stream) {

	char loggedUser[30] = { '\0' };
	if(userLogIn(info, stream, loggedUser)) {

		int checkShouldIRun = 1;

		do
		{
			printf("Pregled dogadjaja [1], Obrada ulaznica [2], Kraj [0]: ");
			char character[15] = { '\0' };
			modifyCharacter(character, 15, stream);

			if(checkFirstCharacter(character)) {

				int numOfEvents = 0;
				struct Event* events = getEvents(&numOfEvents);
				for(int i = 0; i < numOfEvents; i++)
					printf("%s %s %s %s %lf\n", events[i].eventName, events[i].eventPlace, events[i].date, events[i].time, events[i].ticketPrice);

			}
			else if(checkSecondCharacter(character)) {

				int checkShouldIRun1 = 1;
				do
				{
					printf("Kupovina ulaznica [1], Pregled kupljenih ulaznica [2], Ponistavanje kupljene ulaznice[3], Kraj[0]: ");

					char character1[15] = { '\0' };
					modifyCharacter(character1, 15, stream);

					if(checkFirstCharacter(character1)) {

						buyTicket(loggedUser, stream);
					}
					else if(checkSecondCharacter(character1)) {

						//printTickets(user.accName,stream);
					}
					/*else if (checkThirdCharacter(character1)) {

						char eventCode[7] = { '\0' };
						printf("Unesite sifru dogadjaja: ");
						modifyCharacter(eventCode, 7, stream);
						returnTicket(eventCode);
					}*/
					else if (checkExitCharacter(character1)) checkShouldIRun1 = 0;
					else printf("Greska. Unesite ponovo!\n");

				} while(checkShouldIRun1);
			}
			else if (checkThirdCharacter(character))
			{
				// checkCredit(stream);
			}
			else if (checkExitCharacter(character)) checkShouldIRun = 1;
			else printf("Greska. Unesite ponovo!\n");
		} while (checkShouldIRun);
	}
}

int userLogIn(struct Info info, FILE* stream, char* loggedUser) {

	struct User user;
	int shouldIRun = 1;

	do {

		printf("Unesite ime naloga: ");
		modifyCharacter(user.accName, 30, stream);

		printf("Unesite lozinku naloga: ");
		modifyCharacter(user.accPass, 30, stream);

		int userNumber = 0;
		if(checkUserLogInInfo(user, &userNumber)) {

			int numberOfUsers = 0;
			struct User* users = getUsers(&numberOfUsers);

			if(++users[userNumber].numOfLogIns == info.allowedNumber) {

				char newUserPass[30] = { '\0' };
				changeAccountCredentials(newUserPass, 30, stream);

				strcpy(users[userNumber].accPass, newUserPass);
				users[userNumber].numOfLogIns = 0;
			}

			writeUsers(users, numberOfUsers);
			shouldIRun = 0;
			free(users);
		}

	} while(shouldIRun);

	strcpy(loggedUser, user.accName);
	return 1;
}

int checkUserLogInInfo(struct User user, int* userNumber) {

	int numberOfUsers = 0;
	struct User* users = getUsers(&numberOfUsers);

	for(int i = 0; i < numberOfUsers; i++) {

		if(strcmp(users[i].accName, user.accName) == 0 && strcmp(users[i].accPass, user.accPass) == 0) {

			*userNumber = i;
			free(users);
			return 1;
		}
	}
	free(users);
	printf("Pogresni uneseni podaci!\n");
	return 0;
}

/*
   void createUser(FILE* stream)
   {

   struct User user;
   int numberOfUsers = 0;
   struct User* users = getUser(&numberOfUsers);

   do {

   printf("Unesite ime korisnickog naloga: "); 
   modifyCharacter(user.accName, 30, stream);

   printf("Unesite sifru klijent naloga: ");
   modifyCharacter(user.accPass, 30, stream);
   } while (checkCredentials(user.accPass) == 0 || checkCredentials(user.accName) == 0 || compareAccountName(user.accName) == 0);

   users = realloc(users, (numberOfUsers + 1) * sizeof(struct Client));
   user.numOfLogIns = 0;

   strcpy(users[numberOfUsers].accName, user.accName);
   strcpy(users[numberOfUsers].accPass, user.accPass);
   users[numberOfUsers].numOfLogIns = user.numOfLogIns;
   strcpy(users[numberOfUsers].accState, "Activated");
   strcpy(users[numberOfUsers].accCondition, "Active");
   users[numberOfUsers].accBalance = 50;

   writeUsers(users, ++numberOfUsers);
   free(users);
   }

   void printTickets(char* accName,FILE* stream)
   {
   int numOfSolfTickets = 0;
   struct soldTickets* sTickets = getBoughtTickets(accName,&numOfSolfTickets);
   for (int i = 0; i < numOfSolfTickets; i++)
   printf("%s	%d  %lf", sTickets[i].ticket.eventCode, sTickets[i].howMany, sTickets[i].ticket.prise);
   }
   void checkCredit(struct User* user)
   {
   printf("Iznos na vasem racunu je %lf.\n", user->accBalance);
   }
   */

void buyTicket(char* loggedUser, FILE* stream) {

	int numOfEvents = 0;
	struct Event* events = getEvents(&numOfEvents);
	if(numOfEvents != 0) {
		
		for(int i = 0; i < numOfEvents; i++) 
			printf("[%d] %s %s %s %s %lf\n", i + 1, events[i].eventName, events[i].eventPlace, events[i].date, events[i].time, events[i].ticketPrice);
		
		printf("Unesite redni broj dogadjaja: ");
		char character[15] = { '\0' };
		modifyCharacter(character, 15, stream);

		int index;
		sscanf(character, "%d", &index);
		index--;

		int numberOfUsers = 0;
		struct User* users = getUsers(&numberOfUsers);

		double tempBalance = 0;

		int userIndex = 0;

		for(int i = 0; i < numberOfUsers; i++)
			if(strcmp(loggedUser, users[i].accName) == 0) {

				userIndex = i;
				tempBalance = users[i].accBalance;
			}

		if(events[index].ticketPrice > tempBalance)
			printf("Nedovoljno kredita na racunu. ");
		else {

			users[userIndex].accBalance -= events[index].ticketPrice;
			int ticketCode = generateTicketCode();

			writeUsers(users, numberOfUsers);
			free(users);

			events[index].soldTickets = realloc(events[index].soldTickets, (events[index].numTickets + 1) * sizeof(int));

			events[index].soldTickets[events[index].eventCode] = ticketCode;
			events[index].numTickets++;
			writeEvent(events, numOfEvents);

			char newFile[50] = { '\0' };
			strcat(newFile, "../Baza_podataka/");
			strcat(newFile, loggedUser);
			strcat(newFile, ".txt");

			FILE* stream;
			
			if((stream = fopen(newFile, "w")) != NULL) {

				for(int i = 0; i < events[index].numTickets; i++)
					fprintf(stream, "%d\n", events[index].soldTickets[i]);
				fclose(stream);
			}

			free(events);

		}
	}
}

int generateTicketCode() {

	int newTicketCode = 0;
	
	int numberOfEvents = 0;
	struct Event* events = getEvents(&numberOfEvents);

	int shouldIRun = 1;
	srand(time(NULL));

	do {

		shouldIRun = 0;
		int newID = 1000 + rand() % 9000;

		for(int i = 0; i < numberOfEvents; i++) {
		
			for(int j = 0; j < events[i].numTickets; j++) {

				if(newID == events[i].soldTickets[j]) {
					
					shouldIRun = 1;
					break;
				}
			}
		}
		
		if(shouldIRun == 0) newTicketCode = newID;

	} while(shouldIRun);

	free(events);

	return newTicketCode;
}

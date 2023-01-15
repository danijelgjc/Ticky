#include "TickyUser.h"

void userOption(struct Info info, FILE* stream)
{
	if (userLogin(info, stream)) {
		int checkShouldIRun = 1;
		do
		{
			printf("Dogadjaji [1], Ulaznice [2], Credit [3], Kraj [0]: ");
			char character[15] = { '\0' };
			modifyCharacter(character, 15, stream);
			if (checkFirstCharacter(character))
				printEvents();
			
			else if (checkSecondCharacter(character))
				do
				{
					int checkSouldIRun = 1;
					printf("Kupovina ulaznica [1], Pregled kupljenih ulaznica [2], Ponistavanje kupljene ulaznice[3] Kraj[0]: ");
					char character1[15] = { '\0' };
					modifyCharacter(character1, 15, stream);
					if (ckeckFirstCharacter(character1))
					{
						buyTicket(user, stream);
					}
					else if (checkSecondCharacter(character1))
					{
						printTickets(user, stream);
					}
					else if (checkThirdCharacter(character1))
					{
						char[7] eventCode = { '\0' };
						printf("Unesite sifru dogadjaja: ");
						modifyCharacter(eventCode, 7, stream);
						returnTicket(user, eventCode);
					}
					else if (checkExitCharacter(character1)) checkShouldIRun = 0;
					else printf("Greska. Unesite ponovo!\n");
				} while (checkShouldIRun)
			else if (checkThirdCharacter(character))
			{
				checkCredit(user);
			}
			else if (checkExitcharacter) checkShouldIRun = 1;
			else printf("Greska. Unesite ponovo!\n");
		}while(checkShouldIRun)
	}
}
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

void printTickets(struct User user)
{
	int numOfBoughtTickets = 0;
	struct boughtTickets* bTickets = getBoughtTickets(user.name,&numOfBoughtTickets);
	for (int i = 0; i < numOfBoughtTickets; i++)
		printf("%s	%d  %lf", bTickets[i]->ticket.eventCode, bTickets[i].howMany, bTickets[i]->ticket.prise);
}
double checkCredit(struct User user)
{
	return user.accBalance;
}
void buyTicket(user, stream)
{
	char[7] eventCode = { '\0' };
	int howMany = 0;
	int numOfEvents = 0;
	int find = 0;
	printf("Unesite sifru dogadjaja: ");
	modifyCharacter(eventCode, 7, stream);
	struct Ticket* ticket = getTickets(&numOfEvents);
	for (int i = 0; i < numOfEvents; i++) {
		if (!strcmp(ticket[i]->eventCode, eventCode))
			find = 1;
	}
	if (find) {
		printf("Unesite kolicinu karata koju kupujete: ");
		scanf("%d", &howMany);
		if (checkCredit(user) >= howMany * ticket->eventCode)
		{
			//DODAJ NOVU INFO O KUPLJENIM KARTAMA U BAZU boughtTickets
		}
		else
			printf("Nemate dovoljno credita na racunu!");
	}
	else
		printf("Sifra dogadjaja nije ispravna!");
}
int userLogIn(struct Info* info, FILE* stream) {

	struct User user;
	int shouldIRun = 1;

	do {

		printf("Unesite ime naloga: ");
		modifyCharacter(user.accName, 30, stream);

		printf("Unesite lozinku naloga: ");
		modifyCharacter(user.accPass, 30, stream);

		int userNumber = 0;
		if (checkClientLogInInfo(user, &userNumber)) {

			int numberOfUser = 0;
			struct Client* user = getUsers(&numberOfUser);
			if (++info[userNumber].numberOfLogIns == info->allowedNumber) {

				char newUserPass[30] = { '\0' };
				changeAccountCredentials(newUserPass, 30, stream);

				strcpy(user[userNumber].accountPass, newUserPass);
				user[userNumber].numberOfLogIns = 0;
			}
			writeUsers(users, numberOfusers);
			shouldIRun = 0;
			free(user);
		}

	} while (shouldIRun);
}

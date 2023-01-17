/*#include "TickyUser.h"

void userOption(struct Info info, FILE* stream)
{
	struct User user;
	if (userLogin(stream, &user)) {
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
					printf("Kupovina ulaznica [1], Pregled kupljenih ulaznica [2], Ponistavanje kupljene ulaznice[3], Kraj[0]: ");
					char character1[15] = { '\0' };
					modifyCharacter(character1, 15, stream);
					if (ckeckFirstCharacter(character1))
					{
						buyTicket(&user, stream);
					}
					else if (checkSecondCharacter(character1))
					{
						printTickets(user.accName,stream);
					}
					else if (checkThirdCharacter(character1))
					{
						char eventCode[7] = { '\0' };
						printf("Unesite sifru dogadjaja: ");
						modifyCharacter(eventCode, 7, stream);
						returnTicket(eventCode);
					}
					else if (checkExitCharacter(character1)) checkShouldIRun = 0;
					else printf("Greska. Unesite ponovo!\n");
				} while (checkShouldIRun);
			else if (checkThirdCharacter(character))
			{
				checkCredit(stream);
			}
			else if (checkExitcharacter()) checkShouldIRun = 1;
			else printf("Greska. Unesite ponovo!\n");
		} while (checkShouldIRun);
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
void buyTicket(struct User* user, FILE* stream)
{
	char eventCode[7] = { '\0' };
	int howMany = 0;
	int numOfEvents = 0;
	int find = 0;
	double prise = 0;
	printf("Unesite sifru dogadjaja: ");
	modifyCharacter(eventCode, 7, stream);
	struct Ticket* tickets = getTickets(&numOfEvents);
	for (int i = 0; i < numOfEvents; i++) {
		if (!strcmp(tickets[i].eventCode, eventCode)) {
			find = 1;
			prise = tickets[i].prise;
		}
	}
	if (find) {
		printf("Unesite kolicinu karata koju kupujete: ");
		scanf("%d", &howMany);
		if (user->accBalance >= howMany * prise)
		{
			//DODAJ NOVU INFO O KUPLJENIM KARTAMA U BAZU boughtTickets
		}
		else
			printf("Nemate dovoljno credita na racunu!");
	}
	else
		printf("Sifra dogadjaja nije ispravna!");

}
*/

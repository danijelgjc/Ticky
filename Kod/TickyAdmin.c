#include "TickyAdmin.h"
#include "TickyGlobal.h"


void adminOption(struct Info* info, FILE* stream) {

	if(adminLogIn(info, stream)) {

		int checkShouldIRun = 1;
		do {

			printf("Kreiranje naloga [1], Obrada naloga [2], Blokiranje dogadjaja [3], Kraj [0]: ");
			char character[15] = { '\0' };
			modifyCharacter(character, 15, stream);

			if(checkFirstCharacter(character)) {

				int checkShouldIRun1 = 1;

				do {

					char character1[15] = { '\0' };
					printf("Kreiranje admin naloga [1], Kreiranje klijent naloga [2], Kraj [0]: ");
					modifyCharacter(character1, 15, stream);

					if(checkFirstCharacter(character1)) {

						createAdmin(stream);	
					}
					else if(checkSecondCharacter(character1)) {

						createClient(stream);
					}
					else if(checkExitCharacter(character1)) checkShouldIRun1 = 0;
					else printf("Greska. Unesite ponovo!\n");

				} while(checkShouldIRun1);
			}
			else if(checkSecondCharacter(character)) {

				int checkShouldIRun1 = 1;

				do {

					char character1[15] = { '\0' };
					printf("Aktivacija [1], Suspendovanje [2], Brisanje [3], Ponistavanje sifre [4], Kraj [0]: ");
					modifyCharacter(character1, 15, stream);

					if(checkFirstCharacter(character1)) {

						activateAccount(stream);
					}
					else if(checkSecondCharacter(character1)) {

						suspendAccount(stream);
					}
					else if(checkThirdCharacter(character1)) {

						deleteAccount(stream);
					}
					else if(checkFourthCharacter(character1)) {

						cancelPass(stream);
					}
					else if(checkExitCharacter(character1)) checkShouldIRun1 = 0;
					else printf("Greska. Unesite ponovo!\n");
				
				} while(checkShouldIRun1);
			}
			else if(checkThirdCharacter(character)) {

				// TODO: Blokiranje dogadjaja
			}
			else if(checkExitCharacter(character)) checkShouldIRun = 0;
			else printf("Greska. Unesite ponovo!\n");
		} while(checkShouldIRun);
	}
}

int adminLogIn(struct Info* info, FILE* stream) {

	struct Admin admin;
	int shouldIRun = 1;

	do {

		if(info->firstTime == 0) {

			printf("Unesite ime naloga: ");
			modifyCharacter(admin.accountName, 30, stream);
			if(strcmp("admin", admin.accountName) != 0) {

				printf("Pogresno ime: \n");
				continue;
			}

			printf("Unesite lozinku naloga: ");
			modifyCharacter(admin.accountPass, 30, stream);
			if(strcmp("admin", admin.accountPass) != 0) {

				printf("Pogresna lozinka: \n");
				continue;
			}
			else {

				char newAdminPass[30] = { '\0' };
				changeAccountCredentials(newAdminPass, 30, stream);

				int numberOfAdmins = 0;
				struct Admin* admins = getAdmins(&numberOfAdmins);

				strcpy(admins[0].accountPass, newAdminPass);
				writeAdmins(admins, numberOfAdmins);

				info->firstTime = 1;
				shouldIRun = 0;
				free(admins);
			}
		}
		else {

			printf("Unesite ime naloga: ");
			modifyCharacter(admin.accountName, 30, stream);

			printf("Unesite lozinku naloga: ");
			modifyCharacter(admin.accountPass, 30, stream);

			int adminNumber = 0;
			if(checkAdminLogInInfo(admin, &adminNumber)) {

				int numberOfAdmins = 0;
				struct Admin* admins = getAdmins(&numberOfAdmins);
				if(++admins[adminNumber].numberOfLogIns == info->allowedNumber) {

					char newAdminPass[30] = { '\0' };
					changeAccountCredentials(newAdminPass, 30, stream);

					strcpy(admins[adminNumber].accountPass, newAdminPass);
					admins[adminNumber].numberOfLogIns = 0;
				}
				writeAdmins(admins, numberOfAdmins);
				shouldIRun = 0;
				free(admins);
			}
		}

	}while(shouldIRun);

	writeInfo(info);

	return 1;
}

void writeInfo(struct Info* info) {

	FILE* stream;

	if((stream = fopen("../Baza_podataka/info.txt", "w")) != NULL) {

		fprintf(stream, "%d\n", info->allowedNumber);
		fprintf(stream, "%d\n", info->firstTime);
		fclose(stream);
	}
}

int checkAdminLogInInfo(struct Admin admin, int* adminNumber) {

	int numberOfAdmins = 0;
	struct Admin* admins = getAdmins(&numberOfAdmins);
	for(int i = 0; i < numberOfAdmins; i++)
	{
		if(strcmp(admins[i].accountName, admin.accountName) == 0 &&
				strcmp(admins[i].accountPass, admin.accountPass) == 0) {

			*adminNumber = i;
			free(admins);
			return 1;
		}
	}
	free(admins);
	printf("Pogresno uneseni podaci!\n");
	return 0;
}

void writeAdmins(struct Admin* admins, int numberOfAdmins) {

	FILE* stream;

	if((stream = fopen("../Baza_podataka/admin.txt", "w")) != NULL) {

		fprintf(stream, "%d\n", numberOfAdmins);
		for(int i = 0; i < numberOfAdmins; i++)
			fprintf(stream, "%s %s %d\n", admins[i].accountName, admins[i].accountPass, admins[i].numberOfLogIns);

		fclose(stream);
	}
}

void writeClients(struct Client* clients, int numberOfClients) {

	FILE* stream;

	if((stream = fopen("../Baza_podataka/client.txt", "w")) != NULL) {

		fprintf(stream, "%d\n", numberOfClients);
		for(int i = 0; i < numberOfClients; i++)
			fprintf(stream, "%s %s %d %s %s", clients[i].accName, clients[i].accPass, clients[i].numOfLogIns, clients[i].accState, clients[i].accCondition);

		fclose(stream);
	}
}

void createAdmin(FILE* stream) {

	struct Admin admin;
	int numberOfAdmins = 0;
	struct Admin* admins = getAdmins(&numberOfAdmins);

	do {

		printf("Unesite ime admin naloga: ");
		modifyCharacter(admin.accountName, 30, stream);

		printf("Unesite sifru admin naloga: ");
		modifyCharacter(admin.accountPass, 30, stream);
	} while(checkCredentials(admin.accountName) == 0 || checkCredentials(admin.accountPass) == 0 || compareAccountName(admin.accountName) == 0);

	admins = realloc(admins, (numberOfAdmins + 1) * sizeof(struct Admin));
	admin.numberOfLogIns = 0;

	strcpy(admins[numberOfAdmins].accountName, admin.accountName);
	strcpy(admins[numberOfAdmins].accountPass, admin.accountPass);
	admins[numberOfAdmins].numberOfLogIns = admin.numberOfLogIns;

	writeAdmins(admins, ++numberOfAdmins);
	free(admins);
}

void createClient(FILE* stream) {

	struct Client client;
	int numberOfClients = 0;
	struct Client* clients = getClients(&numberOfClients);

	do {

		printf("Unesite ime klijent naloga: ");
		modifyCharacter(client.accName, 30, stream);

		printf("Unesite sifru klijent naloga: ");
		modifyCharacter(client.accPass, 30, stream);
	} while(checkCredentials(client.accPass) == 0 || checkCredentials(client.accName) == 0 || compareAccountName(client.accName) == 0);

	clients = realloc(clients, (numberOfClients + 1) * sizeof(struct Client));
	client.numOfLogIns = 0;

	strcpy(clients[numberOfClients].accName, client.accName);
	strcpy(clients[numberOfClients].accPass, client.accPass);
	clients[numberOfClients].numOfLogIns = client.numOfLogIns;
	strcpy(clients[numberOfClients].accState, "Activated");
	strcpy(clients[numberOfClients].accCondition, "Active");

	writeClients(clients, ++numberOfClients);
	free(clients);
}

void activateAccount(FILE* stream) {

	int checkShouldIRun = 1;

	do {

		char character[15] = { '\0' };
		printf("Aktiviranje klijent naloga [1], Aktiviranje korisnik naloga [2], Kraj [0]: ");

		modifyCharacter(character, 15, stream);

		if(checkFirstCharacter(character)) {

			int numberOfClients = 0;
			struct Client* clients = getClients(&numberOfClients);

			if(numberOfClients != 0) {

				printClients();
				char accountName[30] = { '\0' };
				printf("Unesite ime naloga: ");
				modifyCharacter(accountName, 30, stream);

				for(int i = 0; i < numberOfClients; i++)

					if(strcmp(clients[i].accName, accountName) == 0) {

						if(strcmp(clients[i].accState, "Activated") == 0) {

							printf("Nalog je vec bio aktivan. \n");
						}
						else {

							printf("Nalog je aktiviran. \n");
							strcpy(clients[i].accState, "Activated");
							writeClients(clients, numberOfClients);
							// TODO: Kako sa dogadjajima
							// da li im se gleda neki vremenski raspon
						}
					}
			}
			else printf("Nema klijent naloga. \n");
			
			free(clients);
		}
		else if(checkSecondCharacter(character)) {

			int numberOfUsers = 0;
			struct User* users = getUsers(&numberOfUsers);

			if(numberOfUsers != 0) {

				printUsers();
				char accountName[30] = { '\0' };
				printf("Unesite ime naloga: ");
				modifyCharacter(accountName, 30, stream);

				for(int i = 0; i < numberOfUsers; i++)

					if(strcmp(users[i].accName, accountName) == 0) {

						if(strcmp(users[i].accState, "Acivated") == 0) {

							printf("Nalog je vec bio aktivan. \n");
						}
						else {

							printf("Nalog je aktiviran. \n");
							strcpy(users[i].accState, "Activated");
							writeUsers(users, numberOfUsers);
							// TODO: Provjeri sa ulaznicama
						}
					}
			}
			else printf("Nema korisnik naloga. \n");

			free(users);
		}
		else if(checkExitCharacter(character)) checkShouldIRun = 0;
		else printf("Greska. Unesite ponovo!\n"); 

	} while(checkShouldIRun);
}

void suspendAccount(FILE* stream) {

	int checkShouldIRun = 1; 

	do {

		char character[15] = { '\0' };
		printf("Suspendovanje klijent naloga [1], Suspendovanje korisnik naloga [2], Kraj [0]: ");

		modifyCharacter(character, 15, stream);

		if(checkFirstCharacter(character)) {

			int numberOfClients = 0;
			struct Client* clients = getClients(&numberOfClients);

			if(numberOfClients != 0) {

				printClients();
				char accountName[30] = { '\0' };
				printf("Unesite ime naloga: ");
				modifyCharacter(accountName, 30, stream);

				for(int i = 0; i < numberOfClients; i++)

					if(strcmp(clients[i].accName, accountName) == 0) {

						if(strcmp(clients[i].accState, "Suspended") == 0) {

							printf("Nalog je vec bio suspendovan. \n");
						}
						else {
							printf("Nalog je suspendovan. \n");
							strcpy(clients[i].accState, "Suspended");
							writeClients(clients, numberOfClients);
							// TODO: Pogledati sta se desava sa
							// dogadjajima
						}
					}
			}
			else printf("Nema klijent naloga. \n");

			free(clients);
		}
		else if(checkSecondCharacter(character)) {

			int numberOfUsers = 0;
			struct User* users = getUsers(&numberOfUsers);

			if(numberOfUsers != 0) {

				printUsers();
				char accountName[30] = { '\0' };
				printf("Unesite ime naloga: ");
				modifyCharacter(accountName, 30, stream);

				for(int i = 0; i < numberOfUsers; i++)

					if(strcmp(users[i].accName, accountName) == 0) {

						if(strcmp(users[i].accState, "Suspended") == 0) {

							printf("Nalog je vec bio suspendovan. \n");
						}
						else {

							printf("Nalog je suspendovan. \n");
							strcpy(users[i].accState, "Suspended");
							writeUsers(users, numberOfUsers);
							// TODO: Sta se desava sa kupljenim
							// ulaznicam
						}
					}
			}
			else printf("Nema korisnik naloga. \n");

			free(users);
		}
		else if(checkExitCharacter(character)) checkShouldIRun = 0;
		else printf("Greska. Unesite ponovo!\n"); 
	
	} while(checkShouldIRun);
}

void deleteAccount(FILE* stream) {

	int checkShouldIRun = 1;

	do {

		char character[15] = { '\0' };
		printf("Brisanje klijent naloga [1], Brisanje korisnik naloga [2], Kraj [0]: ");

		modifyCharacter(character, 15, stream);

		if(checkFirstCharacter(character)) {

			int numberOfClients = 0;
			struct Client* clients = getClients(&numberOfClients);
			
			if(numberOfClients != 0) {

				printClients();
				char accountName[30] = { '\0' };
				printf("Unesite ime naloga: ");
				modifyCharacter(accountName, 30, stream);

				for(int i = 0; i < numberOfClients; i++)
					
					if(strcmp(clients[i].accName, accountName) == 0) {

						if(strcmp(clients[i].accCondition, "Deleted") == 0) {

							printf("Nalog je vec bio obrisan. \n");
						}
						else {

							printf("Nalog obrisan. \n");
							strcpy(clients[i].accCondition, "Deleted");
							writeClients(clients, numberOfClients);
							// TODO: Kako sa dogadjajima
						}
					}

			} 
			else printf("Nema klijent naloga. \n");

			free(clients);

		} 
		else if(checkSecondCharacter(character)) {

			int numberOfUsers = 0;
			struct User* users = getUsers(&numberOfUsers);

			if(numberOfUsers != 0) {

				printUsers();
				char accountName[30] = { '\0' };
				printf("Unesite ime naloga: ");
				modifyCharacter(accountName, 30, stream);

				for(int i = 0; i < numberOfUsers; i++)

					if(strcmp(users[i].accName, accountName) == 0) {

						if(strcmp(users[i].accCondition, "Deleted") == 0) {

							printf("Nalog je vec bio obrisan. \n");
						}
						else {

							printf("Nalog obrisan: \n");
							strcpy(users[i].accCondition, "Deleted");
							writeUsers(users, numberOfUsers);
							// TODO: Kako sa ulaznicama
						}
					}

			} else printf("Nema korisnik naloga. \n");

			free(users);

		} 
		else if(checkExitCharacter(character)) checkShouldIRun = 0;
		else printf("Greska. Unesite ponovno!\n");

	} while(checkShouldIRun);
}


void cancelPass(FILE* stream) {

	int checkShouldIRun = 1;

	do {

		char character[15] = { '\0' };
		printf("Ponistavanje sifre klijent naloga [1], Ponistavanje sifre korisnik naloga [2], Kraj [0]: ");

		modifyCharacter(character, 15, stream);

		if(checkFirstCharacter(character)) {

			int numberOfClients = 0;
			struct Client* clients = getClients(&numberOfClients);
			
			if(numberOfClients != 0) {

				printClients();
				char accountName[30] = { '\0' };
				printf("Unesite ime naloga: ");
				modifyCharacter(accountName, 30, stream);

				for(int i = 0; i < numberOfClients; i++)
					
					if(strcmp(clients[i].accName, accountName) == 0) {

						char accountPass[30] = { '\0' };
						printf("Unesite novu sifru naloga: ");
						do {

							modifyCharacter(accountPass, 30, stream);
						
						} while(checkCredentials(accountPass) == 0);

						printf("Sifra je promenjena. \n");
						strcpy(clients[i].accPass, accountPass);
						writeClients(clients, numberOfClients);
					}
			} 
			else printf("Nema klijent naloga. \n");

			free(clients);

		} 
		else if(checkSecondCharacter(character)) {

			int numberOfUsers = 0;
			struct User* users = getUsers(&numberOfUsers);

			if(numberOfUsers != 0) {

				printUsers();
				char accountName[30] = { '\0' };
				printf("Unesite ime naloga: ");
				modifyCharacter(accountName, 30, stream);

				for(int i = 0; i < numberOfUsers; i++)

					if(strcmp(users[i].accName, accountName) == 0) {

						char accountPass[30] = { '\0' };
						printf("Unesite novu sifru naloga: ");
						do {

							modifyCharacter(accountPass, 30, stream);

						} while(checkCredentials(accountPass) == 0);

						printf("Sifra je promenjena. \n");
						strcpy(users[i].accPass, accountPass);
						writeUsers(users, numberOfUsers);
					}

			} 
			else printf("Nema korisnik naloga. \n");

			free(users);

		} 
		else if(checkExitCharacter(character)) checkShouldIRun = 0;
		else printf("Greska. Unesite ponovno!\n");

	} while(checkShouldIRun);
}

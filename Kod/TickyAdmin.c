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

						// TODO: kreiranje klijent naloga
					}
					else if(checkExitCharacter(character1)) checkShouldIRun1 = 0;
					else printf("Greska. Unesite ponovo!\n");

				} while(checkShouldIRun1);
			}
			else if(checkSecondCharacter(character)) {

				// TODO: Obrada naloga
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
				changeAccountPass(newAdminPass, 30, stream);

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
					changeAccountPass(newAdminPass, 30, stream);

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

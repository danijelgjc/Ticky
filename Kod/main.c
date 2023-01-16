#include <stdio.h>
#include <stdlib.h>

#include "TickyGlobal.h"
#include "TickyAdmin.h"
#include "TickyClient.h"
#include "TickyUser.h"

int main() {

	struct Info info;	
	info = readNumberOfLogIns();

	if(info.firstTime == 0) {

		createEnvironment();
	}
	// Koristi se u while petljama
	// za provjeru da li se trebaju
	// ponovo izvrsavati, 1 predstavlja
	// da se treba izvrsavati 0 da se prestaje
	int checkShouldIRun = 1;
	
	do {
		
		// Ulazni "karakter" na osnovu kojeg se bira opcija
		char character[15] = { '\0' };
	
		printf("Prijava [1], Registracija [2], Kraj [0]: ");
		modifyCharacter(character, 15, stdin);
		if(checkFirstCharacter(character)) {
			
			// Prijava na sistem, postoji prijava za
			// korisnika, klijenta i admina
			int checkShouldIRun1 = 1;

			do {
				
				char character1[15] = { '\0' };
			
				printf("Prijava na: Admin [1], Klijent [2], Korisnik [3], Kraj [0]: ");
				modifyCharacter(character1, 15, stdin);
				
				if(checkFirstCharacter(character1)) {

					adminOption(&info, stdin);
				}
				else if(checkSecondCharacter(character1)) {
					// TODO: Prijava na klijent nalog

				}
				else if(checkThirdCharacter(character1)) {
					// TODO: Prijava na korisnik nalog
				}
				else if(checkExitCharacter(character1)) checkShouldIRun1 = 0;
				else printf("Greska. Unesite ponovo!\n");
			} while(checkShouldIRun1);
		}
		else if(checkSecondCharacter(character)) {
			// TODO: Registracija
		}
		else if(checkExitCharacter(character)) checkShouldIRun = 0;
		else printf("Greska. Unesite ponovo!\n");
	} while(checkShouldIRun);
	return 0;
}

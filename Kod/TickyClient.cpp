#include "TickyClient.h"
void clientOption(struct Info* info, FILE* stream)
{
	if(clientLogin(info,stream)) {
		int checkShouldIRun = 1;
		do
		{
			printf("Manipulacija dogadjajima [1], Izvjestaji i pregledi[2]");
				// TODO: Opcija tri
			char character[15] = { '\0' };
			modifyCharacter(character, 15, stream);
			if (checkFirstCharacter(character)) {
				int checkShouldIRun = 1;
				do
				{
					char character1[15] = { '\0' };
					printf("Kreiranje dogadjaja [1], Brisanje dogadjaja [2], Kraj [0]: ");
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
			else if()

	}
}

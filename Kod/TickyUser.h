#ifndef _TickyUser_h_
#define _TickyUser_h_

#include "TickyGlobal.h"
#include "TickyClient.h"

void userOption(struct Info, FILE*); // DONE

int userLogIn(struct Info, FILE*, char*);

int checkUserLogInInfo(struct User, int*);

int generateTicketCode();

//void createUser(struct User*); //DONE NOTE: POCETNI CREDIT ZA SVAKOG USERA JE 50

void buyTicket(char* ,FILE*);

//void printTickets(char[30],FILE*);//TODO: Poravnanje tokom ispisa da lijepse pise

//void sellTicket(char[30],FILE*);

//void checkCredit(struct User *); // DONE

#endif 

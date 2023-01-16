//#ifndef _TickyUser_h_
#define _TickyUser_h_

#include "TickyGlobal.h"
#include "TickyClient.h"
#include "TickyAdmin.h"
void userLogIn(FILE*,struct User* ); // DONE
void userOption(struct Info, FILE*); // DONE
void createUser(struct User*); //DONE NOTE: POCETNI CREDIT ZA SVAKOG USERA JE 50
void buyTicket(struct User* ,FILE*);//TODO
void printTickets(char[30],FILE*);//TODO: Poravnanje tokom ispisa da lijepse pise
void sellTicket(char[30],FILE*);
void checkCredit(struct User *); // DONE
#ifndef _TickyUser_h_
#define _TickyUser_h_

#include "TickyGlobal.h"
#include "TickyClient.h"
void userLogIn(struct Info*, FILE*); // DONE
void userOption(struct Info, FILE*); // DONE
void createUser(FILE*); //DONE NOTE: POCETNI CREDIT ZA SVAKOG USERA JE 50
void buyTicket(struct User, FILE*);//TODO
void printTickets(struct User, FILE*);//TODO: Poravnanje tokom ispisa da lijepse pise
void sellTicket(struct User, FILE*);
double checkCredit(struct User); // DONE
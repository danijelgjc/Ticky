#ifndef _TickyKlijent_h_
#define _TickyKlijent_h_

#include "TickyGlobal.h"

void clientOption(struct Info, FILE*); // TODO: Mozda treba jos par opcija

void createEvent(FILE*); // TODO: Provjera da li ima duplih Eventa

void writeEvent(struct Event*, int);//DONE

void checkSoldTickets(FILE*);	// TODO

void checkSales(FILE*);//TODO

void deleteEvent(char* eventCode);//DONE

int clientLogIn(struct Info*, FILE*); //TODO: POGLEDAJ NMP 


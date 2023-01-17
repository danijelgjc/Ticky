#ifndef _TickyClient_h_
#define _TickyClient_h_

#include "TickyGlobal.h"

void clientOption(struct Info*, FILE*); // TODO: Mozda treba jos par opcija

int checkClientLogInInfo(struct Client, int*);		// DONE

void createEvent(FILE*); // TODO: Provjera da li ima duplih Eventa

void writeEvent(struct Event*, int);//DONE

void checkSoldTickets(FILE*);	// TODO

void checkSales(FILE*);//TODO

void deleteEvent(char* eventCode);//DONE

char* generateEventCode();

int clientLogIn(struct Info*, FILE*); 			// DONE

#endif

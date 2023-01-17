#ifndef _TickyAdmin_h_
#define _TickyAdmin_h_

#include "TickyGlobal.h"

void adminOption(struct Info*, FILE*); // TODO: Blokiranje dogadjaja

void createAdmin(FILE*);	// DONE

void createClient(FILE*);	// DONE

void activateAccount(FILE*);	// TODO:

void suspendAccount(FILE*);	// TODO:	

void deleteAccount(FILE*);	// TODO: Kako sa dogadjajima i parama

void cancelPass(FILE*);		// DONE

int checkAdminLogInInfo(struct Admin, int*); // DONE

void writeAdmins(struct Admin*, int);	// DONE

void writeInfo(struct Info*);	// DONE

int adminLogIn(struct Info*, FILE*);	// DONE

#endif

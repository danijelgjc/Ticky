#ifndef _TickyAdmin_h_
#define _TickyAdmin_h_

#include "TickyGlobal.h"

void adminOption(struct Info*, FILE*); // In-Work

void createAdmin(FILE*);	// DONE

int checkAdminLogInInfo(struct Admin, int*); // DONE

void writeAdmins(struct Admin*, int);	// DONE
		
void writeInfo(struct Info*);	// DONE

int adminLogIn(struct Info*, FILE*);	// DONE

#endif

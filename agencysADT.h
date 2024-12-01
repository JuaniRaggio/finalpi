#include <stdbool.h>
#include <stdio.h>

#ifndef __AGENCYSADT_H__
#define __AGENCYSADT_H__

typedef struct agencysCDT * agencysADT;

agencysADT newAgency(char * agencyName);

bool addTicket(agencysADT agency, char * infractionID, char plate[], char * issueDate, size_t amount);

#endif


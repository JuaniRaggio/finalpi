#include <stdio.h>

// Cities
#define CHI 0
#define NY 1

// Default format
#ifndef FORMAT
#define FORMAT CHI
#endif

// Assign format
#if FORMAT==CHI
typedef enum {ID = 0, DESCRIPTION} INFRACTIONFIELDS;
typedef enum {DATE = 0, PLATE, AGENCY, TID, AMOUNT} TICKETFIELDS;
#define TICKETDIM 5
#define INFRACTIONDIM 2
const INFRACTIONFIELDS INFRACTIONORDER[INFRACTIONDIM] = {ID, DESCRIPTION};
const TICKETFIELDS TICKETORDER[TICKETDIM] = {DATE, PLATE, AGENCY, TID, AMOUNT};
#define DESCRIPTION_LEN 50
#define AGENCY_LEN 13
#define DATE_LEN 19
#elif FORMAT==NY
typedef enum {ID = 0, DESCRIPTION} INFRACTIONFIELDS;
typedef enum {PLATE = 0, DATE, TID, AMOUNT, AGENCY} TICKETFIELDS;
#define TICKETDIM 5
#define INFRACTIONDIM 2
const INFRACTIONFIELDS INFRACTIONORDER[INFRACTIONDIM] = {ID, DESCRIPTION};
const TICKETFIELDS TICKETORDER[TICKETDIM] = {PLATE, DATE, TID, AMOUNT, AGENCY};
#define DESCRIPTION_LEN 30
#define AGENCY_LEN 35
#define DATE_LEN 10
#endif

// General formats
#define PLATE_LEN 10
#define LINE 256 
#define SEPARATOR ";\n"
#define MONTHS 12
#define TICKETARG 1
#define INFRACTIONARG 2

// General structures
typedef struct ticket {
    char * plate;
    char * issueDate;
    size_t infractionID;
    size_t amount;
} TTicket;



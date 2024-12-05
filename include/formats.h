#ifndef __FORMATS_H__
#define __FORMATS_H__

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
#define DATESEPARATORS "-"
#define PLATE_LEN 10
#define DESCRIPTION_LEN 50
#define AGENCY_LEN 13
#define DATE_LEN 19
#define YEAR_LEN 4
#define ID_TYPE unsigned char
#elif FORMAT==NY
typedef enum {ID = 0, DESCRIPTION} INFRACTIONFIELDS;
typedef enum {PLATE = 0, DATE, TID, AMOUNT, AGENCY} TICKETFIELDS;
#define TICKETDIM 5
#define INFRACTIONDIM 2
const INFRACTIONFIELDS INFRACTIONORDER[INFRACTIONDIM] = {ID, DESCRIPTION};
const TICKETFIELDS TICKETORDER[TICKETDIM] = {PLATE, DATE, TID, AMOUNT, AGENCY};
#define DATESEPARATORS "-"
#define PLATE_LEN 10
#define DESCRIPTION_LEN 30
#define AGENCY_LEN 35
#define DATE_LEN 10
#define YEAR_LEN 4
#define ID_TYPE unsigned char
#endif

// General formats
#define LINE 256 
#define SEPARATOR ";\n-"
#define MONTHS 12
#define TICKETARG 1
#define INFRACTIONARG 2
#define UPPERLIMIT 1
#define LOWERLIMIT -1
#define INIT_DIFF 0

// General structures
typedef struct ticket {
    char * plate;
    unsigned char issueMonth;
    size_t issueYear;
    ID_TYPE infractionID;
    size_t amount;
} TTicket;

typedef struct diff {
    ID_TYPE id;
    size_t minAmount;
    size_t maxAmount;
} DDiff;

typedef struct DYear {
    size_t yearN;
    size_t collected[MONTHS];
} DYear;

typedef struct DTicket {
    ID_TYPE id;
    size_t units;
} DTicket;

#endif


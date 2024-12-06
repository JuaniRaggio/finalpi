#include "../include/queries.h"

#define newFile(ptr, name, permission, retValue){ \
    FILE * ptr = fopen(name, permission); \ 
    assert(ptr == NULL, ENOENT,retValue); \
}

void runMultithreadedQueries(agencyTreeADT agency){
    toBeginAgency(agency);
    char * agencyName = NULL;

    while(hasNextAgency(agency)){
        agencyName = nextAgency(agency);
        runQuery1(agency,agencyName);
        runQuery2(agency,agencyName);
        runQuery3(agency,agencyName);
    }
}

void runQueries(agencyTreeADT agency){
    FILE *Q1, *Q2, *Q3;
    
    newFile(Q1, "query1.csv","w",);
    fprintf(Q1,"Agency;Infraction;Tickets\n");
    newFile(Q2, "query2.csv","w",);
    fprintf(Q2, "Agency;Year;Month;YTD\n");
    newFile(Q3, "query3.csv","w",);
    fprintf(Q3, "Agency;MinAmount;MaxAmount;DiffAmount");

    runMultithreadedQueries(agency);

    fclose(Q1);
    fclose(Q2);
    fclose(Q3);
}

void runQuery1(agencyTreeADT agency, char * agencyName){
    
}



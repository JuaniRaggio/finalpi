#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "readData.h"
#include "errorManagement.h"

#define FILE_ERROR -1
#define PLATE_LEN 11 
#define LINE 256 
#define SEPARATOR ";"
//.c del readCSV

//habia definido asi: #define TICKET_FILE 1
// #define INFRACTION_FILE 2

void readInfractions(const char argv[INFRACTION_FILE], LInfraction ** infractionList){ //ojo. ver que le paso como 2do parametro.
    FILE *infractionFile = fopen(argv[INFRACTION_FILE], "r");
    assert(infractionFile == NULL, ENOENT, FILE_ERROR); //Chequeo que el file no sea NULL
    
    char line[LINE];
    // Leo el titulo 
    fgets(line, sizeof(line), infractionFile);
    
    while (fgets(line, sizeof(line), infractionFile)) { //empiezo a guardar los datos hasta que fgets me retorne NULL
        processInfraction(line, infractionList);
    }
    
    fclose(infractionFile);
    return 0;
}

//a chequear
// Función para procesar cada línea del archivo de infracciones
void processInfraction(char *line, LInfraction **list) {
    unsigned char infractionID;
    char description[30];//OJO! El 30 lo tengo que modificar de acuerdo al caso que sea. Si es NY--> 30, CHI-->50
    
    // Dividir la línea por coma
    char *token = strtok(line, SEPARATOR);
    int field = 0;
    
    while (token != NULL) {
        switch (field) {
            case 0: // id (identificador)
                infractionID = (unsigned char)atoi(token);
                break;
            case 1: // description (descripción)
                trimWhitespace(token);
                strncpy(description, token, sizeof(description) - 1);
                description[sizeof(description) - 1] = '\0';
                break;
            default:
                break;
        }
        field++;
        token = strtok(NULL, SEPARATOR);
    }
    
    // Insertar la infracción en la lista-->es un nombre provisorio a la funcion que se encarga de eso. dsp modificar
    insertInfractionToList(list, infractionID, description);
}

// // Función para insertar una infracción en la lista de infracciones
// void insertInfractionToList(LInfraction **list, unsigned char id, const char *description) {
//     LInfraction *newInfraction = (LInfraction *)malloc(sizeof(LInfraction));
//     //Error al asignar memoria para infracción
//     assert(newInfraction == NULL, ENOMEM, NULL);////check valor de retorno. Es NULL??
//     newInfraction->ID = id;
//     strncpy(newInfraction->description, description, sizeof(newInfraction->description) - 1);
//     newInfraction->description[sizeof(newInfraction->description) - 1] = '\0';
//     newInfraction->next = *list;
    
//     *list = newInfraction;
// }

// Función para leer el archivo de multas
int readTicketCSV(const char argv[TICKET_FILE], struct bstCDT *tree) {
    FILE *ticketFile = fopen(argv[TICKET_FILE], "r");
  
    assert(ticketFile == NULL, ENOENT, FILE_ERROR); //Chequeo que el file no sea NULL. //obs: ver si el valor de errno es enoent
    
    char line[LINE];
    // Leo titulo
    fgets(line, sizeof(line), ticketFile);
    
    while (fgets(line, sizeof(line), ticketFile)) {//empiezo a guardar los datos del ticket 
        processTicket(line, tree);
    }
    
    fclose(ticketFile);
    return 0;
}

// Función para procesar cada línea del archivo de multas
void processTicket(char *line, struct bstCDT *tree) {
    TTicket ticket;
    char *token;
    int field = 0;
    
    // Dividir la línea por ";"
    token = strtok(line, SEPARATOR);
    while (token != NULL) {
        switch (field) {
            case 0: // plate (patente)
                trimWhitespace(token);
                strncpy(ticket.plate, token, PLATE_LEN);
                break;
            case 1: // issueDate (fecha)
                trimWhitespace(token);
                strncpy(ticket.issueDate, token, 10); // yyyy-MM-dd
                ticket.issueDate[10] = '\0';
                break;
            case 2: // infractionId
                ticket.infractionID = (size_t)atoi(token);
                break;
            case 3: // fineAmount
                ticket.amount = (size_t)atoi(token);
                break;
            case 4: // issuingAgency (agencia emisora)
                trimWhitespace(token);
                break;
            default:
                break;
        }
        field++;
        token = strtok(NULL, SEPARATOR);
    }
    
    // Insertar la multa en el árbol binario-->es un nombre provisorio a la funcion q agrega el ticket. dsp modificarlo
    insertTicketToTree(&ticket, tree);
}

// Función para eliminar espacios en blanco en una cadena
void trimWhitespace(char *str) {
    char *end;

    // Eliminar espacios al principio
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    
    // Eliminar espacios al final
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}
#ifndef __readData_h_
#define __readData_h_

#define TICKET_FILE 1
#define INFRACTION_FILE 2

/*
*Funcion que lee el archivo de Tickets
* @param argc dimension de argv
* @param argv[] arreglo de la informacion a leer
*/
void csvTickets(int argc, const char * argv[]);

/*
*Funcion que lee el archivo de infracciones
* @param argc dimension de argv
* @param argv[] arreglo de la informacion a leer
*/
void csvInfraction(int argc, const char * argv[]);

#endif


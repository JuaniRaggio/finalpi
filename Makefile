COMPILER = gcc
FRONT = main.c
HEADERS_DIR = include
SRC_DIR = src
CFLAGS = -I$(HEADERS_DIR) -Wall -pedantic -std=c99 -fsanitize=address -g
OBJ = agencyTreeADT.o formats.o lib.o processData.o processQueries.o readData.o runQueries.o validIDADT.o 

ifeq ($(FORMAT), CHI)
OUTPUT_FILE = queriesForChicago
INPUT_FILE_TICKETS = ticketsCHI.csv
INPUT_FILE_INFRACTIONS = infractionsCHI.csv
else ifeq ($(FORMAT), NYC)
OUTPUT_FILE = queriesForNYC
INPUT_FILE_TICKETS = ticketsNYC.csv
INPUT_FILE_INFRACTIONS = infractionsNYC.csv
else
OUTPUT_FILE = queriesForChicago
INPUT_FILE_TICKETS = ticketsCHI.csv
INPUT_FILE_INFRACTIONS = infractionsCHI.csv
endif

.PHONY: all clean run
all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(FRONT) $(OBJ)
	$(COMPILER) $(CFLAGS) $(FRONT) $(OBJ) -o $(OUTPUT_FILE)

%.o: $(SRC_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

agencyTreeADT.o: $(SRC_DIR)/agencyTreeADT.c $(HEADERS_DIR)/agencyTreeADT.h $(HEADERS_DIR)/formats.h $(HEADERS_DIR)/lib.h $(HEADERS_DIR)/validIDADT.h $(HEADERS_DIR)/errorManagement.h

formats.o: $(SRC_DIR)/formats.c $(HEADERS_DIR)/formats.h 

lib.o: $(SRC_DIR)/lib.c $(HEADERS_DIR)/lib.h $(HEADERS_DIR)/errorManagement.h

processData.o: $(SRC_DIR)/processData.c $(HEADERS_DIR)/processData.h $(HEADERS_DIR)/agencyTreeADT.h $(HEADERS_DIR)/formats.h

processQueries.o: $(SRC_DIR)/processQueries.c $(HEADERS_DIR)/processQueries.h $(HEADERS_DIR)/agencyTreeADT.h

readData.o: $(SRC_DIR)/readData.c $(HEADERS_DIR)/readData.h $(HEADERS_DIR)/agencyTreeADT.h $(HEADERS_DIR)/validIDADT.h $(HEADERS_DIR)/processData.h $(HEADERS_DIR)/errorManagement.h

runQueries.o: $(SRC_DIR)/runQueries.c $(HEADERS_DIR)/runQueries.h $(HEADERS_DIR)/agencyTreeADT.h $(HEADERS_DIR)/processQueries.h

validIDADT.o: $(SRC_DIR)/validIDADT.c $(HEADERS_DIR)/validIDADT.h $(HEADERS_DIR)/formats.h $(HEADERS_DIR)/lib.h

clean:
	rm -r *.o $(OUTPUT_FILE) *.dSYM

run: $(OUTPUT_FILE)
	time ./$(OUTPUT_FILE) $(INPUT_FILE_TICKETS) $(INPUT_FILE_INFRACTIONS)


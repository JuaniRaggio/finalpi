ifndef $(FORMAT)
	FORMAT = NYC
endif
OUTPUT_FILE = parkingTickets$(FORMAT)
INPUT_FILE_TICKETS = tickets$(FORMAT).csv
INPUT_FILE_INFRACTIONS = infractions$(FORMAT).csv
COMPILER = gcc
FRONT = main.c
HEADERS_DIR = include
SRC_DIR = src
CFLAGS = -I$(HEADERS_DIR) -Wall -pedantic -std=c99 -fsanitize=address -O2 -g -DFORMAT=$(FORMAT)
OBJ = agencyTreeADT.o formats.o lib.o processData.o readData.o runQueries.o validIDADT.o genericStackADT.o

.PHONY: all clean run
all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(FRONT) $(OBJ)
	$(COMPILER) $(CFLAGS) $(FRONT) $(OBJ) -o $(OUTPUT_FILE)
	@rm -f $(OBJ)

%.o: $(SRC_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

agencyTreeADT.o: $(SRC_DIR)/agencyTreeADT.c $(HEADERS_DIR)/agencyTreeADT.h $(HEADERS_DIR)/formats.h $(HEADERS_DIR)/lib.h $(HEADERS_DIR)/validIDADT.h $(HEADERS_DIR)/errorManagement.h
formats.o: $(SRC_DIR)/formats.c $(HEADERS_DIR)/formats.h 
genericStackADT.o: $(SRC_DIR)/genericStackADT.c $(HEADERS_DIR)/genericStackADT.h 
lib.o: $(SRC_DIR)/lib.c $(HEADERS_DIR)/lib.h $(HEADERS_DIR)/errorManagement.h
processData.o: $(SRC_DIR)/processData.c $(HEADERS_DIR)/processData.h $(HEADERS_DIR)/agencyTreeADT.h $(HEADERS_DIR)/formats.h
readData.o: $(SRC_DIR)/readData.c $(HEADERS_DIR)/readData.h $(HEADERS_DIR)/agencyTreeADT.h $(HEADERS_DIR)/validIDADT.h $(HEADERS_DIR)/processData.h $(HEADERS_DIR)/errorManagement.h
runQueries.o: $(SRC_DIR)/runQueries.c $(HEADERS_DIR)/runQueries.h $(HEADERS_DIR)/agencyTreeADT.h
validIDADT.o: $(SRC_DIR)/validIDADT.c $(HEADERS_DIR)/validIDADT.h $(HEADERS_DIR)/formats.h $(HEADERS_DIR)/lib.h

clean: $(OUTPUT_FILE)
	rm -rf $(OBJ) *.dSYM

run: $(OUTPUT_FILE)
	@rm -f $(OBJ)
	./$(OUTPUT_FILE) $(INPUT_FILE_TICKETS) $(INPUT_FILE_INFRACTIONS)



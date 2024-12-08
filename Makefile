COMPILER = gcc
OUTPUT_FILE = main #creo que main es el output 
CFLAGS = -Iinclude -Wall -pedantic -std=c99 -fsanitize=address -g
FRONT = main.c
SRC_DIR = src
OBJ = agencyTreeADT.o formats.o lib.o processData.o processQueries.o readData.o runQueries.o validId.o 

.PHONY: all clean
all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(FRONT) $(OBJ)
	$(COMPILER) $(CFLAGS) $(FRONT) $(OBJ) -o $(OUTPUT_FILE)

%.o: $(SRC_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

agencyTreeADT.o: agencyTreeADT.c agencyTreeADT.h formats.h lib.h validId.h errorManagement.h

formats.o: formats.c formats.h 

lib.o: lib.c lib.h errorManagement.h

processData.o: processData.c processData.h agencyTreeADT.h formats.h

processQueries.o: processQueries.c processQueries.h agencyTreeADT.h

readData.o: readData.c readData.h agencyTreeADT.h validId.h processData.h errorManagement.h

runQueries.o: runQueries.c runQueries.h agencyTreeADT.h processQueries.h

validId.o: validId.c validId.h formats.h lib.h

clean:
	rm -f *.o $(OUTPUT_FILE)

# # Ejecutar
# run: $(OUTPUT_FILE)
# 	./$(OUTPUT_FILE) $@

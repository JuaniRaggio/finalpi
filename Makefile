# Variables
COMPILER = gcc
OUTPUT_FILE = main #creo que main es el output 
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -g
FRONT = main.c
OBJ = src/agencyTreeADT.o src/formats.o src/lib.o src/processData.o src/processQueries.o src/readData.o src/runQueries.o src/stackADT.o src/validIDADT.o 

# Regla principal
.PHONY: all clean run
all: $(OUTPUT_FILE)

# Regla para construir el ejecutable
$(OUTPUT_FILE): $(FRONT) $(OBJ)
	$(COMPILER) $(CFLAGS) $(FRONT) $(OBJ) -o $(OUTPUT_FILE)

# Regla genérica para compilar archivos .o
%.o: src/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

# Dependencias específicas
agencyTreeADT.o: agencyTreeADT.c agencyTreeADT.h formats.h lib.h validId.h stackADT.h errorManagement.h

formats.o: formats.c formats.h 

lib.o: lib.c lib.h errorManagement.h

processData.o: processData.c processData.h agencyTreeADT.h formats.h

processQueries.o: processQueries.c processQueries.h agencyTreeADT.h

readData.o: readData.c readData.h agencyTreeADT.h validId.h processData.h errorManagement.h

runQueries.o: runQueries.c runQueries.h agencyTreeADT.h processQueries.h

stackADT.o: stackADT.c stackADT.h errorManagement.h

validId.o: validId.c validId.h formats.h lib.h

# Limpieza
clean:
	rm -f src/*.o $(OUTPUT_FILE)

# Ejecutar
run: $(OUTPUT_FILE)
	./$(OUTPUT_FILE)


#con make compila, make run ejecuta, make clean limpia los archivos despues de usarlos creo que los elimina si no entendi mal

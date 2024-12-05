## Multas NYC
---
### Datos de las multas
---
- *plate*: Patente de la multa (cadena de hasta 10 caracteres inclusive)
- *issueDate*: Fecha de la multa en formato yyyy-MM-dd
- *infractionId*: Identificador de la infracción (número entero no negativo)
- *fineAmount*: Monto de la multa (número entero no negativo)
- *issuingAgency*: Agencia emisora de la multa (cadena de hasta 35 caracteres inclusive)

### Infracciones
---
El archivo CSV tiene la siguiente estructura:
- id: Identificador de la infraccion
- description: Nombre de la infraccion
## Chicago
---
### Datos de multas de Chicago, a partir de ahora ticketsCHI.csv​  
---
El archivo CSV tiene la siguiente estructura:
- issueDate: Fecha y hora de la multa en formato yyyy-MM-dd HH:mm:SS
- plateRedacted: Identificador que corresponde a la patente de la multa (cadena de hasta 10 caracteres inclusive). Por privacidad los autores del dataset decidieron anonimizar las patentes.
- unitDescription: Agencia emisora de la multa (cadena de hasta 13 caracteres inclusive)
- infractionCode: Identificador de la infracción (número entero no negativo)
- fineLevel1Amount: Monto de la multa (número entero no negativo)

### Datos de infracciones de Chicago, a partir de ahora infractionsCHI.csv​  
---
El archivo CSV tiene la siguiente estructura:

- id: Identificador de la infracción (número entero no negativo)
- description: Nombre de la infracción (cadena de hasta 50 caracteres inclusive)


## IMPORTANTE ESTILO
---
- **En el .h se debe anteponer a cada prototipo de función un comentario sobre lo que hace la función**
- ![[Pasted image 20241201002844.png]]
- **Cuando se quiere comparar por igualdad con números reales, salvo el caso particular de 0.0, siempre se debe usar un rango de tolerancia (ver ejercicio 24 del TP 3). Esto se debe a los errores de representación de ciertos números reales, como vieron en Introducción a la Computación.**
## Query 1
---
Lista de Agencias (ordenada) de listas de infracciones

> [!NOTE] IMPORTANTE
> *Orden alfabetico por agencia*
> Listar:
> - Nombre de Agencia
> - Nombre de infraccion
> - Cantidad total de multas con esa infraccion por esa agencia (mismo infractionID)

- [ ] ticketList

## Query 2
---
Lista de Agencias de Lista de años de vectores de meses con el total recaudado

> [!NOTE] IMPORTANTE
> *Orden alfabetico por agencia y desempatan por fecha*
> Listar:
> - Nombre de Agencia
> - Año
> - Mes
> - Recaudacion en ese Año;Mes

- [ ] firstYear

## Query 3
---

> [!NOTE] IMPORTANTE
> *Orden DECRECIENTE por diffamount y desempatan alfabeticamente por agencia emisora*
> Listar:
> - Nombre de Agencia
> - MinAmount
> - MaxAmount
> - DiffAmount

- [ ] Vector diffOrder que lo ordenamos al final

```c
typedef struct ticket {
    char plate[PLATE_LEN];
    char * issueDate;
    size_t infractionID;
    size_t amount;
} TTicket;

typedef struct validInfraction {
	char * infractionDescription;
	unsigned char maxDescriptionLen;
} TInfraction;

struct validationCDT {
	TInfraction * validIDs;
	size_t maxID;
};

typedef struct LInfraction {
	unsigned char ID;
	size_t amount;
	struct LInfraction * next;
} LInfraction;

typedef struct LYear {
    size_t yearN;
    size_t collected[MONTHS];
    struct year * next;
} LYear;

typedef struct agency {
    char agencyName[AGENCY_LEN];
    LInfraction * infractionAmount; // -> Lista de cant infrac emitidas con ID=x por agency
    size_t maxID;
    LYear * firstYear;
} TAgency;

typedef struct node {
    TAgency * agencyData;
    size_t nodeHeight;
    struct node * left;
    struct node * right;
    struct node * leftDiff;
    struct node * rightDiff;
} TNode;

struct bstCDT {
    TNode * rootAlphabetica;
    TNode * iterator;
	TNode * rootDiff;
    size_t agencyCounter;
    size_t treeHeight;
};

typedef struct diffNode {
	char agencyName[AGENCY_LEN];
	size_t minAmount;
	size_t maxAmount;
} TDiff;

struct diffbstCDT {
	TDiff * root;
	TDiff * diffIterator;
};
```

## Archivos restantes
---
- [ ] processData.c 
- [ ] queries.c
- [x] agencyTreeADT.c

## OJO EN ERRORMANAGEMENT
---
- *Posible cambio*: Refactor assert
- No es necesario setear errno si usamos nuestro assert ya que va a pisarlo
- Si es necesario setearlo para checkErrno()

### Para ver despues
---
- Ver en validID el caso en el que


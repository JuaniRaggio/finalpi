
import csv
from datetime import datetime

def count_unique_agencies(file_path):
    agencies = set()  # Usamos un conjunto para almacenar agencias únicas
    try:
        with open(file_path, mode='r', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile, delimiter=';')  # Usamos ';' como separador
            for row in reader:
                # Validación opcional de la fecha (si necesitas asegurar su formato)
                try:
                    datetime.strptime(row['issueDate'], '%Y-%m-%d')  # Verifica el formato de fecha
                except ValueError:
                    print(f"Error: Formato de fecha inválido en la fila: {row}")
                    continue

                agencies.add(row['issuingAgency'])  # Agrega cada agencia al conjunto
    except FileNotFoundError:
        print(f"Error: El archivo '{file_path}' no existe.")
        return
    except KeyError as e:
        print(f"Error: Falta la columna requerida en el archivo: {e}")
        return

    print(f"Agencias diferentes encontradas: {len(agencies)}")
    print("Listado de agencias:", ", ".join(agencies))


# Ejemplo de uso
file_path = "ticketsCHI1000000.csv"  # Reemplaza con la ruta de tu archivo
count_unique_agencies(file_path)


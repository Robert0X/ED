# Nombre del ejecutable
TARGET = Main

# Archivos de origen
SOURCES = main.c lista_simple.c lista_doble.c lista_doble_circular.c

# Archivos de cabecera
HEADERS = lista_simple.h lista_doble.h lista_doble_circular.h

# Comando de compilación
CC = gcc
CFLAGS = -Wall -o

# Regla para compilar el ejecutable
$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) $(CFLAGS) $(TARGET)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET)

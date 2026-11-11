# Compilación y pruebas de la práctica 06.
CC = gcc
CFLAGS ?= -g
REQUISITOS_C = -std=c11 -Wall -Wextra -Wpedantic -Werror

.PHONY: all test clean
.DELETE_ON_ERROR:

all: build/practica06

# También compila el programa para revisar sus advertencias.
test: all build/test_practica06
	./build/test_practica06

build/practica06: src/main.c src/conjunto.c src/conjunto.h \
		src/estudiante.c src/estudiante.h src/persistencia.c \
		src/persistencia.h Makefile | build
	$(CC) $(CPPFLAGS) -Isrc $(CFLAGS) $(REQUISITOS_C) \
		src/main.c src/conjunto.c src/estudiante.c src/persistencia.c \
		$(LDFLAGS) $(LDLIBS) -o $@

build/test_practica06: tests/test_practica06.c src/conjunto.c \
		src/conjunto.h src/estudiante.c src/estudiante.h \
		src/persistencia.c src/persistencia.h Makefile | build
	$(CC) $(CPPFLAGS) -Isrc $(CFLAGS) $(REQUISITOS_C) \
		tests/test_practica06.c src/conjunto.c src/estudiante.c \
		src/persistencia.c $(LDFLAGS) $(LDLIBS) -o $@

build:
	mkdir -p $@

clean:
	$(RM) build/practica06 build/test_practica06 \
		build/prueba_carga.csv build/prueba_guardado.csv \
		build/prueba_invalida.csv

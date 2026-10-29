# Compilación y pruebas de la práctica 05.
CC = gcc
CFLAGS ?= -g
REQUISITOS_C = -std=c11 -Wall -Wextra -Wpedantic -Werror

.PHONY: all test clean
.DELETE_ON_ERROR:

all: build/practica05

# También compila el programa de ejemplo para revisar sus advertencias.
test: all build/test_practica05
	./build/test_practica05

build/practica05: src/main.c src/conjunto.c src/conjunto.h \
		src/estudiante.c src/estudiante.h Makefile | build
	$(CC) $(CPPFLAGS) -Isrc $(CFLAGS) $(REQUISITOS_C) \
		src/main.c src/conjunto.c src/estudiante.c \
		$(LDFLAGS) $(LDLIBS) -o $@

build/test_practica05: tests/test_practica05.c src/conjunto.c src/conjunto.h \
		src/estudiante.c src/estudiante.h Makefile | build
	$(CC) $(CPPFLAGS) -Isrc $(CFLAGS) $(REQUISITOS_C) \
		tests/test_practica05.c src/conjunto.c src/estudiante.c \
		$(LDFLAGS) $(LDLIBS) -o $@

build:
	mkdir -p $@

clean:
	$(RM) build/practica05 build/test_practica05

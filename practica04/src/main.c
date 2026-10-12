/*
 * Archivo: main.c
 * Práctica 04: el mismo conjunto para enteros y estudiantes.
 * Programa de ejemplo; las pruebas se ejecutan con make test.
 */

#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"
#include "estudiante.h"

/* Conecta la presentación de estudiantes con la interfaz del conjunto. */
static void mostrarEstudianteEnConjunto(const void *elemento) {
    const Estudiante *estudiante = elemento;
    mostrarEstudiante(estudiante);
}

static int compararEnteros(const void *elementoA, const void *elementoB) {
    const int *a = elementoA;
    const int *b = elementoB;
    return (*a > *b) - (*a < *b);
}

static void mostrarEntero(const void *elemento) {
    const int *numero = elemento;
    printf("%d", *numero);
}

int main(void) {
    int numeros[CAPACIDAD_CONJUNTO];
    Estudiante registros[CAPACIDAD_CONJUNTO];
    Conjunto enteros, estudiantes;
    int datos[] = {30, 10, 20};
    Estudiante ana = {101, {"Ana", "López Ruiz"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez Solís"}, 9.1f};

    inicializarConjunto(&enteros, numeros, CAPACIDAD_CONJUNTO,
                       sizeof numeros[0], compararEnteros);
    inicializarConjunto(&estudiantes, registros, CAPACIDAD_CONJUNTO,
                       sizeof registros[0], compararEstudiantes);
    for (int indice = 0; indice < 3; indice++)
        agregarElemento(&enteros, &datos[indice]);
    agregarElemento(&estudiantes, &bruno);
    agregarElemento(&estudiantes, &ana);

    ordenarConjunto(&enteros);
    ordenarConjunto(&estudiantes);
    printf("Enteros ordenados; esperado: {10, 20, 30}\n");
    mostrarConjunto(&enteros, mostrarEntero);
    printf("Estudiantes ordenados por matrícula; esperado: 101, 205\n");
    mostrarConjunto(&estudiantes, mostrarEstudianteEnConjunto);

    int buscado = 20;
    Estudiante criterio = {.matricula = 205};
    printf("Buscar 20; índice esperado: 1; obtenido: %d\n",
           buscarElementoOrdenado(&enteros, &buscado));
    int indice = buscarElementoOrdenado(&estudiantes, &criterio);
    printf("Buscar 205; índice esperado: 1; obtenido: %d\n", indice);
    if (indice >= 0) {
        Estudiante *registro = obtenerElemento(&estudiantes, indice);
        actualizarPromedio(registro, 9.5f);
        mostrarEstudiante(registro);
    }
    return EXIT_SUCCESS;
}

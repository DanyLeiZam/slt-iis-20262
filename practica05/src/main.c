/*
 * Archivo: main.c
 * Práctica 05: conjuntos genéricos con almacenamiento dinámico.
 * Programa de ejemplo; las pruebas se ejecutan con make test.
 */

#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"
#include "estudiante.h"

static void mostrarEstudianteEnConjunto(const void *elemento) {
    const Estudiante *estudiante = elemento;
    printf("%d | %s %s | %.2f",
           estudiante->matricula,
           estudiante->nombre.nombres,
           estudiante->nombre.apellidos,
           estudiante->promedio);
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
    int datos[] = {30, 10, 20};
    Estudiante ana = {101, {"Ana", "López Ruiz"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez Solís"}, 9.1f};
    Conjunto enteros;
    Conjunto estudiantes;

    if (!inicializarConjunto(&enteros, 1, sizeof datos[0], compararEnteros))
        return EXIT_FAILURE;
    if (!inicializarConjunto(&estudiantes, 1, sizeof(Estudiante),
                             compararEstudiantes)) {
        vaciarConjunto(&enteros);
        return EXIT_FAILURE;
    }

    for (int indice = 0; indice < 3; indice++)
        agregarElemento(&enteros, &datos[indice]);
    agregarElemento(&estudiantes, &bruno);
    agregarElemento(&estudiantes, &ana);

    ordenarConjunto(&enteros);
    ordenarConjunto(&estudiantes);
    printf("Enteros ordenados; esperado: {10, 20, 30}\n");
    mostrarConjunto(&enteros, mostrarEntero);
    printf("Capacidad después de crecer; esperado: 4; obtenido: %d\n",
           enteros.capacidad);
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

    vaciarConjunto(&enteros);
    vaciarConjunto(&estudiantes);
    return EXIT_SUCCESS;
}

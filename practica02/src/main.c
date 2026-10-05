/*
 * Archivo: main.c
 * Práctica 02: Implementación de conjuntos.
 * Programa de ejemplo para consultar las operaciones de la biblioteca.
 * Las pruebas automáticas se ejecutan por separado con make test.
 */

#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"

/*
 * Muestra el resultado de una operación o avisa que falta capacidad.
 * resultado: el arreglo que recibió los elementos.
 * cantidad: la cantidad producida, o -1 si falta capacidad.
 */
static void mostrarResultado(const int resultado[], int cantidad) {
    if (cantidad < 0)
        printf("capacidad insuficiente\n");
    else
        mostrarConjunto(resultado, cantidad);
}

/*
 * Ejecuta el ejemplo de uso de las operaciones sobre conjuntos.
 * Regresa EXIT_SUCCESS al terminar el ejemplo.
 */
int main(void) {
    /* Conjuntos y cantidades del ejemplo. */
    int conjuntoA[CAPACIDAD_CONJUNTO] = {17, 23, 31, 44};
    int conjuntoB[CAPACIDAD_CONJUNTO] = {23, 44, 58};
    int resultado[CAPACIDAD_RESULTADO] = {0};
    int cantidadA = 4;
    int cantidadB = 3;
    /* Cantidad de elementos que produce cada operación. */
    int cantidadResultado;
    /* Estado que indica si agregar o eliminar modificó el conjunto. */
    int estado;

    printf("A = ");
    mostrarConjunto(conjuntoA, cantidadA);
    printf("B = ");
    mostrarConjunto(conjuntoB, cantidadB);

    printf("\nUnión esperada: {17, 23, 31, 44, 58}\n");
    cantidadResultado = unirConjuntos(conjuntoA, cantidadA,
                                     conjuntoB, cantidadB,
                                     resultado, CAPACIDAD_RESULTADO);
    printf("Unión obtenida: ");
    mostrarResultado(resultado, cantidadResultado);

    printf("\nIntersección esperada: {23, 44}\n");
    cantidadResultado = intersectarConjuntos(conjuntoA, cantidadA,
                                            conjuntoB, cantidadB,
                                            resultado, CAPACIDAD_RESULTADO);
    printf("Intersección obtenida: ");
    mostrarResultado(resultado, cantidadResultado);

    printf("\nDiferencia A-B esperada: {17, 31}\n");
    cantidadResultado = diferenciarConjuntos(conjuntoA, cantidadA,
                                            conjuntoB, cantidadB,
                                            resultado, CAPACIDAD_RESULTADO);
    printf("Diferencia A-B obtenida: ");
    mostrarResultado(resultado, cantidadResultado);

    printf("\nAgregar 58 a A. Estado esperado: 1\n");
    estado = agregarElemento(conjuntoA, CAPACIDAD_CONJUNTO, &cantidadA, 58);
    printf("Estado obtenido: %d; A = ", estado);
    mostrarConjunto(conjuntoA, cantidadA);

    printf("\nAgregar otra vez 23. Estado esperado: 0\n");
    estado = agregarElemento(conjuntoA, CAPACIDAD_CONJUNTO, &cantidadA, 23);
    printf("Estado obtenido: %d; A = ", estado);
    mostrarConjunto(conjuntoA, cantidadA);

    printf("\nEliminar 31. Estado esperado: 1\n");
    estado = eliminarElemento(conjuntoA, &cantidadA, 31);
    printf("Estado obtenido: %d; A = ", estado);
    mostrarConjunto(conjuntoA, cantidadA);

    printf("\nEliminar 99. Estado esperado: 0\n");
    estado = eliminarElemento(conjuntoA, &cantidadA, 99);
    printf("Estado obtenido: %d; A = ", estado);
    mostrarConjunto(conjuntoA, cantidadA);

    printf("\nCopia esperada de A: {17, 23, 44, 58}\n");
    cantidadResultado = copiarConjunto(conjuntoA, cantidadA,
                                      resultado, CAPACIDAD_RESULTADO);
    printf("Copia obtenida: ");
    mostrarResultado(resultado, cantidadResultado);

    if (cantidadResultado >= 0) {
        printf("\n¿A y su copia son iguales? Estado esperado: 1\n");
        estado = sonConjuntosIguales(conjuntoA, cantidadA,
                                    resultado, cantidadResultado);
        printf("Estado obtenido: %d\n", estado);
    }
    printf("¿A y B son iguales? Estado esperado: 0\n");
    estado = sonConjuntosIguales(conjuntoA, cantidadA, conjuntoB, cantidadB);
    printf("Estado obtenido: %d\n", estado);

    printf("\n¿B es subconjunto de A? Estado esperado: 1\n");
    estado = esSubconjunto(conjuntoB, cantidadB, conjuntoA, cantidadA);
    printf("Estado obtenido: %d\n", estado);
    printf("¿A es subconjunto de B? Estado esperado: 0\n");
    estado = esSubconjunto(conjuntoA, cantidadA, conjuntoB, cantidadB);
    printf("Estado obtenido: %d\n", estado);

    printf("\nReemplazar 44 por 99 en A. Estado esperado: 1\n");
    estado = reemplazarElemento(conjuntoA, cantidadA, 44, 99);
    printf("Estado obtenido: %d; A = ", estado);
    mostrarConjunto(conjuntoA, cantidadA);

    printf("\nVaciar A. Conjunto esperado: {}\n");
    vaciarConjunto(&cantidadA);
    printf("Conjunto obtenido: ");
    mostrarConjunto(conjuntoA, cantidadA);

    return EXIT_SUCCESS;
}

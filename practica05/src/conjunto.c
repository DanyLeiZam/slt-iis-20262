/*
 * Archivo: conjunto.c
 * Implementación de un conjunto genérico con almacenamiento dinámico.
 * Completen las funciones pendientes según conjunto.h.
 * Autoría: Completa tu nombre.
 */

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conjunto.h"

/* Inicializa el conjunto y reserva un arreglo lleno de bytes con valor 0. */
int inicializarConjunto(Conjunto *conjunto, int capacidadInicial,
                        size_t tamElemento, Comparador comparar) {
    // Aquí va su código.
}

/* Obtiene una posición utilizada para consultarla o modificarla. */
void *obtenerElemento(Conjunto *conjunto, int indice) {
    if (indice < 0 || indice >= conjunto->cantidad)
        return NULL;
    unsigned char *inicio = conjunto->elementos;
    return inicio + (size_t)indice * conjunto->tamElemento;
}

/* Busca con el comparador sólo en las posiciones utilizadas. */
int buscarElemento(const Conjunto *conjunto, const void *elemento) {
    const unsigned char *inicio = conjunto->elementos;
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        const void *actual = inicio + (size_t)indice * conjunto->tamElemento;
        if (conjunto->comparar(actual, elemento) == 0)
            return indice;
    }
    return -1;
}

/* Agrega un elemento y duplica la capacidad cuando el arreglo está lleno. */
int agregarElemento(Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
}

/* Elimina un elemento y conserva el orden de los restantes. */
int eliminarElemento(Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
}

/* Sustituye un elemento sin introducir elementos repetidos. */
int reemplazarElemento(Conjunto *conjunto, const void *elemento,
                       const void *reemplazo) {
    // Aquí va su código.
}

/* Libera el arreglo y deja el conjunto listo para volver a crecer. */
void vaciarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
}

/* Copia todos los elementos y amplía el destino cuando hace falta. */
int copiarConjunto(const Conjunto *origen, Conjunto *destino) {
    // Aquí va su código.
}

/* Comprueba si todos los elementos de A pertenecen a B. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB) {
    // Aquí va su código.
}

/* Comprueba si ambos conjuntos contienen los mismos elementos. */
int sonConjuntosIguales(const Conjunto *conjuntoA,
                        const Conjunto *conjuntoB) {
    // Aquí va su código.
}

/* Calcula la unión y reserva de antemano la capacidad necesaria. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado) {
    // Aquí va su código.
}

/* Calcula la intersección y reserva de antemano la capacidad necesaria. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
}

/* Calcula la diferencia y reserva de antemano la capacidad necesaria. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
}

/* Intercambia registros completos mediante almacenamiento temporal dinámico. */
int intercambiarElementos(Conjunto *conjunto, int indiceA, int indiceB) {
    // Aquí va su código.
}

/* Ordena con el mismo comparador que determina la pertenencia. */
void ordenarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
}

/* Busca mediante búsqueda binaria en un conjunto ya ordenado. */
int buscarElementoOrdenado(const Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
}

/* Muestra el contenido mediante la función correspondiente al tipo. */
void mostrarConjunto(const Conjunto *conjunto, MostrarElemento mostrar) {
    const unsigned char *inicio = conjunto->elementos;
    printf("{");
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        if (indice > 0)
            printf(", ");
        mostrar(inicio + (size_t)indice * conjunto->tamElemento);
    }
    printf("}\n");
}

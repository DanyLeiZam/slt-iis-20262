/*
 * Archivo: conjunto.c
 * Implementación de un conjunto genérico con capacidad fija.
 * Completen las funciones pendientes según conjunto.h.
 * No usen memoria dinámica ni archivos.
 * Autoría: Completa tu nombre.
 */

#include <stdio.h>
#include <string.h>

#include "conjunto.h"

/* Inicializa el conjunto sobre un arreglo proporcionado por quien llama. */
void inicializarConjunto(Conjunto *conjunto, void *elementos, int capacidad,
                        size_t tamElemento, Comparador comparar) {
    conjunto->elementos = elementos;
    conjunto->cantidad = 0;
    conjunto->capacidad = capacidad;
    conjunto->tamElemento = tamElemento;
    conjunto->comparar = comparar;
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

/* Agrega un elemento si no existe y queda espacio. */
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

/* Deja el conjunto vacío y conserva su capacidad. */
void vaciarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
}

/* Copia todos los elementos del origen. */
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

/* Calcula la unión conservando primero el orden de A. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado) {
    // Aquí va su código.
}

/* Calcula la intersección conservando el orden de A. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
}

/* Calcula la diferencia A-B conservando el orden de A. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
}

/* Intercambia registros completos, no sólo sus campos de comparación. */
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

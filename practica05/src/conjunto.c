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
    if (!conjunto || capacidadInicial <= 0 || tamElemento == 0 || !comparar)
        return 0;
    if (tamElemento > SIZE_MAX / (size_t)capacidadInicial)
        return 0;

    void *arr = calloc((size_t)capacidadInicial, tamElemento);
    if (!arr) return 0;

    conjunto->elementos = arr;
    conjunto->cantidad = 0;
    conjunto->capacidad = capacidadInicial;
    conjunto->tamElemento = tamElemento;
    conjunto->comparar = comparar;
    return 1;
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
    if (!conjunto || !elemento || !conjunto->comparar) return 0;
    if (buscarElemento(conjunto, elemento) != -1) return 0;

    if (conjunto->cantidad >= conjunto->capacidad) {
        int nuevaCap = conjunto->capacidad == 0 ? 1 : conjunto->capacidad * 2;
        if (nuevaCap <= 0) return 0;
        if (conjunto->tamElemento > SIZE_MAX / (size_t)nuevaCap) return 0;
        void *nuevo = realloc(conjunto->elementos, (size_t)nuevaCap * conjunto->tamElemento);
        if (!nuevo) return 0;
        // Inicializar la memoria nueva a 0 (como pide calloc)
        if (nuevaCap > conjunto->capacidad) {
            unsigned char *ini = nuevo;
            memset(ini + (size_t)conjunto->capacidad * conjunto->tamElemento, 0,
                   (size_t)(nuevaCap - conjunto->capacidad) * conjunto->tamElemento);
        }
        conjunto->elementos = nuevo;
        conjunto->capacidad = nuevaCap;
    }
     unsigned char *dest = (unsigned char *)conjunto->elementos + (size_t)conjunto->cantidad * conjunto->tamElemento;
    memcpy(dest, elemento, conjunto->tamElemento);
    conjunto->cantidad++;
    return 1;
}

/* Elimina un elemento y conserva el orden de los restantes. */
int eliminarElemento(Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
    if (!conjunto || !elemento) return 0;
    int idx = buscarElemento(conjunto, elemento);
    if (idx == -1) return 0;

    unsigned char *inicio = conjunto->elementos;
    unsigned char *aBorrar = inicio + (size_t)idx * conjunto->tamElemento;
    unsigned char *siguiente = aBorrar + conjunto->tamElemento;
    size_t porMover = (size_t)(conjunto->cantidad - idx - 1) * conjunto->tamElemento;
    if (porMover > 0) memmove(aBorrar, siguiente, porMover);
    conjunto->cantidad--;
    return 1;
}

/* Sustituye un elemento sin introducir elementos repetidos. */
int reemplazarElemento(Conjunto *conjunto, const void *elemento,
                       const void *reemplazo) {
    // Aquí va su código.
    if (!conjunto || !elemento || !reemplazo) return 0;
    int idx = buscarElemento(conjunto, elemento);
    if (idx == -1) return 0;
    if (buscarElemento(conjunto, reemplazo) != -1) return 0;

    unsigned char *dest = (unsigned char *)conjunto->elementos + (size_t)idx * conjunto->tamElemento;
    memcpy(dest, reemplazo, conjunto->tamElemento);
    return 1;
}

/* Libera el arreglo y deja el conjunto listo para volver a crecer. */
void vaciarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    if (!conjunto) return;
    free(conjunto->elementos);
    conjunto->elementos = NULL;
    conjunto->cantidad = 0;
    conjunto->capacidad = 0;
}

/* Copia todos los elementos y amplía el destino cuando hace falta. */
int copiarConjunto(const Conjunto *origen, Conjunto *destino) {
    // Aquí va su código.
    if (!origen || !destino || !origen->elementos) return -1;
    if (origen->cantidad == 0) {
        destino->cantidad = 0;
        return 0;
    }
    if (destino->capacidad < origen->cantidad) {
        if (destino->tamElemento > SIZE_MAX / (size_t)origen->cantidad) return -1;
        void *nuevo = realloc(destino->elementos, (size_t)origen->cantidad * destino->tamElemento);
        if (!nuevo) return -1;
        destino->elementos = nuevo;
        destino->capacidad = origen->cantidad;
    }
    memcpy(destino->elementos, origen->elementos, (size_t)origen->cantidad * destino->tamElemento);
    destino->cantidad = origen->cantidad;
    return destino->cantidad;
}

/* Comprueba si todos los elementos de A pertenecen a B. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB) {
    // Aquí va su código.
    if (!conjuntoA || !conjuntoB) return 0;
    if (conjuntoA->cantidad == 0) return 1;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const unsigned char *ini = conjuntoA->elementos;
        const void *elem = ini + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elem) == -1) return 0;
    }
    return 1;
}

/* Comprueba si ambos conjuntos contienen los mismos elementos. */
int sonConjuntosIguales(const Conjunto *conjuntoA,
                        const Conjunto *conjuntoB) {
    // Aquí va su código.
    if (!conjuntoA || !conjuntoB) return 0;
    if (conjuntoA->cantidad != conjuntoB->cantidad) return 0;
    return esSubconjunto(conjuntoA, conjuntoB);
}

static int asegurarCapacidad(Conjunto *res, int necesaria) {
    if (res->capacidad >= necesaria) return 1;
    if (res->tamElemento > SIZE_MAX / (size_t)necesaria) return 0;
    void *nuevo = realloc(res->elementos, (size_t)necesaria * res->tamElemento);
    if (!nuevo) return 0;
    res->elementos = nuevo;
    res->capacidad = necesaria;
    return 1;
}

/* Calcula la unión y reserva de antemano la capacidad necesaria. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado) {
    // Aquí va su código.
    if (!conjuntoA || !conjuntoB || !resultado) return -1;
    int maxNecesaria = conjuntoA->cantidad + conjuntoB->cantidad;
    if (!asegurarCapacidad(resultado, maxNecesaria > 0 ? maxNecesaria : 1)) return -1;

    resultado->cantidad = 0;
    // Copia A
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const unsigned char *ini = conjuntoA->elementos;
        const void *e = ini + (size_t)i * conjuntoA->tamElemento;
        unsigned char *dest = (unsigned char *)resultado->elementos + (size_t)resultado->cantidad * resultado->tamElemento;
        memcpy(dest, e, resultado->tamElemento);
        resultado->cantidad++;
    }
    // Añade B si no está
    for (int i = 0; i < conjuntoB->cantidad; i++) {
        const unsigned char *ini = conjuntoB->elementos;
        const void *e = ini + (size_t)i * conjuntoB->tamElemento;
        if (buscarElemento(conjuntoA, e) == -1 && buscarElemento(resultado, e) == -1) {
            unsigned char *dest = (unsigned char *)resultado->elementos + (size_t)resultado->cantidad * resultado->tamElemento;
            memcpy(dest, e, resultado->tamElemento);
            resultado->cantidad++;
        }
    }
    return resultado->cantidad;
}

/* Calcula la intersección y reserva de antemano la capacidad necesaria. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    if (!conjuntoA || !conjuntoB || !resultado) return -1;
    if (!asegurarCapacidad(resultado, conjuntoA->cantidad > 0 ? conjuntoA->cantidad : 1)) return -1;
    resultado->cantidad = 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const unsigned char *ini = conjuntoA->elementos;
        const void *e = ini + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, e) != -1) {
            unsigned char *dest = (unsigned char *)resultado->elementos + (size_t)resultado->cantidad * resultado->tamElemento;
            memcpy(dest, e, resultado->tamElemento);
            resultado->cantidad++;
        }
    }
    return resultado->cantidad;
}

/* Calcula la diferencia y reserva de antemano la capacidad necesaria. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    if (!conjuntoA || !conjuntoB || !resultado) return -1;
    if (!asegurarCapacidad(resultado, conjuntoA->cantidad > 0 ? conjuntoA->cantidad : 1)) return -1;
    resultado->cantidad = 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const unsigned char *ini = conjuntoA->elementos;
        const void *e = ini + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, e) == -1) {
            unsigned char *dest = (unsigned char *)resultado->elementos + (size_t)resultado->cantidad * resultado->tamElemento;
            memcpy(dest, e, resultado->tamElemento);
            resultado->cantidad++;
        }
    }
    return resultado->cantidad;
}

/* Intercambia registros completos mediante almacenamiento temporal dinámico. */
int intercambiarElementos(Conjunto *conjunto, int indiceA, int indiceB) {
    // Aquí va su código.
    if (!conjunto || !conjunto->elementos) return 0;
    if (indiceA < 0 || indiceA >= conjunto->cantidad) return 0;
    if (indiceB < 0 || indiceB >= conjunto->cantidad) return 0;
    if (indiceA == indiceB) return 1;

    void *tmp = malloc(conjunto->tamElemento);
    if (!tmp) return 0;

    unsigned char *ini = conjunto->elementos;
    unsigned char *a = ini + (size_t)indiceA * conjunto->tamElemento;
    unsigned char *b = ini + (size_t)indiceB * conjunto->tamElemento;

    memcpy(tmp, a, conjunto->tamElemento);
    memcpy(a, b, conjunto->tamElemento);
    memcpy(b, tmp, conjunto->tamElemento);
    free(tmp);
    return 1;
}

/* Ordena con el mismo comparador que determina la pertenencia. */
void ordenarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    if (!conjunto || conjunto->cantidad <= 1) return;
    for (int i = 0; i < conjunto->cantidad - 1; i++) {
        for (int j = 0; j < conjunto->cantidad - i - 1; j++) {
            unsigned char *ini = conjunto->elementos;
            void *e1 = ini + (size_t)j * conjunto->tamElemento;
            void *e2 = ini + (size_t)(j+1) * conjunto->tamElemento;
            if (conjunto->comparar(e1, e2) > 0) {
                intercambiarElementos(conjunto, j, j+1);
            }
        }
    }
}

/* Busca mediante búsqueda binaria en un conjunto ya ordenado. */
int buscarElementoOrdenado(const Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
    if (!conjunto || !conjunto->elementos || !elemento) return -1;
    int izq = 0, der = conjunto->cantidad - 1;
    const unsigned char *ini = conjunto->elementos;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        const void *actual = ini + (size_t)medio * conjunto->tamElemento;
        int cmp = conjunto->comparar(actual, elemento);
        if (cmp == 0) return medio;
        if (cmp < 0) izq = medio + 1;
        else der = medio - 1;
    }
    return -1;
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

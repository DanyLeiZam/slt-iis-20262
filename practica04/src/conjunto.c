/*
 * Archivo: conjunto.c
 * Implementación de un conjunto genérico con capacidad fija.
 * Completen las funciones pendientes según conjunto.h.
 * No usen memoria dinámica ni archivos.
 * Autoría: Daniela Díaz Morales.
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
    if (conjunto->cantidad >= conjunto->capacidad)
        return 0;
    if (buscarElemento(conjunto, elemento) != -1)
        return 0;
    unsigned char *inicio = conjunto->elementos;
    void *destino = inicio + (size_t)conjunto->cantidad * conjunto->tamElemento;
    memcpy(destino, elemento, conjunto->tamElemento);
    conjunto->cantidad++;
    return 1;
}

/* Elimina un elemento y conserva el orden de los restantes. */
int eliminarElemento(Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
    int indice = buscarElemento(conjunto, elemento);
    if (indice == -1)
        return 0;
    unsigned char *inicio = conjunto->elementos;
    size_t tam = conjunto->tamElemento;
    // desplaza los posteriores
    for (int i = indice; i < conjunto->cantidad - 1; i++) {
        void *dest = inicio + (size_t)i * tam;
        void *src = inicio + (size_t)(i + 1) * tam;
        memcpy(dest, src, tam);
    }
    conjunto->cantidad--;
    return 1;
}

/* Sustituye un elemento sin introducir elementos repetidos. */
int reemplazarElemento(Conjunto *conjunto, const void *elemento,
                       const void *reemplazo) {
    // Aquí va su código.
    int indice = buscarElemento(conjunto, elemento);
    if (indice == -1)
        return 0;
    // Si el reemplazo ya pertenece, incluso si es el mismo, no hacer nada
    if (buscarElemento(conjunto, reemplazo) != -1)
        return 0;
    
    unsigned char *inicio = conjunto->elementos;
    void *dest = inicio + (size_t)indice * conjunto->tamElemento;
    memcpy(dest, reemplazo, conjunto->tamElemento);
    return 1;
}

/* Deja el conjunto vacío y conserva su capacidad. */
void vaciarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    conjunto->cantidad = 0;
}

/* Copia todos los elementos del origen. */
int copiarConjunto(const Conjunto *origen, Conjunto *destino) {
    // Aquí va su código.
    if (destino->capacidad < origen->cantidad)
        return -1;
    const unsigned char *src = origen->elementos;
    unsigned char *dst = destino->elementos;
    for (int i = 0; i < origen->cantidad; i++) {
        memcpy(dst + (size_t)i * destino->tamElemento,
               src + (size_t)i * origen->tamElemento,
               origen->tamElemento);
    }
    destino->cantidad = origen->cantidad;
    return destino->cantidad;
}

/* Comprueba si todos los elementos de A pertenecen a B. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB) {
    // Aquí va su código.
    const unsigned char *inicioA = conjuntoA->elementos;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elem = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elem) == -1)
            return 0;
    }
    return 1;
}

/* Comprueba si ambos conjuntos contienen los mismos elementos. */
int sonConjuntosIguales(const Conjunto *conjuntoA,
                        const Conjunto *conjuntoB) {
    // Aquí va su código.
    if (conjuntoA->cantidad != conjuntoB->cantidad)
        return 0;
    return esSubconjunto(conjuntoA, conjuntoB) && esSubconjunto(conjuntoB, conjuntoA);
}

/* Calcula la unión conservando primero el orden de A. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado) {
    // Aquí va su código.
    // calcular cuántos se necesitan
    int necesarios = conjuntoA->cantidad;
    const unsigned char *inicioB = conjuntoB->elementos;
    for (int i = 0; i < conjuntoB->cantidad; i++) {
        const void *elemB = inicioB + (size_t)i * conjuntoB->tamElemento;
        if (buscarElemento(conjuntoA, elemB) == -1)
            necesarios++;
    }
    if (resultado->capacidad < necesarios)
        return -1;

    // copiar A en orden
    const unsigned char *inicioA = conjuntoA->elementos;
    unsigned char *inicioR = resultado->elementos;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        memcpy(inicioR + (size_t)i * resultado->tamElemento,
               inicioA + (size_t)i * conjuntoA->tamElemento,
               resultado->tamElemento);
    }
    int cant = conjuntoA->cantidad;
    // añadir los nuevos de B en su orden
    for (int i = 0; i < conjuntoB->cantidad; i++) {
        const void *elemB = inicioB + (size_t)i * conjuntoB->tamElemento;
        if (buscarElemento(conjuntoA, elemB) == -1) {
            memcpy(inicioR + (size_t)cant * resultado->tamElemento,
                   elemB, resultado->tamElemento);
            cant++;
        }
    }
    resultado->cantidad = cant;
    return cant;
}

/* Calcula la intersección conservando el orden de A. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    // contar primero
    int necesarios = 0;
    const unsigned char *inicioA = conjuntoA->elementos;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elem = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elem) != -1)
            necesarios++;
    }
    if (resultado->capacidad < necesarios)
        return -1;

    unsigned char *inicioR = resultado->elementos;
    int cant = 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elem = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elem) != -1) {
            memcpy(inicioR + (size_t)cant * resultado->tamElemento,
                   elem, resultado->tamElemento);
            cant++;
        }
    }
    resultado->cantidad = cant;
    return cant;
}

/* Calcula la diferencia A-B conservando el orden de A. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    int necesarios = 0;
    const unsigned char *inicioA = conjuntoA->elementos;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elem = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elem) == -1)
            necesarios++;
    }
    if (resultado->capacidad < necesarios)
        return -1;

    unsigned char *inicioR = resultado->elementos;
    int cant = 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elem = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elem) == -1) {
            memcpy(inicioR + (size_t)cant * resultado->tamElemento,
                   elem, resultado->tamElemento);
            cant++;
        }
    }
    resultado->cantidad = cant;
    return cant;
}

/* Intercambia registros completos, no sólo sus campos de comparación. */
int intercambiarElementos(Conjunto *conjunto, int indiceA, int indiceB) {
    // Aquí va su código.
    if (indiceA < 0 || indiceA >= conjunto->cantidad ||
        indiceB < 0 || indiceB >= conjunto->cantidad)
        return 0;
    if (indiceA == indiceB)
        return 1;

    unsigned char *inicio = conjunto->elementos;
    size_t tam = conjunto->tamElemento;
    unsigned char *a = inicio + (size_t)indiceA * tam;
    unsigned char *b = inicio + (size_t)indiceB * tam;
    unsigned char tmp[tam];
    memcpy(tmp, a, tam);
    memcpy(a, b, tam);
    memcpy(b, tmp, tam);
    return 1;
}


/* Ordena con el mismo comparador que determina la pertenencia. */
void ordenarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    if (conjunto->cantidad <= 1) return;
    for (int i = 0; i < conjunto->cantidad - 1; i++) {
        for (int j = 0; j < conjunto->cantidad - 1 - i; j++) {
            void *act = obtenerElemento(conjunto, j);
            void *sig = obtenerElemento(conjunto, j + 1);
            if (conjunto->comparar(act, sig) > 0)
                intercambiarElementos(conjunto, j, j + 1);
        }
    }
}

/* Busca mediante búsqueda binaria en un conjunto ya ordenado. */
int buscarElementoOrdenado(const Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
    int izq = 0;
    int der = conjunto->cantidad - 1;
    const unsigned char *inicio = conjunto->elementos;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        const void *mid = inicio + (size_t)medio * conjunto->tamElemento;
        int cmp = conjunto->comparar(mid, elemento);
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

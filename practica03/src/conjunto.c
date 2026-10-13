/*
 * Archivo: conjunto.c
 * Implementación de un conjunto de estudiantes con capacidad fija.
 * Completen las funciones pendientes según conjunto.h.
 * No usen memoria dinámica ni archivos.
 * Autoría: Daniela Díaz Morales.
 */

#include <stdio.h>

#include "conjunto.h"

/* Inicializa la cantidad y la capacidad del conjunto. */
void inicializarConjunto(Conjunto *conjunto, int capacidad) {
    conjunto->cantidad = 0;
    conjunto->capacidad = capacidad;
}

/* Obtiene una posición utilizada para consultarla o modificarla. */
Estudiante *obtenerElemento(Conjunto *conjunto, int indice) {
    if (indice < 0 || indice >= conjunto->cantidad)
        return NULL;
    return &conjunto->elementos[indice];
}

/* Busca por matrícula sólo en las posiciones utilizadas. */
int buscarElemento(const Conjunto *conjunto, const Estudiante *estudiante) {
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        if (compararEstudiantes(&conjunto->elementos[indice], estudiante) == 0)
            return indice;
    }
    return -1;
}

/* Agrega un estudiante si no existe y queda espacio. */
int agregarElemento(Conjunto *conjunto, const Estudiante *estudiante) {
    // Aquí va su código.
if (buscarElemento(conjunto, estudiante)!= -1)
 return 0;
    if (conjunto->cantidad >= conjunto->capacidad)
     return 0;
    conjunto->elementos[conjunto->cantidad] = *estudiante;
    conjunto->cantidad++;
    return 1;
}

/* Elimina un estudiante y conserva el orden de los restantes. */
int eliminarElemento(Conjunto *conjunto, const Estudiante *estudiante) {
    // Aquí va su código.
    int idx = buscarElemento(conjunto, estudiante);
    if (idx == -1)
     return 0;
    for (int i = idx; i < conjunto->cantidad - 1; i++) {
        conjunto->elementos[i] = conjunto->elementos[i+1];
    }
    conjunto->cantidad--;
    return 1;
}

/* Sustituye un estudiante sin introducir matrículas repetidas. */
int reemplazarElemento(Conjunto *conjunto, const Estudiante *estudiante,
                       const Estudiante *reemplazo) {
    // Aquí va su código.
    int idx = buscarElemento(conjunto, estudiante);
    if (idx == -1)
     return 0;
    // si la nueva matricula es diferente, no debe existir ya
    if (compararEstudiantes(estudiante, reemplazo)!= 0) {
        if (buscarElemento(conjunto, reemplazo)!= -1)
         return 0;
    }
    conjunto->elementos[idx] = *reemplazo;
    return 1;
}

/* Deja el conjunto vacío y conserva su capacidad. */
void vaciarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    conjunto->cantidad = 0;
}

/* Copia todos los estudiantes del origen. */
int copiarConjunto(const Conjunto *origen, Conjunto *destino) {
    // Aquí va su código.
    if (origen->cantidad > destino->capacidad) 
    return -1;
    for (int i = 0; i < origen->cantidad; i++) {
        destino->elementos[i] = origen->elementos[i];
    }
    destino->cantidad = origen->cantidad;
    return destino->cantidad;
}

/* Comprueba si todos los estudiantes de A pertenecen a B. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB) {
    // Aquí va su código.
for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (buscarElemento(conjuntoB, &conjuntoA->elementos[i]) == -1)
            return 0;
    }
    return 1;
}

/* Comprueba si ambos conjuntos contienen las mismas matrículas. */
int sonConjuntosIguales(const Conjunto *conjuntoA,
                        const Conjunto *conjuntoB) {
    // Aquí va su código.
    if (conjuntoA->cantidad!= conjuntoB->cantidad)
     return 0;
    return esSubconjunto(conjuntoA, conjuntoB);
}

/* Calcula la unión conservando primero el orden de A. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado) {
    // Aquí va su código.
    int necesarios = conjuntoA->cantidad;
    for (int i = 0; i < conjuntoB->cantidad; i++) {
        if (buscarElemento(conjuntoA, &conjuntoB->elementos[i]) == -1)
            necesarios++;
    }
    if (necesarios > resultado->capacidad)
     return -1;

    vaciarConjunto(resultado);
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        resultado->elementos[i] = conjuntoA->elementos[i];
    }
    resultado->cantidad = conjuntoA->cantidad;

    for (int i = 0; i < conjuntoB->cantidad; i++) {
        if (buscarElemento(conjuntoA, &conjuntoB->elementos[i]) == -1) {
            resultado->elementos[resultado->cantidad] = conjuntoB->elementos[i];
            resultado->cantidad++;
        }
    }
    return resultado->cantidad;
}

/* Calcula la intersección conservando el orden de A. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    int necesarios = 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (buscarElemento(conjuntoB, &conjuntoA->elementos[i])!= -1)
            necesarios++;
    }
    if (necesarios > resultado->capacidad)
     return -1;

    vaciarConjunto(resultado);
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (buscarElemento(conjuntoB, &conjuntoA->elementos[i])!= -1) {
            resultado->elementos[resultado->cantidad] = conjuntoA->elementos[i];
            resultado->cantidad++;
        }
    }
    return resultado->cantidad;
}

/* Calcula la diferencia A-B conservando el orden de A. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    int necesarios = 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (buscarElemento(conjuntoB, &conjuntoA->elementos[i]) == -1)
            necesarios++;
    }
    if (necesarios > resultado->capacidad)
     return -1;

    vaciarConjunto(resultado);
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (buscarElemento(conjuntoB, &conjuntoA->elementos[i]) == -1) {
            resultado->elementos[resultado->cantidad] = conjuntoA->elementos[i];
            resultado->cantidad++;
        }
    }
    return resultado->cantidad;
}

/* Muestra todos los estudiantes del conjunto entre llaves. */
void mostrarConjunto(const Conjunto *conjunto) {
    printf("{");
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        if (indice > 0)
            printf(", ");
        mostrarEstudiante(&conjunto->elementos[indice]);
    }
    printf("}\n");
}

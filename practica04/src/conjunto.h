/*
 * Archivo: conjunto.h
 * Conjuntos genéricos con almacenamiento de capacidad fija.
 *
 * elementos señala un arreglo del tipo correspondiente que existe mientras
 * se usa el conjunto; tamElemento es sizeof de ese tipo. capacidad no excede
 * el tamaño del arreglo y 0 <= cantidad <= capacidad. Sólo se consultan las
 * primeras cantidad posiciones y no hay elementos repetidos.
 *
 * comparar devuelve un valor negativo, cero o positivo si A es menor, igual
 * o mayor que B. La misma comparación determina pertenencia y orden.
 * Los conjuntos de una operación usan el mismo tipo, tamaño y comparador.
 * Todos los apuntadores son válidos. En copias y operaciones con resultado,
 * el destino usa un arreglo distinto de las entradas. Los elementos que se
 * agregan o sustituyen se reciben desde variables fuera del arreglo destino.
 *
 * Las funciones conservan el arreglo, la capacidad, el tamaño y el comparador.
 * No se usa memoria dinámica. Los recorridos genéricos se hacen por bytes
 * mediante unsigned char *, no mediante aritmética sobre void *.
 */

#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <stddef.h>

#define CAPACIDAD_CONJUNTO 10
#define CAPACIDAD_RESULTADO (2 * CAPACIDAD_CONJUNTO)

typedef int (*Comparador)(const void *, const void *);
typedef void (*MostrarElemento)(const void *);

typedef struct Conjunto {
    void *elementos;
    int cantidad;
    int capacidad;
    size_t tamElemento;
    Comparador comparar;
} Conjunto;

/* Inicializa un conjunto vacío sobre el arreglo recibido; no copia ni reserva. */
void inicializarConjunto(Conjunto *conjunto, void *elementos, int capacidad,
                        size_t tamElemento, Comparador comparar);

/* Regresa la dirección de una posición utilizada, o NULL si no existe. */
void *obtenerElemento(Conjunto *conjunto, int indice);

/* Búsqueda lineal: regresa el índice del elemento o -1 si no pertenece. */
int buscarElemento(const Conjunto *conjunto, const void *elemento);

/*
 * Copia el elemento al final e incrementa cantidad. Regresa 1 si agrega;
 * 0, sin cambios, si ya pertenece o no queda espacio.
 */
int agregarElemento(Conjunto *conjunto, const void *elemento);

/*
 * Elimina y desplaza los elementos posteriores conservando su orden.
 * Regresa 1 y disminuye cantidad si elimina; 0, sin cambios, si no existe.
 */
int eliminarElemento(Conjunto *conjunto, const void *elemento);

/*
 * Sustituye en la misma posición y regresa 1. Regresa 0, sin cambios, si el
 * elemento no existe o el reemplazo ya pertenece, incluso si es el mismo.
 */
int reemplazarElemento(Conjunto *conjunto, const void *elemento,
                       const void *reemplazo);

/* Deja cantidad en cero sin modificar el contenido del arreglo. */
void vaciarConjunto(Conjunto *conjunto);

/*
 * Copia los elementos utilizados en su orden y actualiza cantidad del destino.
 * Regresa la cantidad copiada, o -1, sin cambios, si falta capacidad.
 * Las posiciones posteriores a la copia permanecen como estaban.
 */
int copiarConjunto(const Conjunto *origen, Conjunto *destino);

/* Regresa 1 si todo A pertenece a B; 0 en otro caso. El vacío es subconjunto. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB);

/* Regresa 1 si contienen los mismos elementos, sin importar el orden; 0 si no. */
int sonConjuntosIguales(const Conjunto *conjuntoA, const Conjunto *conjuntoB);

/*
 * Estas tres operaciones no modifican las entradas. Regresan la cantidad
 * del resultado y actualizan resultado->cantidad; si falta capacidad,
 * regresan -1 sin modificar el resultado. Sólo escriben las posiciones
 * utilizadas del resultado. Si un elemento aparece en ambas entradas,
 * se conserva la copia de A.
 */
/* Unión: conserva el orden de A y añade los elementos nuevos de B en su orden. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado);
/* Intersección: elementos de A presentes en B, en el orden de A. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado);
/* Diferencia A-B: elementos de A ausentes de B, en el orden de A. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado);

/*
 * Intercambia los registros completos en dos índices utilizados y regresa 1.
 * Si los índices coinciden, regresa 1 sin cambios. Si alguno está fuera del
 * intervalo [0, cantidad), regresa 0 sin cambios.
 */
int intercambiarElementos(Conjunto *conjunto, int indiceA, int indiceB);

/*
 * Ordena por burbuja según comparar, usando intercambiarElementos.
 * Conserva los registros completos y cantidad. Vacío o de un elemento:
 * sin cambios. No usa qsort ni modifica posiciones posteriores a cantidad.
 */
void ordenarConjunto(Conjunto *conjunto);

/*
 * Búsqueda binaria en un conjunto ya ordenado con su comparador.
 * Regresa el índice o -1 si no pertenece; no modifica ni ordena el conjunto.
 */
int buscarElementoOrdenado(const Conjunto *conjunto, const void *elemento);

/* Muestra los elementos con la función recibida, entre llaves, separados por comas. */
void mostrarConjunto(const Conjunto *conjunto, MostrarElemento mostrar);

#endif

/*
 * Archivo: conjunto.h
 * Conjuntos genéricos con almacenamiento dinámico.
 *
 * elementos señala un arreglo reservado dinámicamente; tamElemento es el
 * sizeof del tipo almacenado y 0 <= cantidad <= capacidad. Sólo se consultan
 * las primeras cantidad posiciones y no hay elementos repetidos.
 *
 * comparar devuelve un valor negativo, cero o positivo si A es menor, igual
 * o mayor que B. La misma comparación determina pertenencia y orden.
 * Los conjuntos de una operación usan el mismo tipo, tamaño y comparador.
 * En copias y operaciones con resultado, el destino es distinto de las
 * entradas. Los elementos agregados o sustituidos se reciben desde objetos
 * que no pertenecen al arreglo del conjunto que se modifica.
 *
 * Los recorridos genéricos se hacen por bytes mediante unsigned char *, no
 * mediante aritmética sobre void *. En las funciones implementadas se accede
 * a los arreglos mediante apuntadores y desplazamientos, sin usar subíndices.
 */

#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <stddef.h>

typedef int (*Comparador)(const void *, const void *);
typedef void (*MostrarElemento)(const void *);

typedef struct Conjunto {
    void *elementos;
    int cantidad;
    int capacidad;
    size_t tamElemento;
    Comparador comparar;
} Conjunto;

/*
 * Inicializa un conjunto vacío y reserva con calloc un arreglo de
 * capacidadInicial posiciones. Regresa 1 si lo consigue; regresa 0 si los
 * argumentos son inválidos, el tamaño se desborda o la reservación falla.
 */
int inicializarConjunto(Conjunto *conjunto, int capacidadInicial,
                        size_t tamElemento, Comparador comparar);

/* Regresa la dirección de una posición utilizada, o NULL si no existe. */
void *obtenerElemento(Conjunto *conjunto, int indice);

/* Búsqueda lineal: regresa el índice del elemento o -1 si no pertenece. */
int buscarElemento(const Conjunto *conjunto, const void *elemento);

/*
 * Copia el elemento al final e incrementa cantidad. Si el arreglo está lleno,
 * duplica su capacidad mediante realloc antes de copiar. Después de vaciar,
 * comienza nuevamente con capacidad 1. Regresa 1 si agrega; 0, sin cambios,
 * si el elemento ya pertenece o no es posible reservar la memoria necesaria.
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

/*
 * Deja cantidad y capacidad en cero, libera el arreglo y deja elementos en
 * NULL. Conserva tamElemento y comparar para que se puedan agregar elementos
 * nuevamente.
 */
void vaciarConjunto(Conjunto *conjunto);

/*
 * Copia los elementos utilizados en su orden y actualiza cantidad del destino.
 * Aumenta la capacidad del destino con realloc si es necesario. Regresa la
 * cantidad copiada, o -1, sin cambios, si no puede reservar memoria.
 */
int copiarConjunto(const Conjunto *origen, Conjunto *destino);

/* Regresa 1 si todo A pertenece a B; 0 en otro caso. El vacío es subconjunto. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB);

/* Regresa 1 si contienen los mismos elementos, sin importar el orden; 0 si no. */
int sonConjuntosIguales(const Conjunto *conjuntoA,
                        const Conjunto *conjuntoB);

/*
 * Estas tres operaciones no modifican las entradas. Aumentan mediante realloc
 * la capacidad del resultado cuando hace falta, actualizan su cantidad y
 * regresan esa cantidad. Si no pueden reservar memoria, regresan -1 sin
 * modificar el resultado. Si un elemento aparece en ambas entradas, se
 * conserva la copia de A.
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
 * Intercambia los registros completos mediante un bloque temporal reservado
 * con malloc y regresa 1. Si los índices coinciden, regresa 1 sin cambios.
 * Si algún índice es inválido o la reservación falla, regresa 0 sin cambios.
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

/* Muestra los elementos con la función recibida, entre llaves y separados por comas. */
void mostrarConjunto(const Conjunto *conjunto, MostrarElemento mostrar);

#endif

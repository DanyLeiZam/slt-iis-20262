/*
 * Archivo: test_practica04.c
 * Pruebas unitarias sin dependencias externas para la práctica 04.
 * Este archivo forma parte de la infraestructura y no debe modificarse.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conjunto.h"
#include "estudiante.h"

static int pruebas;
static int fallas;

#define COMPROBAR(condicion) do { \
    if (!(condicion)) { \
        printf("    %s:%d: falló %s\n", __FILE__, __LINE__, #condicion); \
        return 0; \
    } \
} while (0)

static void registrarResultado(const char nombre[], int pasa) {
    pruebas++;
    if (!pasa)
        fallas++;
    printf("[%s] %s\n", pasa ? "PASA" : "FALLA", nombre);
}

static int mismoEstudiante(const Estudiante *obtenido,
                           const Estudiante *esperado) {
    return obtenido->matricula == esperado->matricula &&
           strcmp(obtenido->nombre.nombres, esperado->nombre.nombres) == 0 &&
           strcmp(obtenido->nombre.apellidos,
                  esperado->nombre.apellidos) == 0 &&
           obtenido->promedio == esperado->promedio;
}

static int mismosEstudiantes(const Conjunto *conjunto,
                             const Estudiante esperados[], int cantidad) {
    if (conjunto->cantidad != cantidad)
        return 0;
    for (int indice = 0; indice < cantidad; indice++) {
        if (!mismoEstudiante(&((const Estudiante *)conjunto->elementos)[indice],
                            &esperados[indice]))
            return 0;
    }
    return 1;
}

static int testInicializarYBuscar(void) {
    Conjunto conjunto;
    Estudiante almacen_conjunto[CAPACIDAD_RESULTADO] = {0};
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante ausente = {.matricula = 999};
    inicializarConjunto(&conjunto, almacen_conjunto, 3,
                       sizeof(Estudiante), compararEstudiantes);
    COMPROBAR(conjunto.cantidad == 0);
    COMPROBAR(conjunto.capacidad == 3);
    COMPROBAR(obtenerElemento(&conjunto, 0) == NULL);
    almacen_conjunto[0] = ana;
    almacen_conjunto[1] = bruno;
    conjunto.cantidad = 2;
    COMPROBAR(buscarElemento(&conjunto, &ana) == 0);
    COMPROBAR(buscarElemento(&conjunto, &bruno) == 1);
    COMPROBAR(buscarElemento(&conjunto, &ausente) == -1);
    return 1;
}

static int testAgregarYCapacidad(void) {
    Conjunto conjunto;
    Estudiante almacen_conjunto[CAPACIDAD_RESULTADO] = {0};
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante repetida = {101, {"Otra", "Persona"}, 10.0f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante carla = {307, {"Carla", "Ruiz"}, 8.8f};
    inicializarConjunto(&conjunto, almacen_conjunto, 2,
                       sizeof(Estudiante), compararEstudiantes);
    COMPROBAR(agregarElemento(&conjunto, &ana) == 1);
    COMPROBAR(agregarElemento(&conjunto, &repetida) == 0);
    COMPROBAR(agregarElemento(&conjunto, &bruno) == 1);
    COMPROBAR(agregarElemento(&conjunto, &carla) == 0);
    COMPROBAR(conjunto.cantidad == 2);
    COMPROBAR(mismoEstudiante(&almacen_conjunto[0], &ana));
    COMPROBAR(mismoEstudiante(&almacen_conjunto[1], &bruno));
    return 1;
}

static int testEliminar(void) {
    Conjunto conjunto;
    Estudiante almacen_conjunto[CAPACIDAD_RESULTADO] = {0};
    Estudiante datos[] = {
        {101, {"Ana", "López"}, 8.5f},
        {205, {"Bruno", "Pérez"}, 9.1f},
        {307, {"Carla", "Ruiz"}, 8.8f}
    };
    Estudiante esperado[] = {datos[0], datos[2]};
    Estudiante ausente = {.matricula = 999};
    inicializarConjunto(&conjunto, almacen_conjunto, 3,
                       sizeof(Estudiante), compararEstudiantes);
    for (int indice = 0; indice < 3; indice++)
        almacen_conjunto[indice] = datos[indice];
    conjunto.cantidad = 3;
    COMPROBAR(eliminarElemento(&conjunto, &datos[1]) == 1);
    COMPROBAR(mismosEstudiantes(&conjunto, esperado, 2));
    COMPROBAR(eliminarElemento(&conjunto, &ausente) == 0);
    COMPROBAR(conjunto.cantidad == 2);
    return 1;
}

static int testReemplazarYVaciar(void) {
    Conjunto conjunto;
    Estudiante almacen_conjunto[CAPACIDAD_RESULTADO] = {0};
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante carla = {307, {"Carla", "Ruiz"}, 8.8f};
    inicializarConjunto(&conjunto, almacen_conjunto, 3,
                       sizeof(Estudiante), compararEstudiantes);
    almacen_conjunto[0] = ana;
    almacen_conjunto[1] = bruno;
    conjunto.cantidad = 2;
    COMPROBAR(reemplazarElemento(&conjunto, &bruno, &carla) == 1);
    COMPROBAR(mismoEstudiante(&almacen_conjunto[1], &carla));
    COMPROBAR(reemplazarElemento(&conjunto, &ana, &carla) == 0);
    COMPROBAR(conjunto.cantidad == 2);
    vaciarConjunto(&conjunto);
    COMPROBAR(conjunto.cantidad == 0);
    COMPROBAR(conjunto.capacidad == 3);
    return 1;
}

static int testCopiaSubconjuntoEIgualdad(void) {
    Conjunto origen;
    Estudiante almacen_origen[CAPACIDAD_RESULTADO] = {0};
    Conjunto copia;
    Estudiante almacen_copia[CAPACIDAD_RESULTADO] = {0};
    Conjunto pequeno;
    Estudiante almacen_pequeno[CAPACIDAD_RESULTADO] = {0};
    Conjunto subconjunto;
    Estudiante almacen_subconjunto[CAPACIDAD_RESULTADO] = {0};
    Estudiante datos[] = {
        {101, {"Ana", "López"}, 8.5f},
        {205, {"Bruno", "Pérez"}, 9.1f},
        {307, {"Carla", "Ruiz"}, 8.8f}
    };
    inicializarConjunto(&origen, almacen_origen, 3,
                       sizeof(Estudiante), compararEstudiantes);
    inicializarConjunto(&copia, almacen_copia, 3,
                       sizeof(Estudiante), compararEstudiantes);
    inicializarConjunto(&pequeno, almacen_pequeno, 2,
                       sizeof(Estudiante), compararEstudiantes);
    inicializarConjunto(&subconjunto, almacen_subconjunto, 2,
                       sizeof(Estudiante), compararEstudiantes);
    for (int indice = 0; indice < 3; indice++)
        almacen_origen[indice] = datos[indice];
    origen.cantidad = 3;
    almacen_subconjunto[0] = datos[0];
    almacen_subconjunto[1] = datos[2];
    subconjunto.cantidad = 2;
    COMPROBAR(copiarConjunto(&origen, &copia) == 3);
    COMPROBAR(sonConjuntosIguales(&origen, &copia) == 1);
    COMPROBAR(esSubconjunto(&subconjunto, &origen) == 1);
    COMPROBAR(esSubconjunto(&origen, &subconjunto) == 0);
    COMPROBAR(copiarConjunto(&origen, &pequeno) == -1);
    COMPROBAR(pequeno.cantidad == 0);
    return 1;
}

static int testOperacionesEntreConjuntos(void) {
    Conjunto a;
    Estudiante almacen_a[CAPACIDAD_RESULTADO] = {0};
    Conjunto b;
    Estudiante almacen_b[CAPACIDAD_RESULTADO] = {0};
    Conjunto resultado;
    Estudiante almacen_resultado[CAPACIDAD_RESULTADO] = {0};
    Conjunto pequeno;
    Estudiante almacen_pequeno[CAPACIDAD_RESULTADO] = {0};
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante carla = {307, {"Carla", "Ruiz"}, 8.8f};
    Estudiante diana = {409, {"Diana", "Soto"}, 9.4f};
    Estudiante unionEsperada[] = {ana, bruno, carla, diana};
    Estudiante interseccionEsperada[] = {bruno};
    Estudiante diferenciaEsperada[] = {ana, carla};
    inicializarConjunto(&a, almacen_a, 3,
                       sizeof(Estudiante), compararEstudiantes);
    inicializarConjunto(&b, almacen_b, 2,
                       sizeof(Estudiante), compararEstudiantes);
    inicializarConjunto(&resultado, almacen_resultado, 5,
                       sizeof(Estudiante), compararEstudiantes);
    inicializarConjunto(&pequeno, almacen_pequeno, 2,
                       sizeof(Estudiante), compararEstudiantes);
    almacen_a[0] = ana;
    almacen_a[1] = bruno;
    almacen_a[2] = carla;
    a.cantidad = 3;
    almacen_b[0] = bruno;
    almacen_b[1] = diana;
    b.cantidad = 2;
    almacen_pequeno[0] = diana;
    pequeno.cantidad = 1;
    COMPROBAR(unirConjuntos(&a, &b, &pequeno) == -1);
    COMPROBAR(pequeno.cantidad == 1);
    COMPROBAR(mismoEstudiante(&almacen_pequeno[0], &diana));
    COMPROBAR(unirConjuntos(&a, &b, &resultado) == 4);
    COMPROBAR(mismosEstudiantes(&resultado, unionEsperada, 4));
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == 1);
    COMPROBAR(mismosEstudiantes(&resultado, interseccionEsperada, 1));
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == 2);
    COMPROBAR(mismosEstudiantes(&resultado, diferenciaEsperada, 2));
    return 1;
}

static int testOperacionesDeEstudiante(void) {
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante mismaMatricula = {101, {"Otra", "Persona"}, 6.0f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    COMPROBAR(compararEstudiantes(&ana, &mismaMatricula) == 0);
    COMPROBAR(compararEstudiantes(&ana, &bruno) != 0);
    actualizarPromedio(&ana, 9.5f);
    COMPROBAR(ana.promedio == 9.5f);
    COMPROBAR(ana.matricula == 101);
    COMPROBAR(strcmp(ana.nombre.nombres, "Ana") == 0);
    return 1;
}

static int compararEnteros(const void *elementoA, const void *elementoB) {
    const int *a = elementoA;
    const int *b = elementoB;
    return (*a > *b) - (*a < *b);
}

static int compararEnterosDescendente(const void *a, const void *b) {
    return compararEnteros(b, a);
}

static int mismosEnteros(const Conjunto *conjunto, const int esperados[],
                        int cantidad) {
    const int *datos = conjunto->elementos;
    if (conjunto->cantidad != cantidad)
        return 0;
    for (int i = 0; i < cantidad; i++) {
        if (datos[i] != esperados[i])
            return 0;
    }
    return 1;
}

static int testComparadorEstudiantes(void) {
    Estudiante menor = {INT_MIN, {"Ana", "López"}, 8.5f};
    Estudiante mayor = {INT_MAX, {"Bruno", "Pérez"}, 9.0f};
    Estudiante mismo = {INT_MIN, {"Otra", "Persona"}, 7.0f};
    COMPROBAR(compararEstudiantes(&menor, &mayor) < 0);
    COMPROBAR(compararEstudiantes(&mayor, &menor) > 0);
    COMPROBAR(compararEstudiantes(&menor, &mismo) == 0);
    COMPROBAR(compararEstudiantes(&mayor, &mayor) == 0);
    return 1;
}

static int testOperacionesEnteros(void) {
    int datos[4] = {90, 91, 92, 93};
    Conjunto conjunto;
    int diez = 10, veinte = 20, treinta = 30, cuarenta = 40;
    int esperados[] = {10, 20};
    inicializarConjunto(&conjunto, datos, 2, sizeof datos[0], compararEnteros);
    COMPROBAR(conjunto.elementos == datos && conjunto.cantidad == 0);
    COMPROBAR(conjunto.capacidad == 2 && conjunto.tamElemento == sizeof(int));
    COMPROBAR(conjunto.comparar == compararEnteros);
    COMPROBAR(datos[0] == 90 && datos[3] == 93);
    COMPROBAR(obtenerElemento(&conjunto, 0) == NULL);
    COMPROBAR(buscarElemento(&conjunto, &diez) == -1);
    COMPROBAR(agregarElemento(&conjunto, &diez) == 1);
    COMPROBAR(agregarElemento(&conjunto, &veinte) == 1);
    COMPROBAR(agregarElemento(&conjunto, &diez) == 0);
    COMPROBAR(agregarElemento(&conjunto, &treinta) == 0);
    COMPROBAR(mismosEnteros(&conjunto, esperados, 2));
    COMPROBAR(datos[2] == 92 && datos[3] == 93);
    COMPROBAR(obtenerElemento(&conjunto, -1) == NULL);
    COMPROBAR(obtenerElemento(&conjunto, 0) == &datos[0]);
    COMPROBAR(obtenerElemento(&conjunto, 1) == &datos[1]);
    COMPROBAR(obtenerElemento(&conjunto, 2) == NULL);
    COMPROBAR(buscarElemento(&conjunto, &veinte) == 1);
    COMPROBAR(reemplazarElemento(&conjunto, &cuarenta, &treinta) == 0);
    COMPROBAR(reemplazarElemento(&conjunto, &diez, &diez) == 0);
    COMPROBAR(reemplazarElemento(&conjunto, &diez, &veinte) == 0);
    COMPROBAR(mismosEnteros(&conjunto, esperados, 2));
    COMPROBAR(reemplazarElemento(&conjunto, &diez, &treinta) == 1);
    COMPROBAR(datos[0] == 30 && datos[1] == 20 && conjunto.cantidad == 2);
    COMPROBAR(eliminarElemento(&conjunto, &cuarenta) == 0);
    COMPROBAR(eliminarElemento(&conjunto, &treinta) == 1);
    COMPROBAR(conjunto.cantidad == 1 && datos[0] == 20);
    COMPROBAR(eliminarElemento(&conjunto, &veinte) == 1);
    COMPROBAR(conjunto.cantidad == 0);
    COMPROBAR(agregarElemento(&conjunto, &cuarenta) == 1);
    vaciarConjunto(&conjunto);
    COMPROBAR(conjunto.cantidad == 0 && datos[0] == 40);
    COMPROBAR(conjunto.capacidad == 2 && conjunto.elementos == datos);
    COMPROBAR(conjunto.tamElemento == sizeof(int));
    COMPROBAR(conjunto.comparar == compararEnteros);
    return 1;
}

static int testCopiaYRelacionesEnteros(void) {
    int datosA[] = {30, 10, 20};
    int datosB[] = {20, 30, 10, 99};
    int datosC[] = {30, 50, 20};
    int datosDestino[] = {70, 80, 90, 100};
    Conjunto a, b, c, destino;
    inicializarConjunto(&a, datosA, 3, sizeof(int), compararEnteros);
    inicializarConjunto(&b, datosB, 4, sizeof(int), compararEnteros);
    inicializarConjunto(&c, datosC, 3, sizeof(int), compararEnteros);
    inicializarConjunto(&destino, datosDestino, 4, sizeof(int), compararEnteros);
    a.cantidad = b.cantidad = c.cantidad = 3;
    destino.cantidad = 4;
    COMPROBAR(sonConjuntosIguales(&a, &b) == 1);
    COMPROBAR(esSubconjunto(&a, &b) == 1);
    COMPROBAR(esSubconjunto(&a, &a) == 1);
    COMPROBAR(sonConjuntosIguales(&a, &c) == 0);
    COMPROBAR(esSubconjunto(&a, &c) == 0);
    COMPROBAR(copiarConjunto(&a, &destino) == 3);
    COMPROBAR(mismosEnteros(&destino, datosA, 3));
    COMPROBAR(datosDestino[3] == 100 && destino.capacidad == 4);
    COMPROBAR(destino.elementos == datosDestino);
    COMPROBAR(destino.tamElemento == sizeof(int));
    COMPROBAR(destino.comparar == compararEnteros);
    destino.capacidad = 2;
    destino.cantidad = 2;
    COMPROBAR(copiarConjunto(&a, &destino) == -1);
    COMPROBAR(destino.cantidad == 2 && datosDestino[0] == 30);
    COMPROBAR(datosDestino[1] == 10 && datosDestino[2] == 20);
    b.cantidad = 0;
    COMPROBAR(esSubconjunto(&b, &a) == 1);
    COMPROBAR(esSubconjunto(&a, &b) == 0);
    COMPROBAR(sonConjuntosIguales(&a, &b) == 0);
    COMPROBAR(copiarConjunto(&b, &destino) == 0);
    COMPROBAR(destino.cantidad == 0 && datosDestino[0] == 30);
    COMPROBAR(sonConjuntosIguales(&b, &destino) == 1);
    COMPROBAR(esSubconjunto(&b, &destino) == 1);
    return 1;
}

static int testOperacionesEntreEnteros(void) {
    int datosA[] = {30, 10, 20};
    int datosB[] = {20, 40};
    int datosR[] = {70, 71, 72, 73, 74};
    int unionEsperada[] = {30, 10, 20, 40};
    int interseccionEsperada[] = {20};
    int diferenciaEsperada[] = {30, 10};
    Conjunto a, b, resultado;
    inicializarConjunto(&a, datosA, 3, sizeof(int), compararEnteros);
    inicializarConjunto(&b, datosB, 2, sizeof(int), compararEnteros);
    inicializarConjunto(&resultado, datosR, 4, sizeof(int), compararEnteros);
    a.cantidad = 3;
    b.cantidad = 2;
    resultado.cantidad = 1;
    COMPROBAR(unirConjuntos(&a, &b, &resultado) == 4);
    COMPROBAR(mismosEnteros(&resultado, unionEsperada, 4));
    COMPROBAR(datosR[4] == 74);
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == 1);
    COMPROBAR(mismosEnteros(&resultado, interseccionEsperada, 1));
    COMPROBAR(datosR[1] == 10 && datosR[2] == 20 && datosR[3] == 40);
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == 2);
    COMPROBAR(mismosEnteros(&resultado, diferenciaEsperada, 2));
    COMPROBAR(datosR[2] == 20 && datosR[4] == 74);
    COMPROBAR(resultado.capacidad == 4 && resultado.elementos == datosR);
    COMPROBAR(resultado.comparar == compararEnteros);
    COMPROBAR(resultado.tamElemento == sizeof(int));
    COMPROBAR(mismosEnteros(&a, (int[]){30, 10, 20}, 3));
    COMPROBAR(mismosEnteros(&b, (int[]){20, 40}, 2));
    b.cantidad = 0;
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == 0);
    COMPROBAR(resultado.cantidad == 0);
    COMPROBAR(unirConjuntos(&b, &a, &resultado) == 3);
    COMPROBAR(mismosEnteros(&resultado, datosA, 3));
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == 3);
    COMPROBAR(diferenciarConjuntos(&a, &a, &resultado) == 0);
    COMPROBAR(resultado.cantidad == 0);
    a.cantidad = 0;
    COMPROBAR(unirConjuntos(&a, &b, &resultado) == 0);
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == 0);
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == 0);
    COMPROBAR(resultado.cantidad == 0);
    return 1;
}

static int testCapacidadInsuficiente(void) {
    int datosA[] = {1, 2, 3};
    int datosB[] = {2, 3, 4};
    int datosR[] = {90, 91, 92, 93};
    Conjunto a, b, resultado;
    inicializarConjunto(&a, datosA, 3, sizeof(int), compararEnteros);
    inicializarConjunto(&b, datosB, 3, sizeof(int), compararEnteros);
    inicializarConjunto(&resultado, datosR, 1, sizeof(int), compararEnteros);
    a.cantidad = b.cantidad = 3;
    resultado.cantidad = 1;
    COMPROBAR(unirConjuntos(&a, &b, &resultado) == -1);
    COMPROBAR(resultado.cantidad == 1 && datosR[0] == 90);
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == -1);
    COMPROBAR(resultado.cantidad == 1 && datosR[0] == 90);
    COMPROBAR(datosR[1] == 91 && datosR[2] == 92 && datosR[3] == 93);
    resultado.capacidad = resultado.cantidad = 0;
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == -1);
    COMPROBAR(resultado.cantidad == 0 && datosR[0] == 90);
    COMPROBAR(agregarElemento(&resultado, &datosA[0]) == 0);
    COMPROBAR(datosR[1] == 91 && datosR[2] == 92 && datosR[3] == 93);
    return 1;
}

static int testIntercambioYOrdenEnteros(void) {
    int datos[] = {30, 10, 20, 99};
    Conjunto conjunto;
    inicializarConjunto(&conjunto, datos, 4, sizeof(int), compararEnteros);
    conjunto.cantidad = 3;
    COMPROBAR(intercambiarElementos(&conjunto, -1, 1) == 0);
    COMPROBAR(intercambiarElementos(&conjunto, 1, 3) == 0);
    COMPROBAR(intercambiarElementos(&conjunto, 3, 1) == 0);
    COMPROBAR(intercambiarElementos(&conjunto, 1, -1) == 0);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){30, 10, 20}, 3));
    COMPROBAR(intercambiarElementos(&conjunto, 0, 0) == 1);
    COMPROBAR(intercambiarElementos(&conjunto, 0, 2) == 1);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){20, 10, 30}, 3));
    ordenarConjunto(&conjunto);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){10, 20, 30}, 3));
    COMPROBAR(datos[3] == 99 && conjunto.capacidad == 4);
    ordenarConjunto(&conjunto);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){10, 20, 30}, 3));
    conjunto.comparar = compararEnterosDescendente;
    ordenarConjunto(&conjunto);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){30, 20, 10}, 3));
    COMPROBAR(buscarElementoOrdenado(&conjunto, &(int){30}) == 0);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &(int){10}) == 2);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &(int){25}) == -1);
    conjunto.cantidad = 1;
    ordenarConjunto(&conjunto);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){30}, 1));
    COMPROBAR(datos[1] == 20 && datos[2] == 10 && datos[3] == 99);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &(int){30}) == 0);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &(int){20}) == -1);
    conjunto.cantidad = 0;
    ordenarConjunto(&conjunto);
    COMPROBAR(conjunto.cantidad == 0 && datos[0] == 30);
    COMPROBAR(intercambiarElementos(&conjunto, 0, 0) == 0);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &(int){30}) == -1);
    return 1;
}

static int testBusquedaBinaria(void) {
    int datos[CAPACIDAD_RESULTADO];
    Conjunto conjunto;
    inicializarConjunto(&conjunto, datos, CAPACIDAD_RESULTADO,
                       sizeof(int), compararEnteros);
    for (int i = 0; i < CAPACIDAD_RESULTADO; i++)
        datos[i] = 3 * i;
    conjunto.cantidad = CAPACIDAD_RESULTADO;
    for (int valor = -1; valor <= 3 * CAPACIDAD_RESULTADO; valor++) {
        int esperado = valor >= 0 && valor % 3 == 0 &&
                       valor < 3 * CAPACIDAD_RESULTADO ? valor / 3 : -1;
        COMPROBAR(buscarElementoOrdenado(&conjunto, &valor) == esperado);
        COMPROBAR(buscarElemento(&conjunto, &valor) == esperado);
    }
    COMPROBAR(conjunto.cantidad == CAPACIDAD_RESULTADO);
    for (int i = 0; i < CAPACIDAD_RESULTADO; i++)
        COMPROBAR(datos[i] == 3 * i);
    return 1;
}

static int testOrdenYBusquedaEstudiantes(void) {
    Estudiante datos[] = {
        {307, {"Carla", "Ruiz"}, 8.8f},
        {101, {"Ana", "López"}, 8.5f},
        {205, {"Bruno", "Pérez"}, 9.1f},
        {999, {"Fuera", "Del conjunto"}, 0.0f}
    };
    Estudiante esperado[] = {datos[1], datos[2], datos[0]};
    Estudiante sinUsar = datos[3];
    Estudiante criterio = {.matricula = 205};
    Conjunto conjunto;
    inicializarConjunto(&conjunto, datos, 4, sizeof(Estudiante),
                       compararEstudiantes);
    conjunto.cantidad = 3;
    COMPROBAR(obtenerElemento(&conjunto, 1) == &datos[1]);
    COMPROBAR(intercambiarElementos(&conjunto, 0, 1) == 1);
    COMPROBAR(mismoEstudiante(&datos[0], &esperado[0]));
    COMPROBAR(mismoEstudiante(&datos[1], &esperado[2]));
    ordenarConjunto(&conjunto);
    COMPROBAR(mismosEstudiantes(&conjunto, esperado, 3));
    COMPROBAR(mismoEstudiante(&datos[3], &sinUsar));
    COMPROBAR(buscarElementoOrdenado(&conjunto, &criterio) == 1);
    COMPROBAR(buscarElemento(&conjunto, &criterio) == 1);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &esperado[0]) == 0);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &esperado[2]) == 2);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &sinUsar) == -1);
    COMPROBAR(mismosEstudiantes(&conjunto, esperado, 3));
    return 1;
}

static int testIdentidadYConservacionDeRegistros(void) {
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante otra = {101, {"Otra", "Persona"}, 10.0f};
    Estudiante datosA[] = {ana};
    Estudiante datosB[] = {otra};
    Estudiante datosR[2] = {0};
    Conjunto a, b, resultado;
    inicializarConjunto(&a, datosA, 1, sizeof(Estudiante), compararEstudiantes);
    inicializarConjunto(&b, datosB, 1, sizeof(Estudiante), compararEstudiantes);
    inicializarConjunto(&resultado, datosR, 2, sizeof(Estudiante), compararEstudiantes);
    a.cantidad = b.cantidad = 1;
    COMPROBAR(sonConjuntosIguales(&a, &b) == 1);
    COMPROBAR(esSubconjunto(&a, &b) == 1);
    COMPROBAR(reemplazarElemento(&a, &ana, &otra) == 0);
    COMPROBAR(mismoEstudiante(&datosA[0], &ana));
    COMPROBAR(unirConjuntos(&a, &b, &resultado) == 1);
    COMPROBAR(mismosEstudiantes(&resultado, datosA, 1));
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == 1);
    COMPROBAR(mismosEstudiantes(&resultado, datosA, 1));
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == 0);
    COMPROBAR(resultado.cantidad == 0);
    COMPROBAR(mismoEstudiante(&datosA[0], &ana));
    COMPROBAR(mismoEstudiante(&datosB[0], &otra));
    return 1;
}

static void registrarPruebasNuevas(void) {
    registrarResultado("comparación de estudiantes: menor, igual y mayor",
                       testComparadorEstudiantes());
    registrarResultado("operaciones con enteros", testOperacionesEnteros());
    registrarResultado("copia y relaciones entre conjuntos de enteros",
                       testCopiaYRelacionesEnteros());
    registrarResultado("unión, intersección y diferencia de enteros",
                       testOperacionesEntreEnteros());
    registrarResultado("capacidad insuficiente sin cambios",
                       testCapacidadInsuficiente());
    registrarResultado("intercambio y ordenamiento de enteros",
                       testIntercambioYOrdenEnteros());
    registrarResultado("búsqueda binaria: posiciones y ausencias",
                       testBusquedaBinaria());
    registrarResultado("ordenamiento y búsqueda de estudiantes",
                       testOrdenYBusquedaEstudiantes());
    registrarResultado("identidad por matrícula y conservación de registros",
                       testIdentidadYConservacionDeRegistros());
}

int main(void) {
    registrarPruebasNuevas();
    registrarResultado("inicializar y buscar", testInicializarYBuscar());
    registrarResultado("agregar y respetar capacidad",
                       testAgregarYCapacidad());
    registrarResultado("eliminar y conservar el orden", testEliminar());
    registrarResultado("reemplazar y vaciar", testReemplazarYVaciar());
    registrarResultado("copiar, subconjunto e igualdad",
                       testCopiaSubconjuntoEIgualdad());
    registrarResultado("unión, intersección y diferencia",
                       testOperacionesEntreConjuntos());
    registrarResultado("operaciones propias de estudiante",
                       testOperacionesDeEstudiante());

    printf("\nPruebas: %d; pasaron: %d; fallaron: %d.\n",
           pruebas, pruebas - fallas, fallas);
    return fallas == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

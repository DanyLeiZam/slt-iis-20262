/*
 * Archivo: test_practica05.c
 * Pruebas unitarias sin dependencias externas para la práctica 05.
 * Este archivo forma parte de la infraestructura y no debe modificarse.
 */

#include <limits.h>
#include <stdint.h>
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

static int compararEnteros(const void *elementoA, const void *elementoB) {
    const int *a = elementoA;
    const int *b = elementoB;
    return (*a > *b) - (*a < *b);
}

static void liberarInfraestructura(Conjunto *conjunto) {
    free(conjunto->elementos);
    conjunto->elementos = NULL;
    conjunto->cantidad = 0;
    conjunto->capacidad = 0;
}

static int prepararEnteros(Conjunto *conjunto, int capacidad,
                           const int valores[], int cantidad) {
    if (capacidad < cantidad)
        return 0;
    if (!inicializarConjunto(conjunto, capacidad, sizeof(int), compararEnteros))
        return 0;
    int *datos = conjunto->elementos;
    for (int indice = 0; indice < cantidad; indice++)
        *(datos + indice) = *(valores + indice);
    conjunto->cantidad = cantidad;
    return 1;
}

static int prepararEstudiantes(Conjunto *conjunto, int capacidad,
                               const Estudiante valores[], int cantidad) {
    if (capacidad < cantidad)
        return 0;
    if (!inicializarConjunto(conjunto, capacidad, sizeof(Estudiante),
                             compararEstudiantes))
        return 0;
    Estudiante *datos = conjunto->elementos;
    for (int indice = 0; indice < cantidad; indice++)
        *(datos + indice) = *(valores + indice);
    conjunto->cantidad = cantidad;
    return 1;
}

static int mismosEnteros(const Conjunto *conjunto, const int esperados[],
                         int cantidad) {
    const int *datos = conjunto->elementos;
    if (conjunto->cantidad != cantidad)
        return 0;
    for (int indice = 0; indice < cantidad; indice++) {
        if (*(datos + indice) != *(esperados + indice))
            return 0;
    }
    return 1;
}

static int mismoEstudiante(const Estudiante *obtenido,
                           const Estudiante *esperado) {
    return obtenido->matricula == esperado->matricula &&
           strcmp(obtenido->nombre.nombres, esperado->nombre.nombres) == 0 &&
           strcmp(obtenido->nombre.apellidos,
                  esperado->nombre.apellidos) == 0 &&
           obtenido->promedio == esperado->promedio;
}

/* Pruebas de inicializarConjunto. */

static int testInicializarConjuntoReservaEInicializa(void) {
    Conjunto conjunto;
    COMPROBAR(inicializarConjunto(&conjunto, 3, sizeof(int),
                                  compararEnteros) == 1);
    COMPROBAR(conjunto.elementos != NULL);
    COMPROBAR(conjunto.cantidad == 0);
    COMPROBAR(conjunto.capacidad == 3);
    COMPROBAR(conjunto.tamElemento == sizeof(int));
    COMPROBAR(conjunto.comparar == compararEnteros);
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testInicializarConjuntoUsaCalloc(void) {
    Conjunto conjunto;
    COMPROBAR(inicializarConjunto(&conjunto, 3, sizeof(int),
                                  compararEnteros) == 1);
    const unsigned char *bytes = conjunto.elementos;
    for (size_t indice = 0; indice < 3 * sizeof(int); indice++)
        COMPROBAR(*(bytes + indice) == 0);
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testInicializarConjuntoRechazaArgumentosInvalidos(void) {
    Conjunto conjunto = {0};
    COMPROBAR(inicializarConjunto(&conjunto, 0, sizeof(int),
                                  compararEnteros) == 0);
    COMPROBAR(conjunto.elementos == NULL && conjunto.capacidad == 0);
    COMPROBAR(inicializarConjunto(&conjunto, -1, sizeof(int),
                                  compararEnteros) == 0);
    COMPROBAR(inicializarConjunto(&conjunto, 1, 0, compararEnteros) == 0);
    COMPROBAR(inicializarConjunto(&conjunto, 1, sizeof(int), NULL) == 0);
    COMPROBAR(inicializarConjunto(NULL, 1, sizeof(int), compararEnteros) == 0);
    COMPROBAR(inicializarConjunto(&conjunto, INT_MAX, SIZE_MAX,
                                  compararEnteros) == 0);
    return 1;
}

/* Pruebas de agregarElemento. */

static int testAgregarElementoEvitaRepetidos(void) {
    Conjunto conjunto;
    int diez = 10;
    COMPROBAR(prepararEnteros(&conjunto, 2, NULL, 0));
    COMPROBAR(agregarElemento(&conjunto, &diez) == 1);
    COMPROBAR(agregarElemento(&conjunto, &diez) == 0);
    COMPROBAR(conjunto.capacidad == 2);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){10}, 1));
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testAgregarElementoCreceYConserva(void) {
    Conjunto conjunto;
    int valores[] = {10, 20, 30, 40, 50};
    COMPROBAR(prepararEnteros(&conjunto, 1, NULL, 0));
    for (int indice = 0; indice < 5; indice++)
        COMPROBAR(agregarElemento(&conjunto, valores + indice) == 1);
    COMPROBAR(conjunto.capacidad == 8);
    COMPROBAR(mismosEnteros(&conjunto, valores, 5));
    liberarInfraestructura(&conjunto);
    return 1;
}

/* Pruebas de eliminarElemento. */

static int testEliminarElementoConservaOrden(void) {
    Conjunto conjunto;
    int valores[] = {10, 20, 30};
    int veinte = 20;
    COMPROBAR(prepararEnteros(&conjunto, 3, valores, 3));
    COMPROBAR(eliminarElemento(&conjunto, &veinte) == 1);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){10, 30}, 2));
    COMPROBAR(conjunto.capacidad == 3);
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testEliminarElementoAusenteNoModifica(void) {
    Conjunto conjunto;
    int valores[] = {10, 20};
    int ausente = 99;
    COMPROBAR(prepararEnteros(&conjunto, 2, valores, 2));
    COMPROBAR(eliminarElemento(&conjunto, &ausente) == 0);
    COMPROBAR(mismosEnteros(&conjunto, valores, 2));
    liberarInfraestructura(&conjunto);
    return 1;
}

/* Pruebas de reemplazarElemento. */

static int testReemplazarElementoConservaPosicion(void) {
    Conjunto conjunto;
    int valores[] = {10, 20, 30};
    int veinte = 20, cuarenta = 40;
    COMPROBAR(prepararEnteros(&conjunto, 3, valores, 3));
    COMPROBAR(reemplazarElemento(&conjunto, &veinte, &cuarenta) == 1);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){10, 40, 30}, 3));
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testReemplazarElementoRechazaCasosInvalidos(void) {
    Conjunto conjunto;
    int valores[] = {10, 20, 30};
    int diez = 10, veinte = 20, ausente = 99;
    COMPROBAR(prepararEnteros(&conjunto, 3, valores, 3));
    COMPROBAR(reemplazarElemento(&conjunto, &ausente, &diez) == 0);
    COMPROBAR(reemplazarElemento(&conjunto, &veinte, &diez) == 0);
    COMPROBAR(mismosEnteros(&conjunto, valores, 3));
    liberarInfraestructura(&conjunto);
    return 1;
}

/* Pruebas de vaciarConjunto. */

static int testVaciarConjuntoLiberaYReinicia(void) {
    Conjunto conjunto;
    int valores[] = {10, 20};
    COMPROBAR(prepararEnteros(&conjunto, 2, valores, 2));
    Comparador compararAnterior = conjunto.comparar;
    size_t tamAnterior = conjunto.tamElemento;
    vaciarConjunto(&conjunto);
    COMPROBAR(conjunto.elementos == NULL);
    COMPROBAR(conjunto.cantidad == 0 && conjunto.capacidad == 0);
    COMPROBAR(conjunto.comparar == compararAnterior);
    COMPROBAR(conjunto.tamElemento == tamAnterior);
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testVaciarConjuntoPermiteVolverAAgregar(void) {
    Conjunto conjunto;
    int diez = 10, veinte = 20;
    COMPROBAR(prepararEnteros(&conjunto, 1, &diez, 1));
    vaciarConjunto(&conjunto);
    COMPROBAR(agregarElemento(&conjunto, &veinte) == 1);
    COMPROBAR(conjunto.capacidad == 1);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){20}, 1));
    liberarInfraestructura(&conjunto);
    return 1;
}

/* Pruebas de copiarConjunto. */

static int testCopiarConjuntoRedimensionaDestino(void) {
    Conjunto origen;
    Conjunto destino;
    int valores[] = {5, 10, 15, 20};
    COMPROBAR(prepararEnteros(&origen, 4, valores, 4));
    COMPROBAR(prepararEnteros(&destino, 1, NULL, 0));
    COMPROBAR(copiarConjunto(&origen, &destino) == 4);
    COMPROBAR(destino.capacidad >= 4);
    COMPROBAR(mismosEnteros(&destino, valores, 4));
    liberarInfraestructura(&origen);
    liberarInfraestructura(&destino);
    return 1;
}

static int testCopiarConjuntoEsIndependienteYAdmiteVacio(void) {
    Conjunto origen;
    Conjunto destino;
    int valores[] = {10, 20};
    COMPROBAR(prepararEnteros(&origen, 2, valores, 2));
    COMPROBAR(prepararEnteros(&destino, 2, NULL, 0));
    COMPROBAR(copiarConjunto(&origen, &destino) == 2);
    *(int *)obtenerElemento(&origen, 0) = 100;
    COMPROBAR(*(int *)obtenerElemento(&destino, 0) == 10);
    origen.cantidad = 0;
    COMPROBAR(copiarConjunto(&origen, &destino) == 0);
    COMPROBAR(destino.cantidad == 0);
    liberarInfraestructura(&origen);
    liberarInfraestructura(&destino);
    return 1;
}

/* Pruebas de esSubconjunto. */

static int testEsSubconjuntoReconocePertenencia(void) {
    Conjunto conjunto;
    Conjunto subconjunto;
    Conjunto vacio;
    int valores[] = {10, 20, 30};
    int valoresSubconjunto[] = {30, 10};
    COMPROBAR(prepararEnteros(&conjunto, 3, valores, 3));
    COMPROBAR(prepararEnteros(&subconjunto, 2, valoresSubconjunto, 2));
    COMPROBAR(prepararEnteros(&vacio, 1, NULL, 0));
    COMPROBAR(esSubconjunto(&subconjunto, &conjunto) == 1);
    COMPROBAR(esSubconjunto(&vacio, &conjunto) == 1);
    liberarInfraestructura(&conjunto);
    liberarInfraestructura(&subconjunto);
    liberarInfraestructura(&vacio);
    return 1;
}

static int testEsSubconjuntoDetectaElementoAusente(void) {
    Conjunto conjunto;
    Conjunto candidato;
    int valores[] = {10, 20};
    int otros[] = {10, 99};
    COMPROBAR(prepararEnteros(&conjunto, 2, valores, 2));
    COMPROBAR(prepararEnteros(&candidato, 2, otros, 2));
    COMPROBAR(esSubconjunto(&candidato, &conjunto) == 0);
    liberarInfraestructura(&conjunto);
    liberarInfraestructura(&candidato);
    return 1;
}

/* Pruebas de sonConjuntosIguales. */

static int testSonConjuntosIgualesIgnoraOrden(void) {
    Conjunto a;
    Conjunto b;
    int valoresA[] = {10, 20, 30};
    int valoresB[] = {30, 10, 20};
    COMPROBAR(prepararEnteros(&a, 3, valoresA, 3));
    COMPROBAR(prepararEnteros(&b, 3, valoresB, 3));
    COMPROBAR(sonConjuntosIguales(&a, &b) == 1);
    liberarInfraestructura(&a);
    liberarInfraestructura(&b);
    return 1;
}

static int testSonConjuntosIgualesDetectaDiferencias(void) {
    Conjunto a;
    Conjunto b;
    Conjunto c;
    int valoresA[] = {10, 20};
    int valoresB[] = {10, 99};
    int valoresC[] = {10};
    COMPROBAR(prepararEnteros(&a, 2, valoresA, 2));
    COMPROBAR(prepararEnteros(&b, 2, valoresB, 2));
    COMPROBAR(prepararEnteros(&c, 1, valoresC, 1));
    COMPROBAR(sonConjuntosIguales(&a, &b) == 0);
    COMPROBAR(sonConjuntosIguales(&a, &c) == 0);
    liberarInfraestructura(&a);
    liberarInfraestructura(&b);
    liberarInfraestructura(&c);
    return 1;
}

/* Pruebas de unirConjuntos. */

static int testUnirConjuntosRedimensionaYConservaOrden(void) {
    Conjunto a;
    Conjunto b;
    Conjunto resultado;
    int valoresA[] = {1, 2, 3};
    int valoresB[] = {2, 4};
    COMPROBAR(prepararEnteros(&a, 3, valoresA, 3));
    COMPROBAR(prepararEnteros(&b, 2, valoresB, 2));
    COMPROBAR(prepararEnteros(&resultado, 1, NULL, 0));
    COMPROBAR(unirConjuntos(&a, &b, &resultado) == 4);
    COMPROBAR(resultado.capacidad >= 4);
    COMPROBAR(mismosEnteros(&resultado, (int[]){1, 2, 3, 4}, 4));
    liberarInfraestructura(&a);
    liberarInfraestructura(&b);
    liberarInfraestructura(&resultado);
    return 1;
}

static int testUnirConjuntosConVacioNoDuplica(void) {
    Conjunto a;
    Conjunto vacio;
    Conjunto resultado;
    int valores[] = {1, 2};
    COMPROBAR(prepararEnteros(&a, 2, valores, 2));
    COMPROBAR(prepararEnteros(&vacio, 1, NULL, 0));
    COMPROBAR(prepararEnteros(&resultado, 1, NULL, 0));
    COMPROBAR(unirConjuntos(&a, &vacio, &resultado) == 2);
    COMPROBAR(mismosEnteros(&resultado, valores, 2));
    liberarInfraestructura(&a);
    liberarInfraestructura(&vacio);
    liberarInfraestructura(&resultado);
    return 1;
}

/* Pruebas de intersectarConjuntos. */

static int testIntersectarConjuntosConservaOrden(void) {
    Conjunto a;
    Conjunto b;
    Conjunto resultado;
    int valoresA[] = {3, 1, 2};
    int valoresB[] = {2, 3, 4};
    COMPROBAR(prepararEnteros(&a, 3, valoresA, 3));
    COMPROBAR(prepararEnteros(&b, 3, valoresB, 3));
    COMPROBAR(prepararEnteros(&resultado, 1, NULL, 0));
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == 2);
    COMPROBAR(resultado.capacidad >= 2);
    COMPROBAR(mismosEnteros(&resultado, (int[]){3, 2}, 2));
    liberarInfraestructura(&a);
    liberarInfraestructura(&b);
    liberarInfraestructura(&resultado);
    return 1;
}

static int testIntersectarConjuntosDisjuntosProduceVacio(void) {
    Conjunto a;
    Conjunto b;
    Conjunto resultado;
    int valoresA[] = {1, 2};
    int valoresB[] = {3, 4};
    int anterior = 99;
    COMPROBAR(prepararEnteros(&a, 2, valoresA, 2));
    COMPROBAR(prepararEnteros(&b, 2, valoresB, 2));
    COMPROBAR(prepararEnteros(&resultado, 1, &anterior, 1));
    COMPROBAR(intersectarConjuntos(&a, &b, &resultado) == 0);
    COMPROBAR(resultado.cantidad == 0);
    liberarInfraestructura(&a);
    liberarInfraestructura(&b);
    liberarInfraestructura(&resultado);
    return 1;
}

/* Pruebas de diferenciarConjuntos. */

static int testDiferenciarConjuntosConservaOrden(void) {
    Conjunto a;
    Conjunto b;
    Conjunto resultado;
    int valoresA[] = {3, 1, 2, 4};
    int valoresB[] = {2, 3};
    COMPROBAR(prepararEnteros(&a, 4, valoresA, 4));
    COMPROBAR(prepararEnteros(&b, 2, valoresB, 2));
    COMPROBAR(prepararEnteros(&resultado, 1, NULL, 0));
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == 2);
    COMPROBAR(resultado.capacidad >= 2);
    COMPROBAR(mismosEnteros(&resultado, (int[]){1, 4}, 2));
    liberarInfraestructura(&a);
    liberarInfraestructura(&b);
    liberarInfraestructura(&resultado);
    return 1;
}

static int testDiferenciarConjuntosContenidoProduceVacio(void) {
    Conjunto a;
    Conjunto b;
    Conjunto resultado;
    int valoresA[] = {1, 2};
    int valoresB[] = {1, 2, 3};
    COMPROBAR(prepararEnteros(&a, 2, valoresA, 2));
    COMPROBAR(prepararEnteros(&b, 3, valoresB, 3));
    COMPROBAR(prepararEnteros(&resultado, 1, NULL, 0));
    COMPROBAR(diferenciarConjuntos(&a, &b, &resultado) == 0);
    COMPROBAR(resultado.cantidad == 0);
    liberarInfraestructura(&a);
    liberarInfraestructura(&b);
    liberarInfraestructura(&resultado);
    return 1;
}

/* Pruebas de intercambiarElementos. */

static int testIntercambiarElementosMueveRegistrosCompletos(void) {
    Conjunto conjunto;
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante valores[] = {ana, bruno};
    COMPROBAR(prepararEstudiantes(&conjunto, 2, valores, 2));
    COMPROBAR(intercambiarElementos(&conjunto, 0, 1) == 1);
    const Estudiante *datos = conjunto.elementos;
    COMPROBAR(mismoEstudiante(datos, &bruno));
    COMPROBAR(mismoEstudiante(datos + 1, &ana));
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testIntercambiarElementosValidaIndices(void) {
    Conjunto conjunto;
    int valores[] = {10, 20};
    COMPROBAR(prepararEnteros(&conjunto, 2, valores, 2));
    COMPROBAR(intercambiarElementos(&conjunto, 0, 0) == 1);
    COMPROBAR(intercambiarElementos(&conjunto, -1, 1) == 0);
    COMPROBAR(intercambiarElementos(&conjunto, 0, 2) == 0);
    COMPROBAR(mismosEnteros(&conjunto, valores, 2));
    liberarInfraestructura(&conjunto);
    return 1;
}

/* Pruebas de ordenarConjunto. */

static int testOrdenarConjuntoOrdenaEnteros(void) {
    Conjunto conjunto;
    int valores[] = {40, 10, 30, 20};
    COMPROBAR(prepararEnteros(&conjunto, 4, valores, 4));
    ordenarConjunto(&conjunto);
    COMPROBAR(mismosEnteros(&conjunto, (int[]){10, 20, 30, 40}, 4));
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testOrdenarConjuntoConservaEstudiantesCompletos(void) {
    Conjunto conjunto;
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    Estudiante carla = {307, {"Carla", "Ruiz"}, 8.8f};
    Estudiante valores[] = {carla, ana, bruno};
    COMPROBAR(prepararEstudiantes(&conjunto, 3, valores, 3));
    ordenarConjunto(&conjunto);
    const Estudiante *datos = conjunto.elementos;
    COMPROBAR(mismoEstudiante(datos, &ana));
    COMPROBAR(mismoEstudiante(datos + 1, &bruno));
    COMPROBAR(mismoEstudiante(datos + 2, &carla));
    liberarInfraestructura(&conjunto);
    return 1;
}

/* Pruebas de buscarElementoOrdenado. */

static int testBuscarElementoOrdenadoEncuentraExtremosYCentro(void) {
    Conjunto conjunto;
    int valores[] = {10, 20, 30, 40, 50};
    int diez = 10, treinta = 30, cincuenta = 50;
    COMPROBAR(prepararEnteros(&conjunto, 5, valores, 5));
    COMPROBAR(buscarElementoOrdenado(&conjunto, &diez) == 0);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &treinta) == 2);
    COMPROBAR(buscarElementoOrdenado(&conjunto, &cincuenta) == 4);
    liberarInfraestructura(&conjunto);
    return 1;
}

static int testBuscarElementoOrdenadoDetectaAusenciaYVacio(void) {
    Conjunto conjunto;
    Conjunto vacio;
    int valores[] = {10, 20, 30};
    int ausente = 99;
    COMPROBAR(prepararEnteros(&conjunto, 3, valores, 3));
    COMPROBAR(prepararEnteros(&vacio, 1, NULL, 0));
    COMPROBAR(buscarElementoOrdenado(&conjunto, &ausente) == -1);
    COMPROBAR(buscarElementoOrdenado(&vacio, &ausente) == -1);
    liberarInfraestructura(&conjunto);
    liberarInfraestructura(&vacio);
    return 1;
}

/* Pruebas de compararEstudiantes. */

static int testCompararEstudiantesUsaSoloMatricula(void) {
    Estudiante ana = {101, {"Ana", "López"}, 8.5f};
    Estudiante otra = {101, {"Otra", "Persona"}, 6.0f};
    Estudiante bruno = {205, {"Bruno", "Pérez"}, 9.1f};
    COMPROBAR(compararEstudiantes(&ana, &otra) == 0);
    COMPROBAR(compararEstudiantes(&ana, &bruno) < 0);
    COMPROBAR(compararEstudiantes(&bruno, &ana) > 0);
    return 1;
}

static int testCompararEstudiantesEvitaDesbordamiento(void) {
    Estudiante menor = {INT_MIN, {"Ana", "López"}, 8.5f};
    Estudiante mayor = {INT_MAX, {"Bruno", "Pérez"}, 9.1f};
    COMPROBAR(compararEstudiantes(&menor, &mayor) < 0);
    COMPROBAR(compararEstudiantes(&mayor, &menor) > 0);
    COMPROBAR(compararEstudiantes(&menor, &menor) == 0);
    return 1;
}

int main(void) {
    registrarResultado("inicializarConjunto: reservar e inicializar",
                       testInicializarConjuntoReservaEInicializa());
    registrarResultado("inicializarConjunto: usar calloc",
                       testInicializarConjuntoUsaCalloc());
    registrarResultado("inicializarConjunto: argumentos inválidos",
                       testInicializarConjuntoRechazaArgumentosInvalidos());

    registrarResultado("agregarElemento: evitar repetidos",
                       testAgregarElementoEvitaRepetidos());
    registrarResultado("agregarElemento: crecer y conservar",
                       testAgregarElementoCreceYConserva());

    registrarResultado("eliminarElemento: conservar orden",
                       testEliminarElementoConservaOrden());
    registrarResultado("eliminarElemento: elemento ausente",
                       testEliminarElementoAusenteNoModifica());

    registrarResultado("reemplazarElemento: conservar posición",
                       testReemplazarElementoConservaPosicion());
    registrarResultado("reemplazarElemento: casos inválidos",
                       testReemplazarElementoRechazaCasosInvalidos());

    registrarResultado("vaciarConjunto: liberar y reiniciar",
                       testVaciarConjuntoLiberaYReinicia());
    registrarResultado("vaciarConjunto: volver a agregar",
                       testVaciarConjuntoPermiteVolverAAgregar());

    registrarResultado("copiarConjunto: redimensionar destino",
                       testCopiarConjuntoRedimensionaDestino());
    registrarResultado("copiarConjunto: independencia y origen vacío",
                       testCopiarConjuntoEsIndependienteYAdmiteVacio());

    registrarResultado("esSubconjunto: pertenencia y vacío",
                       testEsSubconjuntoReconocePertenencia());
    registrarResultado("esSubconjunto: elemento ausente",
                       testEsSubconjuntoDetectaElementoAusente());

    registrarResultado("sonConjuntosIguales: ignorar orden",
                       testSonConjuntosIgualesIgnoraOrden());
    registrarResultado("sonConjuntosIguales: detectar diferencias",
                       testSonConjuntosIgualesDetectaDiferencias());

    registrarResultado("unirConjuntos: redimensionar y conservar orden",
                       testUnirConjuntosRedimensionaYConservaOrden());
    registrarResultado("unirConjuntos: conjunto vacío",
                       testUnirConjuntosConVacioNoDuplica());

    registrarResultado("intersectarConjuntos: conservar orden",
                       testIntersectarConjuntosConservaOrden());
    registrarResultado("intersectarConjuntos: conjuntos disjuntos",
                       testIntersectarConjuntosDisjuntosProduceVacio());

    registrarResultado("diferenciarConjuntos: conservar orden",
                       testDiferenciarConjuntosConservaOrden());
    registrarResultado("diferenciarConjuntos: resultado vacío",
                       testDiferenciarConjuntosContenidoProduceVacio());

    registrarResultado("intercambiarElementos: registros completos",
                       testIntercambiarElementosMueveRegistrosCompletos());
    registrarResultado("intercambiarElementos: validar índices",
                       testIntercambiarElementosValidaIndices());

    registrarResultado("ordenarConjunto: enteros",
                       testOrdenarConjuntoOrdenaEnteros());
    registrarResultado("ordenarConjunto: estudiantes completos",
                       testOrdenarConjuntoConservaEstudiantesCompletos());

    registrarResultado("buscarElementoOrdenado: extremos y centro",
                       testBuscarElementoOrdenadoEncuentraExtremosYCentro());
    registrarResultado("buscarElementoOrdenado: ausencia y vacío",
                       testBuscarElementoOrdenadoDetectaAusenciaYVacio());

    registrarResultado("compararEstudiantes: usar sólo matrícula",
                       testCompararEstudiantesUsaSoloMatricula());
    registrarResultado("compararEstudiantes: evitar desbordamiento",
                       testCompararEstudiantesEvitaDesbordamiento());

    printf("\nResumen: %d pruebas, %d fallas.\n", pruebas, fallas);
    return fallas == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

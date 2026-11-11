/* Pruebas unitarias de persistencia para la práctica 06. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conjunto.h"
#include "estudiante.h"
#include "persistencia.h"

#define RUTA_CARGA "build/prueba_carga.csv"
#define RUTA_GUARDADO "build/prueba_guardado.csv"
#define RUTA_INVALIDA "build/prueba_invalida.csv"
#define RUTA_INEXISTENTE "build/no_existe.csv"

#define COMPROBAR(condicion)                                                   \
    do {                                                                       \
        if (!(condicion)) {                                                    \
            printf("Falla en %s, línea %d: %s\n",                            \
                   __func__, __LINE__, #condicion);                            \
            return 0;                                                          \
        }                                                                      \
    } while (0)

static int inicializarEstudiantes(Conjunto *estudiantes) {
    return inicializarConjunto(estudiantes, 1, sizeof(Estudiante),
                               compararEstudiantes);
}

static int escribirTexto(const char *ruta, const char *contenido) {
    FILE *archivo = fopen(ruta, "w");
    if (archivo == NULL)
        return 0;
    int escrito = fputs(contenido, archivo) != EOF;
    return fclose(archivo) == 0 && escrito;
}

static int leerTexto(const char *ruta, char *contenido, size_t capacidad) {
    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
        return 0;
    size_t leidos = fread(contenido, 1, capacidad - 1, archivo);
    *(contenido + leidos) = '\0';
    int valido = !ferror(archivo);
    return fclose(archivo) == 0 && valido;
}

static int testCargaArchivoVacio(void) {
    Conjunto estudiantes;
    COMPROBAR(escribirTexto(RUTA_CARGA,
        "matricula,nombres,apellidos,promedio\n"));
    COMPROBAR(inicializarEstudiantes(&estudiantes));
    COMPROBAR(cargarEstudiantes(RUTA_CARGA, &estudiantes) == 0);
    COMPROBAR(estudiantes.cantidad == 0);
    vaciarConjunto(&estudiantes);
    return 1;
}

static int testCargaEstudiantes(void) {
    Conjunto estudiantes;
    COMPROBAR(escribirTexto(RUTA_CARGA,
        "matricula,nombres,apellidos,promedio\n"
        "205,Bruno,Pérez Solís,9.10\n"
        "101,Ana María,López Ruiz,8.50\n"));
    COMPROBAR(inicializarEstudiantes(&estudiantes));
    COMPROBAR(cargarEstudiantes(RUTA_CARGA, &estudiantes) == 2);
    COMPROBAR(estudiantes.cantidad == 2);

    Estudiante *primero = obtenerElemento(&estudiantes, 0);
    Estudiante *segundo = obtenerElemento(&estudiantes, 1);
    COMPROBAR(primero->matricula == 205);
    COMPROBAR(strcmp(primero->nombre.nombres, "Bruno") == 0);
    COMPROBAR(strcmp(primero->nombre.apellidos, "Pérez Solís") == 0);
    COMPROBAR(primero->promedio == 9.10f);
    COMPROBAR(segundo->matricula == 101);
    COMPROBAR(strcmp(segundo->nombre.nombres, "Ana María") == 0);
    COMPROBAR(strcmp(segundo->nombre.apellidos, "López Ruiz") == 0);
    COMPROBAR(segundo->promedio == 8.50f);
    vaciarConjunto(&estudiantes);
    return 1;
}

static int testCargaRechazaArchivoInvalido(void) {
    Conjunto estudiantes;
    Estudiante existente = {10, {"Registro", "Existente"}, 7.0f};
    COMPROBAR(escribirTexto(RUTA_INVALIDA,
        "matricula,nombres,apellidos,promedio\n"
        "20,Registro,Válido,8.00\n"
        "línea incorrecta\n"));
    COMPROBAR(inicializarEstudiantes(&estudiantes));
    COMPROBAR(agregarElemento(&estudiantes, &existente));
    COMPROBAR(cargarEstudiantes(RUTA_INVALIDA, &estudiantes) == -1);
    COMPROBAR(estudiantes.cantidad == 1);
    Estudiante *resultado = obtenerElemento(&estudiantes, 0);
    COMPROBAR(resultado->matricula == 10);
    vaciarConjunto(&estudiantes);
    return 1;
}

static int testCargaDetectaArchivoInexistente(void) {
    Conjunto estudiantes;
    (void)remove(RUTA_INEXISTENTE);
    COMPROBAR(inicializarEstudiantes(&estudiantes));
    COMPROBAR(cargarEstudiantes(RUTA_INEXISTENTE, &estudiantes) == -1);
    COMPROBAR(estudiantes.cantidad == 0);
    vaciarConjunto(&estudiantes);
    return 1;
}

static int testGuardaEstudiantes(void) {
    Conjunto estudiantes;
    Estudiante ana = {101, {"Ana María", "López Ruiz"}, 8.5f};
    Estudiante bruno = {205, {"Bruno", "Pérez Solís"}, 9.1f};
    char contenido[512];

    COMPROBAR(inicializarEstudiantes(&estudiantes));
    COMPROBAR(agregarElemento(&estudiantes, &ana));
    COMPROBAR(agregarElemento(&estudiantes, &bruno));
    COMPROBAR(guardarEstudiantes(RUTA_GUARDADO, &estudiantes) == 2);
    COMPROBAR(leerTexto(RUTA_GUARDADO, contenido, sizeof contenido));
    COMPROBAR(strcmp(contenido,
        "matricula,nombres,apellidos,promedio\n"
        "101,Ana María,López Ruiz,8.50\n"
        "205,Bruno,Pérez Solís,9.10\n") == 0);
    vaciarConjunto(&estudiantes);
    return 1;
}

int main(void) {
    int aprobadas = 0;
    aprobadas += testCargaArchivoVacio();
    aprobadas += testCargaEstudiantes();
    aprobadas += testCargaRechazaArchivoInvalido();
    aprobadas += testCargaDetectaArchivoInexistente();
    aprobadas += testGuardaEstudiantes();

    (void)remove(RUTA_CARGA);
    (void)remove(RUTA_GUARDADO);
    (void)remove(RUTA_INVALIDA);

    printf("Pruebas aprobadas: %d de 5.\n", aprobadas);
    return aprobadas == 5 ? EXIT_SUCCESS : EXIT_FAILURE;
}

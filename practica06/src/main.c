/*
 * Archivo: main.c
 * Práctica 06: interfaz de la base de datos de estudiantes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conjunto.h"
#include "estudiante.h"
#include "persistencia.h"

#define RUTA_DATOS "estudiantes.csv"

static int leerTexto(const char *mensaje, char *texto, size_t capacidad) {
    printf("%s", mensaje);
    if (fgets(texto, (int)capacidad, stdin) == NULL)
        return 0;

    size_t longitud = strcspn(texto, "\n");
    if (*(texto + longitud) == '\n')
        *(texto + longitud) = '\0';
    else {
        int caracter;
        while ((caracter = getchar()) != '\n' && caracter != EOF)
            ;
    }
    return *texto != '\0';
}

static int leerEntero(const char *mensaje, int *valor) {
    char linea[64];
    char extra;
    if (!leerTexto(mensaje, linea, sizeof linea))
        return 0;
    return sscanf(linea, " %d %c", valor, &extra) == 1;
}

static int leerReal(const char *mensaje, float *valor) {
    char linea[64];
    char extra;
    if (!leerTexto(mensaje, linea, sizeof linea))
        return 0;
    return sscanf(linea, " %f %c", valor, &extra) == 1;
}

static int capturarEstudiante(Estudiante *estudiante) {
    if (!leerEntero("Matrícula: ", &estudiante->matricula) ||
        !leerTexto("Nombre: ", estudiante->nombre.nombres,
                   sizeof estudiante->nombre.nombres) ||
        !leerTexto("Apellidos: ", estudiante->nombre.apellidos,
                   sizeof estudiante->nombre.apellidos) ||
        !leerReal("Promedio: ", &estudiante->promedio)) {
        printf("Datos inválidos.\n");
        return 0;
    }
    return 1;
}

static void agregarEstudiante(Conjunto *estudiantes) {
    Estudiante estudiante;
    if (!capturarEstudiante(&estudiante))
        return;
    if (agregarElemento(estudiantes, &estudiante))
        printf("Estudiante agregado.\n");
    else
        printf("No fue posible agregar: la matrícula ya existe.\n");
}

static void buscarEstudiante(Conjunto *estudiantes) {
    Estudiante criterio = {0};
    if (!leerEntero("Matrícula a buscar: ", &criterio.matricula)) {
        printf("Matrícula inválida.\n");
        return;
    }

    int indice = buscarElemento(estudiantes, &criterio);
    if (indice == -1) {
        printf("Estudiante no encontrado.\n");
        return;
    }
    mostrarEstudiante(obtenerElemento(estudiantes, indice));
}

static void eliminarEstudiante(Conjunto *estudiantes) {
    Estudiante criterio = {0};
    if (!leerEntero("Matrícula a eliminar: ", &criterio.matricula)) {
        printf("Matrícula inválida.\n");
        return;
    }
    if (eliminarElemento(estudiantes, &criterio))
        printf("Estudiante eliminado.\n");
    else
        printf("Estudiante no encontrado.\n");
}

static void cambiarPromedio(Conjunto *estudiantes) {
    Estudiante criterio = {0};
    float promedio;
    if (!leerEntero("Matrícula a actualizar: ", &criterio.matricula)) {
        printf("Matrícula inválida.\n");
        return;
    }

    int indice = buscarElemento(estudiantes, &criterio);
    if (indice == -1) {
        printf("Estudiante no encontrado.\n");
        return;
    }
    if (!leerReal("Nuevo promedio: ", &promedio)) {
        printf("Promedio inválido.\n");
        return;
    }
    actualizarPromedio(obtenerElemento(estudiantes, indice), promedio);
    printf("Promedio actualizado.\n");
}

static void mostrarEstudiantes(Conjunto *estudiantes) {
    if (estudiantes->cantidad == 0) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    for (int indice = 0; indice < estudiantes->cantidad; indice++)
        mostrarEstudiante(obtenerElemento(estudiantes, indice));
}

static void mostrarMenu(void) {
    printf("\nBase de datos de estudiantes\n");
    printf("1. Agregar estudiante\n");
    printf("2. Buscar estudiante\n");
    printf("3. Eliminar estudiante\n");
    printf("4. Actualizar promedio\n");
    printf("5. Mostrar estudiantes\n");
    printf("6. Ordenar por matrícula\n");
    printf("7. Guardar y salir\n");
}

int main(void) {
    Conjunto estudiantes;
    if (!inicializarConjunto(&estudiantes, 1, sizeof(Estudiante),
                             compararEstudiantes)) {
        fprintf(stderr, "No fue posible iniciar la base de datos.\n");
        return EXIT_FAILURE;
    }

    int cargados = cargarEstudiantes(RUTA_DATOS, &estudiantes);
    if (cargados == -1)
        printf("No fue posible cargar %s; la base inicia vacía.\n",
               RUTA_DATOS);
    else
        printf("Estudiantes cargados: %d\n", cargados);

    int salir = 0;
    while (!salir) {
        int opcion;
        mostrarMenu();
        if (!leerEntero("Opción: ", &opcion)) {
            if (feof(stdin))
                salir = 1;
            else
                printf("Opción inválida.\n");
            continue;
        }

        switch (opcion) {
            case 1:
                agregarEstudiante(&estudiantes);
                break;
            case 2:
                buscarEstudiante(&estudiantes);
                break;
            case 3:
                eliminarEstudiante(&estudiantes);
                break;
            case 4:
                cambiarPromedio(&estudiantes);
                break;
            case 5:
                mostrarEstudiantes(&estudiantes);
                break;
            case 6:
                ordenarConjunto(&estudiantes);
                printf("Estudiantes ordenados.\n");
                break;
            case 7:
                salir = 1;
                break;
            default:
                printf("Opción inválida.\n");
        }
    }

    int guardados = guardarEstudiantes(RUTA_DATOS, &estudiantes);
    vaciarConjunto(&estudiantes);
    if (guardados == -1) {
        fprintf(stderr, "No fue posible guardar la base de datos.\n");
        return EXIT_FAILURE;
    }
    printf("Estudiantes guardados: %d\n", guardados);
    return EXIT_SUCCESS;
}

/*
 * Archivo: estudiante.c
 * Completen la comparación; se conservan las otras operaciones de la práctica 4.
 * Autoría: Completa tu nombre.
 */

#include <stdio.h>

#include "estudiante.h"

int compararEstudiantes(const void *estudianteA, const void *estudianteB) {
    // Aquí va su código.
}

void actualizarPromedio(Estudiante *estudiante, float nuevoPromedio) {
    estudiante->promedio = nuevoPromedio;
}

void mostrarEstudiante(const Estudiante *estudiante) {
    printf("%d | %s %s | %.2f\n",
        estudiante->matricula,
        estudiante->nombre.nombres,
        estudiante->nombre.apellidos,
        estudiante->promedio);
}

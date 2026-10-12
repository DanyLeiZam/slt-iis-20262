/*
 * Archivo: estudiante.c
 * Completen la comparación; se conservan las otras operaciones de la práctica 3.
 * Autoría: Completa tu nombre.
 */

#include <stdio.h>

#include "estudiante.h"

/* Compara las matrículas para determinar igualdad y orden. */
int compararEstudiantes(const void *estudianteA, const void *estudianteB) {
    // Aquí va su código.
}

/* Modifica un campo mediante un apuntador a la estructura. */
void actualizarPromedio(Estudiante *estudiante, float nuevoPromedio) {
    estudiante->promedio = nuevoPromedio;
}

/* Muestra los campos de un estudiante. */
void mostrarEstudiante(const Estudiante *estudiante) {
    printf("%d | %s %s | %.2f\n",
        estudiante->matricula,
        estudiante->nombre.nombres,
        estudiante->nombre.apellidos,
        estudiante->promedio);
}

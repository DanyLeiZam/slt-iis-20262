/*
 * Archivo: estudiante.c
 * Operaciones propias de un estudiante.
 * Completen las funciones pendientes según estudiante.h.
 * Autoría: Daniela Díaz Morales.
 */

#include <stdio.h>

#include "estudiante.h"

/* Compara el campo que identifica a cada estudiante. */
int compararEstudiantes(const Estudiante *estudianteA,
                        const Estudiante *estudianteB) {
    // Aquí va su código.
    return estudianteA ->matricula - estudianteB ->matricula;
}

/* Modifica un campo mediante un apuntador a la estructura. */
void actualizarPromedio(Estudiante *estudiante, float nuevoPromedio) {
    // Aquí va su código.
    estudiante ->promedio = nuevoPromedio;
}

/* Muestra los campos de un estudiante. */
void mostrarEstudiante(const Estudiante *estudiante) {
    // Aquí va su código.
    printf("%d, %s %s, %.2f\n", 
        estudiante->matricula,
        estudiante->nombre.nombres,
        estudiante->nombre.apellidos, 
        estudiante->promedio);
}

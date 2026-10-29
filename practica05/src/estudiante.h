/*
 * Archivo: estudiante.h
 * Modelo y operaciones propias de un estudiante.
 */

#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#define LONGITUD_NOMBRE 40

typedef struct {
    char nombres[LONGITUD_NOMBRE];
    char apellidos[LONGITUD_NOMBRE];
} NombreCompleto;

typedef struct Estudiante {
    int matricula;
    NombreCompleto nombre;
    float promedio;
} Estudiante;

/* Compara estudiantes por matrícula para determinar pertenencia y orden. */
int compararEstudiantes(const void *estudianteA, const void *estudianteB);

/* Modifica únicamente el promedio del estudiante. */
void actualizarPromedio(Estudiante *estudiante, float nuevoPromedio);

/* Muestra los campos del estudiante en una línea. */
void mostrarEstudiante(const Estudiante *estudiante);

#endif

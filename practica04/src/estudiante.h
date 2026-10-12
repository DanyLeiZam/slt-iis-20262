/*
 * Archivo: estudiante.h
 * Modelo y operaciones propias de un estudiante.
 */

#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#define LONGITUD_NOMBRE 40

/* Alias de una estructura anónima que agrupa las partes del nombre. */
typedef struct {
    char nombres[LONGITUD_NOMBRE];
    char apellidos[LONGITUD_NOMBRE];
} NombreCompleto;

/* Estructura nombrada y alias para representar un registro. */
typedef struct Estudiante {
    int matricula;
    NombreCompleto nombre;
    float promedio;
} Estudiante;

/*
 * Compara dos estudiantes por matrícula: negativo si A es menor, cero si
 * coinciden y positivo si A es mayor. No compara nombres ni promedios.
 */
int compararEstudiantes(const void *estudianteA, const void *estudianteB);

/* Modifica únicamente el promedio del estudiante. */
void actualizarPromedio(Estudiante *estudiante, float nuevoPromedio);

/* Muestra los campos del estudiante en una línea. */
void mostrarEstudiante(const Estudiante *estudiante);

#endif

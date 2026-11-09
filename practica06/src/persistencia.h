/*
 * Archivo: persistencia.h
 * Operaciones para conservar la base de datos de estudiantes en un CSV.
 */

#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "conjunto.h"

/*
 * El CSV comienza con la cabecera:
 * matricula,nombres,apellidos,promedio
 *
 * Cada línea posterior contiene un estudiante. Los nombres y apellidos
 * pueden tener espacios, pero no comas.
 */

/*
 * Carga los registros en un conjunto inicializado. Regresa la cantidad
 * agregada o -1 si no puede abrir, leer, validar o cerrar el archivo.
 */
int cargarEstudiantes(const char *ruta, Conjunto *estudiantes);

/*
 * Sobrescribe el CSV con los registros del conjunto. Regresa la cantidad
 * guardada o -1 si no puede abrir, escribir o cerrar el archivo.
 */
int guardarEstudiantes(const char *ruta, const Conjunto *estudiantes);

#endif

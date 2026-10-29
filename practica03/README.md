# Introducción a la Ingeniería de Software

## Práctica 3: Conjunto de estudiantes

### Fecha de entrega: lunes 12 de octubre de 2026

Deben implementar las funciones faltantes de [conjunto.c](src/conjunto.c) y [estudiante.c](src/estudiante.c).

En esta práctica adaptarán el conjunto de enteros de la práctica 2 para almacenar estudiantes. La matrícula identifica a cada estudiante y determina si ya pertenece al conjunto.

Los únicos archivos que deben modificar son:

- [`conjunto.c`](src/conjunto.c) con la implementación de la biblioteca de conjuntos.
- [`estudiante.c`](src/estudiante.c) con la implementación de las operaciones de estudiantes.
- [`resumen.docx`](doc/resumen.docx) con el resumen del plan del proyecto.
- [`tiempos.docx`](doc/tiempos.docx) con el registro de tiempos que tomaron en la realización de esta práctica.

*No deben modificar de ninguna manera ninguno de los otros archivos ni estructura de la práctica ni repositorio.*

### Repositorio

Deberán seguir el **formato general de entrega** descrito en el repositorio.

Si ya realizaron la configuración inicial, **no deberán volver a clonar el repositorio**. Únicamente deberán entrar al directorio correspondiente y obtener la versión más reciente:

```bash
$ cd slt-iis-20262
$ git pull upstream main
```

Si es la primera vez que trabajan con el repositorio, deberán realizar primero los pasos indicados en la sección **Configuración inicial: sólo la primera vez** del formato general de entrega.

### Compilación y pruebas

Una vez terminado el trabajo correspondiente a la práctica, deberán comprobar que el programa compila y que todas las pruebas unitarias pasan correctamente al ejecutar:

```bash
$ make test
```

Este comando compila el código necesario y ejecuta el conjunto de pruebas definido para la práctica.

Recuerden que si hay advertencias al compilar, se considera como si no compilara.

### Archivos de la práctica

Deberán modificar **únicamente los archivos indicados explícitamente para esta práctica**. No deberán modificar de ninguna manera el `Makefile`, los archivos de pruebas ni otros archivos proporcionados como parte de la infraestructura de la práctica, salvo que las instrucciones indiquen lo contrario.

### Entrega

Antes de entregar deberán ejecutar nuevamente:

```bash
$ make clean && make test
```

Así comprobarán una compilación completa desde cero y que todas las pruebas pasen correctamente.

Posteriormente deberán realizar el commit correspondiente a la entrega y subirlo a su repositorio privado de GitHub:

```bash
$ git add .
$ git commit -m "Entrega de la práctica 3"
$ git push
```

Finalmente, deberán entregar en Classroom la liga al **commit correspondiente a la entrega**, siguiendo el formato general de entrega.

Recuerden que el repositorio deberá ser **privado** y que el usuario **`manu-msr`** deberá estar agregado como colaborador para que la práctica pueda ser revisada.

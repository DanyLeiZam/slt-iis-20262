/*
 * Archivo: conjunto.c
 * Implementación de conjuntos de enteros con arreglos de capacidad fija.
 * Completen las funciones pendientes según conjunto.h.
 * Usen funciones, arreglos y apuntadores; no usen estructuras, memoria
 * dinámica, archivos ni ordenamientos.
 * Autoría: Daniela D�az Morales.
 */

#include <stdio.h>

#include "conjunto.h"

	/* Busca Unicamente en las posiciones utilizadas del conjunto. */
	int buscarElemento(const int conjunto[], int cantidad, int elemento) {
    	int i;
    	for(i = 0; i < cantidad; i++){
			if(conjunto[i] == elemento){
           		 return i;
       		}
    	}
    	return -1;
	}

	/* Agrega un elemento si no existe y queda espacio. */
	int agregarElemento(int conjunto[], int capacidad, int *cantidad,
    	                int elemento) {
    	if (*cantidad >= capacidad)
    		return 0;
    	if (buscarElemento(conjunto, *cantidad, elemento) != -1)
    		return 0;
    	conjunto[*cantidad] = elemento;
    	(*cantidad)++;
    	return 1;
	}

	/* Elimina un elemento y conserva el orden de los restantes. */
	int eliminarElemento(int conjunto[], int *cantidad, int elemento) {
    	int posicion = buscarElemento(conjunto, *cantidad, elemento);
    	if (posicion == -1)
    		return 0;
	}
        for (int i = indice; i < *cantidad - 1; i++) {
        conjunto[i] = conjunto[i + 1];
        }
        (*cantidad)--;
        return 1;
   }


/* Sustituye un elemento sin cambiar la cantidad ni introducir repetidos. */
int reemplazarElemento(int conjunto[], int cantidad, int elemento,
                       int reemplazo) {
    // Aquí va su código.
if (elemento == reemplazo) {
        return 0;
    }
    int indice = buscarElemento(conjunto, cantidad, elemento);
    if (indice == -1) {
        return 0;
    }
    if (buscarElemento(conjunto, cantidad, reemplazo)!= -1) {
        return 0;
    }
    conjunto[indice] = reemplazo;
    return 1;
}


	/* Deja el conjunto vacio, conservando el arreglo y su capacidad. */
	void vaciarConjunto(int *cantidad) {
    	*cantidad = 0;
	}

	/* Copia los elementos a otro arreglo, conservando su orden. */
	int copiarConjunto(const int origen[], int cantidad,
                   int destino[], int capacidadDestino) {
                   	int limite = (cantidad < capacidadDestino)? cantidad: capacidadDestino;
                   	capacidadDestino;
                   	int i;
                   	for(i = 0; i < limite; i++){
                   		destino[i] = origen[i];
					   }
					   return limite;
    
}

/* Indica si A es subconjunto de B, sin importar el orden. */
int esSubconjunto(const int conjuntoA[], int cantidadA,
                 const int conjuntoB[], int cantidadB) {
    // Aquí va su código.
    int i;
    for(i = 0; i <cantidadA; i++){
    	if(!elementoExiste(conjuntoB, cantidadB, conjuntoA[i])){
    		return 0;
		}
	}
	return 1;
}

/* Indica si los conjuntos tienen los mismos elementos, sin importar el orden. */
int sonConjuntosIguales(const int conjuntoA[], int cantidadA,
                       const int conjuntoB[], int cantidadB) {
    // Aquí va su código.
    if(cantidadA !=cantidadB){
    	return 0; 
	}
	int i;
	int j;
	for(i = 0; i <cantidadA; i++){
		int elemento = conjuntoA[i];
		int encontrado = 0;
		for(j = 0; j <cantidadB; j++){
			if(conjuntoB[j] == elemento){
				encontrado = 1;
				break;
			}
		}
		if(encontrado == 0){
			return 0;
		}
	}
	return 1;
}

/* Calcula la unión conservando primero A y después los elementos nuevos de B. */
int unirConjuntos(const int conjuntoA[], int cantidadA,
                 const int conjuntoB[], int cantidadB,
                 int resultado[], int capacidadResultado) {
    // Aquí va su código.
    int contador = 0;
    int i;
    for(i = 0; i <cantidadA;i++){
    	if(contador <capacidadResultado){
    		if(!elementoExiste(resultado, contador, conjuntoA[i])){
    			resultado[contador] = conjuntoA[i];
    			contador++;
			}
		}else{
			return contador;
		}
	}
}

/* Calcula la intersección conservando el orden de A. */
int intersectarConjuntos(const int conjuntoA[], int cantidadA,
                        const int conjuntoB[], int cantidadB,
                        int resultado[], int capacidadResultado) {
    // Aquí va su código.
    int contador = 0;
    int i;
    int j;
    for(i = 0; i <cantidadA; i++){
    	int elemento = conjuntoA[i];
    	int encontrado = 0;
    	for(j = 0; j <cantidadB; j++){
    		if(conjuntoB[j] == elemento){
    			encontrado = 1;
    			break;
			}
		}
		if(encontrado && contador < capacidadResultado){
			resultado[contador++] = elemento;
		}
	}
	return contador;
    
}

/* Calcula la diferencia A-B conservando el orden de A. */
int diferenciarConjuntos(const int conjuntoA[], int cantidadA,
                        const int conjuntoB[], int cantidadB,
                        int resultado[], int capacidadResultado) {
    // Aquí va su código.
    int contador = 0;
    int i;
    int j;
    for(i = 0; i <cantidadA; i++){
    	int elemento = conjuntoA[i];
    	int encontrado = 0;
    	for(j = 0; j <cantidadB; j++){
    		if(conjuntoB[j] == elemento){
    			encontrado = 1;
    			break;
			}
		}
		if(!encontrado && contador < capacidadResultado){
			resultado[contador++] = elemento;
			}
		}
		return contador;
	}


/* Muestra el conjunto con llaves, comas y un salto de línea al final. */
void mostrarConjunto(const int conjunto[], int cantidad) {
    printf("{");
    int indice;
    for (indice = 0; indice < cantidad; indice++) {
        if (indice > 0)
            printf(", ");
        printf("%d", conjunto[indice]);
    }
    printf("}\n");
}

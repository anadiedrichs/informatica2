#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definición de la estructura para un nodo de la lista
typedef struct Nodo {
	int id;
	char evento[50];
	float medicion;
	int prioridad;
	time_t tiempoMedicion;
	struct Nodo* siguiente;
} Nodo;

size_t memoriaAsignada = 0;

void* miMalloc(size_t tamano) {
	void* ptr = malloc(tamano);
	if (ptr) {
		memoriaAsignada += tamano;
	}
	return ptr;
}

void miFree(void* ptr, size_t tamano) {
	if (ptr) {
		memoriaAsignada -= tamano;
		free(ptr);
	}
}

size_t obtenerMemoriaAsignada() {
	return memoriaAsignada;
}

// Función para crear un nuevo nodo
Nodo* crearNodo(int id, const char* evento, float medicion, int prioridad, time_t tiempoMedicion) {
	
	Nodo* nuevoNodo = (Nodo*)miMalloc(sizeof(Nodo));
	if (!nuevoNodo) {
		printf("Error al asignar memoria\n");
		exit(1);
	}
	nuevoNodo->id = id;
	strcpy(nuevoNodo->evento, evento);
	nuevoNodo->medicion = medicion;
	nuevoNodo->prioridad = prioridad;
	nuevoNodo->tiempoMedicion = tiempoMedicion;
	nuevoNodo->siguiente = NULL;
	return nuevoNodo;
}

// Función para mostrar la información de un nodo en pantalla
void imprimirNodo(Nodo* n){
	
	char tiempoCadena[26];
	struct tm* tm_info = localtime(&n->tiempoMedicion);
	strftime(tiempoCadena, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	printf("------------------------\n");
	printf("| ID: %d \n| Evento: %s \n| Medición: %.2f \n| Prioridad: %d \n| Fecha: %s\n", 
		   n->id, n->evento, n->medicion, n->prioridad, tiempoCadena);
	printf("------------------------\n");
}
	
// Función para imprimir la pila
void imprimirPila(Nodo* cabeza) {
	Nodo* temp = cabeza;
	while (temp != NULL) {
		imprimirNodo(temp);
		temp = temp->siguiente;
	}
}
	

// Función para agregamos un nodo a la pila
void push(Nodo** cabeza, int id, const char* evento, float medicion, int prioridad, time_t tiempoMedicion) {
	Nodo* nuevoNodo = crearNodo(id, evento, medicion, prioridad, tiempoMedicion);
	nuevoNodo->siguiente = *cabeza;
	*cabeza = nuevoNodo;
}

// Función para eliminar un nodo de la pila
void pop(Nodo** cabeza) {
	if (*cabeza == NULL) {
		printf("La pila está vacía\n");
		return;
	}
	Nodo* temp = *cabeza;
	*cabeza = (*cabeza)->siguiente;
	miFree(temp, sizeof(Nodo));
}

// Función para buscar un nodo en la pila por ID
Nodo* buscar(Nodo* cabeza, int id) {
	Nodo* temp = cabeza;
	
	while (temp != NULL) {
		if (temp->id == id) {
			return temp;
		}
		temp = temp->siguiente;
	}
	
	return NULL;
}


// Función para modificar un nodo de la pila por ID
void modificar(Nodo* cabeza, int id, const char* evento, float medicion, int prioridad, time_t tiempoMedicion) {
	
	Nodo* temp = buscar(cabeza,id);
	
	// si encontró el nodo 
	
	if (temp != NULL) {
		
		strcpy(temp->evento, evento);
		temp->medicion = medicion;
		temp->prioridad = prioridad;
		temp->tiempoMedicion = tiempoMedicion;
		return;
		
	}else
	{		
		printf("Nodo con ID %d no encontrado\n", id);
	}
	
}
/*
Copia la información del nodo max 
al nodo actual
*/

void intercambiarNodos(Nodo* actual, Nodo* max)
{
	// copio el nodo actual en temp  
	
	Nodo* temp = crearNodo(actual->id,actual->evento,actual->medicion,actual->prioridad,actual->tiempoMedicion);
	
	// asigno los valores del nodo max 
	// al nodo actual
	actual->id = max->id;
	max->id = temp->id;
	
	strcpy(actual->evento, max->evento);
	strcpy(max->evento, temp->evento);
	
	actual->medicion = max->medicion;
	max->medicion = temp->medicion;
	
	actual->prioridad = max->prioridad;
	max->prioridad = temp->prioridad;
	
	actual->tiempoMedicion = max->tiempoMedicion;
	max->tiempoMedicion = temp->tiempoMedicion;
	
	// libero la memoria 
	miFree(temp,sizeof(Nodo));
	
}
// Función para reordenar la pila por prioridad de mayor a menor
void reordenarPorPrioridad(Nodo** cabeza) {
	if (*cabeza == NULL) {
		return;
	}	
	Nodo* actual = *cabeza;
	Nodo* siguiente = NULL;
	Nodo* max = NULL;
	
	while (actual != NULL) {
		max = actual;
		siguiente = actual->siguiente;
		
		while (siguiente != NULL) {
			if (siguiente->prioridad > max->prioridad) {
				max = siguiente;
			}
			siguiente = siguiente->siguiente;
		}
		// si tengo un nuevo máximo
		if (max != actual) {			
			// Intercambiar nodos
			intercambiarNodos(actual,max);
		}
		
		actual = actual->siguiente;
	}
}

int main() {
	
	Nodo* cabeza = NULL;
	time_t ahora = time(NULL);
	char g;
	// 1-intro
	// cabeza = crearNodo( 1, "sensor de temperatura en valores anómalos", -2, 5, ahora);
	// imprimirNodo(cabeza);	
	
	
	
	//2- agregar y eliminar nodo 
	// agregar Nodo
	push(&cabeza, 1, "sensor de temperatura en valores anómalos", -2, 5, ahora);	
	printf("Memoria dinámica utilizada:  %d bytes\n",obtenerMemoriaAsignada());		
	// quitar un elemento de la pila
	//pop(&cabeza);
	//printf("Memoria dinámica utilizada:  %d bytes\n",obtenerMemoriaAsignada());	
	
	
	// 3-Agregar nodos
	//push(&cabeza, 1, "sensor de temperatura en valores anómalos", -2, 10, ahora);	
	push(&cabeza, 2, "humedad alta en deshidratadores", 90.0, 6, ahora);		
	push(&cabeza, 3, "conteo cajas linea 3", 100, 2, ahora);
	
	// Imprimir pila
	printf("Pila inicial:\n");
	imprimirPila(cabeza);	
	g=getchar(); 
	system("clear");
	
	// Modificar nodo
	printf("\nMODIFICAR NODO \n");
	// Añadir 1 hora al tiempo de medición
	modificar(cabeza, 12, "Humedad", 65.5, 2, ahora + 3600); 
	imprimirPila(cabeza);
	
	// Reordenar pila por prioridad
	printf("REORDENAMIENTO DE LA LISTA");
	reordenarPorPrioridad(&cabeza);
	imprimirPila(cabeza);	
	g=getchar(); 
	system("clear");
	
	// Liberar memoria restante
	while (cabeza != NULL) {
		pop(&cabeza);
	}	
	// printf("\nMemoria dinámica total asignada después de liberar: %zu bytes\n", obtenerMemoriaAsignada());

		
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definición de la estructura para un nodo de la lista
typedef struct Nodo {
	int id;
	char sensor[50];
	float medicion;
	char modelo;
	time_t tiempoMedicion;
	struct Nodo* siguiente;
} Nodo;

typedef struct Cola {
	Nodo* frente;
	Nodo* final;
} Cola;

static size_t memoriaAsignada = 0;

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
Nodo* crearNodo(int id, const char* sensor, float medicion, char modelo, time_t tiempoMedicion) {
	Nodo* nuevoNodo = (Nodo*)miMalloc(sizeof(Nodo));
	if (!nuevoNodo) {
		printf("Error al asignar memoria\n");
		exit(1);
	}
	nuevoNodo->id = id;
	strcpy(nuevoNodo->sensor, sensor);
	nuevoNodo->medicion = medicion;
	nuevoNodo->modelo = modelo;
	nuevoNodo->tiempoMedicion = tiempoMedicion;
	nuevoNodo->siguiente = NULL;
	return nuevoNodo;
}

// Función para inicializar la cola
void inicializarCola(Cola* cola) {
	cola->frente = NULL;
	cola->final = NULL;
}

// Función para añadir un nodo a la cola
void alta(Cola* cola, int id, const char* sensor, float medicion, char modelo, time_t tiempoMedicion) {
	Nodo* nuevoNodo = crearNodo(id, sensor, medicion, modelo, tiempoMedicion);
	if (cola->final == NULL) {
		cola->frente = nuevoNodo;
		cola->final = nuevoNodo;
	} else {
		cola->final->siguiente = nuevoNodo;
		cola->final = nuevoNodo;
	}
}

// Función para eliminar un nodo de la cola por ID
void baja(Cola* cola) {
	if (cola->frente == NULL) {
		printf("La cola está vací­a\n");
		return;
	}
	Nodo* temp = cola->frente;
	cola->frente = cola->frente->siguiente;
	if (cola->frente == NULL) {
		cola->final = NULL;
	}
	miFree(temp, sizeof(Nodo));
}

// Función para modificar un nodo de la cola por ID
void modificar(Cola* cola, int id, const char* sensor, float medicion, char modelo, time_t tiempoMedicion) {
	Nodo* temp = cola->frente;
	
	while (temp != NULL) {
		if (temp->id == id) {
			strcpy(temp->sensor, sensor);
			temp->medicion = medicion;
			temp->modelo = modelo;
			temp->tiempoMedicion = tiempoMedicion;
			return;
		}
		temp = temp->siguiente;
	}
	
	printf("Nodo con ID %d no encontrado\n", id);
}

// Función para buscar un nodo en la cola por ID
Nodo* buscar(Cola* cola, int id) {
	Nodo* temp = cola->frente;
	
	while (temp != NULL) {
		if (temp->id == id) {
			return temp;
		}
		temp = temp->siguiente;
	}
	
	return NULL;
}

// Función para imprimir la cola
void imprimirCola(Cola* cola) {
	Nodo* temp = cola->frente;
	char tiempoCadena[26];
	while (temp != NULL) {
		struct tm* tm_info = localtime(&temp->tiempoMedicion);
		strftime(tiempoCadena, 26, "%Y-%m-%d %H:%M:%S", tm_info);
		printf("ID: %d, Sensor: %s, Medición: %.2f, Modelo: %c, Fecha: %s\n", 
			   temp->id, temp->sensor, temp->medicion, temp->modelo, tiempoCadena);
		temp = temp->siguiente;
	}
}

int main() {
	Cola cola;
	inicializarCola(&cola);
	time_t ahora = time(NULL);
	
	// AÃ±adir nodos
	alta(&cola, 1, "Temperatura", 23.5, 'A', ahora);
	alta(&cola, 2, "Humedad", 60.0, 'B', ahora);
	alta(&cola, 3, "Presión", 1013.25, 'C', ahora);
	
	// Imprimir cola
	printf("Cola inicial:\n");
	imprimirCola(&cola);
	
	// Modificar nodo
	modificar(&cola, 2, "Humedad", 65.5, 'B', ahora + 3600);
	printf("\nCola después de modificar ID 2:\n");
	imprimirCola(&cola);
	
	// Buscar nodo
	Nodo* encontrado = buscar(&cola, 3);
	if (encontrado) {
		struct tm* tm_info = localtime(&encontrado->tiempoMedicion);
		char tiempoCadena[26];
		strftime(tiempoCadena, 26, "%Y-%m-%d %H:%M:%S", tm_info);
		printf("\nNodo encontrado - ID: %d, Sensor: %s, MediciÃ³n: %.2f, Modelo: %c, Tiempo de MediciÃ³n: %s\n", 
			   encontrado->id, encontrado->sensor, encontrado->medicion, encontrado->modelo, tiempoCadena);
	} else {
		printf("\nNodo con ID 3 no encontrado\n");
	}
	
	// Eliminar nodo
	baja(&cola);
	printf("\nCola después de eliminar el nodo frente:\n");
	imprimirCola(&cola);
	
	printf("\nMemoria dinámica total asignada: %zu bytes\n", obtenerMemoriaAsignada());
	
	// Liberar memoria restante
	while (cola.frente != NULL) {
		baja(&cola);
	}
	
	printf("\nMemoria dinámica total asignada despuÃ©s de liberar: %zu bytes\n", obtenerMemoriaAsignada());
	
	return 0;
}

#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define DEBUG TRUE


void mi_printf(char* cadena)
{
 	if(DEBUG) 
		printf("%s \n",cadena);
}

// estados
typedef enum
{
    APAGADO = 0, //apagado
    PRENDIDO, // prendido
    SALIR // salir o finhttps://github.com/anadiedri
} my_state_t;

my_state_t  state = APAGADO;   // estado inicial

// función de transición de estados según los eventos
void evaluar(int input)
{
    switch(state)
    {
        case APAGADO:
            if(input==1)
			{  
				mi_printf("BOMBILLA PRENDIDA.");
				state = PRENDIDO;
			}
			if(input==2) state = SALIR;
            break;

        case PRENDIDO:
            if(input==0)
			{  
				mi_printf("BOMBILLA APAGADA.");
				state = APAGADO;
			} 
            if(input==2)  state = SALIR;https://github.com/anadiedri
            break;

		case SALIR:
			 break;
    }

}

/*
El usuario ingresa valores enteros 0,1,2.
Se valida que ingrese valores válidos.
Si ingresa 0, bombilla se apaga
Si ingresa 1, bombilla se prende
Si ingresa 2, se sale del sistema.
*/

int main(void)
{

	int opcion = 0;

	while(TRUE)
	{
		mi_printf("Ingrese 0, 1, o 2");
		scanf("%d",&opcion); // nuestro evento
		
		if(opcion>=0 && opcion <3) evaluar(opcion); //ojo falla al ingresar un char
		else{ opcion=0; printf("Ingrese una opción válida.");}
		
		if(state==SALIR)
		{mi_printf("Adios mundo cruel"); break;}
	}

	return(0);
}


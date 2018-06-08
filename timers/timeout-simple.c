/* Ejemplo manejo timers de forma no bloqueante */
#include <stdio.h>
#include <time.h>
// http://www.cplusplus.com/reference/ctime/

//estructura timer
typedef struct {
 time_t init;
 time_t end;
 time_t duration_secs;
 // other things??
} MiTimer;
// prototipos de funcion

void init_timer(MiTimer *t);
void reset_timer(MiTimer *t);
int is_expired(MiTimer *t);
void set_duration(MiTimer *t,int secs);
// funciones
void init_timer(MiTimer *t)
{
 t->init = time(NULL);
 char buff[20];
 strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&t->init));
 printf("Time init %s \n",buff);
}
void set_duration(MiTimer *t,int secs)
{

 t->duration_secs = secs;
 t->end = t-> init + secs;
 printf("Duration set to %d \n",secs);
 char buff[20];
 strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&t->end));
 printf("Time end %s \n",buff);

}

void reset_timer(MiTimer *t)
{
 t->init = 0;
 t->end = 0;
 t->duration_secs=0;
}

int is_expired(MiTimer *t)
{
  time_t now = time(0);
  double dif = difftime(t->end,now);  

  //printf("Diferencia %.2lf \n ",dif);

  if(dif <=0) return 1;
  else return 0;
  // else return 0
 
}

int main ()
{
  MiTimer timemachine;
  int secs = 2;
// inicializar timer 
  init_timer(&timemachine);
  set_duration(&timemachine,secs);

 // hacer cosas - do things
  int acummulator = 0 ;

while(1)
{
  //contar
  acummulator+=1;
  printf("*");
 // si expira el timer, salir del bucle
  if(is_expired(&timemachine)){  break;}

}
  printf("tOTAL ACUMULADOR ES %d \n",acummulator);

  return 0;
}




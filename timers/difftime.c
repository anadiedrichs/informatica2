/* Ejemplo diferencia de tiempo */
#include <stdio.h>
#include <time.h>
// http://www.cplusplus.com/reference/ctime/
#include <unistd.h> //sleep en linux
int main ()
{
  time_t start,end;
  double dif;

  time(&start);
  // hacer algo
  sleep(10);
  time(&end);
  //dif = difftime(end,start);
  dif = difftime(start,end);  
  printf ("El tiempo transcurrido es de %.2lf segundos.\n", dif );

  return 0;
}




#include <stdio.h>
#include <time.h>
// https://en.wikipedia.org/wiki/C_date_and_time_functions

int main() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%c", tm);
    printf("%s\n", s);

	// obtener año
	printf("Nro año es  %d\n",(1900+tm->tm_year));
	// obtener día
	printf("Nro día es %d\n",tm->tm_mday);
	// obtener mes. Valor de 0 a 11 
	printf("Nro de mes es %d\n",(tm->tm_mon)+1);
	// obtener hora
	printf("Hora es %d\n",tm->tm_hour);
	// obtener minutos
	printf("Minutos es %d\n",tm->tm_min);
}

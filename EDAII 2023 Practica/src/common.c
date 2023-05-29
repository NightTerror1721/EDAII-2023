#include "common.h"

#include <time.h>


int random_int(int max)
{
	//Las variables static actuan como si fueran variables globales, pero solo son visibles en la funcion en la que se definen.
	//Solo se inicializan una vez, despues la instruccion que les da valor en su inicializacion se ignora. Mantienen su valor antiguo cada vez que se entra a la funcion.
	static bool first_time = true;
	if (first_time)
	{
		srand((unsigned int) time(NULL));
		first_time = false;
	}

	return rand() % max;
}

int read_option(void)
{
	int value;
	if (scanf("%d", &value) != 1)
		return -1;

	consume_stdin();

	return value;
}

void consume_stdin()
{
	char c;
	while ((c = getchar()) && (c != '\n') && (c != EOF));
}

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

char read_csv_token(FILE* f, char* buffer)
{
	int count = 0;
	int ch;
	while ((ch = fgetc(f)) != EOF)
	{
		if (ch == CSV_SEPARATOR || ch == CSV_ENDLINE)
		{
			buffer[count] = '\0';
			return ch;
		}
		else
		{
			buffer[count] = ch;
			count++;
		}
	}

	return CSV_ENDLINE;
}

char read_csv_number(FILE* f, int* number)
{
	char buffer[50];
	char stop = read_csv_token(f, buffer);
	*number = atoi(buffer);

	//La función atoi retorna 0 en caso de error//
	if (*number == 0)
		printf("[CSV number parser error]: Cannot concert '%s' to int.\n", buffer);

	return stop;
}

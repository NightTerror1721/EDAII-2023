#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

#define CSV_SEPARATOR ','
#define CSV_ENDLINE '\n'


int random_int(int max);

char read_csv_token(FILE* f, char* buffer);
char read_csv_number(FILE* f, int* number);


#endif //__COMMON_H__

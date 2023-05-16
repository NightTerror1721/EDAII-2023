#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INVALID_OPTION -1

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)


int random_int(int max);

int read_option(void);



#endif //__COMMON_H__

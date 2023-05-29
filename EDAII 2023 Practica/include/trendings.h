#ifndef __TRENDINGS_H__
#define __TRENDINGS_H__

#include "common.h"

#define HASHTABLE_ARRAY_LEN 32


void trendings_init();

void trendings_clear();

size_t trendings_add_word(const char* word);

void trendings_add_words_from_text(const char* text);

void trendings_print_top_10();



#endif //__TRENDINGS_H__

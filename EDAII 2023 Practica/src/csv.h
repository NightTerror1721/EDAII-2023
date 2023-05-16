#ifndef __CSV_H__
#define __CSV_H__

#include "user.h"
#include "user_list.h"


User* read_user_from_csv_row(FILE* f);

void fill_users_list_from_csv(UsersList* list, const char* filename);


#endif //__CSV_H__

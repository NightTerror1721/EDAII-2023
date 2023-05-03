#ifndef __USER_H__
#define __USER_H__

#include <stdlib.h>

#define MAX_STRING_LEN 256
#define PREFERENCES_COUNT 5


typedef struct {
	char username[MAX_STRING_LEN];
	int born_year;
	char email[MAX_STRING_LEN];
	char current_location[MAX_STRING_LEN];
	char preferences[PREFERENCES_COUNT][MAX_STRING_LEN];
} User;


void init_user(User* user);

const char* get_user_username(const User* user);
void set_user_username(User* user, const char* username);

int get_user_born_year(const User* user);
void set_user_born_year(User* user, int year);

const char* get_user_email(const User* user);
void set_user_email(User* user, const char* email);

const char* get_user_current_location(const User* user);
void set_user_current_location(User* user, const char* location);

const char* get_user_preference(const User* user, size_t index);
void set_user_preference(User* user, size_t index, const char* preference);


void show_fill_user_data_menu(User* user);



typedef struct UsersListNode {
	User* user;
	struct UsersListNode* next;
	struct UsersListNode* prev;
} UsersListNode;

typedef struct {
	UsersListNode* first;
	UsersListNode* last;
	size_t size;
} UsersList;


void init_users_list(UsersList* list);

void add_user_to_list(UsersList* list, User* user);

void show_all_users_in_list(UsersList* list);

void clear_users_list(UsersList* list);


#endif //__USER_H__



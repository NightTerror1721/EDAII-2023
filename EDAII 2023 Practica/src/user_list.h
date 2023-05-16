#ifndef __USER_LIST_H__
#define __USER_LIST_H__

#include "common.h"


typedef struct User User;

typedef struct UsersListNode {
	struct User* user;
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

void show_all_users_in_list(const UsersList* list);

void clear_users_list(UsersList* list, bool destroy_users);

size_t users_list_size(const UsersList* list);

bool users_list_empty(const UsersList* list);

User* search_user_by_username(const UsersList* list, const char* username);


#endif //__USER_LIST_H__

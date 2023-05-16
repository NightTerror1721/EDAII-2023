#include "user_list.h"
#include "user.h"


void init_users_list(UsersList* list)
{
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
}

void add_user_to_list(UsersList* list, User* user)
{
	UsersListNode* node = (UsersListNode*)malloc(sizeof(UsersListNode));
	node->user = user;
	node->next = NULL;

	if (list->first == NULL)
	{
		list->first = node;
		list->last = node;
		node->prev = NULL;
	}
	else
	{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
	list->size++;
}

void show_all_users_in_list(const UsersList* list)
{
	printf("All users:\n");
	for (UsersListNode* node = list->first; node != NULL; node = node->next)
		printf("    - %s\n", node->user->username);
	printf("\n");
}

void clear_users_list(UsersList* list, bool destroy_users)
{
	for (UsersListNode* node = list->first, *next; node != NULL; node = next)
	{
		next = node->next;
		if (destroy_users)
			destroy_user(node->user);
		free(node);
	}

	init_users_list(list);
}

size_t users_list_size(const UsersList* list) { return list->size; }

bool users_list_empty(const UsersList* list) { return list->size == 0; }

User* search_user_by_username(const UsersList* list, const char* username)
{
	for (UsersListNode* node = list->first; node != NULL; node = node->next)
		if (strcmp(node->user->username, username) == 0)
			return node->user;

	return NULL;
}

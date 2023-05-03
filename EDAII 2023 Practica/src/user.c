#include "user.h"

#include <stdio.h>
#include <string.h>


void init_user(User* user)
{
	user->username[0] = '\0';
	user->born_year = 0;
	user->email[0] = '\0';
	user->current_location[0] = '\0';
	
	for (int i = 0; i < PREFERENCES_COUNT; ++i)
		user->preferences[i][0] = '\0';
}

const char* get_user_username(const User* user) { return user->username; }
void set_user_username(User* user, const char* username) {
	strcpy(user->username, username);
}

int get_user_born_year(const User* user) { return user->born_year; }
void set_user_born_year(User* user, int year) { user->born_year = year; }

const char* get_user_email(const User* user) { return user->email; }
void set_user_email(User* user, const char* email) {
	strcpy(user->email, email);
}

const char* get_user_current_location(const User* user) { return user->current_location; }
void set_user_current_location(User* user, const char* location) {
	strcpy(user->current_location, location);
}

const char* get_user_preference(const User* user, size_t index) { return user->preferences[index]; }
void set_user_preference(User* user, size_t index, const char* preference) {
	strcpy(user->preferences[index], preference);
}



void show_fill_user_data_menu(User* user)
{
	int status = 0;

	while (status != 1)
	{
		printf("Write a username:\n");
		status = scanf("%s", user->username);
	}

	status = 0;
	while (status != 1)
	{
		printf("Write a born year:\n");
		status = scanf("%d", &user->born_year);
	}

	status = 0;
	while (status != 1)
	{
		printf("Write an email:\n");
		status = scanf("%s", user->email);
	}

	status = 0;
	while (status != 1)
	{
		printf("Write a current location:\n");
		status = scanf("%s", user->current_location);
	}

	for (int i = 0; i < PREFERENCES_COUNT; ++i)
	{
		status = 0;
		while (status != 1)
		{
			printf("Write preference %d/%d:\n", (i + 1), PREFERENCES_COUNT);
			status = scanf("%s", user->preferences[i]);
		}
	}

	printf("\n");
}




void init_users_list(UsersList* list)
{
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
}

void add_user_to_list(UsersList* list, User* user)
{
	UsersListNode* node = (UsersListNode*) malloc(sizeof(UsersListNode));
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

void show_all_users_in_list(UsersList* list)
{
	printf("All users:\n");
	for (UsersListNode* node = list->first; node != NULL; node = node->next)
		printf("    - %s\n", node->user->username);
	printf("\n");
}

void clear_users_list(UsersList* list)
{
	for (UsersListNode *node = list->first, *next; node != NULL; node = next)
	{
		next = node->next;
		free(node->user);
		free(node);
	}

	init_users_list(list);
}

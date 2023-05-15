#include "user.h"


void init_user(User* user)
{
	user->username[0] = '\0';
	user->born_year = 0;
	user->email[0] = '\0';
	user->current_location[0] = '\0';
	
	for (int i = 0; i < PREFERENCES_COUNT; ++i)
		user->preferences[i][0] = '\0';

	init_users_list(&user->friend_requests);
}

User* create_user()
{
	User* user = (User*) malloc(sizeof(User));
	init_user(user);
	return user;
}

void destroy_user(User* user)
{
	clear_user_friend_requests(user);
	free(user);
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

void add_user_friend_request(User* user, User* friend_request)
{
	if (search_user_by_username(&user->friend_requests, friend_request->username) == NULL)
		add_user_to_list(&user->friend_requests, friend_request);
}

const UsersList* get_user_friend_requests(const User* user) { return &user->friend_requests; }

void clear_user_friend_requests(User* user) { clear_users_list(&user->friend_requests, false); }



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
	list->sorted = false;
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
	list->sorted = false;
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
	for (UsersListNode *node = list->first, *next; node != NULL; node = next)
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



User* read_user_from_csv_row(FILE* f)
{
	User* user = create_user();

	char stop;

	stop = read_csv_token(f, user->username);

	if (stop != CSV_SEPARATOR)
	{
		destroy_user(user);
		printf("Invalid CSV row.\n");
		return NULL;
	}
	stop = read_csv_number(f, &user->born_year);

	if (stop != CSV_SEPARATOR)
	{
		destroy_user(user);
		printf("Invalid CSV row.\n");
		return NULL;
	}
	stop = read_csv_token(f, user->email);

	if (stop != CSV_SEPARATOR)
	{
		destroy_user(user);
		printf("Invalid CSV row.\n");
		return NULL;
	}
	stop = read_csv_token(f, user->current_location);

	if (stop != CSV_SEPARATOR)
	{
		destroy_user(user);
		printf("Invalid CSV row.\n");
		return NULL;
	}

	for (int i = 0; i < PREFERENCES_COUNT; ++i)
	{
		if (stop != CSV_SEPARATOR)
		{
			destroy_user(user);
			printf("Invalid CSV row.\n");
			return NULL;
		}
		stop = read_csv_token(f, user->preferences[i]);
	}

	if (stop != CSV_ENDLINE)
	{
		destroy_user(user);
		printf("Invalid CSV row 'endline'.\n");
		return NULL;
	}

	return user;
}

void fill_users_list_from_csv(UsersList* list, const char* filename)
{
	FILE* f = fopen(filename, "r");
	if (!f)
	{
		printf("CSV File '%s' not found.", filename);
		return;
	}

	while (!feof(f))
	{
		User* user = read_user_from_csv_row(f);
		if (user != NULL)
			add_user_to_list(list, user);
	}

	fclose(f);
}

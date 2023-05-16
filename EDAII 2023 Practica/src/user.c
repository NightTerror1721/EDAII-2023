#include "user.h"


void init_user(User* user)
{
	user->username[0] = '\0';
	user->born_year = 0;
	user->email[0] = '\0';
	user->current_location[0] = '\0';
	
	for (int i = 0; i < PREFERENCES_COUNT; ++i)
		user->preferences[i][0] = '\0';

	init_users_queue(&user->friend_requests);
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
	if (search_user_by_username_on_queue(&user->friend_requests, friend_request->username) == NULL)
		enqueue_user(&user->friend_requests, friend_request);
}

bool has_user_friend_requests(User* user)
{
	return !users_queue_empty(&user->friend_requests);
}

User* get_user_next_friend_request(User* user)
{
	return get_users_queue_first(&user->friend_requests);
}

User* remove_user_next_friend_request(User* user)
{
	return dequeue_user(&user->friend_requests);
}

void clear_user_friend_requests(User* user) { clear_users_queue(&user->friend_requests); }



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

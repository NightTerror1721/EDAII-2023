#ifndef __USER_H__
#define __USER_H__

#include "common.h"
#include "user_queue.h"

#define MAX_STRING_LEN 256
#define PREFERENCES_COUNT 5


typedef struct User {
	char username[MAX_STRING_LEN];
	int born_year;
	char email[MAX_STRING_LEN];
	char current_location[MAX_STRING_LEN];
	char preferences[PREFERENCES_COUNT][MAX_STRING_LEN];
	UsersQueue friend_requests;
} User;



void init_user(User* user);

User* create_user();
void destroy_user(User* user);

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

void add_user_friend_request(User* user, User* friend_request);
bool has_user_friend_requests(User* user);
User* get_user_next_friend_request(User* user);
User* remove_user_next_friend_request(User* user);
void clear_user_friend_requests(User* user);


#endif //__USER_H__



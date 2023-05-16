#include "menu.h"


// UTILITY FUNCTIONS //

static User* select_user(const UsersList* users)
{
	char username[MAX_STRING_LEN];
	printf("Type the username of the user you want to select:\n");
	if (scanf("%s", username) != 1)
	{
		printf("Invalid username!\n\n");
		return NULL;
	}

	User* user = search_user_by_username(users, username);
	if (user == NULL)
	{
		printf("Invalid username!\n\n");
		return NULL;
	}
	return user;
}

static void send_friend_request(const UsersList* users, User* main_user)
{
	char username[MAX_STRING_LEN];
	printf("Type the username of the user you want to send a friend request:\n");
	if (scanf("%s", username) != 1)
	{
		printf("Invalid username!\n\n");
		return;
	}

	User* friend_request = search_user_by_username(users, username);
	if (friend_request == NULL)
	{
		printf("Invalid username!\n\n");
		return;
	}

	add_user_friend_request(main_user, friend_request);
	printf("Friend request to user '%s' sent successfully.\n\n", username);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_user_menu(UsersList* users)
{
	User* selected_user = select_user(users);
	if (selected_user == NULL)
		return;

	int option = -1;
	while (option != 6)
	{
		printf("User '%s' menu:\n", get_user_username(selected_user));
		printf("    1) Send friend requests\n");
		printf("    2) Show several random users\n");
		printf("    3) Manage pending requests\n");
		printf("    4) Make a post\n");
		printf("    5) Show user posts\n");
		printf("    6) Back\n\n");

		option = read_option();
		switch (option)
		{
		case 1:
			send_friend_request(users, selected_user);
			break;

		case 2:
			show_unknown_friends_menu(selected_user, users);
			break;

		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;

		default:
			printf("Invalid option.\n\n");
			break;
		}
	}
}

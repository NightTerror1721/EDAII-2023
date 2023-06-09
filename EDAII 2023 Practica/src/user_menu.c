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

	add_user_friend_request(friend_request, main_user);
	printf("Friend request to user '%s' sent successfully.\n\n", username);
}

static void manage_pending_requests(User* main_user)
{
	while (has_user_friend_requests(main_user))
	{
		User* req = get_user_next_friend_request(main_user);
		
		int option = -1;
		while (option < 1 || option >= 3)
		{
			printf("The user '%s' has sent you a friend request. What do you want to do?\n", get_user_username(req));
			printf("    1) Accept\n");
			printf("    2) Decline\n");
			printf("    3) Back\n\n");

			option = read_option();
			switch (option)
			{
				case 1:
					accept_user_next_friend_request(main_user);
					break;

				case 2:
					decline_user_next_friend_request(main_user);
					break;

				case 3: break;

				default:
					printf("Invalid option.\n\n");
					break;
			}
		}
	}
}

static void make_a_post(User* main_user)
{
	char text[MAX_POST_LEN + 1];

	printf("Write the text of the post (max 120 characters):\n");

	fgets(text, MAX_POST_LEN, stdin);

	//We empty the rest of the characters that may have remained in the terminal (This happens if we have written more than 120 characters)
	consume_stdin();

	const size_t text_len = strlen(text);
	bool valid_post = false;
	for (int i = 0; i < text_len; ++i)
	{
		if (text[i] != ' ')
		{
			valid_post = true;
			break;
		}
	}

	if (!valid_post)
		printf("\n\nInvalid or empty post text.\n\n");
	else
	{
		add_user_post(main_user, text);
		printf("\n\nPost created successfully!\n\n");
	}
}

static void print_user_timeline(User* main_user)
{
	PostsList* timeline = get_user_timeline(main_user);
	for (const Post* post = get_first_post_on_list(timeline); post != NULL; post = get_next_post(post))
		printf("    - %s\n\n", get_post_text(post));
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

		case 3:
			manage_pending_requests(selected_user);
			break;

		case 4:
			make_a_post(selected_user);
			break;

		case 5:
			print_user_timeline(selected_user);
			break;

		case 6: break;

		default:
			printf("Invalid option.\n\n");
			break;
		}
	}
}

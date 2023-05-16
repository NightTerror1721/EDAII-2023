#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "user_stack.h"
#include "csv.h"


void show_main_menu(UsersList* users);


int main()
{
	UsersList users;
	init_users_list(&users);

	fill_users_list_from_csv(&users, "users.csv");

	show_main_menu(&users);

	clear_users_list(&users, true);
	return 0;
}





int read_option(void)
{
	int value;
	if (scanf("%d", &value) != 1)
		return -1;

	return value;
}

void fill_stack_with_n_random_users_from_list(UsersStack* stack, const UsersList* list, size_t n)
{
	n = MIN(n, users_list_size(list));
	if (n <= 0)
		return;

	for (size_t i = 0; i < n; ++i)
	{
		size_t idx = (size_t)random_int((int)n);
		UsersListNode* node = list->first;
		while (idx > 0)
		{
			node = node->next;
			idx--;
		}

		push_users_stack(stack, node->user);
	}
}

void show_unknown_friends_menu(const UsersList* users, User* main_user)
{
	UsersStack stack;
	init_users_stack(&stack);
	
	fill_stack_with_n_random_users_from_list(&stack, users, 3);

	printf("We are going to show you a few users in case you want to send them a friend request:\n");

	while (!users_stack_empty(&stack))
	{
		User* user = pop_users_stack(&stack);
		if (user != NULL)
		{
			int option = -1;
			while (option < 1 || option > 3)
			{
				printf("Do you want to send the user '%s' a friend request?:\n", get_user_username(user));
				printf("    1) Yes\n");
				printf("    2) No\n");
				printf("    3) Cancel\n\n");

				option = read_option();
				switch (option)
				{
					case 1:
						add_user_friend_request(main_user, user);
						break;

					case 2: break;
					case 3:
						clear_users_stack(&stack);
						break;

				default:
					printf("Invalid option.\n\n");
					break;
				}
			}
		}
	}

	printf("\n");
}





User* select_user(const UsersList* users)
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

void send_friend_request(const UsersList* users, User* main_user)
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
				show_unknown_friends_menu(users, selected_user);
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

void create_new_user(UsersList* users)
{
	User* user = create_user();

	show_fill_user_data_menu(user);
	add_user_to_list(users, user);
}

void show_main_menu(UsersList* users)
{
	int option = -1;
	while (option != 4)
	{
		printf("Main menu:\n");
		printf("    1) Insert new user\n");
		printf("    2) Show all users\n");
		printf("    3) Operate as specific user\n");
		printf("    4) Exit\n\n");

		option = read_option();
		switch (option)
		{
			case 1:
				create_new_user(users);
				break;

			case 2:
				show_all_users_in_list(users);
				break;

			case 3:
				show_user_menu(users);
				break;

			case 4: break;

			default:
				printf("Invalid option.\n\n");
				break;
		}
	}
}

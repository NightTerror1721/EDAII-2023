#include <stdio.h>
#include <stdlib.h>

#include "user.h"


void show_main_menu(UsersList* users);


int main()
{
	UsersList users;
	init_users_list(&users);

	show_main_menu(&users);

	clear_users_list(&users);
	return 0;
}





int read_option(void)
{
	int value;
	if (scanf("%d", &value) != 1)
		return -1;

	return value;
}

void show_user_menu(void)
{
	int option = -1;
	while (option != 5)
	{
		printf("User menu:\n");
		printf("    1) Send frend requests\n");
		printf("    2) Manage pending requests\n");
		printf("    3) Make a post\n");
		printf("    4) Show user posts\n");
		printf("    5) Back\n\n");

		option = read_option();
		switch (option)
		{
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;

		default:
			printf("Invalid option.\n\n");
			break;
		}
	}
}

void create_new_user(UsersList* users)
{
	User* user = (User*) malloc(sizeof(User));

	init_user(user);
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
				show_user_menu();
				break;

			case 4: break;

			default:
				printf("Invalid option.\n\n");
				break;
		}
	}
}

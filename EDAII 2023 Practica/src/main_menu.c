#include "menu.h"


// UTILITY FUNCTIONS //

static void create_new_user(UsersList* users)
{
	User* user = create_user();

	show_fill_user_data_menu(user);
	add_user_to_list(users, user);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

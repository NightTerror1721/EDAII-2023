#include "menu.h"

#include "user_stack.h"


// UTILITY FUNCTIONS //

static void fill_stack_with_n_random_users_from_list(UsersStack* stack, const UsersList* list, size_t n)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_unknown_friends_menu(User* current_user, const UsersList* users)
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
					add_user_friend_request(current_user, user);
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

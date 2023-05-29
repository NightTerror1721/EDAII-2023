#include <stdio.h>
#include <stdlib.h>

#include "csv.h"
#include "menu.h"


int main()
{
	trendings_init();

	UsersList users;
	init_users_list(&users);

	fill_users_list_from_csv(&users, "users.csv");

	show_main_menu(&users);

	clear_users_list(&users, true);
	trendings_clear();
	return 0;
}

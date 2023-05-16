#include "menu.h"


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

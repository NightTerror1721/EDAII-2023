#include "csv.h"


User* read_user_from_csv_row(FILE* f)
{
	User* user = create_user();

	char stop;

	stop = read_csv_token(f, user->username);

	if (stop != CSV_SEPARATOR)
	{
		destroy_user(user);
		printf("Invalid CSV row.\n");
		return NULL;
	}
	stop = read_csv_number(f, &user->born_year);

	if (stop != CSV_SEPARATOR)
	{
		destroy_user(user);
		printf("Invalid CSV row.\n");
		return NULL;
	}
	stop = read_csv_token(f, user->email);

	if (stop != CSV_SEPARATOR)
	{
		destroy_user(user);
		printf("Invalid CSV row.\n");
		return NULL;
	}
	stop = read_csv_token(f, user->current_location);

	if (stop != CSV_SEPARATOR)
	{
		destroy_user(user);
		printf("Invalid CSV row.\n");
		return NULL;
	}

	for (int i = 0; i < PREFERENCES_COUNT; ++i)
	{
		if (stop != CSV_SEPARATOR)
		{
			destroy_user(user);
			printf("Invalid CSV row.\n");
			return NULL;
		}
		stop = read_csv_token(f, user->preferences[i]);
	}

	if (stop != CSV_ENDLINE)
	{
		destroy_user(user);
		printf("Invalid CSV row 'endline'.\n");
		return NULL;
	}

	return user;
}

void fill_users_list_from_csv(UsersList* list, const char* filename)
{
	FILE* f = fopen(filename, "r");
	if (!f)
	{
		printf("CSV File '%s' not found.", filename);
		return;
	}

	while (!feof(f))
	{
		User* user = read_user_from_csv_row(f);
		if (user != NULL)
			add_user_to_list(list, user);
	}

	fclose(f);
}

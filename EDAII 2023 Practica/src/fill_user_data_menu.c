#include "menu.h"


// UTILITY FUNCTIONS //

static bool scan_string_limited(char* buffer, size_t max_len)
{
	if (fgets(buffer, max_len, stdin) == NULL)
		return false;

	size_t len = strlen(buffer);
	if (len >= max_len - 1) //Si esto pasa, quedan caracteres por leer. Tenemos que descartarlos
		consume_stdin();

	if (len <= 1)
		return false;

	if (buffer[len - 1] == '\n')
		buffer[len - 1] = '\0';

	return true;
}

static bool scan_string(char* buffer)
{
	return scan_string_limited(buffer, MAX_STRING_LEN);
}

static bool scan_int(int* out)
{
	char buffer[16];
	if (!scan_string_limited(buffer, 16))
		return false;

	int result = sscanf(buffer, "%d", out);
	if (result != 1)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_fill_user_data_menu(User* user)
{
	bool status = false;

	while (!status)
	{
		printf("Write a username:\n");
		status = scan_string(user->username);
	}

	status = false;
	while (!status)
	{
		printf("Write a born year:\n");
		status = scan_int(&user->born_year);
	}

	status = false;
	while (!status)
	{
		printf("Write an email:\n");
		status = scan_string(user->email);
	}

	status = false;
	while (!status)
	{
		printf("Write a current location:\n");
		status = scan_string(user->current_location);
	}

	for (int i = 0; i < PREFERENCES_COUNT; ++i)
	{
		status = false;
		while (!status)
		{
			printf("Write preference %d/%d:\n", (i + 1), PREFERENCES_COUNT);
			status = scan_string(user->preferences[i]);
		}
	}

	printf("\n");
}

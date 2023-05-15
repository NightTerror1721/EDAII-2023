#include "user_stack.h"

#include <stdlib.h>


void init_users_stack(UsersStack* stack)
{
	stack->top = NULL;
}

bool users_stack_empty(const UsersStack* stack) { return stack->top != NULL; }

void push_users_stack(UsersStack* stack, User* user)
{
	UsersStackNode* node = (UsersStackNode*) malloc(sizeof(UsersStackNode));
	node->user = user;
	node->next = stack->top;
	stack->top = node;
}

User* pop_users_stack(UsersStack* stack)
{
	if (!users_stack_empty(stack))
	{
		UsersStackNode* node = stack->top;
		stack->top = node->next;
		User* user = node->user;
		free(node);
		return user;
	}
	return NULL;
}

User* get_users_stack_top(const UsersStack* stack)
{
	if (!users_stack_empty(stack))
		return stack->top->user;
	return NULL;
}

void clear_users_stack(UsersStack* stack)
{
	for (UsersStackNode* node = stack->top, *next; node != NULL; node = next)
	{
		next = node;
		free(node);
	}

	init_users_stack(stack);
}


void fill_stack_with_n_random_users_from_list(UsersStack* stack, const UsersList* list, size_t n)
{
	n = MIN(n, users_list_size(list));
	if (n <= 0)
		return;

	for (size_t i = 0; i < n; ++i)
	{
		size_t idx = (size_t) random_int(n);
		UsersListNode* node = list->first;
		while (idx > 0)
		{
			node = node->next;
			idx--;
		}

		push_users_stack(stack, node->user);
	}
}

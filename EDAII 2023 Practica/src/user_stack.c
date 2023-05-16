#include "user_stack.h"
#include "user.h"


void init_users_stack(UsersStack* stack)
{
	stack->top = NULL;
}

bool users_stack_empty(const UsersStack* stack) { return stack->top == NULL; }

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
		next = node->next;
		free(node);
	}

	init_users_stack(stack);
}

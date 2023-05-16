#ifndef __USER_STACK_H__
#define __USER_STACK_H__

#include "common.h"


typedef struct User User;

typedef struct UsersStackNode {
	User* user;
	struct UsersStackNode* next;
} UsersStackNode;

typedef struct {
	UsersStackNode* top;
} UsersStack;


void init_users_stack(UsersStack* stack);

bool users_stack_empty(const UsersStack* stack);

void push_users_stack(UsersStack* stack, User* user);

User* pop_users_stack(UsersStack* stack);

User* get_users_stack_top(const UsersStack* stack);

void clear_users_stack(UsersStack* stack);


#endif //__USER_STACK_H__

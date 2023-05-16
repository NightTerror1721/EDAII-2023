#ifndef __USER_QUEUE_H__
#define __USER_QUEUE_H__

#include "common.h"


typedef struct User User;

typedef struct UsersQueueNode {
	User* user;
	struct UsersQueueNode* next;
} UsersQueueNode;

typedef struct {
	UsersQueueNode* first;
	UsersQueueNode* last;
} UsersQueue;


void init_users_queue(UsersQueue* queue);

bool users_queue_empty(const UsersQueue* queue);

void enqueue_user(UsersQueue* queue, User* user);

User* dequeue_user(UsersQueue* queue);

User* get_users_queue_first(const UsersQueue* queue);

void clear_users_queue(UsersQueue* queue);


User* search_user_by_username_on_queue(const UsersQueue* queue, const char* username);


#endif //__USER_QUEUE_H__

#include "user_queue.h"

#include "user.h"


void init_users_queue(UsersQueue* queue)
{
	queue->first = NULL;
	queue->last = NULL;
}

bool users_queue_empty(const UsersQueue* queue) { return queue->first == NULL; }

void enqueue_user(UsersQueue* queue, User* user)
{
	UsersQueueNode* node = (UsersQueueNode*) malloc(sizeof(UsersQueueNode));
	node->user = user;
	node->next = NULL;

	if (queue->last == NULL)
	{
		queue->first = node;
		queue->last = node;
	}
	else
	{
		queue->last->next = node;
		queue->last = node;
	}
}

User* dequeue_user(UsersQueue* queue)
{
	if (users_queue_empty(queue))
		return NULL;

	User* user = queue->first->user;
	if (queue->first == queue->last)
	{
		free(queue->first);
		queue->first = NULL;
		queue->last = NULL;
	}
	else
	{
		UsersQueueNode* node = queue->first;
		queue->first = node->next;
		free(node);
	}
	return user;
}

User* get_users_queue_first(const UsersQueue* queue)
{
	if (users_queue_empty(queue))
		return NULL;

	return queue->first->user;
}

void clear_users_queue(UsersQueue* queue)
{
	for (UsersQueueNode *node = queue->first, *next; node != NULL; node = next)
	{
		next = node;
		free(node);
	}

	init_users_queue(queue);
}



User* search_user_by_username_on_queue(const UsersQueue* queue, const char* username)
{
	for (UsersQueueNode* node = queue->first; node != NULL; node = node->next)
		if (strcmp(node->user->username, username) == 0)
			return node->user;

	return NULL;
}

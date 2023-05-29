#include "post.h"


void init_posts_list(PostsList* list)
{
	list->first = NULL;
	list->size = 0;
}

void clear_posts_list(PostsList* list)
{
	Post* post = list->first;
	while (post != NULL)
	{
		Post* next = post->next;
		free(post);
		post = next;
	}

	init_posts_list(list);
}

bool posts_list_empty(const PostsList* list) { return list->first == NULL; }

size_t posts_list_size(const PostsList* list) { return list->size; }

const Post* post_text_on_list(PostsList* list, const char* text)
{
	Post* post = (Post*) malloc(sizeof(Post));
	post->next = list->first;
	list->first = post;

	strncpy(post->text, text, MAX_POST_LEN);
	post->text[MAX_POST_LEN] = '\0';

	return post;
}

const Post* get_first_post_on_list(const PostsList* list)
{
	if (posts_list_empty(list))
		return NULL;

	return list->first;
}


bool has_next_post(const Post* post) { return post->next != NULL; }

const Post* get_next_post(const Post* post) { return post->next; }

const char* get_post_text(const Post* post) { return post->text; }

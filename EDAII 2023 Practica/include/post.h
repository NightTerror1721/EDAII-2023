#ifndef __POST_H__
#define __POST_H__

#include "common.h"

#define MAX_POST_LEN 120


typedef struct Post {
	char text[MAX_POST_LEN + 1];
	struct Post* next;
} Post;

typedef struct {
	Post* first;
	size_t size;
} PostsList;


void init_posts_list(PostsList* list);

void clear_posts_list(PostsList* list);

bool posts_list_empty(const PostsList* list);

size_t posts_list_size(const PostsList* list);

const Post* post_text_on_list(PostsList* list, const char* text);

const Post* get_first_post_on_list(const PostsList* list);


bool has_next_post(const Post* post);
const Post* get_next_post(const Post* post);
const char* get_post_text(const Post* post);

#endif //__POST_H__

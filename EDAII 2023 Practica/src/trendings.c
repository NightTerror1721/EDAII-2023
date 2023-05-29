#include "trendings.h"

#define TOP_LEN 10

// PRIVATE THINGS //

typedef struct TrendingTableBucket {
	char word[MAX_TRENDING_LEN];
	size_t count;
	struct TrendingTableNode* next;
} TrendingTableBucket;

typedef struct {
	TrendingTableBucket* array[HASHTABLE_ARRAY_LEN];
	size_t size;
} TrendingsTable;

static TrendingsTable Trendings;



static int trendings_hash(const char* word)
{
	size_t len = strlen(word);
	int sum = 0;
	for (int i = 0; i < len; ++i)
		sum += (int) word[i];
	return sum % HASHTABLE_ARRAY_LEN;
}

static TrendingTableBucket* trendings_find_bucket(const char* word)
{
	int hash = trendings_hash(word);
	for (TrendingTableBucket* bucket = Trendings.array[hash]; bucket != NULL; bucket = bucket->next)
	{
		if (strcmp(bucket->word, word) == 0)
			return bucket;
	}
	return NULL;
}

static void trendings_find_top_10(const TrendingTableBucket* top[TOP_LEN])
{
	for (int i = 0; i < TOP_LEN; ++i)
		top[i] = NULL;

	for (int i = 0; i < HASHTABLE_ARRAY_LEN; ++i)
	{
		for (TrendingTableBucket* bucket = Trendings.array[i]; bucket != NULL; bucket = bucket->next)
		{
			for (int j = 0; j < TOP_LEN; ++j)
			{
				if (top[j] == NULL || top[j]->count < bucket->count)
				{
					for (int k = TOP_LEN - 2; k >= j; --k)
						top[k + 1] = top[k];

					top[j] = bucket;
				}
			}
		}
	}
}



// PUBLIC THINGS //

void trendings_init()
{
	for (int i = 0; i < HASHTABLE_ARRAY_LEN; ++i)
		Trendings.array[i] = NULL;

	Trendings.size = 0;
}

void trendings_clear()
{
	for (int i = 0; i < HASHTABLE_ARRAY_LEN; ++i)
	{
		TrendingTableBucket* bucket = Trendings.array[i];
		while (bucket != NULL)
		{
			TrendingTableBucket* next = bucket->next;
			free(bucket);
			bucket = next;
		}
	}

	trendings_init();
}

size_t trendings_add_word(const char* word)
{
	TrendingTableBucket* bucket = trendings_find_bucket(word);
	if (bucket != NULL)
	{
		bucket->count++;
		return bucket->count;
	}

	bucket = (TrendingTableBucket*) malloc(sizeof(TrendingTableBucket));
	bucket->count = 1;
	strcpy(bucket->word, word);

	int hash = trendings_hash(word);
	if (Trendings.array[hash] == NULL)
		bucket->next = Trendings.array[hash];
	else
		bucket->next = NULL;
	
	Trendings.array[hash] = bucket;
	return 1;
}

void trendings_add_words_from_text(const char* text)
{
	const size_t text_len = strlen(text);

	char word[MAX_TRENDING_LEN];
	size_t word_len = 0;

	for (size_t i = 0; i < text_len; ++i)
	{
		if (text[i] == ' ')
		{
			if (word_len > 0)
			{
				word[word_len] = '\n';
				trendings_add_word(word);
			}
			word_len = 0;
		}
		else
		{
			word[word_len] = text[i];
			word_len++;
		}
	}
}

void trendings_print_top_10()
{
	const TrendingTableBucket* top[TOP_LEN];
	trendings_find_top_10(top);

	printf("Top 10 trending topics:\n");
	for (int i = 0; i < TOP_LEN; ++i)
		if (top[i] != NULL)
			printf("    %d: %s\n", (i + 1), top[i]->word);
	printf("\n\n");
}

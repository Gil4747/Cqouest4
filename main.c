#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define alphabet size (a-z)
#define NUM_LETTERS ((int)26)

// max length of sentence from the user
#define MAX_SENTENCE_LENGTH 2500
#define MAX_WORD_LENGTH 250

typedef enum {FALSE=0, TRUE=1} boolean;

// A Trie node
struct Trie
{
	int isLeaf;
	unsigned int count;
	struct Trie* character[NUM_LETTERS];
};

// Creates new trie node
struct Trie* createNewTrieNode()
{
	struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
	node->isLeaf = 0;
	node->count = 0;
	for (int i = 0; i < NUM_LETTERS; i++)
		node->character[i] = NULL;
	return node;
}

void destroyTrie(struct Trie* node)
{
	for (int i = 0; i < NUM_LETTERS; i++)  
    {
        if (node->character[i])  
        { 
        	destroyTrie(node->character[i]);
        } 
    } 
	free(node);
}

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

void insert(struct Trie* head, char* str)
{
	struct Trie* curr = head;
	while (*str)
	{
		if (curr->character[*str - 'a'] == NULL)
			curr->character[*str - 'a'] = createNewTrieNode();
		curr = curr->character[*str - 'a'];
		str++;
	}
	curr->count++;
	curr->isLeaf = 1;
}

void print_all(struct Trie* curr, char* str, int level, boolean reversed)
{
	if(curr == NULL){
		return;
	}

    if (curr->isLeaf)  
    { 
        str[level] = '\0'; 
        printf("%s\t%d\n", str, curr->count); 
    } 
  
  	if(reversed == TRUE){
  		for (int i = NUM_LETTERS - 1; i >= 0; i--)  
	    {
	        if (curr->character[i])  
	        { 
	            str[level] = i + 'a'; 
	            print_all(curr->character[i], str, level + 1, reversed); 
	        } 
	    } 
  		return;
  	}

    for (int i = 0; i < NUM_LETTERS; i++)  
    {
        if (curr->character[i])  
        { 
            str[level] = i + 'a'; 
            print_all(curr->character[i], str, level + 1, reversed); 
        } 
    } 
}

int main(int argc, char **argv)
{
	boolean reversed = FALSE;
	if(argc > 0 && strcmp(argv[1], "r") == 0){
		reversed = TRUE;
	}

	struct Trie* head = createNewTrieNode();

	char msg[MAX_SENTENCE_LENGTH];
	int i = 0;
	char ch;

	while ((ch = getchar()) != '\n') 
	{
		if ('A' <= ch && ch <= 'Z')
		{
			ch = 'a' + (ch - 'A');
		}
		if(('a' <= ch && ch <= 'z') || ch == ' ')
		{
    		msg[i++] = ch;
		}
	}

    msg[i] = '\0';

    char* token = strtok(msg, " ");
	while (token != NULL) {
		insert(head, token);
		token = strtok(NULL, " ");
	}

	char word[MAX_WORD_LENGTH] = { 0 };
	int level = 0;
	print_all(head, word, level, reversed);

	destroyTrie(head);
	return 0;
}

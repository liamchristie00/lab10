#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie *next[26];
};
struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie* tree, char word[]) {
    for (int i = 0; i < strlen(word); i++) {

        if (tree == NULL) {
            printf("NULL tree\n");
            return;
        }
        
        int nextIndex = word[i] - 'a';
        if (nextIndex < 0 || nextIndex >= 26) {
            return;
        }
        
        if (tree->next[nextIndex] == NULL) {
            tree->next[nextIndex] = createTrie();
            if (tree->next[nextIndex] == NULL) {
                printf("Memory allocation failed\n");
                return;
            }
        }     
    }
    tree->count += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL || word == NULL) {
        printf("Invalid arguments\n");
        return 0;
    }

    struct Trie *temp = pTrie;
    for (int i = 0; i < strlen(word); i++)
    {
        int nextIndex = word[i] - 'a';
        if (temp->next[nextIndex] == NULL)
        {
            printf("\ntriggered %s", temp->next[nextIndex]);
            return 0;
        }
        temp = temp->next[nextIndex];
    }

    if(temp->count > 0)
    {
        return pTrie->count;
    }

    printf("\nword");
    return 0;
    
}
// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for (int i = 0; i < 26; i++)
    {
        if (pTrie->next[i] != NULL)
        {
            deallocateTrie(pTrie->next[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->count = 0;
    for (int i = 0; i < 26; i++)
    {
        pTrie->next[i] = NULL;
    }
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: File not found\n");
        return 0;
    }
    int numWords = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = (char *)malloc(strlen(word) + 1);
        strcpy(pInWords[numWords], word);
        numWords++;
    }
    fclose(file);
    return numWords;

}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
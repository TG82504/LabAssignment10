#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    char data;
    struct Trie *children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if (*word == '\0') {
        return;
    }
    int index = *word - 'a';
    if (!pTrie->children[index]) {
        pTrie->children[index] = malloc(sizeof(struct Trie));
        pTrie->children[index]->data = *word;
    }
    
    insert(pTrie->children[index], word+1);
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (*word == '\0') {
        return 1;
    }
    
    int index = *word - 'a';
    if (!pTrie->children[index]) {
        return 0;
    }
    
    return numberOfOccurances(pTrie->children[index], word+1);
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i = 0; i < 26; i++) {
        if (pTrie->children[i] != NULL) {
            deallocateTrie(pTrie->children[i]);
        }
        else {
            continue;
        }
    }
    free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = malloc(sizeof(struct Trie));
    pTrie->data = '\0';
    
    for (int i = 0; i < 26; i++) {
        pTrie->children[i] = NULL;
    }
    
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    
    int numWords = 0;
    char word[256];
    
    while(fscanf(fp, "%s", word) != EOF) {
        pInWords[numWords] = malloc(strlen(word) + 1);
        strcpy(pInWords[numWords], word);
        numWords++;
    }
    
    fclose(fp);
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
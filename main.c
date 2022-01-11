/* Name: Thomas Green
 * ID: 1048389
 * Date: March 27 2021
 * Assignment #: 4
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "header.h"


int main (int argc, char *argv[]) {

  int selection;
  struct node *root;
  struct wordArray wordArray;
  char inputString[100];

  printf("*===================================================================================*\n");
  printf("|   Option 1: Create optimal BST by using the technique of dynamic programming (Q1) |\n");
  printf("|   Option 2: Create optimal BST by using the greedy technique                      |\n");
  printf("*===================================================================================*\n\n");

  /* Choose which algorithm to test */
  printf("Please make a selection: ");
  scanf("%d", &selection);

  if (selection < 1 || selection > 8)
  {
    printf("Invalid selection\n");
    return 0;
  }

  /* Choose word to search for */
  printf("Enter a key: ");
  scanf("%s", inputString);
  printf("\n");

  /* Get the sorted word array */
  wordArray = getWordArray();

  /* Create BST using the dynamic programming algorithm */
  if (selection == 1)
  {
    root = getBSTDynamicProgramming(wordArray);
  }
  /* Create BST using the greedy technique */
  else if (selection == 2)
  {
    root = NULL;
    root = getBSTGreedyTechnique(wordArray, root, 0, wordArray.numDistinctWords - 1);
  }

  /* Search the BST for the word input */
  searchBST(root, inputString, selection);

  return 0;
}


/* Reads in words from data.txt and stores them into an array (sorted alphebetically)
 * @return structure containing the sorted array of words
 */
struct wordArray getWordArray() {

  FILE *fp;
  struct wordArray wordArray;
  char word[100];
  int i;
  bool isNew;

  fp = fopen("data.txt", "rb");
  fseek(fp, 0, SEEK_SET);

  wordArray.words = (struct word*)malloc(0);
  wordArray.numDistinctWords = 0;
  wordArray.numWords = 0;

  /* While fp is within the file */
  while (!feof (fp))
  {
    /* Scan a word, increment numWords */
    fscanf(fp, "%s", word);
    isNew = true;
    i = 0;
    wordArray.numWords++;

    /* Compare this word with every other word in the current wordArray and check to see if it is a new distinct word */
    while (i < wordArray.numDistinctWords && isNew == true)
    {
      /* If this word is found to already be in the current word array, increment repetitions for that word */
      if (strcmp(word, wordArray.words[i].ptr) == 0)
      {
        isNew = false;
        wordArray.words[i].repetitions++;
      }
      i++;
    }

    /* If this is a new word, add it to the current word array and increment numDistinctWords */
    if (isNew == true)
    {
      wordArray.words = (struct word*)realloc(wordArray.words, (wordArray.numDistinctWords+1) * sizeof(struct word));
      wordArray.words[wordArray.numDistinctWords].ptr = (char*) malloc((strlen(word)) * sizeof(char));
      strcpy(wordArray.words[wordArray.numDistinctWords].ptr, word);
      wordArray.words[wordArray.numDistinctWords].repetitions = 1;
      wordArray.numDistinctWords++;
    }
  }

  /* Compute the probability of each word in the word array */
  for (i = 0; i < wordArray.numDistinctWords; i++)
  {
    wordArray.words[i].probability = (float)wordArray.words[i].repetitions / wordArray.numWords;
  }

  fclose(fp);

  /* Sort the word array using the utility function sortWordArray */
  wordArray = sortWordArray (wordArray);

  return wordArray;
}


/* Utility function of getWordArray. Sorts the word array alphabetically
 * @param wordArray: array containing words
 * @return the sorted word array
 */
struct wordArray sortWordArray(struct wordArray wordArray)
{
  int i;
  int j;
  int minIndex;
  struct word tempWord;

  /* Use selection sort to sort word array */
  for (i = 0; i < wordArray.numDistinctWords - 1; i++)
  {
    minIndex = i;
    for (j = i + 1; j < wordArray.numDistinctWords; j++)
    {
      if (strcmp(wordArray.words[minIndex].ptr, wordArray.words[j].ptr) > 0)
      {
        minIndex = j;
      }
    }
    tempWord = wordArray.words[i];
    wordArray.words[i] = wordArray.words[minIndex];
    wordArray.words[minIndex] = tempWord;
  }

  return wordArray;
}


/* Recursively searches through a BST for a given input string
 * @param node: Node pointer
 * @param inputString: The input string to be searched for
 * @param mode: Determines whether a word's probability or minimum average number of comparisions is printed (differ for Q1/Q2)
 */
void searchBST(struct node *node, char *inputString, int mode)
{
  /* If a NULL pointer is found, end search; word cannot be found */
  if (node == NULL)
  {
    printf("Not found.\n");
    return;
  }
  /* If Q1 is being tested, need to print probability assossiated with a given word */
  if (mode == 1)
  {
    printf("Compared with %s (%.3f), ", node->word->ptr, node->word->aveNumCom);
  }
  /* If Q2 is being tested, need to print the minimum average number of comparisons assossiated with a given word */
  else
  {
    printf("Compared with %s (%.3f), ", node->word->ptr, node->word->probability);
  }

  /* If the word is found */
  if (strcmp(node->word->ptr, inputString) == 0)
  {
    printf("found.\n");
  }
  /* If the current node's word precedes the input string when sorted alphabetically, go left */
  else if(strcmp(node->word->ptr, inputString) > 0)
  {
    printf("go left subtree.\n");
    searchBST(node->leftChild, inputString, mode);
  }
  /* If the current node's word succeeds the input string when sorted alphabetically, go right */
  else
  {
    printf("go right subtree.\n");
    searchBST(node->rightChild, inputString, mode);
  }
}

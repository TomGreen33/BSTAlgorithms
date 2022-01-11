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


 /* Creates an optimized BST using the dynamic programming technique
  * @param wordArray: Sorted word array from which the tree will be created
  * @return the root of the optimized BST
  */
struct node *getBSTDynamicProgramming(struct wordArray wordArray) {

  int i;
  int j;
  int d;
  int k;
  int s;
  int n;
  float **C;    /* Average number table */
  int **R;      /* Root table */
  float minVal;
  float sum;
  int kMin;
  struct node *root;

  /* Allocate memory for the BST root */
  root = (struct node*)malloc(sizeof(struct node));

  n = wordArray.numDistinctWords;

  /* Allocate memory for the average number table and root table */
  C = (float **)malloc((n+1) * sizeof(float*));
  R = (int **)malloc((n+1) * sizeof(int*));
  for (i = 0; i <= n; i++)
  {
    C[i] = (float*)malloc((n+1) * sizeof(float));
    R[i] = (int*)malloc((n+1) * sizeof(int));
  }
  /* Initialize both tables with all 0's */
  for (i = 0; i <= n; i++)
  {
    for (j = 0; j <= n; j++)
    {
      C[i][j] = 0;
      R[i][j] = 0;
    }
  }
  /* Write the first diagonal of each table with their respective probablities/roots */
  for (i = 0; i <= n; i++)
  {
    C[i][i+1] = wordArray.words[i].probability;
    R[i][i+1] = i+1;
  }

  /* For each additional diagonal of each table */
  for (d = 2; d <=n; d++)
  {
    /* For each element in a given diagonal */
    for (i = 0; i <= n-d; i++)
    {
      j = i + d;
      minVal = 10000000;

      /* Search for the smallest sum C(i, k) and C(k+1, j) */
      for (k = i; k < j; k++)
      {
        if ((C[i][k] + C[k+1][j]) < minVal)
        {
          minVal = C[i][k] + C[k+1][j];
          kMin = k;
        }
      }
      /* Record the corresponding optimal root in the root table */
      R[i][j] = kMin+1;

      /* Compute the average number of comparisions for the corresponding optimized
      *  sub tree and record it in the average number table */
      sum = wordArray.words[i].probability;
      for (s = i+1; s < j; s++)
      {
        sum += wordArray.words[s].probability;
      }
      C[i][j] = minVal + sum;
    }
  }

  /* Shifting root table 1 row down such that it is easier to index */
  for (i = n; i > 0; i--)
  {
    for (j = 0; j <= n; j++)
    {
      R[i][j] = R[i-1][j];
    }
  }

  /* Build the BST now that the word array and corresponding root table and known */
  root = build(root, wordArray, 1, n, R, C);

  return root;
}


/* Recursively builds an optimized BST using the root table
 * @param node: The root of the subtree being created
 * @param wordArray: Word array
 * @param i: Leftmost index of the subtree being created
 * @param j: Rightmost index of the subtree being created
 * @param R: Root table
 * @param C: Average number table
 * @return the root of the optimized BST
 */
struct node* build(struct node *node, struct wordArray wordArray, int i, int j, int **R, float **C) {

  int k; /* The root of the optimized subtree */

  /* Assign k with the corresponding value from the root table */
  k = R[i][j];

  /* Assign the root of the current subtree with the corresponding word/average number of comparisons */
  node->word = &wordArray.words[k-1];
  node->word->aveNumCom = C[i][j];

  /* If both left and right subtrees have elements left to assign */
  if (i < k && k < j)
  {
    node->leftChild = (struct node*)malloc(sizeof(struct node));
    node->rightChild = (struct node*)malloc(sizeof(struct node));
    node->leftChild = build(node->leftChild, wordArray, i, k-1, R, C);
    node->rightChild = build(node->rightChild, wordArray, k+1, j, R, C);
  }
  /* If there are no more elements to be assigned */
  else if (i == j && i == k)
  {
    node->leftChild = NULL;
    node->rightChild = NULL;
  }
  /* If the left subtree contains no elements left to be assigned but the right one does */
  else if (k == i)
  {
    node->leftChild = NULL;
    node->rightChild = (struct node*)malloc(sizeof(struct node));
    node->rightChild = build(node->rightChild, wordArray, i+1, j, R, C);
  }
  /* If the right subtree contains no elements left to be assigned but the left one does */
  else if (k == j)
  {
    node->rightChild = NULL;
    node->leftChild = (struct node*)malloc(sizeof(struct node));
    node->leftChild = build(node->leftChild, wordArray, i, j-1, R, C);
  }

  return node;
}

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


/* Creates an optimized BST using the greedy technique
 * @param wordArray: Sorted word array from which the tree will be created
 * @param node: The root of the subtree being created
 * @param left: Leftmost index of the subtree being created
 * @param right: Rightmost index of the subtree being created
 * @return the root of the optimized BST
 */
 struct node *getBSTGreedyTechnique(struct wordArray wordArray, struct node *node, int left, int right) {

   int i;
   int maxIndex;
   float maxProbability;

   maxIndex = left;
   maxProbability = wordArray.words[left].probability;

   /* If the current subtree is the final tree, allocate memory for its root */
   if (left == 0 && right == wordArray.numDistinctWords - 1)
   {
     node = (struct node*)malloc(sizeof(struct node));
   }

   /* Find the element with the highest probability in the current word sub array */
   for (i = left; i <= right; i++)
   {
     if (wordArray.words[i].probability > maxProbability)
     {
       maxProbability = wordArray.words[i].probability;
       maxIndex = i;
     }
   }

   /* Assign current root with this word (found above) */
   node->word = &wordArray.words[maxIndex];

   /* If there are no other words left to be assigned in the current word sub array */
   if (left == right)
   {
     node->leftChild = NULL;
     node->rightChild = NULL;
     return node;
   }
   /* If there is no longer a left subarray but there exists a right subarray*/
   else if (left == maxIndex)
   {
     node->leftChild = NULL;
     node->rightChild = (struct node*)malloc(sizeof(struct node));
     node->rightChild = getBSTGreedyTechnique(wordArray, node->rightChild, left, right-1);
   }
   /* If there is no longer a right subarray but there exists a left subarray*/
   else if (right == maxIndex)
   {
     node->rightChild = NULL;
     node->leftChild = (struct node*)malloc(sizeof(struct node));
     node->leftChild = getBSTGreedyTechnique(wordArray, node->leftChild, left+1, right);
   }
   /* If there exists both left and right subarrays */
   else
   {
     node->leftChild = (struct node*)malloc(sizeof(struct node));
     node->leftChild = getBSTGreedyTechnique(wordArray, node->leftChild, left, maxIndex-1);
     node->rightChild = (struct node*)malloc(sizeof(struct node));
     node->rightChild = getBSTGreedyTechnique(wordArray, node->rightChild, maxIndex+1, right);
   }

   return node;
}

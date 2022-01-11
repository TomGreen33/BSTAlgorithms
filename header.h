/* Name: Thomas Green
 * ID: 1048389
 * Date: March 27 2021
 * Assignment #: 4
 */


 typedef struct word {
   char *ptr;
   int repetitions;
   float probability;
   float aveNumCom;
 } word;

typedef struct node {
  struct word *word;
  struct node *rightChild;
  struct node *leftChild;
} node;

typedef struct wordArray{
  struct word *words;
  int numDistinctWords;
  int numWords;
} wordArray;


/* Main */
struct wordArray getWordArray();
struct wordArray sortWordArray(struct wordArray wordArray);
void searchBST(struct node *node, char *word, int mode);

/* Q1 */
struct node *getBSTDynamicProgramming(struct wordArray wordArray);
struct node* build(struct node *node, struct wordArray wordArray, int i, int j, int **R, float **C);

/* Q2 */
struct node *getBSTGreedyTechnique(struct wordArray wordArray, struct node *node, int left, int right);

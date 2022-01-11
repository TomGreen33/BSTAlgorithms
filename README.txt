This program was my final submission for assignment 4 of my computer algorithms course at the university
of Guelph (CIS 3490). I took this course during the winter of 2021 alongside my full time job as a
technical support analyst.

This program revolves around the creation and use of binary search trees (BST's). The program begins by creating a word array object, where
its contents are pulled from the data.txt file. The array stores each word, as well as the number of times it a given word is repeated 
in the file. The array's contents are also sorted using selection sort, where the quantitative values of each word are assessed using 
strcmp(). The program then has 2 different algorithms to build the BST. The first algorithm (option 1) does so using a dynamic programming 
technique. In essence, the algorithm begins by dynamically allocating space for a cost table and root table. The cost table[i][j] 
contains information of the average number of key comparisons made when searching an optimized BST containing keys ki...kj. 
The root table is built using the information from the cost table. It contains information regarding which key to use as the root for a tree
containing keys ki through kj. The algorithm uses this root table to recursively create the BST. The second algorithm builds a BST using a 
greedy technique. The fundamental operation of this algorithm is to assign the root of a tree containing keys ki through kj to the key 
associated with the greatest probability (i.e. repetitions in the text). It then recursively builds the left and right subtrees by assigning the
children of the newly established root with the output of recursive calls who's parameters are keys (ki...kroot-1) and 
(kroot+1...kj) respectively. The program finnishes with prompting the user for a word to search for, and uses searchBST() to search
the newly created BST for the word given. 

The following section was the original read me file that was part of the assignment's submission.

Name: Thomas Green
ID: 1048389
Date: March 27 2021
Assignment #: 4

Please insert the test files into the folder.
Use make to compile the program.
Use ./main to run the program.
Use make clean to clear the directory of any object files.

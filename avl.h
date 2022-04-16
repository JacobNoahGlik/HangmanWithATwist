#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include "super_vector.h"

//forward declarations
typedef struct Node tNode;
// An AVL tree node (we have just added a height attribute to a normal BST)
struct Node
{
    SuperVector *SV; //this could also be the data (Key, Vector) = SuperVector
    tNode *lChild;
    tNode *rChild;
    int nodeHeight; // recall height of node as number of edges to the farthest leaf.++
    int keyVal;
};

//Function declarations
tNode *insertNode(tNode *Head, tNode *newNode, MY_STRING Data);
tNode *createNode(SuperVector *SV);
tNode *initTreeDefault(Vector *Vec, MY_STRING Name);
tNode *initOriginalTree(MY_STRING Word, MY_STRING Name);
tNode *insertWord(tNode *Head, MY_STRING Word, MY_STRING Name);

tNode *newGuessTree(SuperVector *svWords, char Guess);

int getHeight(tNode *node);
int getBalancefactor(tNode *node);
int findmax(int x, int y);

tNode *rightRotation(tNode *nodey);
tNode *leftRotation(tNode *nodex);

void inorderTraversal(tNode *root);
void preorderTraversal(tNode *root);

void breadthFirstTraversal(tNode *root); // level order
void printNodeAtLevel(tNode *node, int nodeLevel);

//

SuperVector *getBiggestBucket(tNode *Head, int currentGoal, SuperVector *currentPointer);

void printTree(tNode *Head);
void destroyTree(tNode *Head);
void softWhipeTree(tNode *Head);

#endif
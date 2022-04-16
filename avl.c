#include "avl.h"
// AVL tree (Dynamic Balancing using AVL)

// /* Driver program*/
// int main(int argc, char **argv)
// {
//     tNode *root = NULL;
//     int key;
//
//     //create a tree now.*/
//     for (int i = 0; i < 10; i++)
//     {
//         key = rand() % 100;
//         root = insertNodes(root, key);
//     }
//
//     printf("Preorder traversal : \n");
//     preorderTraversal(root);
//     printf("\n");
//
//     printf("Inorder traversal (sorted tree): \n");
//     inorderTraversal(root);
//     printf("\n");
//
//     printf("Level printing: \n");
//     breadthFirstTraversal(root);
//     printf("\n");
//
//     return 0;
// }

tNode *insertWord(tNode *Head, MY_STRING Word, MY_STRING Name)
{
    if (Head == NULL)
    {
        return initOriginalTree(Word, my_string_init_c_string(my_string_c_str(Name)));
    }

    int direction = my_string_compare(Name, Head->SV->Name);

    if (direction == 0)
    {
        if (addMyStringToVector(Head->SV->Data, Word) == FAILURE)
        {
            printf("FAILED TO ADD NEW WORD TO VECTOR IN FUNCTION INSERTWORD\n");
            exit(1);
        }
    }
    else if (direction == -1)
    {
        Head->lChild = insertWord(Head->lChild, Word, Name);
    }
    else if (direction == 1)
    {
        Head->rChild = insertWord(Head->rChild, Word, Name);
    }
    else
    {
        printf("DID NOT GET -1, 0, or 1 from my_string_compare.  Something went wrong!\n");
        exit(1);
    }

    Head->nodeHeight = 1 + findmax(getHeight(Head->lChild), getHeight(Head->rChild));

    return Head;
}

/*
insert key in subtree rootedwith node and returns new root of subtree.
*/
tNode *insertNode(tNode *Head, tNode *newNode, MY_STRING Data)
{
    /*BST insertion -usual technique , refer to notes */
    if (Head == NULL && newNode != NULL)
        return (newNode);

    if (newNode == NULL)
    {
        printf("newNode was null!\n");
        return NULL;
    }

    int direction = my_string_compare(Head->SV, newNode->SV);

    if (direction == -1)
    {
        Head->lChild = insertNode(Head->lChild, newNode, Data);
    }
    else if (direction == 1)
    {
        Head->rChild = insertNode(Head->rChild, newNode, Data);
    }
    else if (direction == 0)
    {
        if (Head->SV == NULL || Head->SV->Data == NULL)
        {
            printf("NULL found as Head->SV or Head->SV->Data\nCould not compute\n");
            exit(1);
        }
        if (addMyStringToVector(Head->SV->Data, Data) == FAILURE)
        {
            printf("Adding string to vector failed when sim-node found\n");
            return Head;
        }
    }
    else
    {
        printf("DID NOT GET -1, 0, or 1 from my_string_compare.  Something went wrong!\n");
        exit(1);
    }

    /* A update height of the node */
    Head->nodeHeight = 1 + findmax(getHeight(Head->lChild), getHeight(Head->rChild));

    /* B. calculate balance factor (hLeft-hRigh)*/
    int balance = getBalancefactor(Head);

    // 1. LEFT LEFT CASE (In this case, just rotate once on the RIGHT)
    if (balance > 1 && direction < 0)
        return rightRotation(Head);

    // 2. RIGHT RIGHT CASE (In this case, just rotate once on the left)
    if (balance < -1 && direction > 0)
        return leftRotation(Head);

    // 3. LEFT - RIGHT CASE ()
    if (balance > 1 && direction > 0)
    {
        Head->lChild = leftRotation(Head->lChild); //To make it a LEFT LEFT CASE
        return rightRotation(Head);
    }

    // 4. RIGHT - LEFT CASE
    if (balance < -1 && direction < 0)
    {
        Head->rChild = rightRotation(Head->rChild); //To make it a RIGHT RIGHT CASE
        return leftRotation(Head);
    }

    return Head;
}
/* Create a new node with the given key and NULL lChild and rChild pointers. */
tNode *createNode(SuperVector *SV)
{
    tNode *node = (tNode *)malloc(sizeof(tNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->SV = SV;
    node->lChild = NULL;
    node->rChild = NULL;
    node->nodeHeight = 1; //assume that node is added at leaf
    node->keyVal = 0;
    return node;
}

tNode *initTreeDefault(Vector *Vec, MY_STRING Name)
{
    SuperVector *svTemp = initSV(Vec, Name);

    return createNode(svTemp);
}

tNode *initOriginalTree(MY_STRING Word, MY_STRING Name)
{
    Vector *vWordArr = VectorInitDefault();
    if (addMyStringToVector(vWordArr, Word) == FAILURE)
    {
        printf("FAILED TO ADD STRING TO NEW VECTOR\n");
        return NULL;
    }

    return initTreeDefault(vWordArr, Name);
}

// A get method for height of the node.
int getHeight(tNode *node)
{
    if (node == NULL)
        return 0;
    return node->nodeHeight;
}

// Calculates and returns the balance factor
int getBalancefactor(tNode *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->lChild) - getHeight(node->rChild);
}

// This should show a sorted out tree(recall from last class)
// void inorderTraversal(tNode *root)
// {
//     if (root != NULL)
//     {
//         inorderTraversal(root->lChild);
//         printf("%d ", root->SV);
//         inorderTraversal(root->rChild);
//     }
// }
// // This should show tree with root first (recall from last class)
// void preorderTraversal(tNode *root)
// {
//     if (root != NULL)
//     {
//         printf("%d ", root->SV);
//         preorderTraversal(root->lChild);
//         preorderTraversal(root->rChild);
//     }
// }

// Rotate Right
tNode *rightRotation(tNode *nodey)
{
    tNode *nodex = nodey->lChild;
    tNode *T2 = nodex->rChild;

    // Rotate RIGHT
    nodex->rChild = nodey;
    nodey->lChild = T2;

    // Update heights
    nodey->nodeHeight = findmax(getHeight(nodey->lChild), getHeight(nodey->rChild)) + 1;
    nodex->nodeHeight = findmax(getHeight(nodex->lChild), getHeight(nodex->rChild)) + 1;

    // Return new root
    return nodex;
}

// rotate LEFT subtree rooted with a nodex
tNode *leftRotation(tNode *nodex)
{
    tNode *nodey = nodex->rChild;
    tNode *T2 = nodey->lChild;

    // Rotate LEFT
    nodey->lChild = nodex;
    nodex->rChild = T2;

    //  Update height of nodes
    nodex->nodeHeight = findmax(getHeight(nodex->lChild), getHeight(nodex->rChild)) + 1;
    nodey->nodeHeight = findmax(getHeight(nodey->lChild), getHeight(nodey->rChild)) + 1;

    // Return new root
    return nodey;
}

// return the largest value (used for height comparison)
int findmax(int x, int y)
{
    return (x > y) ? x : y;
}

// void breadthFirstTraversal(tNode *root)
// {
//
//     for (int i = 1; i <= getHeight(root); ++i)
//     {
//         printf("Level %d: ", i);
//         printNodeAtLevel(root, i);
//         printf("\n");
//     }
// }
// void printNodeAtLevel(tNode *node, int nodeLevel)
// {
//     if (node == NULL)
//         return;
//
//     if (nodeLevel == 1)
//         printf("%d  ", node->SV);
//     else if (nodeLevel > 1)
//     {
//         printNodeAtLevel(node->lChild, nodeLevel - 1);
//         printNodeAtLevel(node->rChild, nodeLevel - 1);
//     }
// }

void softWhipeTree(tNode *Head)
{
    if (Head == NULL)
        return;

    softWhipeTree(Head->lChild);
    softWhipeTree(Head->rChild);

    swSV(Head->SV);

    free(Head);
}

void printTree(tNode *Head)
{
    if (Head == NULL)
        return;

    printSV(Head->SV);
    printTree(Head->lChild);
    printTree(Head->rChild);
}

void destroyTree(tNode *Head)
{
    if (Head == NULL)
        return;

    destroyTree(Head->lChild);
    destroyTree(Head->lChild);

    destroySV(Head->SV);
    free(Head);
}

tNode *newGuessTree(SuperVector *svWords, char Guess)
{
    if (svWords == NULL || svWords->Data == NULL || svWords->Name == NULL)
    {
        printf("NULL found at svWords, Data, or Name.\n");
        return NULL;
    }

    tNode *Head = NULL;

    Vector *pWords = svWords->Data;
    for (int i = 0; i < pWords->size; ++i)
    {
        MY_STRING tempString = my_string_init_c_string("");
        MY_STRING currentWord = pWords->data[i];

        if (get_word_key_value(svWords->Name, &tempString, currentWord, Guess) == FAILURE)
        {
            printf("got failure durring my getword key\n");
            exit(1);
        }

        Head = insertWord(Head, currentWord, tempString);
        my_string_destroy(&tempString);
    }

    return Head;
}

SuperVector *getBiggestBucket(tNode *Head, int currentGoal, SuperVector *currentPointer)
{
    if (Head == NULL)
        return NULL;

    SuperVector *left = getBiggestBucket(Head->lChild, currentGoal, currentPointer);
    SuperVector *right = getBiggestBucket(Head->rChild, currentGoal, currentPointer);

    if (Head->SV->Data->size > currentGoal)
    {
        currentGoal = Head->SV->Data->size;
        currentPointer = Head->SV;
    }
    if (left != NULL && left->Data->size > currentGoal)
    {
        currentGoal = left->Data->size;
        currentPointer = left;
    }
    if (right != NULL && right->Data->size > currentGoal)
    {
        currentGoal = right->Data->size;
        currentPointer = right;
    }

    return currentPointer;
}
#include "my_string.h"

typedef struct my_string My_String;
struct my_string
{
    int size;
    int capacity;
    char *data;
};

Vector *VectorInitDefault()
{
    Vector *exe = (Vector *)malloc(sizeof(Vector));
    if (exe == NULL)
    {
        printf("Throw new Exception: No memory left!\n");
        exit(1);
    }

    exe->data = (MY_STRING *)malloc(sizeof(MY_STRING) * 10);
    exe->size = 0;
    exe->capacity = 10;

    return exe;
}

Status addMyStringToVector(Vector *Master, MY_STRING addition)
{
    if (Master->size + 1 == Master->capacity)
        if (resize(Master) == FAILURE)
            return FAILURE;

    Master->data[Master->size] = addition;
    Master->size++;
    return SUCCESS;
}

Status resize(Vector *Master)
{
    MY_STRING *pStrArr = (MY_STRING *)malloc(sizeof(MY_STRING) * Master->capacity * 2);
    if (pStrArr == NULL)
    {
        printf("No space in memory for pStrArr\n");
        return FAILURE;
    }
    for (int i = 0; i < Master->size; ++i)
    {
        pStrArr[i] = Master->data[i];
    }
    free(Master->data);
    Master->data = pStrArr;
    Master->capacity *= 2;
    return SUCCESS;
}

void destroyVector(Vector *location)
{
    if (location == NULL)
        return;

    for (int i = 0; i < location->size; ++i)
    {
        my_string_destroy(&location->data[i]);
    }

    free(location->data);

    free(location);
}

MY_STRING my_string_init_default(void)
{
    My_String *pMy_string;
    pMy_string = (My_String *)malloc(sizeof(My_String));
    if (pMy_string != NULL)
    {
        pMy_string->size = 0;
        pMy_string->capacity = 7;
        pMy_string->data = (char *)(malloc(sizeof(char) * pMy_string->capacity));
        if (pMy_string->data == NULL)
        {
            free(pMy_string);
            pMy_string = NULL;
        }
    }
    return pMy_string;
}

void my_string_destroy(Item *pItem)
{
    My_String *pRealString = (My_String *)*pItem;

    if (pRealString == NULL)
    {
        return;
    }

    free(pRealString->data);

    free(pRealString);

    *pItem = NULL;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
    My_String *pStr = (My_String *)hMy_string;

    if (pStr->capacity == pStr->size)
    {
        if (!resizeStringFunction((MY_STRING)pStr))
            return FAILURE;
    }

    pStr->data[pStr->size] = item;
    pStr->size++;
    return SUCCESS;
}

Status resizeStringFunction(MY_STRING hMy_string) // imported from lab 3
{
    My_String *pMy_string = hMy_string;
    int resize = pMy_string->capacity * 2;
    char *temp = (char *)malloc(sizeof(char) * resize);
    if (temp == NULL)
    {
        printf("Error not enough memory to realoc %d chars\n", resize);
        exit(1);
    }

    for (int i = 0; i < pMy_string->size; i++)
    {
        temp[i] = pMy_string->data[i];
    }
    free(pMy_string->data);
    pMy_string->data = temp;
    pMy_string->capacity *= 2;

    return SUCCESS;
}

void printMy_String(MY_STRING hMy_string) // for testing use
{
    My_String *pStr = hMy_string;
    for (int i = 0; i < pStr->size; ++i)
    {
        printf("%c", pStr->data[i]);
    }
}

Status my_string_pop_back(MY_STRING hMy_string)
{
    My_String *pStr = hMy_string;
    if (!pStr->size)
        return FAILURE;

    pStr->size--;
    pStr->data[pStr->size] = '\0';
    return SUCCESS;
}

char *my_string_at(MY_STRING hMy_string, int index)
{
    My_String *pStr = hMy_string;
    if (pStr->size <= index)
        return NULL;

    return &pStr->data[index];
}

char *my_string_c_str(MY_STRING hMy_string)
{
    My_String *pStr = (My_String *)hMy_string;
    if (pStr->size == pStr->capacity)
        resizeStringFunction((MY_STRING)pStr);

    pStr->data[pStr->size] = '\0';
    return (pStr->data);
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
    My_String *pORIG = hAppend;
    My_String *pUpdating = hResult;

    while (pUpdating->size + pORIG->size + 1 > pUpdating->capacity)
    {
        if (!resizeStringFunction(hResult))
            return FAILURE;
    }

    int iUPSize = pUpdating->size;
    for (int i = 0; i <= pORIG->size; ++i)
    {
        pUpdating->data[iUPSize + i] = pORIG->data[i];
    }
    pUpdating->size += pORIG->size;

    printf("old size: %d, new size: %d\n", iUPSize, pUpdating->size);

    return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
    My_String *pStr = hMy_string;
    if (pStr->size == 0)
        return TRUE;

    return FALSE;
}

//

//

/////////////////////////////////////////////////////////////// import from lab 3 ...

//

//

MY_STRING my_string_init_c_string(const char *c_string)
{
    My_String *pMy_String = (My_String *)malloc(sizeof(My_String));
    if (pMy_String == NULL)
    {
        printf("\nERROR:\t pMy_String is empty\n");
        return NULL;
    }

    int size = 0;
    for (size = 0; c_string[size] != '\0'; size++)
        ; // for loop to generate size of parsed C String
    pMy_String->size = size;
    pMy_String->capacity = size + 1;
    pMy_String->data = (char *)malloc(sizeof(char) * pMy_String->capacity);
    if (pMy_String->data == NULL)
    {
        printf("\tERROR: Data for c string init has not been correctly assigned\n");
        return NULL;
    }

    for (int j = 0; j < size; j++)
    {
        pMy_String->data[j] = c_string[j];
        if (c_string[j] == '\0')
        {
            break;
        }
    }
    if (pMy_String->data == NULL)
    {
        printf("\tERROR: Copying Data from C String, to My_String->Data failed\n");
        return NULL;
    }

    //printf("%s -> size: %d, capacity: %d\n", c_string, pMy_String->size, pMy_String->capacity);
    return (MY_STRING)pMy_String;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
    My_String *getCapacity = (My_String *)hMy_string;
    if (getCapacity == NULL)
    {
        printf("\tGetCapacity is empty/ not correctly assigned\n");
        return 0;
    }

    return getCapacity->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{ //	DONE
    My_String *getSize = (My_String *)hMy_string;
    if (getSize == NULL)
    {
        printf("\tGetSize is empty/ not correctly assigned\n");
        return 0;
    }

    return getSize->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
    My_String *pLeftString = (My_String *)hLeft_string;
    My_String *pRightString = (My_String *)hRight_string;

    if (my_string_get_size(hLeft_string) != my_string_get_size(hRight_string))
        return -1;

    for (int i = 0; i < pLeftString->size; ++i)
    {
        if (pLeftString->data[i] != pRightString->data[i])
        {
            if (pLeftString->data[i] > pRightString->data[i])
            {
                return -1;
            }
            return 1;
        }
    }
    return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE *pFile)
{
    My_String *pMy_string = (My_String *)hMy_string;
    int index = 0;
    char ch;

    pMy_string->size = 0;
    do
    {
        ch = fgetc(pFile);
    } while (ch == '\n' || ch == ' ');
    if (ch == EOF)
    {
        return FAILURE;
    }

    while (ch != ' ' && ch != '\n' && ch != EOF)
    {
        if (pMy_string->size >= pMy_string->capacity)
        {
            pMy_string->size = resizeStringFunction(pMy_string);
        }
        pMy_string->data[index++] = ch;
        ch = fgetc(pFile);
        pMy_string->size = index;
    }

    if (ch == ' ')
    {
        ungetc(ch, pFile);
    }

    return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE *fp)
{
    My_String *pMy_string = hMy_string;
    if (fp == NULL || pMy_string->data == NULL)
    {
        return FAILURE;
    }
    for (int i = 0; i < pMy_string->size; i++)
    {
        fputc(pMy_string->data[i], fp);
    }
    return SUCCESS;
}

//

// new for lab 6 ...

void my_string_assignment(Item *pLeft, Item Right)
{
    My_String *left = (My_String *)*pLeft;
    My_String *right = (My_String *)Right;
    if (Right == NULL)
        return;

    if (left != NULL)
    {
        my_string_destroy(pLeft);
        pLeft = NULL;
        left = NULL;
    }
    left = (My_String *)malloc(sizeof(My_String));
    left->capacity = right->capacity;
    left->size = right->size;

    left->data = (char *)malloc(sizeof(char) * left->capacity);

    for (int i = 0; i < left->size; ++i)
    {
        left->data[i] = right->data[i];
    }
    *pLeft = (Item)(left);
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING *new_key, MY_STRING word, char guess)
{
    My_String *Word = (My_String *)word;
    My_String *CurrentFamily = (My_String *)current_word_family;
    My_String *UpdatedWordFamily = (My_String *)(*new_key);

    while (UpdatedWordFamily->capacity < Word->capacity)
    {
        if (resizeStringFunction(*new_key) == FAILURE)
        {
            return FAILURE;
        }
    }

    guess = toLowerCase(guess);
    UpdatedWordFamily->size = 0;
    for (int i = 0; i < Word->size; ++i)
    {
        if (toLowerCase(Word->data[i]) == guess)
        {
            UpdatedWordFamily->data[i] = guess;
            UpdatedWordFamily->size++;
        }
        else
        {
            UpdatedWordFamily->data[i] = toLowerCase(CurrentFamily->data[i]);
            UpdatedWordFamily->size++;
        }
    }

    *new_key = (MY_STRING *)UpdatedWordFamily;

    return SUCCESS;
}

char toLowerCase(char ch)
{
    if (((int)ch) >= 65 && ((int)ch) <= 90)
    {
        ch += 32;
    }

    return ch;
}

// removes vector struction without freeing
// string structures held inside
void softRM_Vector(Vector *DataSet)
{
    if (DataSet != NULL)
        free(DataSet->data);
    free(DataSet);
}

Boolean stringNameIsKnown(MY_STRING str)
{
    My_String *Name = (My_String *)str;
    if (Name == NULL)
    {
        printf("Name does not exist, stringNameIsKnown function failed.\n");
        return FALSE;
    }

    for (int i = 0; i < Name->size; ++i)
    {
        if (Name->data[i] == '-')
            return FALSE;
    }
    return TRUE;
}
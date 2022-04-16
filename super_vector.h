#ifndef SUPER_VECTOR_H
#define SUPER_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

typedef struct
{
    MY_STRING Name;
    Vector *Data;
} SuperVector;

SuperVector *initSV(Vector *Data, MY_STRING Name);
MY_STRING nameMaker(int Size);
void destroySV(SuperVector *Location);
void printSV(SuperVector *SV);

void swSV(SuperVector *List);
Boolean SV_IsKnown(SuperVector *SV);

#endif
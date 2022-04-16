#include "super_vector.h"

SuperVector *initSV(Vector *Data, MY_STRING Name)
{
    if (Data == NULL || Name == NULL)
    {
        printf("Data passed is null, failure initializing supervector.\n");
        return NULL;
    }

    SuperVector *new_sv = (SuperVector *)malloc(sizeof(SuperVector));
    if (new_sv == NULL)
    {
        printf("No space in mem to create new Super Vector Structure.\n");
        return NULL;
    }

    new_sv->Name = Name;
    new_sv->Data = Data;

    return new_sv;
}

MY_STRING nameMaker(int Size)
{
    if (Size <= 1)
    {
        printf("Failed to create name with size %d, %d is too small. (Must be grator then one and less then theirty)\n", Size, Size);
        return NULL;
    }
    if (Size > 30)
    {
        printf("Failed to create name with size %d, %d is too big. (Must be grator then one and less then theirty)\n", Size, Size);
        return NULL;
    }

    char temp[Size + 1];
    for (int i = 0; i < Size; ++i)
    {
        temp[i] = '-';
    }
    temp[Size] = '\0';

    return my_string_init_c_string(temp);
}

void destroySV(SuperVector *Location)
{
    if (Location == NULL)
    {
        printf("Vector not found or already destroyed! (error in func 'DestroySV')\n");
        return;
    }
    destroyVector(Location->Data);
    my_string_destroy(&(Location->Name));
    free(Location);
}

void printSV(SuperVector *SV)
{
    if (SV == NULL || SV->Data == NULL)
    {
        printf("SuperVector cannot be printed because it was initialized improporly.\n");
        return;
    }
    printf("%s %d\n", my_string_c_str(SV->Name), SV->Data->size);

    // this prints the first four strings if we need to trouble shoot code
    //
    // for (int i = 0; (i < SV->Data->size && i < 4); ++i)
    // {
    //     printf(", %s", my_string_c_str(SV->Data->data[i]));
    // }
    // printf("\n");
}

void swSV(SuperVector *List)
{
    my_string_destroy(&List->Name);
    softRM_Vector(List->Data);

    free(List);
}

Boolean SV_IsKnown(SuperVector *SV)
{
    if (SV == NULL)
    {
        printf("SuperVector passed is empty, failed to compute.\n");
        return FALSE;
    }
    return stringNameIsKnown(SV->Name);
}
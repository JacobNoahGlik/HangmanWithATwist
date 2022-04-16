#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char *buffer, int length)
{
    MY_STRING hString = NULL;
    hString = my_string_init_default();
    if (hString == NULL)
    {
        strncpy(buffer, "test_init_default_returns_nonNULL\n"
                        "my_string_init_default returns NULL",
                length);
        return FAILURE;
    }
    else
    {
        my_string_destroy((Item)&hString);
        strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
        return SUCCESS;
    }
}

Status test_get_size_on_init_default_returns_0(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;
    hString = my_string_init_default();
    if (my_string_get_size(hString) != 0)
    {
        status = FAILURE;
        printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
                        "Did not receive 0 from get_size after init_default\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
    }
    my_string_destroy((Item)&hString);
    return status;
}

Status test_get_capacity_on_init_default_returns_grator_then_size(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;
    hString = my_string_init_default();
    if (my_string_get_capacity(hString) < my_string_get_size(hString))
    {
        status = FAILURE;
        printf("Expected a capacity grator then size but got (Size: %d, Capacity: %d)\n", my_string_get_size(hString), my_string_get_capacity(hString));
        strncpy(buffer, "test_get_capacity_on_init_default_returns_grator_then_size\n"
                        "Did not receive capacity grator then size after init_default\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_get_capacity_on_init_default_returns_grator_then_size\n", length);
    }
    my_string_destroy((Item)&hString);
    return status;
}
Status test_compare_two_identical_strings_and_get_zero(char *buffer, int length)
{ // my_string_compare
    MY_STRING str1 = NULL;
    MY_STRING str2 = NULL;
    Status status;
    str1 = my_string_init_default();
    str2 = my_string_init_default();
    if (my_string_compare(str1, str2) != 0)
    {
        status = FAILURE;
        printf("Expected compare to return zero but returned %d\n", my_string_compare(str1, str2));
        strncpy(buffer, "test_compare_two_identical_strings_and_get_zero\n"
                        "Did not receive zero from identical compare\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_compare_two_identical_strings_and_get_zero\n", length);
    }
    my_string_destroy((Item)&str1);
    my_string_destroy((Item)&str2);
    return status;
}

Status test_create_100_coppys_of_my_string_COPY_ME(char *buffer, int length)
{
    Status stat = SUCCESS;
    strncpy(buffer, "sucsessful run of init run of test_create_100_coppys_of_my_string_COPY_ME\n", length);

    MY_STRING original = my_string_init_c_string("COPY ME!");

    int numberCoppys = 100;
    MY_STRING coppys[numberCoppys];
    for (int i = 0; i < numberCoppys; ++i)
    {
        coppys[i] = NULL;
        my_string_assignment(&coppys[i], original);
    }

    int failureNumber = -1;
    for (int i = 0; i < numberCoppys; ++i)
    {
        if (*(my_string_at(original, 4)) != *(my_string_at(coppys[i], 4)))
        {
            failureNumber = i;
            break;
        }
    }
    if (failureNumber != -1)
    {
        stat = FAILURE;
        printf("failed on number %d\n", failureNumber);
        strncpy(buffer, "init run of test_create_100_coppys_of_my_string_COPY_ME\n", length);
    }

    for (int i = 0; i < numberCoppys; ++i)
    {
        my_string_destroy(&coppys[i]);
    }
    my_string_destroy(&original);

    return stat;
}

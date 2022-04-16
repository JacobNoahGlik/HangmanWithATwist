#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "avl.h"

Status test_init_default_returns_nonNULL(char *buffer, int length);

Status test_get_size_on_init_default_returns_0(char *buffer, int length);

Status test_get_capacity_on_init_default_returns_grator_then_size(char *buffer, int length);

Status test_compare_two_identical_strings_and_get_zero(char *buffer, int length);

Status test_create_100_coppys_of_my_string_COPY_ME(char *buffer, int length);

#endif

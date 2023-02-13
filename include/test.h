#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct test {
    int a;
    int b;
    char *str;
}TEST;

void test_print(const TEST *t);
TEST* test_new(int a, int b, const char *str);
void test_free(TEST *t);


#endif
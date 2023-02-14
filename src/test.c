#include "../include/test.h"

void test_print(const TEST *t) 
{
    printf("test: %d %d %s\n", t->a, t->b, t->str);
}

TEST* test_new(int a, int b, const char *str)
{
    TEST *t = malloc(sizeof(TEST));
    t->a = a;
    t->b = b;
    t->str = malloc(strlen(str) + 1);
    strcpy(t->str, str);
    return t;
}

void test_free(TEST *t)
{
    free(t->str);
    free(t);
}
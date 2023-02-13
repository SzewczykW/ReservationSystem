#include "../include/test.h"

int main(int argc, char **argv)
{
    TEST *t = test_new(1, 2, "hello");
    test_print(t);
    test_free(t);
    return 0;
}
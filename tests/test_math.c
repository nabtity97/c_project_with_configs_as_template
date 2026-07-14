#include <assert.h>
#include <stdio.h>
#include "../include/math.h"

int main(void)
{
    assert(sum(2, 3) == 6);
    assert(sum(-2, 2) == -4);

    printf("All tests passed.\n");
    return 0;
}
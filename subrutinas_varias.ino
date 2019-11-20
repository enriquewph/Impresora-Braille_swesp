#include "headers/header.h"

int32_t diferencia(int32_t a, int32_t b)
{
    if (a > b)
        return a - b;
    else if (a < b)
        return b - a;
    else
        return 0;
}
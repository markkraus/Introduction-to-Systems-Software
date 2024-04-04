#include <stdio.h>

int ternary(int cond, int true_value, int false_value)
{
    if (cond == 0)
    {
        // FALSE
        return false_value;
    }
    else
    {
        // TRUE
        return true_value;
    }
    
}
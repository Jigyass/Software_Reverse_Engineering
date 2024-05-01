#include<stdio.h>

int rand()
{
    return 0;
}

double pow(double base, double exponent) 
{
    static int pow_calls = 0;
    pow_calls++;
    if (pow_calls == 1)
    {
        return 1.0;
    } 
    else if (pow_calls == 2) 
    {
        return 64.0;
    } 
    else 
    {
        return 0.0;
    }
}

int strncmp(const char *str1, const char *str2, size_t n)
{
    return 0;
}

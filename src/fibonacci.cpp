#include "fibonacci.h"

uint64_t fib_recursive(uint64_t n)
{
    if (n < 2)
    {
        return n;
    }
    return fib_recursive(n-2) + fib_recursive(n-1);
}


FibGenerator::operator uint64_t()
{
    uint64_t it = a;
    a = b;
    b += it;
    return it;
}


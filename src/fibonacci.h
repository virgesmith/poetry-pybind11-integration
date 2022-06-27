#pragma once

#include <cstdint>

uint64_t fib_recursive(uint64_t n);

class FibGenerator
{
public:
    FibGenerator() : a(0), b(1) {}

    operator uint64_t();

private:
    uint64_t a;
    uint64_t b;
    uint64_t it;
};

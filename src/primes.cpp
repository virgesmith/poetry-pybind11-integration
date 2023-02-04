#include "primes.h"

#include <pybind11/pybind11.h>

#include <cmath>

namespace py = pybind11;

namespace {
// size_t isqrt(size_t n) {
//     return static_cast<size_t>(std::sqrt(n)) + 1;
// }

bool is_prime(size_t n, const std::vector<size_t>& primes_below) {
    switch (n) {
        case 0:
        case 1:
            return false;
        case 2:
        case 3:
            return true;
        default:
            for (size_t p: primes_below) {
                if (n % p == 0) {
                    return false;
                }
                // only need to go as far as sqrt(n)
                if (p * p > n) {
                    break;
                }
            }
            return true;
    }
}

std::vector<size_t> seed_primes(size_t n)
{
    std::vector<size_t> primes{2, 3};
    size_t c = primes.back();
    for (;;) {
        c += 2;
        if (c * c > n)
            break;
        if (is_prime(c, primes))
            primes.push_back(c);
    }
    return primes;
}

std::vector<size_t> extend_seed_primes(const std::vector<size_t>& primes, size_t n) {
    std::vector<size_t> ext_primes;
    size_t c = primes.back();
    for(;;) {
        c += 2;
        if (c * c >= n) {
            break;
        }
        if (is_prime(c, primes) && is_prime(c, ext_primes)){
            ext_primes.push_back(c);
        }
    }
    return ext_primes;
}

}


PrimeGenerator::PrimeGenerator() : found{2, 3} {
}


PrimeGenerator& PrimeGenerator::iter() {
    return *this;
}


size_t PrimeGenerator::next() {
    size_t n = found.back();
    for (;;) {
        n += 2;
        if (is_prime(n, found)) {
            found.push_back(n);
            return n;
        }
    }
}


PrimeRange::PrimeRange(size_t m, size_t n): index{m % 2 ? m : m + 1}, n(n), m_seed_primes(seed_primes(n)) {
}

PrimeRange& PrimeRange::iter() {
    return *this;
}

size_t PrimeRange::next() {
    while (index <= n && !is_prime(index, m_seed_primes)) {
        index += 2;
    }
    size_t ret = index;
    index += 2;
    if (ret > n)
        throw py::stop_iteration();
    return ret;
}


bool is_prime_py(size_t n) {
    size_t m = 1000000;
    if (n < m) {
        return is_prime(n, seed_primes(n));
    }
    std::vector<size_t> primes = seed_primes(m);
    for (;;) {
        for (size_t p: primes) {
            if (n % p == 0) {
                return false;
            }
        }
        if (m > n) {
            break;
        }
        m *= 10;
        primes = extend_seed_primes(primes, m);
    }
    return true;
}


size_t nth_prime(size_t n) {
    if (n == 0) {
        throw py::value_error("n must be >0");
    }
    std::vector<size_t> found;
    found.reserve(n);
    found.push_back(2);
    found.push_back(3);
    while (n > found.size()) {
        size_t c = found.back();
        for(;;) {
            c += 2;
            if (is_prime(c, found)) {
                found.push_back(c);
                break;
            }
        }
    }
    return found[n-1];
}


std::vector<size_t> prime_factors(size_t n) {
    if (n == 0) {
        throw py::value_error("input must be >=1");
    }
    std::vector<size_t> factors;
    for (size_t p: seed_primes(n)) {
        while (n % p == 0) {
            n /= p;
            factors.push_back(p);
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    return factors;
}

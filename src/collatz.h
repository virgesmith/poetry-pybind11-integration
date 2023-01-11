#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include <cstdint>

namespace py = pybind11;
using namespace py::literals;

class Collatz
{
public:
    Collatz(uint64_t n): n(n), at_end() { }

    uint64_t next()
    {
        if (at_end)
        {
            throw py::stop_iteration();
        }
        uint64_t ret = n;
        if (n <= 1)
        {
            at_end = true; // throw on next iteration
        }
        n = n % 2 ? 3 * n + 1 : n / 2;
        return ret;
    }

    Collatz& iter()
    {
        return *this;
    }

    uint64_t send(uint64_t n_)
    {
        n = n_;
        return next();
    }

    void close()
    {
        at_end = true;
    }

    void throw_(py::type e, py::object msg, py::object /*traceback*/)
    {
        auto locals = py::dict("exception_type"_a=e, "exception_message"_a=msg);
        py::exec(R"""(
            raise exception_type(exception_message)
        )""", py::globals(), locals);
    }

    void throw_default()
    {
        throw py::stop_iteration();
    }

private:
    uint64_t n;
    bool at_end;
};
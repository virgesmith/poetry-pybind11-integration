#include "fibonacci.h"

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

PYBIND11_MODULE(_pybind11_extension, m)
{
    m.doc() = R"""(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: _pybind11_extension
        .. autosummary::
           :toctree: _generate
    )""";

    m.def("fib_recursive", &fib_recursive, R"""(
        Return nth value in fibonnacci sequence, computed recursively.
    )""");

    py::class_<FibGenerator>(m, "FibGenerator", R"""(
        C++ implementation of a Fibonacci sequence generator.
    )""")
    // fib_holder
        .def(py::init<>())
        .def("__next__", [](FibGenerator& fg) -> uint64_t { return fg; })
        ;
}

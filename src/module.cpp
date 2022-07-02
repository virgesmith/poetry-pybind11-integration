#include "fibonacci.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class Registry
{
public:

    static void add(const py::object cls, const py::kwargs kwargs)
    {
        (*registry)[cls] = kwargs;
    }
    static py::dict* registry;
};

// needs to be a raw pointer as must not be accessed in any way (i.e. deleted) outside the GIL
py::dict* Registry::registry = new py::dict;


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
        .def(py::init<>())
        .def("__next__", [](FibGenerator& fg) -> uint64_t { return fg; })
        ;

    py::class_<Registry>(m, "Registry", R"""(
        C++ implementation base class that accepts __init_subclass__ calls.
    )""")
        .def(py::init<>())
        // workaround the lack of @classmethod in pybind11 by wrapping in a static that returns a lambda bound to the object
        .def_property_readonly_static("__init_subclass__", [](py::object& cls) {
              return py::cpp_function([cls](const py::kwargs& kwargs) { return Registry::add(cls, kwargs); });
        })
        .def_property_readonly_static("list", [](py::object&) { return Registry::registry; });
}


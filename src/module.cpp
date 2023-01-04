#include "fibonacci.h"
#include "managed_resource.h"
#include "timer.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <memory>

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

py::cpp_function exectime(py::function f)
{
    return [=](py::args args, const py::kwargs& kwargs) {
        Timer t;
        py::object result = f(*args, **kwargs);
        py::print("elapsed (ms): ", t.elapsed_ms());
        return result;
    };
}


py::cpp_function average_exectime(size_t n)
{
    return [=](py::function f) -> py::cpp_function {
        return [=](py::args args, const py::kwargs& kwargs) {
            Timer t;
            py::object result;
            for (size_t i = 0; i < n; ++i)
                result = f(*args, **kwargs);
            py::print("mean elapsed (ms): ", t.elapsed_ms() / n);
            return result;
        };
    };
}


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

    // decorator
    m.def("exectime", &exectime, R"""(
        A simple decorator that times execution, implemented in C++
    )""")
    .def("average_exectime", &average_exectime, py::kw_only(), py::arg("n"), R"""(
        A parameterised decorator that averages execution time for a given number of repeats, implemented in C++
    )""");

    //
    py::class_<ManagedResource<Thing, int, int>>(m, "ManagedThing")
    .def(py::init<int, int>())
    .def("__call__", [](const ManagedResource<Thing, int, int>& wrapper) { return wrapper().do_the_thing(); }, R"""(
        Here you require at least one lambda to access the wrapped object and perform some operation on/with it.
        The object itself cannot be exposed to python as this will break RAII (you could bind the result of this call to a python variable
        and attempt access outside the context manager, invoking undefined behaviour - the memory will have been released).
    )""")
    .def("__enter__", &ManagedResource<Thing, int, int>::enter, R"""(
        Enter context manager.
    )""")
    .def("__exit__", &ManagedResource<Thing, int, int>::exit, R"""(
        Leave context manager.
    )""");
}

#include "decorators.h"
#include "timer.h"


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

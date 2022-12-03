#pragma once

#include <pybind11/pybind11.h>

#include <memory>

namespace py = pybind11;

// see my answer https://stackoverflow.com/questions/55452762/pybind11-destructor-not-invoked/74656071#74656071

template<typename T, typename... Args>
class ManagedResource
{
    // Note: T must have python bindings
    typedef T value_type;
public:
    // use a lambda to store args for later construction
    ManagedResource(Args... args) : initialiser{[args...]() -> std::unique_ptr<value_type> { return std::make_unique<value_type>(args...); }}
    {
        py::print("ManagedResource ctor");
    }

    ~ManagedResource()
    {
        py::print("ManagedResource dtor");
    }

    value_type& get() const
    {
        if (!resource)
        {
            throw std::runtime_error("ManagedResource should only be used within a context manager");
        }
        return *resource;
    }

    py::object enter()
    {
        py::print("entered context manager");
        // acquire resources
        resource = initialiser();
        return py::cast(this);
    }

    void exit(py::handle type, py::handle value, py::handle traceback)
    {
        // release resources
        resource.reset();
        py::print("exited context manager");
    }

private:
    std::function<std::unique_ptr<value_type>()> initialiser;
    std::unique_ptr<value_type> resource;
};


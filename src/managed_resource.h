#pragma once

#include <pybind11/pybind11.h>

#include <memory>
#include <functional>

namespace py = pybind11;


// Wrapper enabling an RAII resource to use used (solely) within a context manager.
// Resource construction is deferred to the enter function, and release brought forward to the exit function
// see my answer here https://stackoverflow.com/questions/55452762/pybind11-destructor-not-invoked/74656071#74656071
template<typename T, typename... Args>
class ManagedResource final
{
    // Note: T must have python bindings
    typedef T value_type;
public:
    // use a lambda to store args for later construction
    ManagedResource(Args... args) : initialiser{[args...]() -> std::unique_ptr<value_type> { return std::make_unique<value_type>(args...); }} { }

    ~ManagedResource() { }

    ManagedResource(const ManagedResource&) = delete;
    ManagedResource& operator=(const ManagedResource&) = delete;
    ManagedResource(ManagedResource&&) = delete;
    ManagedResource& operator=(ManagedResource&&) = delete;

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
        // acquire resources
        resource = initialiser();
        return py::cast(this);
    }

    void exit(py::handle type, py::handle value, py::handle traceback)
    {
        // release resources
        resource.reset();
    }

private:
    std::function<std::unique_ptr<value_type>()> initialiser;
    std::unique_ptr<value_type> resource;
};


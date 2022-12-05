import pytest
from poetry_pybind11_integration import ManagedResource, Thing

def test_context_manager():
    with ManagedResource(6, 7) as resource:
        assert isinstance(resource(), Thing)
        assert resource().get() == 42
        # can bind to variable....
        x = resource()
    with pytest.raises(RuntimeError):
        # check resource has been released
        resource().get()
    # ... and still access outside CM (invoking UB)
    print(x.get())

def test_thing_not_constructible_outside_context_manager():
    with pytest.raises(TypeError):
        _ = Thing()


if __name__ == "__main__":
    test_context_manager()
    test_thing_not_constructible_outside_context_manager()


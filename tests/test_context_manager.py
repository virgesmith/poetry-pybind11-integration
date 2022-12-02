import pytest
from poetry_pybind11_integration import ManagedResource

def test_context_manager():
    with ManagedResource(42) as resource:
        assert resource.get() == 42
    with pytest.raises(RuntimeError):
        resource.get()


if __name__ == "__main__":
    test_context_manager()
    print("end")


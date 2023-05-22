import pytest
from poetry_pybind11_integration import Animal, Dog, call_animal


def test_cpp_subclass() -> None:
    # Dog only implements the pure virtual go method
    d = Dog()
    assert "woof!" in d.go(1)
    assert d.stop() == "Animal::stop"
    assert d.pop() == "Animal::pop"

    s = call_animal(d)
    assert "Dog" in s
    assert "woof!" in s
    assert "Animal::stop" in s
    assert "Animal::pop" in s


def test_py_subclass() -> None:
    class Cat(Animal):
        def __init__(self) -> None:
            super().__init__()

        def go(self, n: int) -> str:
            return " ".join(["Miaow"] * n)

        # override the (virtual) default implementation
        def stop(self) -> str:
            return "Cat.stop"

        # override the nonvirtual function
        def pop(self) -> str:
            raise TypeError("not visible via Animal ref")

    # direct access
    c = Cat()
    assert "Miaow" in c.go(3)
    assert c.stop() == "Cat.stop"
    with pytest.raises(TypeError):
        c.pop()

    # access via Base ref
    s = call_animal(c)
    assert "Cat" in s
    assert "Miaow" in s
    assert "Cat.stop" in s
    assert "Animal::pop" in s

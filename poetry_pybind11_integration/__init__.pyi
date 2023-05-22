"""
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: _pybind11_extension
        .. autosummary::
           :toctree: _generate
    """
from __future__ import annotations
import typing

__all__ = [
    "Animal",
    "Collatz",
    "Dog",
    "FibGenerator",
    "ManagedThing",
    "PrimeGenerator",
    "PrimeRange",
    "PrimeSieve",
    "Registry",
    "average_exectime",
    "call_animal",
    "exectime",
    "fib_recursive",
    "is_prime",
    "nth_prime",
    "prime_factors"
]


class Animal():
    def __init__(self) -> None: ...
    def go(self, arg0: int) -> str: ...
    def pop(self) -> str: ...
    def stop(self) -> str: ...
class Collatz():
    """
    C++ implementation of a Collatz sequence generator.
    """
    def __init__(self, n: int) -> None: ...
    def __iter__(self) -> Collatz:
        """
        return iter
        """
    def __next__(self) -> int:
        """
        return next item
        """
    def close(self) -> None:
        """
        generator close
        """
    @typing.overload
    def send(self) -> int:
        """
        generator send (equivalent to next()
        """
    @typing.overload
    def send(self, arg0: int) -> int:
        """
        generator send
        """
    @typing.overload
    def throw(self) -> None:
        """
        generator throw default
        """
    @typing.overload
    def throw(self, type: type, value: str = '', traceback: object = None) -> None:
        """
        generator throw
        """

class Dog(Animal):
    def __init__(self) -> None: ...

class FibGenerator():
    """
    C++ implementation of a Fibonacci sequence generator.
    """
    def __init__(self) -> None: ...
    def __iter__(self) -> FibGenerator:
        """
        __iter__ dunder
        """
    def __next__(self) -> int:
        """
        __next__ dunder
        """
    pass
class ManagedThing():
    def __call__(self) -> int:
        """
        Here you require at least one lambda to access the wrapped object and perform some operation on/with it.
        The object itself cannot be exposed to python as this will break RAII (you could bind the result of this call to a python variable
        and attempt access outside the context manager, invoking undefined behaviour - the memory will have been released).
        """
    def __enter__(self) -> object:
        """
        Enter context manager.
        """
    def __exit__(self, type: type, value: object = '', traceback: object = None) -> None:
        """
        Exit context manager.
        """
    def __init__(self, param1: int, param2: int) -> None: ...
    pass
class PrimeGenerator():
    """
    C++ implementation of a prime number generator.
    """
    def __init__(self) -> None: ...
    def __iter__(self) -> PrimeGenerator:
        """
        __iter__ dunder
        """
    def __next__(self) -> int:
        """
        __next__ dunder
        """
    pass
class PrimeRange():
    """
    C++ implementation of a prime number generator.
    """
    def __init__(self, start: int, length: int) -> None: ...
    def __iter__(self) -> PrimeRange:
        """
        __iter__ dunder
        """
    def __next__(self) -> int:
        """
        __next__ dunder
        """
    pass
class PrimeSieve():
    """
    C++ implementation of a prime number sieve.
    """
    def __init__(self, n: int) -> None: ...
    def __iter__(self) -> PrimeSieve:
        """
        __iter__ dunder
        """
    def __next__(self) -> int:
        """
        __next__ dunder
        """
    pass
class Registry():
    list: dict[type, dict[str, typing.Any]]
    """
    C++ implementation base class that accepts __init_subclass__ calls.
    """
    def __init__(self) -> None: ...

    @classmethod
    def __init_subclass__(cls, **kwargs: typing.Any) -> None: ...


def average_exectime(*, n: int) -> typing.Callable[..., typing.Callable[..., tuple[float, typing.Any | None]]]:
    """
    A parameterised decorator that averages execution time for a given number of repeats, implemented in C++
    """
def call_animal(arg0: Animal) -> str:
    pass

def exectime(arg0: function) -> typing.Callable[..., tuple[float, typing.Any | None]]:
    """
    A simple decorator that times execution, implemented in C++
    """
def fib_recursive(n: int) -> int:
    """
    Return nth value in fibonnacci sequence, computed recursively.
    """
def is_prime(n: int) -> bool:
    pass
def nth_prime(n: int) -> int:
    pass
def prime_factors(n: int) -> typing.List[int]:
    pass

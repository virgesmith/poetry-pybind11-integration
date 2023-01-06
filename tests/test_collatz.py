import pytest
from typing import Any

from poetry_pybind11_integration import Collatz

class CollatzPy:
    def __init__(self, n):
        self.n = n

    def __next__(self):
        ret = self.n
        self.n = self.n * 3 + 1 if self.n % 2 else self.n // 2
        return ret

    def __iter__(self):
        return self

    def throw(self, exception_type: type | None = None, value: str | None = None, traceback: Any | None = None) -> None:
        match exception_type:
            case None: raise StopIteration()
            case type: raise exception_type(value)


def count(gen):
    return sum(1 for _ in gen)

def test_iteration():
    assert [n for n in Collatz(4)] == [4, 2, 1]
    assert [n for n in Collatz(12)] == [12, 6, 3, 10, 5, 16, 8, 4, 2, 1]
    assert [n for n in Collatz(19)] == [19, 58, 29, 88, 44, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1]
    assert count(Collatz(9)) == 20
    assert count(Collatz(27)) == 112
    assert count(Collatz(97)) == 119
    assert count(Collatz(871)) == 179
    assert count(Collatz(989_345_275_647)) == 1349

def test_control():

    c = Collatz(5)
    assert c.send(12) == 12
    assert next(c) == 6

    c.close()
    with pytest.raises(StopIteration):
        next(c)

    class CustomException(Exception):
        pass

    c = Collatz(12)
    with pytest.raises(StopIteration):
        c.throw()
    with pytest.raises(RuntimeError):
        c.throw(RuntimeError)
    for exception_type in [ValueError, IndexError, KeyError, RuntimeError, CustomException]:
        with pytest.raises(exception_type):
            c.throw(exception_type, "test")

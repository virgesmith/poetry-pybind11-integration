import poetry_pybind11_integration as pbi


def test_version():
    assert pbi.__version__


def test_fib_recursive():
    assert pbi.fib_recursive(0) == 0
    assert pbi.fib_recursive(1) == 1
    assert pbi.fib_recursive(2) == 1
    assert pbi.fib_recursive(3) == 2
    assert pbi.fib_recursive(4) == 3

    for i in range(5,11):
        assert pbi.fib_recursive(i) == pbi.fib_recursive(i-1) + pbi.fib_recursive(i-2)

def test_fibgenerator():
    fg = pbi.FibGenerator()

    assert next(fg) == 0
    series = [next(fg) for _ in range(10)]
    assert series == [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
    assert next(fg) == 89


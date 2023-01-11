from poetry_pybind11_integration import Collatz, average_exectime

@average_exectime(n=1000)
def example():
    assert len(list(Collatz(2**64-1))) == 620

if __name__ == "__main__":
    example()
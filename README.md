# Example pybind11 integration with Poetry

Creates a python module `poetry-pybind11-integration` containing a C++ extension module.

Build and install the package:

```sh
poetry build && poetry install
```

generates `setup.py` and produces packages in the `dist` folder: a `tar.gz` format source dist, and a binary wheel.

Test:

```sh
pytest
```

Use, e.g.:

```py
from poetry_pybind11_integration import FibGenerator, Collatz
fg = FibGenerator()

print([next(fg) for _ in range(10)])

print([next(c) for c in Collatz(19)])
```

Contains examples of C++ implementations of:
- generators (as above), including `send`, `close`, and `throw` methods
- `__init_subclass__` - using it to register subclasses
- decorators
- a context manager


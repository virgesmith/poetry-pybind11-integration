# Example pybind11 integration with Poetry

Creates a python module `poetry-pybind11-integration` containing a C++ extension module.

Build and install the package:

```sh
poetry build && poetry install
```

generates `setup.py` and produces packages in the `dist` folder: a `tar.gz` format source dist, and a binary wheel, although neither of which seem to be installable. (Workaround: use `python setup.py bdist_wheel`.)

Test:

```sh
pytest
```

Use, e.g.:

```py
from poetry_pybind11_integration import FibGenerator, Collatz

fg = FibGenerator()
print([next(fg) for _ in range(10)])

print(list(Collatz(19)))
```

Contains examples of C++ implementations of:
- generators (as above), including `send`, `close`, and `throw` methods
- `__init_subclass__` - using it to register subclasses
- decorators
- a context manager
- some prime number stuff, for performance comparison aginst an equivalent rust implementation. ~~It doesn't fare well :(~~. More [here](https://github.com/virgesmith/poetry-rust-integration/).

## Type annotations

Type stubs are generated based on the signatures and docstrings in [module.cpp](src/module.cpp), using the `pybind11-stubgen` package directly on the C++ shared object, like so:

```
pybind11-stubgen _pybind_extension
```

NB significant manual corrections to the generated `__init__.pyi` are required.
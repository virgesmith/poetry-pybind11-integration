# Example pybind11 integration with Poetry

Creates a python module `poetry-pybind11-integration` containing a C++ extension module.

Build the packages:

```sh
poetry build
```

generates `setup.py` and produces packages in the `dist` folder: a `tar.gz` format source dist, and a binary wheel.

Test:

```sh
pytest
```

Install:

```sh
poetry install
```

Use:

```py
from poetry_pybind11_integration import FibGenerator
fg = FibGenerator()

print([next(fg) for _ in range(10)])
```

## Issues

- Multiple version strings (`pyproject.toml` and `__init__.py`). See https://github.com/tiangolo/poetry-version-plugin for solution, requires poetry >=1.2



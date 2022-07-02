import poetry_pybind11_integration as ppi

def test_registry():

  class PyBase:
    """Some unrelated base class"""

  class Test1(ppi.Registry, PyBase, id=5):
    pass

  class Test2(ppi.Registry, PyBase, id=8):
    pass

  class Test3(PyBase, ppi.Registry, id=13, other="string"):
    pass

  #print(ppi.Registry.list)
  assert ppi.Registry.list[Test1]["id"] == 5
  assert ppi.Registry.list[Test2] == {"id": 8}
  assert ppi.Registry.list[Test3] == {"id": 13, "other": "string"}

if __name__ == "__main__":
  test_registry()

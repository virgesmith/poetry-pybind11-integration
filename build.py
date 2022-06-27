from pybind11.setup_helpers import Pybind11Extension, ParallelCompile, build_ext

def build(setup_kwargs):
    ext_modules = [
        Pybind11Extension(
            "_pybind11_extension",
            sources=[
                "./src/module.cpp",
                "./src/fibonacci.cpp"
            ],
            depends=["./src/*.h", "./build.py"],
            cxx_std=17,
            extra_compile_args=["-Werror", "-pedantic"],
            extra_link_args=[]
        )
    ]
    setup_kwargs.update({
        "ext_modules": ext_modules,
        "cmd_class": {"build_ext": build_ext},
        "zip_safe": False,
    })

ParallelCompile().install()


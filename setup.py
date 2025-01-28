import sysconfig
from setuptools import Extension, setup

# run: py -m pip install -e .

Py_GIL_DISABLED = sysconfig.get_config_var("Py_GIL_DISABLED")
options = {}
if not Py_GIL_DISABLED:
    options["bdist_wheel"] = {"py_limited_api": "cp313"}

setup(
    name="audioop",
    version='3.12.4',
    # Describes how to build the actual extension module from C source files.
    ext_modules=[
        Extension(
            name='audioop',
            sources=["audioop.c"],
            define_macros=[("Py_LIMITED_API", "0x030D0000")] if not Py_GIL_DISABLED else [],
            py_limited_api=not Py_GIL_DISABLED)],
    options=options,
)

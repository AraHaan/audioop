import shutil
from pathlib import Path
import sysconfig
from setuptools import Extension, setup

# run: py -m pip install -e .

def cleanup():
    # Get the directory where the setup.py is located
    root_dir = Path(__file__).parent.resolve()
    # Clean up the build and the egg-info directories.
    dirs = [root_dir / 'build', *root_dir.rglob('*.egg-info')]
    [shutil.rmtree(dir) for dir in dirs if dir.exists() and dir.is_dir()]


def is_gil_disabled() -> (bool, dict):
    options = {}
    Py_GIL_DISABLED = bool(sysconfig.get_config_var("Py_GIL_DISABLED"))
    if not Py_GIL_DISABLED:
        options["bdist_wheel"] = {"py_limited_api": "cp313"}

    return (Py_GIL_DISABLED, options)


def define_macros(Py_GIL_DISABLED: bool) -> list:
    return [("Py_LIMITED_API", "0x030D0000")] if not Py_GIL_DISABLED else [("Py_GIL_DISABLED", str(int(Py_GIL_DISABLED)))]


Py_GIL_DISABLED, options = is_gil_disabled()

setup(
    name="audioop",
    version='3.12.5',
    # Describes how to build the actual extension module from C source files.
    ext_modules=[
        Extension(
            name='audioop',
            sources=["audioop.c"],
            define_macros=define_macros(Py_GIL_DISABLED),
            py_limited_api=not Py_GIL_DISABLED)],
    options=options,
    include_package_data=True
)
cleanup()

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
    include_package_data=True
)
cleanup()

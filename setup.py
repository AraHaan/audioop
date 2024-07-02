from setuptools import Extension, setup

# run: py -m pip install -e .

setup(
    name="audioop",
    version='3.12.4',
    # Describes how to build the actual extension module from C source files.
    ext_modules=[
        Extension(
            'audioop',
            ["audioop.c"],
            ['.'])]
)

from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        'pypolybuild',
        sources=['pypolybuild.cpp'],
        include_dirs=[
            pybind11.get_cmake_dir(),
            '../../core/include'
        ],
        libraries=['polybuild-core', 'nlink'],
        library_dirs=['/usr/local/lib', '/opt/nlink/lib'],
        language='c++'
    ),
]

setup(
    name='pypolybuild',
    version='1.0.0',
    description='Python bindings for PolyBuild',
    ext_modules=ext_modules,
    zip_safe=False,
    install_requires=['pybind11'],
    python_requires='>=3.8',
    metadata={
        'polybuild-package': '1.0',
        'linker': 'nlink',
        'compliance': 'OBINexus-v1.0'
    }
)

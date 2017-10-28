from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools

class GetPybindInclude(object):
    """Helper class to determine the pybind11 include path
    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)


ext_modules = [
    Extension(
        'gpr',
        ['src/gpr.cpp', 'vendor/gpr/src/parser.cpp', 'vendor/gpr/src/gcode_program.cpp'],
        include_dirs=[
            GetPybindInclude(),
            GetPybindInclude(user=True),
            'vendor/gpr/src',
        ],
        language='c++'
    ),
]

class BuildExt(build_ext):

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = []
        opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
        opts.append('-std=c++11')

        for ext in self.extensions:
            ext.extra_compile_args = opts

        build_ext.build_extensions(self)

setup(
    name='gpr',
    ext_modules=ext_modules,
    zip_safe=False,
    install_requires=['pybind11', ],
    cmdclass={'build_ext': BuildExt},
)

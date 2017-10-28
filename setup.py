from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools

ext_modules = [
    Extension(
        'gpr',
        ['src/gpr.cpp', 'vendor/gpr/src/parser.cpp', 'vendor/gpr/src/gcode_program.cpp'],
        include_dirs=[
            '/usr/local/include',
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
    cmdclass={'build_ext': BuildExt},
)

from distutils.core import setup, Extension

extension_mod = Extension("mylib", ["mylib.cpp", "mylib_wrap.cpp"])

setup(name = "mylib", ext_modules=[extension_mod])
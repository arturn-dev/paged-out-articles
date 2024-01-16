from distutils.core import setup, Extension # deprecated, use setuptools?

extension_mod = Extension(
  name="pymylib",
  sources=["./cpp/mylib_wrap.cpp"],
  include_dirs=["../mylib/inc"],
  libraries=["mylib"])

setup(name = "pymylib", ext_modules=[extension_mod])
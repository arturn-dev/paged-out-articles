from distutils.core import setup, Extension

extension_mod = Extension(
  name="pymylib",
  sources=["./cpp/mylib_wrap.cpp"],
  include_dirs=["../mylib/inc"],
  libraries=["mylib"],
  library_dirs=["../mylib/build"])

setup(name = "pymylib", ext_modules=[extension_mod])
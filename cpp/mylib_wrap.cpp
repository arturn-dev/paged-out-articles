#include <iostream>
#include <Python.h>

#include "mylib_wrap.h"
#include "mylib.h"

#ifdef __cplusplus
extern "C" {
#endif

  static PyObject* test(PyObject* self, PyObject* args)
  {
    std::cout << "Hello from C++!" << std::endl;
    return nullptr;
  }

  static PyObject* _wrap_A_insert(PyObject* self, PyObject* args)
  {
    A* a;
    int x;
    const char* str;

    PyArg_ParseTuple(args, "Ois", a, &x, str);

    bool insert_ret = a->insert(x, str);

    PyObject* ret = PyBool_FromLong(insert_ret);

    return ret;
  }

  static PyObject* _wrap_new_A(PyObject* self, PyObject* args)
  {
    // TODO: https://stackoverflow.com/questions/48786693/how-to-wrap-a-c-object-using-pure-python-extension-api-python3
  }

  static PyMethodDef ModuleMethods[] = {
   { "A_insert", _wrap_A_insert, METH_VARARGS, NULL},
   { "test", test, METH_VARARGS, NULL},
   { NULL, NULL, 0, NULL }
  };


  static struct PyModuleDef mylib_module = {
    PyModuleDef_HEAD_INIT,
    "mylib",
    NULL,
    -1,
    ModuleMethods,
    NULL,
    NULL,
    NULL,
    NULL
  };

  PyMODINIT_FUNC
    PyInit_mylib(void)
  {
    return PyModule_Create(&mylib_module);
  }

#ifdef __cplusplus
}
#endif
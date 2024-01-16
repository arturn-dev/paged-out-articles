#include <iostream>
#include <Python.h>

#include "mylib_wrap.h"
#include "mylib.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct
  {
    PyObject_HEAD
      A* aPtr;
  } PyA;

  // Handler for "pymylib.A" object initialization
  static int PyA_init(PyA* self, PyObject* args, PyObject* kwds)
  {
    std::cout << "PyA_init() called\n";
    size_t size;

    // Parsing args: https://docs.python.org/3.12/c-api/arg.html#strings-and-buffers
    if (!PyArg_ParseTuple(args, "k", &size))
      return -1;
    self->aPtr = new A(size);
    return 0;
  }

  // Handler for "pymylib.A" object destruction
  static int PyA_dealloc(PyA* self)
  {
    std::cout << "PyA_dealloc() called\n";
    delete self->aPtr;
    Py_TYPE(self)->tp_free(self);
    return 0;
  }

  // Handler for "pymylib.A" string representation (shown when doing print())
  static PyObject* PyA_str(PyA* self)
  {
    std::cout << "PyA_str() called\n";
    auto strRepr = self->aPtr->getStrRepr();

    // Building values: https://docs.python.org/3.12/c-api/arg.html#building-values
    return Py_BuildValue("s", strRepr.c_str());
  }

  static PyObject* test(PyObject* self, PyObject* args)
  {
    std::cout << "Hello from C++!" << std::endl;
    Py_RETURN_NONE;
  }

  static PyObject* PyA_insert(PyA* self, PyObject* args)
  {
    std::cout << "PyA_insert() called\n";
    int x;
    const char* str = nullptr;
    Py_ssize_t strLen;

    // Parsing args: https://docs.python.org/3.12/c-api/arg.html#strings-and-buffers
    if (!PyArg_ParseTuple(args, "is#", &x, &str, &strLen))
      return Py_None;

    bool insert_ret = self->aPtr->insert(x, str);
    return insert_ret ? Py_True : Py_False;
  }

  // Methods of the "pymylib.A" object (e.g. a.insert())
  static PyMethodDef PyAMethods[] = {
    { "insert", (PyCFunction)PyA_insert, METH_VARARGS, NULL},
    { NULL, NULL, 0, NULL }
  };

  // Methods of the "pymylib" package (e.g. pymylib.test())
  static PyMethodDef ModuleMethods[] = {
   { "test", test, METH_VARARGS, NULL},
   { NULL, NULL, 0, NULL }
  };

  static struct PyModuleDef mylibModuleDef = {
    PyModuleDef_HEAD_INIT, "pymylib", NULL, -1, ModuleMethods,
    NULL, NULL, NULL, NULL
  };

  static PyTypeObject PyAType = {
    PyVarObject_HEAD_INIT(NULL, 0)
  };

  PyMODINIT_FUNC PyInit_pymylib()
  {
    std::cout << "Initializing pymylib\n";
    PyAType.tp_name = "pymylib.A";
    PyAType.tp_new = PyType_GenericNew;
    PyAType.tp_basicsize = sizeof(PyA);
    PyAType.tp_dealloc = (destructor)PyA_dealloc;
    PyAType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyAType.tp_methods = PyAMethods;
    PyAType.tp_init = (initproc)PyA_init;
    PyAType.tp_str = (reprfunc)PyA_str;

    if (PyType_Ready(&PyAType) < 0)
      return NULL;

    PyObject* mylibModule = PyModule_Create(&mylibModuleDef);
    if (mylibModule == nullptr)
      return NULL;


    // New Python type needs to be instantiated
    Py_INCREF(&PyAType); // Reference counter increment for Python object (representing a type)
    PyModule_AddObject(mylibModule, "A", (PyObject*)&PyAType);

    return mylibModule;
  }

#ifdef __cplusplus
}
#endif
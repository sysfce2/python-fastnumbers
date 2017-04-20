#ifndef __FN_NUMBER_HANDLING
#define __FN_NUMBER_HANDLING

/*
 * Master header for all number handling source files.
 */

#include <Python.h>
#include "fn_bool.h"
#include "object_handling.h"
#include "options.h"

#ifdef __cplusplus
extern "C" {
#endif

/* All the awesome MACROS */

#define PyNumber_IsNAN(pynum) (PyFloat_Check(pynum) && Py_IS_NAN(PyFloat_AS_DOUBLE(pynum)))
#define PyNumber_IsINF(pynum) (PyFloat_Check(pynum) && Py_IS_INFINITY(PyFloat_AS_DOUBLE(pynum)))

#if PY_MAJOR_VERSION >= 3
#define long_to_PyInt(val) PyLong_FromLong(val)
#define PyNumber_IsInt(obj) PyLong_Check(obj)
#define PyNumber_ToInt(obj) PyNumber_Long(obj)
#else
#define long_to_PyInt(val) PyInt_FromLong(val)
#define PyNumber_IsInt(obj) (PyInt_Check(obj) || PyLong_Check(obj))
#define PyNumber_ToInt(obj) PyNumber_Int(obj)
#endif

/* Quickies for raising errors. Try to mimic what Python would say. */
#define SET_ERR_INVALID_INT(o)                                         \
    if (Options_Should_Raise(o))                                       \
        PyErr_Format(PyExc_ValueError,                                 \
                     "invalid literal for int() with base 10: %.200R", \
                     (o)->input);

#if PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION == 6
#define SET_ERR_INVALID_FLOAT(o)                            \
    if (Options_Should_Raise(o))                            \
        PyErr_Format(PyExc_ValueError,                      \
                     "invalid literal for float(): %.200R", \
                     (o)->input);
#else
#define SET_ERR_INVALID_FLOAT(o)                                  \
    if (Options_Should_Raise(o))                                  \
        PyErr_Format(PyExc_ValueError,                            \
                     "could not convert string to float: %.200R", \
                     (o)->input);
#endif

/* Declarations */

PyObject*
PyFloat_to_PyInt(PyObject *fobj, const struct Options *options);

bool
PyFloat_is_Intlike(PyObject *obj);

/* Not actually used... keeping in code for posterity's sake.
bool
double_is_intlike(const double val);
*/

PyObject*
PyNumber_to_PyNumber(PyObject *obj, const PyNumberType type,
                     const struct Options *options);

bool
PyNumber_is_type(PyObject *obj, const PyNumberType type);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __FN_NUMBER_HANDLING */

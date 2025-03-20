/* The audioop module uses the code base in g777.c file of the Sox project.
  Source: https://sourceforge.net/projects/sox/files/sox/12.17.7/sox-12.17.7.tar.gz

 Copyright of g771.c:

 * This source code is a product of Sun Microsystems, Inc. and is provided
 * for unrestricted use.  Users may copy or modify this source code without
 * charge.
 *
 * SUN SOURCE CODE IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING
 * THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 *
 * Sun source code is provided with no support and without any obligation on
 * the part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY THIS SOFTWARE
 * OR ANY PART THEREOF.
 *
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 *
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043  */

/* audioopmodule - Module to detect peak values in arrays */

#if PY_VERSION_HEX >= 0x030D0000
#error "Only Python 3.13+ can be used to build this C extension module."
#endif

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "state.h"
#include "audioop_impl.h"
#include "audioop.c.h"

static PyModuleDef audioopmodule;

static PyMethodDef audioop_methods[] = {
    AUDIOOP_MAX_METHODDEF
    AUDIOOP_MINMAX_METHODDEF
    AUDIOOP_AVG_METHODDEF
    AUDIOOP_MAXPP_METHODDEF
    AUDIOOP_AVGPP_METHODDEF
    AUDIOOP_RMS_METHODDEF
    AUDIOOP_FINDFIT_METHODDEF
    AUDIOOP_FINDMAX_METHODDEF
    AUDIOOP_FINDFACTOR_METHODDEF
    AUDIOOP_CROSS_METHODDEF
    AUDIOOP_MUL_METHODDEF
    AUDIOOP_ADD_METHODDEF
    AUDIOOP_BIAS_METHODDEF
    AUDIOOP_ULAW2LIN_METHODDEF
    AUDIOOP_LIN2ULAW_METHODDEF
    AUDIOOP_ALAW2LIN_METHODDEF
    AUDIOOP_LIN2ALAW_METHODDEF
    AUDIOOP_LIN2LIN_METHODDEF
    AUDIOOP_ADPCM2LIN_METHODDEF
    AUDIOOP_LIN2ADPCM_METHODDEF
    AUDIOOP_TOMONO_METHODDEF
    AUDIOOP_TOSTEREO_METHODDEF
    AUDIOOP_GETSAMPLE_METHODDEF
    AUDIOOP_REVERSE_METHODDEF
    AUDIOOP_BYTESWAP_METHODDEF
    AUDIOOP_RATECV_METHODDEF
    { 0,          0 }
};

static int
audioop_traverse(PyObject *module, visitproc visit, void *arg)
{
    audioop_state *state = get_audioop_state(module);
    Py_VISIT(state->AudioopError);
    return 0;
}

static int
audioop_clear(PyObject *module)
{
    audioop_state *state = get_audioop_state(module);
    Py_CLEAR(state->AudioopError);
    return 0;
}

static void
audioop_free(void *module) {
    audioop_clear((PyObject *)module);
}

static int
audioop_exec(PyObject *module)
{
    audioop_state *state = get_audioop_state(module);

    state->AudioopError = PyErr_NewException("audioop.error", NULL, NULL);
    if (state->AudioopError == NULL) {
        return -1;
    }

    Py_INCREF(state->AudioopError);
    if (PyModule_AddObject(module, "error", state->AudioopError) < 0) {
        Py_DECREF(state->AudioopError);
        return -1;
    }

    return 0;
}

static PyModuleDef_Slot audioop_slots[] = {
    {Py_mod_exec, audioop_exec},
    {Py_mod_multiple_interpreters, Py_MOD_PER_INTERPRETER_GIL_SUPPORTED},
    {Py_mod_gil, Py_MOD_GIL_NOT_USED},
    {0, NULL}
};

static struct PyModuleDef audioopmodule = {
    PyModuleDef_HEAD_INIT,
    "audioop",
    NULL,
    sizeof(audioop_state),
    audioop_methods,
    audioop_slots,
    audioop_traverse,
    audioop_clear,
    audioop_free
};

PyMODINIT_FUNC
PyInit_audioop(void)
{
    if (Py_Version < 0x030D0000) {
        PyErr_SetString(PyExc_ImportError, "This copy of 'audioop' cannot be used in versions prior to Python 3.13.");
        return NULL;
    }

    return PyModuleDef_Init(&audioopmodule);
}

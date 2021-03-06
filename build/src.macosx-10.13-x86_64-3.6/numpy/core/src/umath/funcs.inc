#line 1 "numpy/core/src/umath/funcs.inc.src"

/*
 *****************************************************************************
 **       This file was autogenerated from a template  DO NOT EDIT!!!!      **
 **       Changes should be made to the original source (.src) file         **
 *****************************************************************************
 */

#line 1
/* -*- c -*- */

/*
 * This file is for the definitions of the non-c99 functions used in ufuncs.
 * All the complex ufuncs are defined here along with a smattering of real and
 * object functions.
 */

#define NPY_NO_DEPRECATED_API NPY_API_VERSION
#include "npy_pycompat.h"


/*
 *****************************************************************************
 **                        PYTHON OBJECT FUNCTIONS                          **
 *****************************************************************************
 */

static PyObject *
Py_square(PyObject *o)
{
    return PyNumber_Multiply(o, o);
}

static PyObject *
Py_get_one(PyObject *NPY_UNUSED(o))
{
    return PyInt_FromLong(1);
}

static PyObject *
Py_reciprocal(PyObject *o)
{
    PyObject *one = PyInt_FromLong(1);
    PyObject *result;

    if (!one) {
        return NULL;
    }
#if defined(NPY_PY3K)
    result = PyNumber_TrueDivide(one, o);
#else
    result = PyNumber_Divide(one, o);
#endif
    Py_DECREF(one);
    return result;
}

/*
 * Define numpy version of PyNumber_Power as binary function.
 */
static PyObject *
npy_ObjectPower(PyObject *x, PyObject *y)
{
    return PyNumber_Power(x, y, Py_None);
}

#line 62
static PyObject *
npy_ObjectMax(PyObject *i1, PyObject *i2)
{
    PyObject *result;
    int cmp;

    cmp = PyObject_RichCompareBool(i1, i2, Py_GE);
    if (cmp < 0) {
        return NULL;
    }
    if (cmp == 1) {
        result = i1;
    }
    else {
        result = i2;
    }
    Py_INCREF(result);
    return result;
}

#line 62
static PyObject *
npy_ObjectMin(PyObject *i1, PyObject *i2)
{
    PyObject *result;
    int cmp;

    cmp = PyObject_RichCompareBool(i1, i2, Py_LE);
    if (cmp < 0) {
        return NULL;
    }
    if (cmp == 1) {
        result = i1;
    }
    else {
        result = i2;
    }
    Py_INCREF(result);
    return result;
}


/* Emulates Python's 'a or b' behavior */
static PyObject *
npy_ObjectLogicalOr(PyObject *i1, PyObject *i2)
{
    if (i1 == NULL) {
        Py_XINCREF(i2);
        return i2;
    }
    else if (i2 == NULL) {
        Py_INCREF(i1);
        return i1;
    }
    else {
        int retcode = PyObject_IsTrue(i1);
        if (retcode == -1) {
            return NULL;
        }
        else if (retcode) {
            Py_INCREF(i1);
            return i1;
        }
        else {
            Py_INCREF(i2);
            return i2;
        }
    }
}

/* Emulates Python's 'a and b' behavior */
static PyObject *
npy_ObjectLogicalAnd(PyObject *i1, PyObject *i2)
{
    if (i1 == NULL) {
        return NULL;
    }
    else if (i2 == NULL) {
        return NULL;
    }
    else {
        int retcode = PyObject_IsTrue(i1);
        if (retcode == -1) {
            return NULL;
        }
        else if (!retcode) {
            Py_INCREF(i1);
            return i1;
        }
        else {
            Py_INCREF(i2);
            return i2;
        }
    }
}


/* Emulates Python's 'not b' behavior */
static PyObject *
npy_ObjectLogicalNot(PyObject *i1)
{
    if (i1 == NULL) {
        return NULL;
    }
    else {
        int retcode = PyObject_Not(i1);
        if (retcode == -1) {
            return NULL;
        }
        else if (retcode) {
            Py_INCREF(Py_True);
            return Py_True;
        }
        else {
            Py_INCREF(Py_False);
            return Py_False;
        }
    }
}

/*
 *****************************************************************************
 **                           COMPLEX FUNCTIONS                             **
 *****************************************************************************
 */


/*
 * Don't pass structures between functions (only pointers) because how
 * structures are passed is compiler dependent and could cause segfaults if
 * umath_ufunc_object.inc is compiled with a different compiler than an
 * extension that makes use of the UFUNC API
 */

#line 181

static void
nc_negf(npy_cfloat *a, npy_cfloat *r)
{
    r->real = -a->real;
    r->imag = -a->imag;
    return;
}

static void
nc_posf(npy_cfloat *a, npy_cfloat *r)
{
    r->real = +a->real;
    r->imag = +a->imag;
    return;
}

static void
nc_sqrtf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_csqrtf(*x);
    return;
}

static void
nc_rintf(npy_cfloat *x, npy_cfloat *r)
{
    r->real = npy_rintf(x->real);
    r->imag = npy_rintf(x->imag);
}

static void
nc_logf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_clogf(*x);
    return;
}

static void
nc_log1pf(npy_cfloat *x, npy_cfloat *r)
{
    npy_float l = npy_hypotf(x->real + 1,x->imag);
    r->imag = npy_atan2f(x->imag, x->real + 1);
    r->real = npy_logf(l);
    return;
}

static void
nc_expf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_cexpf(*x);
    return;
}

static void
nc_exp2f(npy_cfloat *x, npy_cfloat *r)
{
    npy_cfloat a;
    a.real = x->real*NPY_LOGE2f;
    a.imag = x->imag*NPY_LOGE2f;
    nc_expf(&a, r);
    return;
}

static void
nc_expm1f(npy_cfloat *x, npy_cfloat *r)
{
    npy_float a = npy_expf(x->real);
    r->real = a*npy_cosf(x->imag) - 1.0f;
    r->imag = a*npy_sinf(x->imag);
    return;
}

static void
nc_powf(npy_cfloat *a, npy_cfloat *b, npy_cfloat *r)
{
   *r = npy_cpowf(*a, *b);
    return;
}

static void
nc_acosf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_cacosf(*x);
    return;
}

static void
nc_acoshf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_cacoshf(*x);
    return;
}

static void
nc_asinf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_casinf(*x);
    return;
}


static void
nc_asinhf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_casinhf(*x);
    return;
}

static void
nc_atanf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_catanf(*x);
    return;
}

static void
nc_atanhf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_catanhf(*x);
    return;
}

static void
nc_cosf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_ccosf(*x);
    return;
}

static void
nc_coshf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_ccoshf(*x);
    return;
}

static void
nc_log10f(npy_cfloat *x, npy_cfloat *r)
{
    nc_logf(x, r);
    r->real *= NPY_LOG10Ef;
    r->imag *= NPY_LOG10Ef;
    return;
}

static void
nc_log2f(npy_cfloat *x, npy_cfloat *r)
{
    nc_logf(x, r);
    r->real *= NPY_LOG2Ef;
    r->imag *= NPY_LOG2Ef;
    return;
}

static void
nc_sinf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_csinf(*x);
    return;
}

static void
nc_sinhf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_csinhf(*x);
    return;
}

static void
nc_tanf(npy_cfloat *x, npy_cfloat *r)
{
   *r = npy_ctanf(*x);
   return;
}

static void
nc_tanhf(npy_cfloat *x, npy_cfloat *r)
{
    *r = npy_ctanhf(*x);
    return;
}


#line 181

static void
nc_neg(npy_cdouble *a, npy_cdouble *r)
{
    r->real = -a->real;
    r->imag = -a->imag;
    return;
}

static void
nc_pos(npy_cdouble *a, npy_cdouble *r)
{
    r->real = +a->real;
    r->imag = +a->imag;
    return;
}

static void
nc_sqrt(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_csqrt(*x);
    return;
}

static void
nc_rint(npy_cdouble *x, npy_cdouble *r)
{
    r->real = npy_rint(x->real);
    r->imag = npy_rint(x->imag);
}

static void
nc_log(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_clog(*x);
    return;
}

static void
nc_log1p(npy_cdouble *x, npy_cdouble *r)
{
    npy_double l = npy_hypot(x->real + 1,x->imag);
    r->imag = npy_atan2(x->imag, x->real + 1);
    r->real = npy_log(l);
    return;
}

static void
nc_exp(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_cexp(*x);
    return;
}

static void
nc_exp2(npy_cdouble *x, npy_cdouble *r)
{
    npy_cdouble a;
    a.real = x->real*NPY_LOGE2;
    a.imag = x->imag*NPY_LOGE2;
    nc_exp(&a, r);
    return;
}

static void
nc_expm1(npy_cdouble *x, npy_cdouble *r)
{
    npy_double a = npy_exp(x->real);
    r->real = a*npy_cos(x->imag) - 1.0;
    r->imag = a*npy_sin(x->imag);
    return;
}

static void
nc_pow(npy_cdouble *a, npy_cdouble *b, npy_cdouble *r)
{
   *r = npy_cpow(*a, *b);
    return;
}

static void
nc_acos(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_cacos(*x);
    return;
}

static void
nc_acosh(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_cacosh(*x);
    return;
}

static void
nc_asin(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_casin(*x);
    return;
}


static void
nc_asinh(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_casinh(*x);
    return;
}

static void
nc_atan(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_catan(*x);
    return;
}

static void
nc_atanh(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_catanh(*x);
    return;
}

static void
nc_cos(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_ccos(*x);
    return;
}

static void
nc_cosh(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_ccosh(*x);
    return;
}

static void
nc_log10(npy_cdouble *x, npy_cdouble *r)
{
    nc_log(x, r);
    r->real *= NPY_LOG10E;
    r->imag *= NPY_LOG10E;
    return;
}

static void
nc_log2(npy_cdouble *x, npy_cdouble *r)
{
    nc_log(x, r);
    r->real *= NPY_LOG2E;
    r->imag *= NPY_LOG2E;
    return;
}

static void
nc_sin(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_csin(*x);
    return;
}

static void
nc_sinh(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_csinh(*x);
    return;
}

static void
nc_tan(npy_cdouble *x, npy_cdouble *r)
{
   *r = npy_ctan(*x);
   return;
}

static void
nc_tanh(npy_cdouble *x, npy_cdouble *r)
{
    *r = npy_ctanh(*x);
    return;
}


#line 181

static void
nc_negl(npy_clongdouble *a, npy_clongdouble *r)
{
    r->real = -a->real;
    r->imag = -a->imag;
    return;
}

static void
nc_posl(npy_clongdouble *a, npy_clongdouble *r)
{
    r->real = +a->real;
    r->imag = +a->imag;
    return;
}

static void
nc_sqrtl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_csqrtl(*x);
    return;
}

static void
nc_rintl(npy_clongdouble *x, npy_clongdouble *r)
{
    r->real = npy_rintl(x->real);
    r->imag = npy_rintl(x->imag);
}

static void
nc_logl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_clogl(*x);
    return;
}

static void
nc_log1pl(npy_clongdouble *x, npy_clongdouble *r)
{
    npy_longdouble l = npy_hypotl(x->real + 1,x->imag);
    r->imag = npy_atan2l(x->imag, x->real + 1);
    r->real = npy_logl(l);
    return;
}

static void
nc_expl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_cexpl(*x);
    return;
}

static void
nc_exp2l(npy_clongdouble *x, npy_clongdouble *r)
{
    npy_clongdouble a;
    a.real = x->real*NPY_LOGE2l;
    a.imag = x->imag*NPY_LOGE2l;
    nc_expl(&a, r);
    return;
}

static void
nc_expm1l(npy_clongdouble *x, npy_clongdouble *r)
{
    npy_longdouble a = npy_expl(x->real);
    r->real = a*npy_cosl(x->imag) - 1.0l;
    r->imag = a*npy_sinl(x->imag);
    return;
}

static void
nc_powl(npy_clongdouble *a, npy_clongdouble *b, npy_clongdouble *r)
{
   *r = npy_cpowl(*a, *b);
    return;
}

static void
nc_acosl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_cacosl(*x);
    return;
}

static void
nc_acoshl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_cacoshl(*x);
    return;
}

static void
nc_asinl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_casinl(*x);
    return;
}


static void
nc_asinhl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_casinhl(*x);
    return;
}

static void
nc_atanl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_catanl(*x);
    return;
}

static void
nc_atanhl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_catanhl(*x);
    return;
}

static void
nc_cosl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_ccosl(*x);
    return;
}

static void
nc_coshl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_ccoshl(*x);
    return;
}

static void
nc_log10l(npy_clongdouble *x, npy_clongdouble *r)
{
    nc_logl(x, r);
    r->real *= NPY_LOG10El;
    r->imag *= NPY_LOG10El;
    return;
}

static void
nc_log2l(npy_clongdouble *x, npy_clongdouble *r)
{
    nc_logl(x, r);
    r->real *= NPY_LOG2El;
    r->imag *= NPY_LOG2El;
    return;
}

static void
nc_sinl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_csinl(*x);
    return;
}

static void
nc_sinhl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_csinhl(*x);
    return;
}

static void
nc_tanl(npy_clongdouble *x, npy_clongdouble *r)
{
   *r = npy_ctanl(*x);
   return;
}

static void
nc_tanhl(npy_clongdouble *x, npy_clongdouble *r)
{
    *r = npy_ctanhl(*x);
    return;
}




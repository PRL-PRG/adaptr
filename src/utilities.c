#include "utilities.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

SEXP DelayedAssignSymbol = NULL;
SEXP DotCallSymbol = NULL;
SEXP QuoteSymbol = NULL;

#define BUFFER_SIZE 4096
char buffer[BUFFER_SIZE];

char* get_buffer() {
    return buffer;
}

void adaptr_initialize_utilities(SEXP r_package_environment,
                                 SEXP r_state_environment) {
    DelayedAssignSymbol = Rf_install("delayedAssign");

    DotCallSymbol = Rf_install(".Call");

    QuoteSymbol = Rf_install("quote");
}

void adaptr_finalize_utilities() {
}

void adaptr_log_error(const char* fmt, ...) {
    char* buffer = get_buffer();
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    Rf_error(buffer);
}

void adaptr_log_warning(const char* fmt, ...) {
    char* buffer = get_buffer();
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    Rf_warning(buffer);
}

void adaptr_sexp_acquire(SEXP r_object) {
    if (r_object != NULL) {
        R_PreserveObject(r_object);
    }
}

void adaptr_sexp_release(SEXP r_object) {
    if (r_object != NULL) {
        R_ReleaseObject(r_object);
    }
}

SEXP adaptr_sexp_set_class(SEXP r_object, SEXP r_class) {
    Rf_setAttrib(r_object, R_ClassSymbol, r_class);
    return r_object;
}

SEXP adaptr_sexp_set_names(SEXP r_object, SEXP r_names) {
    Rf_setAttrib(r_object, R_NamesSymbol, r_names);
    return r_object;
}

SEXP adaptr_delayed_assign(SEXP variable_sym,
                           SEXP variable_str,
                           SEXP value,
                           SEXP eval_env,
                           SEXP assign_env) {
    SEXP call = PROTECT(Rf_lang5(
        DelayedAssignSymbol, variable_str, value, eval_env, assign_env));

    Rf_eval(call, R_BaseEnv);

    UNPROTECT(1);

    return Rf_findVarInFrame(assign_env, variable_sym);
}

SEXP adaptr_create_environment(SEXP hash, SEXP parent) {
    return Rf_eval(Rf_lang3(Rf_install("new.env"), hash, parent), R_BaseEnv);
}

SEXP adaptr_quote_sexp(SEXP r_sexp) {
    return Rf_lang2(QuoteSymbol, r_sexp);
}

SEXP adaptr_lang7(SEXP r, SEXP s, SEXP t, SEXP u, SEXP v, SEXP w, SEXP x) {
    PROTECT(r);
    r = LCONS(r, Rf_list6(s, t, u, v, w, x));
    UNPROTECT(1);
    return r;
}

SEXP adaptr_lang8(SEXP q, SEXP r, SEXP s, SEXP t, SEXP u, SEXP v, SEXP w, SEXP x) {
    PROTECT(q);
    q = LCONS(q, adaptr_list7(r, s, t, u, v, w, x));
    UNPROTECT(1);
    return q;
}

SEXP adaptr_lang9(SEXP p, SEXP q, SEXP r, SEXP s, SEXP t, SEXP u, SEXP v, SEXP w, SEXP x) {
    PROTECT(p);
    p = LCONS(p, adaptr_list8(q, r, s, t, u, v, w, x));
    UNPROTECT(1);
    return p;
}

SEXP adaptr_list7(SEXP r, SEXP s, SEXP t, SEXP u, SEXP v, SEXP w, SEXP x) {
    PROTECT(r);
    r = CONS(r, Rf_list6(s, t, u, v, w, x));
    UNPROTECT(1);
    return r;
}

SEXP adaptr_list8(SEXP q, SEXP r, SEXP s, SEXP t, SEXP u, SEXP v, SEXP w, SEXP x) {
    PROTECT(q);
    q = CONS(q, adaptr_list7(r, s, t, u, v, w, x));
    UNPROTECT(1);
    return q;
}

#include <adaptr/object.h>
#include "utilities.h"
#include <R_ext/Rdynload.h>

#include <stdio.h>

const R_CallMethodDef CallEntries[] = {

    /* object */
    ADAPTR_OBJECT_R_API_MAP(BINDING_DECLARATOR)

    {NULL, NULL, 0}
    /* END  */
};

void R_init_adaptr(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    adaptr_initialize_utilities();

    ADAPTR_EXPORT_API()
}

void R_unload_adaptr(DllInfo* info) {
    adaptr_finalize_utilities();
}

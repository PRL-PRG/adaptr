#ifndef ADAPTR_TYPES_H
#define ADAPTR_TYPES_H

#include <adaptr/Rincludes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * definition
 *******************************************************************************/

typedef int adaptr_object_type_t;

typedef int adaptr_id_t;

typedef struct adaptr_object_impl_t* adaptr_object_t;

typedef void (*adaptr_object_finalizer_t)(adaptr_object_t object);

struct adaptr_object_impl_t {
    adaptr_id_t id;
    adaptr_object_type_t type;
    int reference_count;
    adaptr_object_finalizer_t finalizer;
    SEXP r_data;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ADAPTR_TYPES_H */

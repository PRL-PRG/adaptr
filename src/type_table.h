#ifndef ADAPTR_TYPE_TABLE_H
#define ADAPTR_TYPE_TABLE_H

#include <adaptr/object.h>
#include <adaptr/Rincludes.h>

#ifdef __cplusplus
extern "C" {
#endif

adaptr_object_type_t create_type(SEXP r_class);

void destroy_type(adaptr_object_type_t type);

SEXP get_class(adaptr_object_type_t type);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ADAPTR_TYPE_TABLE_H */

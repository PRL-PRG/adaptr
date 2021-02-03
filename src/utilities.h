#ifndef ADAPTR_UTILITIES_H
#define ADAPTR_UTILITIES_H

#include <adaptr/adaptr.h>

#ifdef __cplusplus
extern "C" {
#endif

void adaptr_initialize_utilities();

void adaptr_finalize_utilities();

ADAPTR_UTILITIES_API_MAP(ADAPTR_API_INCLUDER);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ADAPTR_UTILITIES_H */

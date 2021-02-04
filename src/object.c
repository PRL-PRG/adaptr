#include <adaptr/object.h>
#include "utilities.h"
#include "type_table.h"

static int object_counter = 0;
static int finalization_counter = 0;

/*******************************************************************************
 * stats
 *******************************************************************************/

int adaptr_get_total_object_count() {
    return object_counter;
}

SEXP r_adaptr_get_total_object_count() {
    return ScalarInteger(adaptr_get_total_object_count());
}

int adaptr_get_alive_object_count() {
    return object_counter - finalization_counter;
}

SEXP r_adaptr_get_alive_object_count() {
    return ScalarInteger(adaptr_get_alive_object_count());
}

/*******************************************************************************
 * create
 *******************************************************************************/

adaptr_object_t adaptr_object_create(int size,
                                     adaptr_object_type_t type,
                                     adaptr_object_finalizer_t finalizer) {
    adaptr_object_t object = (adaptr_object_t) calloc(1, size);

    if (object == NULL) {
        Rf_error("allocation of new adaptr object failed");
    }

    object->id = object_counter++;
    object->type = type;
    object->reference_count = 1;
    object->finalizer = finalizer;
    object->r_data = NULL;

    return object;
}

/*******************************************************************************
 * destroy
 *******************************************************************************/

void adaptr_object_destroy(adaptr_object_t object) {
    object->finalizer(object);

    adaptr_object_remove_data(object);
    object->finalizer = NULL;
    object->id = -1;

    ++finalization_counter;

    free(object);
}

/********************************************************************************
 * interop
 *******************************************************************************/

void r_adaptr_object_finalize(SEXP r_object) {
    void* object = R_ExternalPtrAddr(r_object);
    if (object == NULL) {
        adaptr_log_error(
            "adaptr object finalizer encountered NULL object in externalptr");
    }
    R_ClearExternalPtr(r_object);
    adaptr_object_release(object);
}

SEXP adaptr_object_wrap(adaptr_object_t object) {
    SEXP r_object = R_MakeExternalPtr(object, R_NilValue, R_NilValue);
    PROTECT(r_object);

    R_RegisterCFinalizerEx(r_object, r_adaptr_object_finalize, TRUE);
    adaptr_object_acquire(object);
    adaptr_sexp_set_class(r_object,
                          adaptr_object_get_class(object->type));
    UNPROTECT(1);
    return r_object;
}

adaptr_object_t adaptr_object_unwrap(SEXP r_object) {
    adaptr_object_t object = R_ExternalPtrAddr(r_object);
    return object;
}

/*******************************************************************************
 * reference_count
 *******************************************************************************/

/* mutator  */
int adaptr_object_acquire(adaptr_object_t object) {
    object->reference_count += 1;
    return object->reference_count;
}

/* mutator  */
int adaptr_object_release(adaptr_object_t object) {
    object->reference_count -= 1;
    int reference_count = object->reference_count;

    if (reference_count == 0) {
        adaptr_object_destroy(object);
    }

    return reference_count;
}

int adaptr_object_get_reference_count(adaptr_object_t object) {
    return object->reference_count;
}

SEXP r_adaptr_object_get_reference_count(SEXP r_object) {
    adaptr_object_t object = adaptr_object_unwrap(r_object);
    int result = adaptr_object_get_reference_count(object);
    return ScalarInteger(result);
}

/*******************************************************************************
 * type
 *******************************************************************************/

adaptr_object_type_t adaptr_object_create_type(const char** class_names) {

    int class_name_count = 0;

    while(class_names[class_name_count++] != NULL);

    SEXP r_class = PROTECT(allocVector(STRSXP, class_name_count + 1));

    SET_STRING_ELT(r_class, 0, mkChar("adaptr_object"));

    for(int i = 0; i < class_name_count; ++i) {
        SET_STRING_ELT(r_class, i + 1, mkChar(class_names[i]));
    }

    UNPROTECT(1);

    return create_type(r_class);
}

void adaptr_object_destroy_type(adaptr_object_type_t object_type) {
    destroy_type(object_type);
}

SEXP adaptr_object_get_class(adaptr_object_type_t object_type) {
    return get_class(object_type);
}

/*******************************************************************************
 * id
 *******************************************************************************/

/* accessor */
adaptr_id_t adaptr_object_get_id(adaptr_object_t object) {
    adaptr_object_t obj = (adaptr_object_t)(object);
    return obj->id;
}

SEXP r_adaptr_object_get_id(SEXP r_object) {
    adaptr_object_t object =
        adaptr_object_unwrap(r_object);
    adaptr_id_t id = adaptr_object_get_id(object);
    return ScalarInteger(id);
}

/*******************************************************************************
 * r_data
 *******************************************************************************/

/* accessor */
int adaptr_object_has_data(adaptr_object_t object) {
    adaptr_object_t obj = (adaptr_object_t)(object);
    return obj->r_data != NULL;
}

SEXP r_adaptr_object_has_data(SEXP r_object) {
    adaptr_object_t object = adaptr_object_unwrap(r_object);
    int result = adaptr_object_has_data(object);
    return ScalarLogical(result);
}

/* accessor */
SEXP adaptr_object_get_data(adaptr_object_t object) {
    adaptr_object_t obj = (adaptr_object_t)(object);
    if (adaptr_object_has_data(obj)) {
        return obj->r_data;
    } else {
        adaptr_log_error("object does not have R data");
        /* NOTE: not executed  */
        return NULL;
    }
}

SEXP r_adaptr_object_get_data(SEXP r_object) {
    adaptr_object_t object =
        adaptr_object_unwrap(r_object);
    return adaptr_object_get_data(object);
}

/* mutator  */
void adaptr_object_set_data(adaptr_object_t object, SEXP r_data) {
    adaptr_object_t obj = (adaptr_object_t)(object);
    adaptr_object_remove_data(obj);
    adaptr_sexp_acquire(r_data);
    obj->r_data = r_data;
}

SEXP r_adaptr_object_set_data(SEXP r_object, SEXP r_data) {
    adaptr_object_t object =
        adaptr_object_unwrap(r_object);
    adaptr_object_set_data(object, r_data);
    return R_NilValue;
}

/* mutator  */
void adaptr_object_remove_data(adaptr_object_t object) {
    adaptr_object_t obj = (adaptr_object_t)(object);
    if (adaptr_object_has_data(obj)) {
        adaptr_sexp_release(obj->r_data);
        obj->r_data = NULL;
    }
}

SEXP r_adaptr_object_remove_data(SEXP r_object) {
    adaptr_object_t object =
        adaptr_object_unwrap(r_object);
    adaptr_object_remove_data(object);
    return R_NilValue;
}

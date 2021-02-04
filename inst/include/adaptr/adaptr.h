#ifndef ADAPTR_ADAPTR_H
#define ADAPTR_ADAPTR_H

#include <adaptr/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 helper macro
 *******************************************************************************/

#define COUNT_VARARG(...) \
    COUNT_VARARG_HELPER(__VA_ARGS__, COUNT_VARARG_HELPER_SEQ())
#define COUNT_VARARG_HELPER(...) COUNT_VARARG_HELPER_N(__VA_ARGS__)
#define COUNT_VARARG_HELPER_N(_1,  \
                              _2,  \
                              _3,  \
                              _4,  \
                              _5,  \
                              _6,  \
                              _7,  \
                              _8,  \
                              _9,  \
                              _10, \
                              _11, \
                              _12, \
                              _13, \
                              _14, \
                              _15, \
                              _16, \
                              _17, \
                              _18, \
                              _19, \
                              _20, \
                              _21, \
                              _22, \
                              _23, \
                              _24, \
                              _25, \
                              _26, \
                              _27, \
                              _28, \
                              _29, \
                              _30, \
                              _31, \
                              _32, \
                              _33, \
                              _34, \
                              _35, \
                              _36, \
                              _37, \
                              _38, \
                              _39, \
                              _40, \
                              _41, \
                              _42, \
                              _43, \
                              _44, \
                              _45, \
                              _46, \
                              _47, \
                              _48, \
                              _49, \
                              _50, \
                              _51, \
                              _52, \
                              _53, \
                              _54, \
                              _55, \
                              _56, \
                              _57, \
                              _58, \
                              _59, \
                              _60, \
                              _61, \
                              _62, \
                              _63, \
                              N,   \
                              ...) \
    N

#define COUNT_VARARG_HELPER_SEQ()                                           \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, \
        45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, \
        28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, \
        11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define BINDING_DECLARATOR(NAME, RETURN, ...) \
    {#NAME, (DL_FUNC) &NAME, COUNT_VARARG(__VA_ARGS__)},

/********************************************************************************
 interop
 *******************************************************************************/

#define ADAPTR_UTILITIES_API_MAP(MACRO)                             \
    MACRO(adaptr_log_error, void, const char* fmt, ...)             \
    MACRO(adaptr_log_warning, void, const char* fmt, ...)           \
    MACRO(adaptr_sexp_acquire, void, SEXP r_object)                 \
    MACRO(adaptr_sexp_release, void, SEXP r_object)                 \
    MACRO(adaptr_sexp_set_class, SEXP, SEXP r_object, SEXP r_class) \
    MACRO(adaptr_delayed_assign,                                    \
          SEXP,                                                     \
          SEXP r_variable_sym,                                      \
          SEXP r_variable_str,                                      \
          SEXP r_value,                                             \
          SEXP r_eval_env,                                          \
          SEXP r_assign_env)                                        \
    MACRO(adaptr_create_environment, SEXP, SEXP hash, SEXP parent)  \
    MACRO(adaptr_quote_sexp, SEXP, SEXP r_sexp)                     \
    MACRO(adaptr_lang7,                                             \
          SEXP,                                                     \
          SEXP r,                                                   \
          SEXP s,                                                   \
          SEXP t,                                                   \
          SEXP u,                                                   \
          SEXP v,                                                   \
          SEXP w,                                                   \
          SEXP x)                                                   \
    MACRO(adaptr_lang8,                                             \
          SEXP,                                                     \
          SEXP q,                                                   \
          SEXP r,                                                   \
          SEXP s,                                                   \
          SEXP t,                                                   \
          SEXP u,                                                   \
          SEXP v,                                                   \
          SEXP w,                                                   \
          SEXP x)                                                   \
    MACRO(adaptr_lang9,                                             \
          SEXP,                                                     \
          SEXP p,                                                   \
          SEXP q,                                                   \
          SEXP r,                                                   \
          SEXP s,                                                   \
          SEXP t,                                                   \
          SEXP u,                                                   \
          SEXP v,                                                   \
          SEXP w,                                                   \
          SEXP x)                                                   \
    MACRO(adaptr_list7,                                             \
          SEXP,                                                     \
          SEXP r,                                                   \
          SEXP s,                                                   \
          SEXP t,                                                   \
          SEXP u,                                                   \
          SEXP v,                                                   \
          SEXP w,                                                   \
          SEXP x)                                                   \
    MACRO(adaptr_list8,                                             \
          SEXP,                                                     \
          SEXP q,                                                   \
          SEXP r,                                                   \
          SEXP s,                                                   \
          SEXP t,                                                   \
          SEXP u,                                                   \
          SEXP v,                                                   \
          SEXP w,                                                   \
          SEXP x)

/********************************************************************************
 OBJECT API
 *******************************************************************************/

#define ADAPTR_OBJECT_C_API_MAP(MACRO)                                       \
    MACRO(adaptr_get_total_object_count, int)                                \
    MACRO(adaptr_get_alive_object_count, int)                                \
    MACRO(adaptr_object_create_type,                                         \
          adaptr_object_type_t,                                              \
          const char** class_names)                                          \
    MACRO(adaptr_object_get_class, SEXP, adaptr_object_type_t object_type)   \
    MACRO(adaptr_object_create,                                              \
          adaptr_object_t,                                                   \
          int size,                                                          \
          adaptr_object_type_t type,                                         \
          adaptr_object_finalizer_t finalizer)                               \
    MACRO(adaptr_object_wrap, SEXP, adaptr_object_t object)                  \
    MACRO(adaptr_object_unwrap, adaptr_object_t, SEXP r_object)              \
    MACRO(adaptr_object_acquire, int, adaptr_object_t object)                \
    MACRO(adaptr_object_release, int, adaptr_object_t object)                \
    MACRO(adaptr_object_get_id, adaptr_id_t, adaptr_object_t object)         \
    MACRO(adaptr_object_has_data, int, adaptr_object_t object)               \
    MACRO(adaptr_object_set_data, void, adaptr_object_t object, SEXP r_data) \
    MACRO(adaptr_object_get_data, SEXP, adaptr_object_t object)              \
    MACRO(adaptr_object_remove_data, void, adaptr_object_t object)           \
    MACRO(adaptr_object_get_reference_count, int, adaptr_object_t object)

#define ADAPTR_OBJECT_R_API_MAP(MACRO)                                \
    MACRO(r_adaptr_get_total_object_count, SEXP)                      \
    MACRO(r_adaptr_get_alive_object_count, SEXP)                      \
    MACRO(r_adaptr_object_get_id, SEXP, SEXP r_object)                \
    MACRO(r_adaptr_object_has_data, SEXP, SEXP r_object)              \
    MACRO(r_adaptr_object_set_data, SEXP, SEXP r_object, SEXP r_data) \
    MACRO(r_adaptr_object_get_data, SEXP, SEXP r_object)              \
    MACRO(r_adaptr_object_remove_data, SEXP, SEXP r_object)           \
    MACRO(r_adaptr_object_get_reference_count, SEXP, SEXP r_object)

#define ADAPTR_OBJECT_API_MAP(MACRO) \
    ADAPTR_OBJECT_C_API_MAP(MACRO)   \
    ADAPTR_OBJECT_R_API_MAP(MACRO)

#define ADAPTR_API_MAP(MACRO)       \
    ADAPTR_UTILITIES_API_MAP(MACRO) \
    ADAPTR_OBJECT_API_MAP(MACRO)

#define ADAPTR_API_DEFINER(FUNCTION, OUTPUT_TYPE, ...) \
    OUTPUT_TYPE (*FUNCTION)(__VA_ARGS__);

#define ADAPTR_DEFINE_API() ADAPTR_API_MAP(ADAPTR_API_DEFINER)

#define ADAPTR_API_INCLUDER(FUNCTION, OUTPUT_TYPE, ...) \
    OUTPUT_TYPE FUNCTION(__VA_ARGS__);

#define ADAPTR_API_DECLARATOR(FUNCTION, OUTPUT_TYPE, ...) \
    extern OUTPUT_TYPE (*FUNCTION)(__VA_ARGS__);

#define ADAPTR_DECLARE_API() ADAPTR_API_MAP(ADAPTR_API_DECLARATOR)

#define ADAPTR_API_INITIALIZER(FUNCTION, OUTPUT_TYPE, ...) \
    FUNCTION =                                             \
        (OUTPUT_TYPE(*)(__VA_ARGS__))(R_GetCCallable("adaptr", #FUNCTION));

#define ADAPTR_INITIALIZE_API() ADAPTR_API_MAP(ADAPTR_API_INITIALIZER)

#define ADAPTR_API_EXPORTER(FUNCTION, OUTPUT_TYPE, ...) \
    R_RegisterCCallable("adaptr", #FUNCTION, (DL_FUNC)(FUNCTION));

#define ADAPTR_EXPORT_API() ADAPTR_API_MAP(ADAPTR_API_EXPORTER)

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ADAPTR_ADAPTR_H */

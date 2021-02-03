#include "type_table.h"
#include "utilities.h"
#include <vector>

struct type_table_entry_t {
    adaptr_object_type_t type;
    SEXP r_class;
};

std::vector<type_table_entry_t> type_table;

adaptr_object_type_t create_type(SEXP r_class) {
    adaptr_object_type_t new_type = (adaptr_object_type_t)(type_table.size());
    adaptr_sexp_acquire(r_class);
    type_table.push_back({new_type, r_class});
    return new_type;
}

void destroy_type(adaptr_object_type_t type) {

    /* NOTE: type cannot be larger than type_table */
    if(type >= type_table.size()) {
        adaptr_log_error("adaptr :: attempt to remove invalid type '%d'", type);
    }

    /* NOTE: don't delete the entry as this will create a mismatch between
       type and vector index. Set type and class to invalid value instead */
    type_table[type].type = -1;
    adaptr_sexp_release(type_table[type].r_class);
    type_table[type].r_class = NULL;
}


SEXP get_class(adaptr_object_type_t type) {
    /* NOTE: type cannot be larger than type_table */
    if(type >= type_table.size()) {
        adaptr_log_error("adaptr :: attempt to get class for invalid type '%d'", type);
    }

    /* NOTE: don't delete the entry as this will create a mismatch between
       type and vector index. Set type and class to invalid value instead */
    return type_table[type].r_class;
}

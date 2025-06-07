#include "core.h"

nlink_result_t polybuild_core_init(void) {
    printf("[CORE] PolyBuild core initialized\n");
    return NLINK_SUCCESS;
}

void polybuild_core_cleanup(void) {
    printf("[CORE] PolyBuild core cleaned up\n");
}

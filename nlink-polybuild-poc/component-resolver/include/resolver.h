#ifndef POLYBUILD_RESOLVER_H
#define POLYBUILD_RESOLVER_H

#include "polybuild_common.h"

// Single-pass priority resolution
typedef struct {
    polybuild_component_t* components;
    uint32_t component_count;
    bool single_pass_mode;
} polybuild_resolver_t;

// Core resolver API
nlink_result_t resolver_initialize(polybuild_resolver_t* resolver);
nlink_result_t resolver_execute_single_pass(polybuild_resolver_t* resolver);
nlink_result_t resolver_validate_cost_threshold(polybuild_resolver_t* resolver);
void resolver_cleanup(polybuild_resolver_t* resolver);

// Sinphasé governance functions
bool resolver_check_acyclic_dependencies(const polybuild_resolver_t* resolver);
double resolver_calculate_cost_function(const polybuild_resolver_t* resolver);
nlink_result_t resolver_isolate_component(polybuild_component_t* component);

#endif // POLYBUILD_RESOLVER_H

#ifndef POLYBUILD_RESOLVER_H
#define POLYBUILD_RESOLVER_H

#include <stdbool.h>

typedef struct polybuild_resolution polybuild_resolution_t;

// Core API functions
void execute_priority_resolution(polybuild_resolution_t* resolutions, int count);
polybuild_resolution_t* select_highest_priority(polybuild_resolution_t* resolutions, int count);
void isolate_component(polybuild_resolution_t* component);
void execute_single_pass(polybuild_resolution_t* component);
void mark_resolved(polybuild_resolution_t* component);

// Sinphasé governance
int validate_cost_threshold(double cost);
void enforce_single_pass_constraint(void);

#endif // POLYBUILD_RESOLVER_H

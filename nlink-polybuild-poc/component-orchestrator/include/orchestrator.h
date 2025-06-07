#ifndef POLYBUILD_ORCHESTRATOR_H
#define POLYBUILD_ORCHESTRATOR_H

#include "polybuild_common.h"
#include "resolver.h"

// NLink orchestration
typedef struct {
    char nlink_path[256];
    char project_root[256];
    bool polybuild_mode;
    polybuild_resolver_t* resolver;
} polybuild_orchestrator_t;

// Core orchestration API
nlink_result_t orchestrator_initialize(polybuild_orchestrator_t* orch, const char* config_path);
nlink_result_t orchestrator_execute_build(polybuild_orchestrator_t* orch);
nlink_result_t orchestrator_coordinate_components(polybuild_orchestrator_t* orch);
void orchestrator_cleanup(polybuild_orchestrator_t* orch);

// PolyBuild-specific functions
nlink_result_t orchestrator_enable_polybuild_mode(polybuild_orchestrator_t* orch);
nlink_result_t orchestrator_link_with_polybuild(polybuild_orchestrator_t* orch, const char* output);

#endif // POLYBUILD_ORCHESTRATOR_H

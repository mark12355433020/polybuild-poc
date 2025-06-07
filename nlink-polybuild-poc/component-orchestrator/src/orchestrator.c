/*
 * PolyBuild Orchestrator Component
 * NLink Integration and Component Coordination
 */
#include "orchestrator.h"
#include <stdlib.h>
#include <string.h>

nlink_result_t orchestrator_initialize(polybuild_orchestrator_t* orch, const char* config_path) {
    if (!orch || !config_path) return NLINK_ERROR_COMPONENT;
    
    // Set default NLink path
    strncpy(orch->nlink_path, "./shared/nlink", sizeof(orch->nlink_path) - 1);
    strncpy(orch->project_root, ".", sizeof(orch->project_root) - 1);
    orch->polybuild_mode = true;
    
    // Initialize resolver component
    orch->resolver = malloc(sizeof(polybuild_resolver_t));
    if (!orch->resolver) return NLINK_ERROR_COMPONENT;
    
    nlink_result_t result = resolver_initialize(orch->resolver);
    if (result != NLINK_SUCCESS) {
        free(orch->resolver);
        return result;
    }
    
    printf("[ORCHESTRATOR] Initialized with NLink integration\n");
    printf("[ORCHESTRATOR] PolyBuild mode: %s\n", orch->polybuild_mode ? "ENABLED" : "DISABLED");
    
    return NLINK_SUCCESS;
}

nlink_result_t orchestrator_execute_build(polybuild_orchestrator_t* orch) {
    if (!orch) return NLINK_ERROR_COMPONENT;
    
    printf("[ORCHESTRATOR] Starting NLink-coordinated build\n");
    
    // Execute resolver in single-pass mode
    nlink_result_t result = resolver_execute_single_pass(orch->resolver);
    if (result != NLINK_SUCCESS) {
        printf("[ORCHESTRATOR] Resolver execution failed\n");
        return result;
    }
    
    // Coordinate component builds
    result = orchestrator_coordinate_components(orch);
    if (result != NLINK_SUCCESS) {
        printf("[ORCHESTRATOR] Component coordination failed\n");
        return result;
    }
    
    printf("[ORCHESTRATOR] Build completed successfully\n");
    return NLINK_SUCCESS;
}

nlink_result_t orchestrator_coordinate_components(polybuild_orchestrator_t* orch) {
    if (!orch) return NLINK_ERROR_COMPONENT;
    
    // Component build coordination
    const char* components[] = {
        "component-resolver",
        "component-core", 
        "component-cli"
    };
    
    for (int i = 0; i < 3; i++) {
        printf("[ORCHESTRATOR] Building component: %s\n", components[i]);
        
        // Execute component Makefile via NLink
        char command[512];
        snprintf(command, sizeof(command), 
                "cd %s && make all", components[i]);
        
        int result = system(command);
        if (result != 0) {
            printf("[ORCHESTRATOR] Component build failed: %s\n", components[i]);
            return NLINK_ERROR_COMPONENT;
        }
    }
    
    return NLINK_SUCCESS;
}

nlink_result_t orchestrator_enable_polybuild_mode(polybuild_orchestrator_t* orch) {
    if (!orch) return NLINK_ERROR_COMPONENT;
    
    orch->polybuild_mode = true;
    printf("[ORCHESTRATOR] PolyBuild mode enabled for -lpolybuild integration\n");
    
    return NLINK_SUCCESS;
}

void orchestrator_cleanup(polybuild_orchestrator_t* orch) {
    if (orch) {
        if (orch->resolver) {
            resolver_cleanup(orch->resolver);
            free(orch->resolver);
        }
    }
}

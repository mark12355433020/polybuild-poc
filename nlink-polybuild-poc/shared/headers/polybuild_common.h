#ifndef POLYBUILD_COMMON_H
#define POLYBUILD_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Sinphasé governance constants
#define POLYBUILD_COST_THRESHOLD 0.5
#define POLYBUILD_MAX_COMPONENTS 64
#define POLYBUILD_VERSION "1.0.0"

// NLink orchestration types
typedef enum {
    NLINK_SUCCESS = 0,
    NLINK_ERROR_CONFIG = 1,
    NLINK_ERROR_COMPONENT = 2,
    NLINK_ERROR_COST_EXCEEDED = 3
} nlink_result_t;

typedef struct {
    char name[64];
    double cost;
    bool isolated;
    uint32_t priority;
} polybuild_component_t;

// Component interface
nlink_result_t polybuild_component_init(const char* config_path);
nlink_result_t polybuild_component_execute(void);
void polybuild_component_cleanup(void);

#endif // POLYBUILD_COMMON_H

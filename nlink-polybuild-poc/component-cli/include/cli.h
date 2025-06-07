#ifndef POLYBUILD_CLI_H
#define POLYBUILD_CLI_H

#include "polybuild_common.h"

// CLI option structure
typedef struct {
    char project_root[256];
    char linker[64];
    char libpath[256];
    bool verbose;
    bool dry_run;
    bool polybuild_mode;
} polybuild_cli_opts_t;

// CLI functions
nlink_result_t cli_parse_arguments(int argc, char* argv[], polybuild_cli_opts_t* opts);
nlink_result_t cli_execute_build(const polybuild_cli_opts_t* opts);
void cli_print_usage(const char* program_name);
void cli_print_version(void);

#endif // POLYBUILD_CLI_H

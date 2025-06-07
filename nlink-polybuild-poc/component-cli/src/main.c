/*
 * PolyBuild CLI - NLink Orchestration Entry Point
 * Support for --linker=nlink and -lpolybuild integration
 */
#include "cli.h"
#include "orchestrator.h"
#include <getopt.h>
#include <string.h>

int main(int argc, char* argv[]) {
    polybuild_cli_opts_t opts = {0};
    
    // Parse command line arguments
    nlink_result_t result = cli_parse_arguments(argc, argv, &opts);
    if (result != NLINK_SUCCESS) {
        cli_print_usage(argv[0]);
        return result;
    }
    
    printf("PolyBuild v%s - NLink Orchestrated Build System\n", POLYBUILD_VERSION);
    printf("Project: %s\n", opts.project_root);
    printf("Linker: %s\n", opts.linker);
    printf("PolyBuild Mode: %s\n", opts.polybuild_mode ? "ENABLED" : "DISABLED");
    
    if (opts.dry_run) {
        printf("[DRY-RUN] Would execute NLink orchestration\n");
        return NLINK_SUCCESS;
    }
    
    // Execute build orchestration
    result = cli_execute_build(&opts);
    if (result == NLINK_SUCCESS) {
        printf("[POLYBUILD] Build completed successfully\n");
    } else {
        printf("[POLYBUILD] Build failed with error code: %d\n", result);
    }
    
    return result;
}

nlink_result_t cli_parse_arguments(int argc, char* argv[], polybuild_cli_opts_t* opts) {
    // Set defaults
    strncpy(opts->project_root, ".", sizeof(opts->project_root) - 1);
    strncpy(opts->linker, "nlink", sizeof(opts->linker) - 1);
    strncpy(opts->libpath, "../artifacts", sizeof(opts->libpath) - 1);
    opts->polybuild_mode = false;
    
    static struct option long_options[] = {
        {"linker", required_argument, 0, 'L'},
        {"libpath", required_argument, 0, 'P'},
        {"project-root", required_argument, 0, 'r'},
        {"verbose", no_argument, 0, 'v'},
        {"dry-run", no_argument, 0, 'n'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'V'},
        {0, 0, 0, 0}
    };
    
    int c;
    while ((c = getopt_long(argc, argv, "L:P:r:l:vnhV", long_options, NULL)) != -1) {
        switch (c) {
            case 'L':
                strncpy(opts->linker, optarg, sizeof(opts->linker) - 1);
                break;
            case 'P':
                strncpy(opts->libpath, optarg, sizeof(opts->libpath) - 1);
                break;
            case 'r':
                strncpy(opts->project_root, optarg, sizeof(opts->project_root) - 1);
                break;
            case 'l':
                if (strcmp(optarg, "polybuild") == 0) {
                    opts->polybuild_mode = true;
                    printf("[CLI] PolyBuild self-orchestration mode enabled\n");
                }
                break;
            case 'v':
                opts->verbose = true;
                break;
            case 'n':
                opts->dry_run = true;
                break;
            case 'h':
                cli_print_usage(argv[0]);
                exit(0);
            case 'V':
                cli_print_version();
                exit(0);
            default:
                return NLINK_ERROR_CONFIG;
        }
    }
    
    return NLINK_SUCCESS;
}

nlink_result_t cli_execute_build(const polybuild_cli_opts_t* opts) {
    // Initialize orchestrator
    polybuild_orchestrator_t orchestrator = {0};
    
    nlink_result_t result = orchestrator_initialize(&orchestrator, "pkg.nlink");
    if (result != NLINK_SUCCESS) {
        printf("[CLI] Failed to initialize orchestrator\n");
        return result;
    }
    
    // Enable PolyBuild mode if requested
    if (opts->polybuild_mode) {
        result = orchestrator_enable_polybuild_mode(&orchestrator);
        if (result != NLINK_SUCCESS) {
            orchestrator_cleanup(&orchestrator);
            return result;
        }
    }
    
    // Execute build
    result = orchestrator_execute_build(&orchestrator);
    
    // Cleanup
    orchestrator_cleanup(&orchestrator);
    
    return result;
}

void cli_print_usage(const char* program_name) {
    printf("Usage: %s [OPTIONS]\n", program_name);
    printf("\nNLink Orchestration Options:\n");
    printf("  --linker=LINKER       Specify linker (default: nlink)\n");
    printf("  --libpath=PATH        Library search path\n");
    printf("  --project-root=PATH   Project root directory\n");
    printf("  -lpolybuild           Enable PolyBuild self-orchestration\n");
    printf("  -v, --verbose         Verbose output\n");
    printf("  -n, --dry-run         Show commands without executing\n");
    printf("  -h, --help            Show this help\n");
    printf("  -V, --version         Show version information\n");
    printf("\nExamples:\n");
    printf("  %s --linker=nlink --project-root=.\n", program_name);
    printf("  %s -lpolybuild --verbose\n", program_name);
}

void cli_print_version(void) {
    printf("PolyBuild %s\n", POLYBUILD_VERSION);
    printf("NLink Orchestration: ENABLED\n");
    printf("Sinphasé Governance: ENABLED\n");
    printf("Compliance: %s\n", "OBINexus-v1.0");
}

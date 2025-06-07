#include <stdio.h>

int main() {
    printf("Cross-Platform PolyBuild Demo\n");
    printf("Platform: ");
    
#ifdef _WIN32
    printf("Windows\n");
#elif __linux__
    printf("Linux\n");
#elif __APPLE__
    printf("macOS\n");
#else
    printf("Unknown\n");
#endif

    return 0;
}

#include <stdio.h>

int main(int argc, char *argv[]) {
    // Check if there are command line arguments
    if (argc < 2) {
        printf("Usage: %s <arguments>\n", argv[0]);
        return 1;
    }

    // Print out the command line arguments
    printf("You entered %d command line argument(s):\n", argc - 1);
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    return 0;
}

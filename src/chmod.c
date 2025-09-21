#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define DEFAULT_MASK 0664

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [mode] [file]\n", argv[0]);
        return 1;
    }

    char *endptr;
    long mode = strtol(argv[1], &endptr, 8);
    if (*endptr != '\0' || mode < 0 || mode > 0777) {
        fprintf(stderr, "Invalid mode: %s\n", argv[1]);
        return 1;
    }

    if (chmod(argv[2], (mode_t)mode) != 0) {
        perror("chmod");
        return 1;
    }

    return 0;
}

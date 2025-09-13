#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: kill [pid] [signal]\n");
        return 1;
    }
    if (kill(strtol(argv[1], NULL, 10), strtol(argv[2], NULL, 10)) != 0) {
        perror("kill");
        return 1;
    }
    return 0;
}
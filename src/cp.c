#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096
#define DEFAULT_MASK 0664

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [source] [destination]\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("fopen source");
        return 1;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (!dst) {
        perror("fopen destination");
        fclose(src);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t n;
    while ((n = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        if (fwrite(buffer, 1, n, dst) != n) {
            perror("fwrite");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    if (ferror(src)) {
        perror("fread");
    }

    fclose(src);
    fclose(dst);

    return 0;
}

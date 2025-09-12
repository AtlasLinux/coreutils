#include <stdio.h>
#include <dirent.h>

int main(int argc, char **argv) {
    const char *path = "."; // default to current directory
    if (argc > 1) path = argv[1]; // optional argument

    DIR *d = opendir(path);
    if (!d) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(d);
    return 0;
}

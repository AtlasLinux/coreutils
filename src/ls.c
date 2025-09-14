#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char **entries = NULL;
size_t count = 0;

void add_entry(const char *entry_name, int is_dir) {
    size_t len = strlen(entry_name) + (is_dir ? 2 : 1); // +1 for '/' if dir, +1 for '\0'
    char *copy = malloc(len);
    if (!copy) {
        perror("malloc");
        exit(1);
    }
    strcpy(copy, entry_name);
    if (is_dir) {
        strcat(copy, "/");
    }

    char **tmp = realloc(entries, sizeof(char*) * (count + 1));
    if (!tmp) {
        perror("realloc");
        exit(1);
    }
    entries = tmp;
    entries[count++] = copy;
}

void out_sorted() {
    for (int i = 32; i < 256; i++) {
        for (size_t b = 0; b < count; b++) {
            if ((unsigned char)entries[b][0] == i) {
                printf("%s\n", entries[b]);
            }
        }
    }
}

int main(int argc, char **argv) {
    const char *path = "."; // default to current directory
    if (argc > 1) path = argv[1];

    DIR *d = opendir(path);
    if (!d) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        // Build full path for stat
        char fullpath[4096];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        int is_dir = 0;
        if (stat(fullpath, &st) == 0 && S_ISDIR(st.st_mode)) {
            is_dir = 1;
        }

        add_entry(entry->d_name, is_dir);
    }

    out_sorted();

    // Free memory
    for (size_t i = 0; i < count; i++) {
        free(entries[i]);
    }
    free(entries);
    closedir(d);
    return 0;
}

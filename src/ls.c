#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

char** entries;
size_t count = 0;

void add_entry(char* entry_name) {
    entries = (char**)realloc(entries, sizeof(char*)*(count+1));
    entries[count] = entry_name;
    count++;
}

void out_sorted() {
    for (int i = 32; i < 256; i++) {
        for (int b = 0; b < count; b++) {
            if (entries[b][0] == i) {
                printf("%s\n", entries[b]);
            }
	}
    }
}

int main(int argc, char **argv) {
    entries = (char**)malloc(sizeof(char*));
    const char *path = "."; // default to current directory
    if (argc > 1) path = argv[1]; // optional argument

    DIR *d = opendir(path);
    if (!d) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        add_entry(entry->d_name);
    }
    out_sorted();

    closedir(d);
    return 0;
}

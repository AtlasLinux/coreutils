#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DEFAULT_MODE 0775

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: mkdir [flags] [file]\n");
    return 1;
  }

  umask(0000);
  int mode = DEFAULT_MODE;

  // No flags for now
  // uint8_t flag = 0b0; // Use an 8-bit flag in order to save on bytes
  size_t curr_index = 1;
  if (argc > 2) {
    while (curr_index < (unsigned)argc && argv[curr_index][0] == '-') {
      if (strcmp(argv[curr_index], "-m") == 0 ||
          strcmp(argv[curr_index], "--mode") == 0) {
        mode = atoi(argv[++curr_index]);
      } else {
        fprintf(stderr, "Error: Invalid flag\n");
        return 1;
      }
      ++curr_index;
    }
  }

  for (; curr_index < (unsigned)argc; ++curr_index) {
    if (mkdir(argv[curr_index], mode) == -1)
      perror("mkdir");
  }

  return 0;
}

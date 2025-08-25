#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define DEFAULT_MASK 0664

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: cat [flags] [file]\n");
    return 1;
  }

  // No flags for now
  // uint8_t flag = 0b0; // Use an 8-bit flag in order to save on bytes
  size_t curr_index = 1;
  if (argc > 2) {
    while (curr_index < (unsigned)argc && argv[curr_index][0] == '-') {
      fprintf(stderr, "Error: Invalid flag\n");
      return 1;
    }
  }

  umask(0000);
  for (; curr_index < (unsigned)argc; ++curr_index) {
    int fdes = creat(argv[curr_index], DEFAULT_MASK);
    if (fdes == -1) {
      perror("creat");
      return 1;
    }
  }
  return 0;
}

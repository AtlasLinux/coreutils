#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_LINE 1
#define IS_SET(flag, index) (flag) & (index)

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: cat [flags] [file]\n");
    return 1;
  }

  // The first byte (LSB) is the number line flag
  // The rest is padding for now
  uint8_t flag = 0b0; // Use an 8-bit flag in order to save on bytes
  size_t curr_index = 1;
  if (argc > 2) {
    while (curr_index < (unsigned)argc && argv[curr_index][0] == '-') {
      if (strcmp(argv[curr_index], "-n") == 0) {
        flag |= 1;
      } else {
        fprintf(stderr, "Error: Invalid flag\n");
        return 1;
      }
      ++curr_index;
    }
  }

  uint16_t row = 1;
  while ((unsigned)argc > curr_index) {
    FILE *file = fopen(argv[curr_index++], "r");

    if (file == NULL) {
      perror("cat: fopen");
      return 1;
    }

    char c;
    if (IS_SET(flag, NUMBER_LINE))
      printf("%*d ", 5, row++);

    while ((c = fgetc(file)) != EOF) {
      putchar(c);
      if (IS_SET(flag, NUMBER_LINE) && c == '\n')
        printf("%*d ", 5, row++);
    }

    putchar('\n');
    fclose(file);
  }
  return 0;
}

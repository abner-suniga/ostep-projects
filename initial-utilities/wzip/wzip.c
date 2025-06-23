#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }

  char last_char = 0;
  int last_char_count = 0;

  for (int f = 1; f < argc; f++) {
    FILE *fp = fopen(argv[f], "r");
    if (fp == NULL) {
      printf("wzip: cannot open file\n");
      exit(1);
    }

    int READ_BUFFER_SIZE = 1024;
    char read_buffer[READ_BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(read_buffer, 1, sizeof(read_buffer) - 1, fp)) >
           0) {
      for (int b = 0; b < bytes_read; b++) {
        if (last_char == 0) {
          // First character
          last_char = read_buffer[b];
          last_char_count = 1;
        } else if (last_char == read_buffer[b]) {
          // Same character, increment count
          last_char_count++;
        } else {
          // Different character, write previous run
          fwrite(&last_char_count, sizeof(int), 1, stdout);
          fwrite(&last_char, sizeof(char), 1, stdout);
          last_char = read_buffer[b];
          last_char_count = 1;
        }
      }
    }

    fclose(fp);
  }

  // Write the final run
  if (last_char_count > 0) {
    fwrite(&last_char_count, sizeof(int), 1, stdout);
    fwrite(&last_char, sizeof(char), 1, stdout);
  }

  return 0;
}

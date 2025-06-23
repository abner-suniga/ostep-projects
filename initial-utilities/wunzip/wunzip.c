#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  }

  for (int f = 1; f < argc; f++) {
    FILE *fp = fopen(argv[f], "r");
    if (fp == NULL) {
      printf("wunzip: cannot open file\n");
      exit(1);
    }

    size_t BUFFER_SIZE = 4096;
    size_t bytes_read;
    char buffer[BUFFER_SIZE];

    int value = 0;
    int byte_position = 0; // 0 to 4
    char ascii = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {

      for (size_t i = 0; i < bytes_read; i++) {

        if (byte_position < 4) {
          value |= (buffer[i] << (byte_position * 8));
          byte_position++;
        } else {
          ascii = buffer[i];

          for (size_t j = 0; j < value; j++) {
            printf("%c", ascii);
          }

          value = 0;
          byte_position = 0;
          ascii = 0;
        }
      }
    }

    fclose(fp);
  }

  return 0;
}

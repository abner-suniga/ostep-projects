#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  for (int i = 0; i < argc - 1; i++) {

    FILE *fp = fopen(argv[i + 1], "r");
    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }

    int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
      printf("%s", buffer);
    }

    fclose(fp);
  }

  return 0;
}

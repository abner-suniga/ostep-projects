#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  char *search_term = argv[1];

  FILE *fp;
  if (argc == 2) {
    fp = stdin;
  } else {
    char *filepath = argv[2];
    fp = fopen(filepath, "r");
  }

  if (fp == NULL) {
    printf("wgrep: cannot open file\n");
    exit(1);
  }

  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1) {
    bool match = false;

    int i = 0;
    while (line[i] != '\0') {

      int j = 0;
      while (search_term[j] != '\0') {
        if (line[i + j] != search_term[j]) {
          break;
        }

        // last letter
        if (search_term[j + 1] == '\0') {
          match = true;
          break;
        }
        j++;
      }

      if (match) {
        break;
      }
      i++;
    }

    if (match) {
      printf("%s", line);
    }
  }

  free(line);
  fclose(fp);

  return 0;
}

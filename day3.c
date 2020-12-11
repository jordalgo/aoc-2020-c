#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int main (int argc, char **argv) {
    char *input = "day3-input.txt";
    FILE *input_file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int numlines = 0;
    int linelen = 0;

    input_file = fopen(input, "r");

    if (input_file == 0) {
        perror("Canot open input file\n");
        exit(-1);
	      return 0;
    }

    while ((read = getline(&line, &len, input_file)) != -1) {
      linelen = strlen(line) - 1;
      ++numlines;
    }

    int inputs[numlines][linelen];

    fseek(input_file, 0, SEEK_SET);

    int index = 0;
    line = NULL;
    len = 0;
    int i;

    while ((read = getline(&line, &len, input_file)) != -1) {
      for (i = 0; i < linelen; i++) {
        if (line[i] == '.') {
          inputs[index][i] = 1;
        } else {
          inputs[index][i] = 2;
        }
      }
      ++index;
    }

    index = 0;

    int x = 0;
    int treeCount = 0;

    for (i = 0; i < numlines - 1; i++) {
      x = x + 3;

      if (x >= linelen) {
        x = x - linelen;
      }

      if (inputs[i + 1][x] == 2) {
        ++treeCount;
      }
    }

    printf("Tree Count: %d\n", treeCount);
    fclose(input_file);

    return 0;
}

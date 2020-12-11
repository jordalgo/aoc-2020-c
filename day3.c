#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int getHitTreeCount(int moveX, int moveY, int lineLen, const int inputs[][lineLen], int inputsLen) {
  int treeCount = 0;
  int i, x = 0;

  for (i = 0; i < inputsLen - 1;) {
    x = x + moveX;

    if (x >= lineLen) {
      x = x - lineLen;
    }

    i = i + moveY;

    if (i >= inputsLen) {
      break;
    }

    if (inputs[i][x] == 2) {
      ++treeCount;
    }
  }

  return treeCount;
}

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

    uint64_t hitTreeCount = getHitTreeCount(3, 1, linelen, inputs, numlines);

    printf("Tree Count:%llu\n", hitTreeCount);

    uint64_t hitTreeCount2 = getHitTreeCount(1, 1, linelen, inputs, numlines);
    uint64_t hitTreeCount3 = getHitTreeCount(5, 1, linelen, inputs, numlines);
    uint64_t hitTreeCount4 = getHitTreeCount(7, 1, linelen, inputs, numlines);
    uint64_t hitTreeCount5 = getHitTreeCount(1, 2, linelen, inputs, numlines);

    uint64_t n = hitTreeCount * hitTreeCount2 * hitTreeCount3 * hitTreeCount4 * hitTreeCount5;

    printf("Tree Count 2: %llu\n", n);

    fclose(input_file);

    return 0;
}

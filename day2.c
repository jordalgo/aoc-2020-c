#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

struct Password
{
  int min;
  int max;
  char letter;
  char pw[50];
};

int main (int argc, char **argv) {
    char *input = "day2-input.txt";
    FILE *input_file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int index = 0;

    struct Password passwords[1001];

    input_file = fopen(input, "r");

    if (input_file == 0) {
        perror("Canot open input file\n");
        exit(-1);
	      return 0;
    }

    char delim[] = "- :";
    char *ptr = NULL;
    int parseIndex = 0;
    while ((read = getline(&line, &len, input_file)) != -1) {
      ptr = strtok(line, delim);
      while(ptr != NULL)
      {
        if (parseIndex == 0) {
          passwords[index].min = atoi(ptr);
        } else if (parseIndex == 1) {
          passwords[index].max = atoi(ptr);
        } else if (parseIndex == 2) {
          passwords[index].letter = *ptr;
        } else if (parseIndex == 3) {
          strcpy(passwords[index].pw, ptr);
        } else {
          break;
        }
        ptr = strtok(NULL, delim);
        ++parseIndex;
      }
      if (index == 999) {
        break;
      }
      ++index;
      parseIndex = 0;

    }
    fclose(input_file);

    int x;
    int validCount = 0;
    for (x=0; x<=index; x++) {
      size_t i = 0;
      int count = 0;
      while (passwords[x].pw[i] != '\0') {
          if (passwords[x].pw[i] == passwords[x].letter) {
            ++count;
          }
          i++;
      }
      if (passwords[x].min <= count && count <= passwords[x].max) {
        ++validCount;
      }
    }

    printf("Valid Count: %d", validCount);

    return 0;
}

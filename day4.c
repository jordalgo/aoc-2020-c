#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


int main (int argc, char **argv) {
    char *input = "day4-input.txt";
    FILE *input_file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    input_file = fopen(input, "r");

    if (input_file == 0) {
        perror("Canot open input file\n");
        exit(-1);
	      return 0;
    }

    const char delim[] = ": ";
    char *ptr = NULL;
    int keys = 0;
    int validCount = 0;

// byr (Birth Year)
// iyr (Issue Year)
// eyr (Expiration Year)
// hgt (Height)
// hcl (Hair Color)
// ecl (Eye Color)
// pid (Passport ID)
// cid (Country ID)

    while ((read = getline(&line, &len, input_file)) != -1) {
      if (line[0] == '\n') {
        if (keys == 7) {
          ++validCount;
        }
        keys = 0;
      } else {
        ptr = strtok(line, delim);
        while(ptr != NULL)
        {
          if (
              !strcmp(ptr, "byr")
              || !strcmp(ptr, "iyr")
              || !strcmp(ptr, "eyr")
              || !strcmp(ptr, "hgt")
              || !strcmp(ptr, "hcl")
              || !strcmp(ptr, "ecl")
              || !strcmp(ptr, "pid")) {
            ++keys;
          }
          ptr = strtok(NULL, delim);
        }
      }
    }

    printf("Valid Count: %d\n", validCount);

    fclose(input_file);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

int get_char_index(char c) {
  switch(c) {
    case 'a' :
      return 0;
    case 'b' :
      return 1;
    case 'c':
      return 2;
    case 'd':
      return 3;
    case 'e':
      return 4;
    case 'f':
      return 5;
    case 'g':
      return 6;
    case 'h':
      return 7;
    case 'i':
      return 8;
    case 'j':
      return 9;
    case 'k':
      return 10;
    case 'l':
      return 11;
    case 'm':
      return 12;
    case 'n':
      return 13;
    case 'o':
      return 14;
    case 'p':
      return 15;
    case 'q':
      return 16;
    case 'r':
      return 17;
    case 's':
      return 18;
    case 't':
      return 19;
    case 'u':
      return 20;
    case 'v':
      return 21;
    case 'w':
      return 22;
    case 'x':
      return 23;
    case 'y':
      return 24;
    case 'z':
      return 25;
    default :
      return 100;
   }
}

int main (int argc, char **argv) {
    char *input = "day6-input.txt";
    FILE *input_file = fopen(input, "r");

    if (input_file == 0) {
        perror("Canot open input file\n");
        exit(-1);
	      return 0;
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int alphabet[26];
    memset(alphabet, 0, sizeof(alphabet));

    int answered_count = 0;

    while ((read = getline(&line, &len, input_file)) != -1) {
      //printf("line %s", line);
      char * t; // first copy the pointer to not change the original
      int size = 0;

      for (t = line; *t != '\0'; t++) {
        int idx = get_char_index(t[0]);
        // printf("char %c and idx %d\n", t[0], idx);
        if (idx != 100) {
          alphabet[idx] = 1;
        }
      }
      if (line[0] == '\n') {
        int x;
        for (x =0; x < 26; x++) {
          if (alphabet[x] == 1) {
            // printf("found at idx %d\n", x);
            ++answered_count;
            alphabet[x] = 0;
          }
        }
        // printf("count %d\n", answered_count);
      }
    }

    int x;
    for (x =0; x < 26; x++) {
      if (alphabet[x] == 1) {
        ++answered_count;
        alphabet[x] = 0;
      }
    }

    printf("Answered Count %d\n", answered_count);

    fseek(input_file, 0, SEEK_SET);
    memset(alphabet, 0, sizeof(alphabet));

    answered_count = 0;
    line = NULL;
    len = 0;
    int people_count = 0;

    while ((read = getline(&line, &len, input_file)) != -1) {
      char * t; // first copy the pointer to not change the original
      int size = 0;

      for (t = line; *t != '\0'; t++) {
        int idx = get_char_index(t[0]);
        // printf("char %c and idx %d\n", t[0], idx);
        if (idx != 100) {
          alphabet[idx] = alphabet[idx] + 1;
        }
      }

      if (line[0] == '\n') {
        // printf("peoplecount %d\n", people_count);
        int x;
        for (x =0; x < 26; x++) {
          if (alphabet[x] == people_count) {
            //printf("found num %d at idx %d\n", people_count, x);
            ++answered_count;
          }
        }
        memset(alphabet, 0, sizeof(alphabet));
        people_count = 0;
      } else {
        ++people_count;
      }
    }

    //printf("people count %d", people_count);

    for (x =0; x < 26; x++) {
      if (alphabet[x] == people_count) {
        ++answered_count;
      }
    }

    printf("Answered Count Next %d", answered_count);

    fclose(input_file);

    return 0;
}

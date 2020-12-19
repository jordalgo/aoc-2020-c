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


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main (int argc, char **argv) {
    char *input = "day5-input.txt";
    FILE *input_file = fopen(input, "r");

    if (input_file == 0) {
        perror("Canot open input file\n");
        exit(-1);
	      return 0;
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int highest_id = 0;

    int ids[2000];
    int count = 0;

    while ((read = getline(&line, &len, input_file)) != -1) {
      //printf("line %s", line);
      char * t; // first copy the pointer to not change the original
      int row_min = 0;
      int row_max = 127;
      int selected_row = 0;
      int row_count = 0;

      int col_min = 0;
      int col_max = 7;
      int selected_col = 0;
      int col_count = 0;

      for (t = line; *t != '\0' && *t != '\n'; t++) {
        //printf("char %c\n", t[0]);
        if (t[0] == 'F') {
          row_max = row_max - (ceil((row_max - row_min) / 2.0));
          if (row_count == 6) {
            selected_row = row_min;
          }
          ++row_count;
        } else if (t[0] == 'B') {
          row_min = row_min + (ceil((row_max - row_min) / 2.0));
          if (row_count == 6) {
            selected_row = row_max;
          }
          ++row_count;
        } else if (t[0] == 'R') {
          col_min = col_min + (ceil((col_max - col_min) / 2.0));
          if (col_count == 2) {
            selected_col = col_max;
          }
          ++col_count;
        } else if (t[0] == 'L') {
          col_max = col_max - (ceil((col_max - col_min) / 2.0));
          if (col_count == 2) {
            selected_col = col_min;
          }
          ++col_count;
        }
      }

      int id = (selected_row * 8) + selected_col;

      if (id > highest_id) {
        highest_id = id;
      }

      ids[count] = id;
       ++count;

      // printf("selected_row %d\n", selected_row);
      // printf("selected_col %d\n", selected_col);
      // printf("row id %d\n", (selected_row * 8) + selected_col);
    }

    qsort(ids, count, sizeof(int), cmpfunc);

    printf("highest id %d", highest_id);

    int min_id = ids[0];

    int n;
    for( n = 0 ; n < count; n++ ) {
      while (min_id != ids[n] && min_id < ids[n]) {
        printf("missing %d\n", min_id);
        ++min_id;
      }
      ++min_id;
    }

    fclose(input_file);

    return 0;
}

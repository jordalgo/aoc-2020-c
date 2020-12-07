#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main (int argc, char **argv) {
    char *input = "day1-input.txt";
    FILE *input_file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int nums[1000];
    int index = 0;

    input_file = fopen(input, "r");

    if (input_file == 0) {
        perror("Canot open input file\n");
        exit(-1);
	return 0;
    }

    while ((read = getline(&line, &len, input_file)) != -1) {
      nums[index] = atoi(line);
      ++index;
    }
   
    fclose(input_file);

    int first, second, x, y;
    bool found = false;

    for (x=0; x<=index; x++) {
       if (found) {
         break;
       }
       first = nums[x];	    
       for (y=0; y<=index; y++) {
         if (y != x) {
	   second = nums[y];
	   if ((first + second) == 2020) {
	      found = true;
	      break;
	   }
	 }
       }
    }

    printf("Answer is: %d", first * second);

    printf("\n");

    return 0;
}

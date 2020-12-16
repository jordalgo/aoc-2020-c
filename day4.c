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

static const char *const re = "^#[0-9a-f]{6}";
static const char *const pid_re = "^[0-9]{9}";

bool checkBirthYear(char * yearstr) {
  int year = atoi(yearstr);
  if (1920 <= year && year <= 2002) {
    return true;
  }
  return false;
}

bool checkIssueYear(char * yearstr) {
  int year = atoi(yearstr);
  if (2010 <= year && year <= 2020) {
    return true;
  }
  return false;
}

bool checkExpYear(char * yearstr) {
  int year = atoi(yearstr);
  if (2020 <= year && year <= 2030) {
    return true;
  }
  return false;
}

bool checkHairColor(regex_t regex, char * haircolor) {
  int status = regexec(&regex, haircolor, (size_t) 0, NULL, 0);
  if (status != 0) {
    return false;
  }
  return true;
}

bool checkPid(regex_t regex, char * pid) {
  int status = regexec(&regex, pid, (size_t) 0, NULL, 0);
  if (status != 0) {
    return false;
  }
  return true;
}

bool checkEyeColor(char * color) {
  if (
      !strcmp(color, "amb")
      || !strcmp(color, "blu")
      || !strcmp(color, "brn")
      || !strcmp(color, "gry")
      || !strcmp(color, "grn")
      || !strcmp(color, "hzl")
      || !strcmp(color, "oth")) {
    return true;
  }
  return false;
}

bool checkHeight(const char * text) {
  char height[50];
  strncpy(height, text, sizeof(height)-1);
  height[sizeof(height)-1] = '\0';
  char *in = strrchr(height, 'i');
  if (in && !strcmp(in, "in")) {
    int i = strcspn(height,"i");
    char metric[i];
    strncpy(metric, height, i);
    int num = atoi(metric);
    if (59 <= num && num <= 76) {
      return true;
    }
    return false;
  }
  char *cm = strrchr(height, 'c');
  if (cm && !strcmp(cm, "cm")) {
    int i = strcspn(height,"c");
    char metric[i];
    strncpy(metric, height, i);
    int num = atoi(metric);
    if (150 <= num && num <= 193) {
      return true;
    }
    return false;
  }
  return false;
}

int main (int argc, char **argv) {
    char *input = "day4-input.txt";
    FILE *input_file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    regex_t regex;
    if (regcomp(&regex, re, REG_NOTBOL)) {
      perror("Cannot compile regex\n");
      exit(-1);
    }

    regex_t pid_regex;
    if (regcomp(&pid_regex, pid_re, REG_NOTBOL)) {
      perror("Cannot compile regex\n");
      exit(-1);
    }

    input_file = fopen(input, "r");

    if (input_file == 0) {
        perror("Canot open input file\n");
        exit(-1);
	      return 0;
    }

    const char delim[] = ": \n";
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

    fseek(input_file, 0, SEEK_SET);
    validCount = 0;
    int keysValid = 0;

    while ((read = getline(&line, &len, input_file)) != -1) {
      //printf("line %s", line);
      if (*line == '\n') {
        if (keysValid == 7) {
         // printf("valid\n");
          ++validCount;
        } else {
          //printf("keys %d\n", keysValid);
        }
        keysValid = 0;
        continue;
      }
      ptr = strtok(line, delim);
      while(ptr != NULL)
      {
        if (!strcmp(ptr, "byr")) {
          ptr = strtok(NULL, delim);
          if (checkBirthYear(ptr)) {
            ++keysValid;
          }
        } else if (!strcmp(ptr, "iyr")) {
          ptr = strtok(NULL, delim);
          if (checkIssueYear(ptr)) {
            ++keysValid;
          }
        } else if (!strcmp(ptr, "eyr")) {
          ptr = strtok(NULL, delim);
          if (checkExpYear(ptr)) {
            ++keysValid;
          }
        } else if (!strcmp(ptr, "hgt")) {
          ptr = strtok(NULL, delim);
          if (checkHeight(ptr)) {
            ++keysValid;
          }
        } else if (!strcmp(ptr, "hcl")) {
          ptr = strtok(NULL, delim);
          if (checkHairColor(regex, ptr)) {
            ++keysValid;
          }
        } else if (!strcmp(ptr, "ecl")) {
          ptr = strtok(NULL, delim);
          if (checkEyeColor(ptr)) {
            ++keysValid;
          }
        } else if (!strcmp(ptr, "pid")) {
          ptr = strtok(NULL, delim);
          if (checkPid(pid_regex, ptr)) {
            ++keysValid;
          }
        }
        ptr = strtok(NULL, delim);
      }
    }

    printf("Valid Count 2: %d\n", validCount);

    fclose(input_file);
    regfree(&regex);

    return 0;
}

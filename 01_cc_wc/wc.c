#include <stdio.h>
#include <string.h>

void print_result(int c, char *file_name) {
  printf("%d\t%s\n", c, file_name);
}

void print_valid_flags() {
  printf("Valid Flags: '-c' '-l' '-w'\n");
}

void print_usage() {
  printf("USAGE:\n");
  printf("\nRun program with 2 additional arguments.\n");
  print_valid_flags();
  printf("Last argument is the file name (can be relative path): ./test.txt ../test.txt\n");
  printf("\n    Example: ./a.out -c test.txt\n");
  
}

void count_chars(char *file_name) {
  long cc = 0;
  FILE *f_reader = fopen(file_name, "r");

  while (fgetc(f_reader) != EOF)
    cc++;

  print_result(cc, file_name);
}

int main(int argc, char **argv) {
  int exit_code = 0;
  if (argc != 3) {
    exit_code = 1;
    print_usage();
  } else {
    char *flag = argv[1];
    char *cchar = "-c";
    char *cline = "-l";
    char *cword = "-w";

    if (strcmp(flag, cchar) == 0) {
      exit_code = 0;
      count_chars(argv[2]);
    }
    else if (strcmp(flag, cline) == 0) {
      exit_code = 0;
      printf("RECEIVED_FLAG = Print Line Counts Flag.\n");
    }
    else if (strcmp(flag, cword) == 0) {
      exit_code = 0;
      printf("RECEIVED_FLAG = Pring Word Counts Flag.\n");
    }
    else {
      exit_code = 1;
      print_valid_flags();
    }
  }
  return exit_code;
}

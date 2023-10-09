#include <stdio.h>
#include <string.h>

#define IN 1    /* Inside a word */
#define OUT 0   /* Outside a word */

void print_result(int c, char *file_name) {
  printf("%d %s\n", c, file_name);
}

void print_valid_flags() {
  printf("\e[1;33mValid Flags: '-c' '-l' '-w'\e[m\n");
}

void print_usage() {
  printf("USAGE:\n");
  printf("\nRun program with 2 additional arguments.\n");
  print_valid_flags();
  printf("Last argument is the file name (can be relative path): ./test.txt ../test.txt\n");
  printf("\n    Example: ./a.out -c test.txt\n");
  printf("    Example: ./a.out test.txt\n");
  
}

void print_error(char *file_name) {
  printf("\e[1;31mError opening file: %s\e[m\n", file_name);
}

int count_bytes(char *file_name) {
  long cb = 0;
  FILE *f_reader = fopen(file_name, "r");

  if (f_reader == NULL) {
    print_error(file_name);
    return 1;
  }
 
  while (fgetc(f_reader) != EOF)
    cb++;

  fclose(f_reader);

  print_result(cb, file_name);

  return 0;
}

int count_lines(char *file_name) {
  long cl = 0;
  char c;
  FILE *f_reader = fopen(file_name, "r");

  if (f_reader == NULL) {
    print_error(file_name);
    return 1;
  }
 
  while ((c = fgetc(f_reader)) != EOF)
    if (c == '\n')
      ++cl;

  fclose(f_reader);
  
  print_result(cl, file_name);

  return 0;
}

int count_words(char *file_name) {
  long cw = 0;
  char c;
  int state = OUT;
  FILE *f_reader = fopen(file_name, "r");

  if (f_reader == NULL) {
    print_error(file_name);
    return 1;
  }
  
  while ((c = fgetc(f_reader)) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      ++cw;
    }
  }

  fclose(f_reader);

  print_result(cw, file_name);

  return 0;
}

int count_chars(char *file_name) {
  long cc = 0;
  char c;
  FILE *f_reader = fopen(file_name, "r");

  if (f_reader == NULL) {
    print_error(file_name);
    return 1;
  }
 
  while ((c = getc(f_reader)) != EOF) {
    // Counting all the UTF-8 Characters
    if ((c & 0xC0) != 0x80)
	++cc;
  }

  fclose(f_reader);

  print_result(cc, file_name);
  
  return 0;
}

int main(int argc, char **argv) {
  int exit_code = 0;
  if (argc < 2 || argc > 3) {
    exit_code = 1;
    print_usage();
    return exit_code;
  } else {
    if (argc == 3) {
      char *flag = argv[1];
      char *cbyte = "-c";
      char *cline = "-l";
      char *cword = "-w";
      char *cchar = "-m";
      
      if (strcmp(flag, cbyte) == 0) {
	exit_code = count_bytes(argv[2]);
      } else if (strcmp(flag, cline) == 0) {
	exit_code = count_lines(argv[2]);
      } else if (strcmp(flag, cword) == 0) {
	exit_code = count_words(argv[2]);
      } else if (strcmp(flag, cchar) == 0) {
	exit_code = count_chars(argv[2]);
      } else {
	exit_code = 1;
	print_valid_flags();
      }
    } else if (argc == 2) {
      if (argv[1][0] == '-' && argv[1][1] != 'c' && argv[1][1] != 'l' && argv[1][1] != 'w') {
	exit_code = 1;
	printf("\e[1;31mInvalid flag = %s\n", argv[1]);
	print_valid_flags();
	return exit_code;
      }
      if (argv[1][0] == '-' && (argv[1][1] == 'c' || argv[1][1] == 'l' || argv[1][1] == 'w')) {
	exit_code = 1;
	printf("\e[1;31mMissing file name.\e[m\n");
	print_usage();
	return exit_code;
      }
      if (argv[1] == NULL) {
	exit_code = 1;
	printf("\e[1;31mEnter a valid file name.\n");
	printf("FILE NAME CANNOT BE = %s\e[m\n", argv[2]);
	return exit_code;
      }
      exit_code = 0;
      long cl, cw, cc, state;
      char c;
      state = OUT;
      cl = cw = cc = 0;
      FILE *f_reader = fopen(argv[1], "r");
      if (f_reader == NULL) {
	printf("Error opening file: %s\n", argv[1]);
	exit_code = 1;
	return exit_code;
      }
      while ((c = fgetc(f_reader)) != EOF) {
	++cc;
	if (c == '\n') {
	  ++cl;
	}
	if (c == ' ' || c ==  '\n' || c == '\t') {
	  state = OUT;
	} else if (state == OUT) {
	  state = IN;
	  ++cw;
	}
      }
      printf("  %ld %ld %ld %s\n", cl, cw, cc, argv[1]);
    }
  } 
  return exit_code;
}

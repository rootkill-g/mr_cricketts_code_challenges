# Word Count

The word count program is a unix command line tool which when passed a file or a stream of characters can count the number of characters in the stream|file.
<br />
The program which we will create will mimic some parts of the wc utility.

### Functionalities

The program will take 2 Arguments `./a.out -c <file_name>` to count characters of file with name identifier as `'file_name'`.
<br />
There are three functionalities as per comparing with wc utility that this program will mimic.

      1. Bytes Count
      2. Line Count
      3. Word Count
      4. Character Count
      5. Genaral wc

The program then will produce the output in the similar format as wc, i.e.:<br />
`<int> <file_name>`

### Build this program

To build this program you need to have gcc installed (or any other local C compiler).
If you have the gcc installed then you can build this program with :<br />
```bash
gcc wc.c -O2 -o ccwc
```

### To run

After building the program as mentioned above, you will now have a binary named `wc` inside your current working directory.<br />
Then to run the program:
```bash
ccwc -c test.txt
```
which will result in an output:
```bash
319234	test.txt
```
Or you can call the function without any flag but just the file name as:
```bash
ccwc test.txt
```
which will output:
```bash
  6853 55723 319234 test.txt
```

### Explaination of the code:

The code on invocation runs the main function and checks if the total number of arguments passed to the program are correct or not (i.e., 3, because the first argument will be the program itself).
If when the passed arguments count equates with the set condition, the program can further proceed to check the value of flag passed and prints the valid flags that the program expects if the so passed flag was an invalid flag.

#### A flag (valid or invalid) was provided

If the program was called with the either `-c` or `-l` or `-w` or `-m` flag along with a valid file name, then the program calls either `count_bytes(file_name)` for `-c` flag, `count_lines(file_name)` for `-l` flag, `count_words(file_name)` for `-w` flag or `count_characters(file_name)` for `-m` flag, function respectively, and which will then initialize a variable to keep the count, let `long counter = 0;`, and then it initializes a character variable called `c` as `char c;` (where it's necessary to check individual character or byte in the file) and then tries to open the file with name `file_name` that was provided as the last argument to the program, and if the file exists then the program proceeds further on checking if the current character is a valid byte (for `-c`), a valid line (for `-l`), a valid word (for `-w`), or a valid UTF-8 character (for `-m`), or not.

In case the flag passed was not valid (lets say `-q`) then the program reports that to the user and exits after printing the valid flags information for the user.

If the file with name `file_name` does not exist thent the program reports so and exitswith code 1. Finally when the program was successfully called with valid file and valid `-m` flag, the program then after looping over the UTF-8 Characters of the file, calls the `print_result(cc, file_name)` function which prints the result, and the function then returns the code 0, which is assigned to the `exit_code` variable in the main function and then the main function returns with that `exit_code`.


#### A flag was not provided

If the program is called without any flags then the program will print the generic result of `wc` program which will be formatted as:
```bash
  <line_count> <word_count> <byte_count> <file_name>
```
which is a result of the following subroutine:
      ```c
      if (argc == 2) {
      	 // Initialize Variables
	 // Initialize State
	 // Open file
	 // Check for Errors
	 // Loop through the bytes of the file
	    // Increment the char count by 1 on all iterations
	    // Check if the current character is a \n (new line character)
	       // If yes then increment the line counter by 1
	    // check if the current character is either a \n, ' ' or a '\t',
	       // If yes then set the state as OUT
	    // Else if the state is already set to OUT
	       // Then set the state as IN
	       // Increment the word count by 1
	 // Print the generic result
      }
      ```

<br />
This concludes the Code Challenge #1 🎉

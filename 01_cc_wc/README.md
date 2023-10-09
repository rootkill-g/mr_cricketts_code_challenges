# Word Count

The word count program is a unix command line tool which when passed a file or a stream of characters can count the number of characters in the stream|file.
<br />
The program which we will create will mimic some parts of the wc utility.

### Functionalities

The program will take 2 Arguments `./a.out -c <file_name>` to count characters of file with name identifier as `'file_name'`.
<br />
There are three functionalities as per comparing with wc utility that this program will mimic.

      1. Character Count
      2. Line Count
      3. Word Count

The program then will produce the output in the similar format as wc, i.e.:<br />
`<int> <file_name>`

## Build this program

To build this program you need to have gcc installed (or any other local C compiler).
If you have the gcc installed then you can build this program with :<br />
```bash
gcc wc.c -O2 -o wc
```

### To run

After building the program as mentioned above, you will now have a binary named `wc` inside your current working directory.<br />
Then to run the program:
```bash
wc -c test.txt
```
which will result in an output:
```bash
319234	test.txt
```

### Explaination of the code:

The code on invocation runs the main function and checks if the total number of arguments passed to the program are correct or not (i.e., 3, because the first argument will be the program itself).
If when the passed arguments count equates with the set condition, the program can further proceed to check the value of flag passed and prints the valid flags that the program expects if the so passed flag was an invalid flag.

If the program was passed the `-c` flag along with a valid file name, then the program takes the file name and opens it, and start counting characters in the file until it finds `EOF` (End Of File), after which the program call the `print_result(c, file_name)` function with count of characters and file name to finally print the result.

At the moment the code does only till this check and prints which flag was passed if the program gets a valid flag (after checking the correct number of arguments passed of course.)

#### WIP
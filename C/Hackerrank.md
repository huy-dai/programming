# Things that I learned from Hackerrank C Practice Challenge

### Scanf:

1. `scanf("%c", &ch);`
    * scans in a single character to the char `ch`.
2. `scanf("%[^\n]%*c", s);`
    * [] is the scanset character, `^\n` stands for taking input as long as a newline isn’t encountered, `%*c` reads the newline character, where `*` indicates that the newline character is discarded
    * Note that this scan will NOT work as expected without first scanning in a newline character with `scanf(“\n”);` because the newline will be “leftover” from the previous line if you are scanning in multiple things.

## Printf

You can specify the rounding of floats in printf with `.*` specifier. Here we round things to 1 decimal place:

`printf("%.1f %.1f",c,d);`

## Numerical Digits

If we want to get a specific digit of a number, we can do so using modular arithmetic and integer division:

~~~c 
int getNthDigit(int num, int n){
    //n specifies the digit we want to get, from 1 (rightmost) and up.
    return (num % (int)pow(10,n)) / (int)pow(10,n-1);
}
~~~

## Char array into int

`strol()` is the function used to convert a char array into a long int. The second parameter *end_ptr is used to dump characters that comes in the string that comes after the integer.

~~~c
char* n_endptr;
char* n_str = readline();
int n = strtol(n_str, &n_endptr, 10);
~~~

## Print each word in char array

For a challenge that had us print out print each word (e.g., separated by a space) on a line from a char array, I had the following solution:

~~~c
    // Assuming that s is properly formatted
    char *curr = s;
    char *ptr = strchr(curr, ' ');
    
    while (ptr != NULL) {
        int r_index = (int)(ptr-curr);
        curr[r_index] = '\0';
        printf("%s\n",curr);
        curr = ptr+1;
        ptr = strchr(curr, ' ');
    }
    printf("%s\n",curr); //Get last part
~~~

## Text Frequency

Another problem asked me to read a line of text and then print out the frequency of each digit in that string:

~~~c
    /*Read input from STDIN. Print output to STDOUT */  
    char line[1000];
    fgets(line,sizeof(line),stdin);

    int freq[10] = {0};
    
    for(int i=0; i < strlen(line); i++){
        char test = line[i];
        if(isdigit(test)) {
            int val = test - '0'; //guaranteed to work by C standards
            //printf("%d",val);
            freq[val] = freq[val] + 1;
        }
    }
    
    for(int i=0; i < 10; i++) {
        printf("%d ",freq[i]);
    }
~~~
## fgets

Here I used the `fgets()` function for a more secure read than `scanf`. I also used an int array to keep track of the frequency (compared to doing it in a hashmap dictionary if we were following the Pythonic way). 

To convert a character to an integer, I used the formula `a_char - '0'` since `atoi` only works for char* array.

### Dynamic Array

In [this](https://www.hackerrank.com/challenges/dynamic-array-in-c/problem?h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen) problem, I learned about 2D arrays in C and also how to use to `realloc` function to dynamically increase the size of a pointer. `realloc` has the syntax of:

`realloc(curr_ptr,new_size)`

It will return a new pointer (which could be the same or different from the `curr_ptr`) that has total size of `new_size`. Realloc will keep all the values of the old pointer up to `new_size`.

### Struct and Member Pointer

We can define a struct like the following:

~~~c
struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;
~~~

When referring to a member of a struct, you can either use the arrow `->` or dot `.` notation, though depending on the standard they might require one or the other.

In this problem, we were asked to sort a list of `triangle` structs by the area from smallest to largest. Instead of implementing quicksort or bubble sort by myself, I found the `qsort` function from stdlib.h that implements the behavior for me.

`void qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));`

You just need to provide a comparison function that compares two entries in the array and determine whether they are smaller, larger, or equal (in this problem we know that the area values are unique).

## Generate all permutations of a given sequence in lexicographic ordering

The problem of [Permutation of Strings](https://www.hackerrank.com/challenges/permutations-of-strings/problem) was difficult in the fact that it requires an algorithm since as the one denoted in Wikipedia ([ref](https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order)) in order to solve it efficiently. I found implementing the algorithm to be a great excercise for working with double pointer arrays `char **`, as we had to learn to compare strings and reverse a section of the array. My solution for it can be found at [perm_of_strings](Sorting/perm_of_strings.c)

### Variadic functions

Variadic functions are those which take in a variable number of arguments. They are defined with an ellipsis as the last function parameter, e.g.,

`int printf(const char* format, ...);`

In the problem I implemented a `sum`, `min`, and `max` functions which takes the first argument as the number of entries to operate on. A guide that I found very helpful to this problem is one from GeeksforGeeks: <https://www.geeksforgeeks.org/variadic-functions-in-c/>

For example, the sum function would look like this:

~~~c
int  sum (int count,...) {
    int tot = 0;
    va_list ptr;
    va_start(ptr, count);
    for(int i=0; i < count; i++) {
        tot += va_arg(ptr, int);
    }
    va_end(ptr);
    return tot;
~~~
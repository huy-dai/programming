#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");

    char *str1 = "One test string";
    char *str2 = "Another test string";

    char **arr = calloc(2,sizeof(char *));
    arr[0] = str1;
    arr[1] = str2;

    printf("Before:\n");
    for(int i=0; i < 2; i++) {
        printf("%s\n",arr[i]);
    }

    char *temp = str1;
    arr[0] = arr[1];
    arr[1] = temp;

    printf("After:\n");
    for(int i=0; i < 2; i++) {
        printf("%s\n",arr[i]);
    }

    return 0;
}
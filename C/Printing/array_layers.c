#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int max(int a, int b){
    if(a>b) return a;
    return b;
}
int min(int a, int b){
    if(a<b) return a;
    return b;
}

int main() 
{
    int n;
    scanf("%d", &n);
  	
    int layers = n;
    int middle = n-1;
    for(int i=0; i<n*2-1; i++) {
        for(int j=0; j<n*2-1; j++) {
            printf("%i ", max(abs(middle-i),abs(middle-j))+1);
        }   
        printf("\n");
    }
    return 0;
}


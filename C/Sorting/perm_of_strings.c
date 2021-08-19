#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    //1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
    int k = n-2; //start from end
    for ( ; k >= 0; ){
        if(strcmp(s[k],s[k+1]) >= 0) {
            k--;
        } else {
            break;
        }
    }
    if(k==-1) return 0;
    //2. Find the largest index l greater than k such that a[k] < a[l].
    int l = n-1;
    while(l >= k+1 && strcmp(s[k],s[l]) >= 0) {
        l--;
    }
    //3. Swap the value of a[k] with that of a[l].
    char *temp = s[k];
    s[k] = s[l];
    s[l] = temp;
    
    //4. Reverse the sequence from a[k + 1] up to and including the final element a[n].
    for(int i = 0; i < (n-k)/2; i++) {
        char *front = s[k+1+i];
        char *back = s[n-i-1];
        s[n-i-1] = front;
        s[k+1+i] = back;
    }
    return 1;

}

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
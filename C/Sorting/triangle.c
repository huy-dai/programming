#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

float calc_area(triangle *tr) {
    float p = (tr->a+tr->b+tr->c) / 2.0; // -> is often equivalent to . notation
    return sqrtf(p*(p-tr->a)*(p-tr->b)*(p-tr->c));
}
    
int triangle_cmp (const void* tr1, const void* tr2) {
    float area1 = calc_area((triangle *)tr1);
    float area2 = calc_area((triangle *)tr2);
    if ((area1 - area2) < 0) {
        return -1;
    }
    return 1; //no equality case
}

void sort_by_area(triangle* tr, int n) {
	/**
	* Sort an array a of the length n
	*/
    return qsort(tr,n,sizeof(triangle),triangle_cmp);
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}

/*
Input:
3
7 24 25
5 12 13
3 4 5

Output:
3 4 5
5 12 13
7 24 25
*/
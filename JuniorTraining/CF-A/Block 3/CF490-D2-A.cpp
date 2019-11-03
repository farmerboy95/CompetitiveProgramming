/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Create 3 arrays to store indexes of students with the same talent, then print out min size of all three arrays
*/

#include <stdio.h>
#include <iostream>

using namespace std;

int d1, d2, d3, a[5555], b[5555], c[5555], res;

int main()
{
    int n, i, k;
    scanf("%d", &n);
    for (i = 1; i<=n; i++) {
        scanf("%d", &k);
        if (k == 1) a[++d1] = i;
        else if (k == 2) b[++d2] = i;
        else c[++d3] = i;
    }
    res = min(d1, min(d2, d3));
    printf("%d\n", res);
    for (i = 1; i<=res; i++) printf("%d %d %d\n", a[i], b[i], c[i]);
    return 0;
}
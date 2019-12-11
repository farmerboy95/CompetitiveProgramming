/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
*/

#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
    long long int n;
    scanf("%I64d", &n);
    if (n % 2 == 0) printf("%I64d", n/2);
    else printf("%I64d", -(n/2)-1);
    return 0;
}
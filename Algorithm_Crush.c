#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

int n, m, a, b, s;

scanf("%d %d", &n, &m);

int *values = calloc(n + 1, sizeof(int));

long long int maxValue = 0;
long long int actual = 0;

for(int i = 0; i < m; i++) {

    scanf("%d %d %d", &a, &b, &s);

    values[a] += s;         
    values[b + 1] -= s;         
}

for(int i = 0; i < n + 1; i++) {    
        actual += values[i];           
        if (actual > maxValue)
            maxValue = actual;             
}

printf("%lli", maxValue);

return 0;
}

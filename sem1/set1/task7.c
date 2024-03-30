#include <stdio.h>
#include <math.h>

int main() {
    int n, m, p, k, l;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &p);
    scanf("%d", &k);
    scanf("%d", &l);

    int q = ceil((double)m / ((p - 1) * l + k));
    int new_s = ceil((double)n / q);
    int new_k = (new_s % l);
    int new_p = 1 + (new_s - new_k) / l;
    
    printf("%d %d", new_p, new_k);
    
    return 0;
}
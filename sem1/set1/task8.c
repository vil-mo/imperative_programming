#include <stdio.h>
#include <math.h>

int main() {
    int h, m, s, k;
    scanf("%d", &h);
    scanf("%d", &m);
    scanf("%d", &s);
    scanf("%d", &k);

    int nh, nm, ns;
    ns = (s + k) % 60;
    nm = (int)(m + floor((s + k) / 60.0)) % 60;
    nh = (int)(h + floor((m + floor((s + k) / 60.0)) / 60.0)) % 24;

    printf("%d %d %d", nh, nm, ns);

    return 0;
}
#include <stdio.h>
#include <stdbool.h>

bool is_rect_inside_rect(int inside_a, int inside_b, int container_a, int container_b) {
    return (inside_a <= container_a && inside_b <= container_b) || (inside_a <= container_b && inside_b <= container_a);
}

void main() {
    int a1, b1, a2, b2, a3, b3;
    scanf("%d %d %d %d %d %d", &a1, &b1, &a2, &b2, &a3, &b3);

    if (is_rect_inside_rect(a2, b2, a1, b1)) {
        if (a2 > a1 || b2 > b1) {
            a2 = a2 + b2;
            b2 = a2 - b2;
            a2 = a2 - b2;
        }

        int new1_a = a2;
        int new1_b = b1 - b2;
        int new2_a = a1 - a2;
        int new2_b = b1;
        int new3_a = a1 - a2;
        int new3_b = b2;
        int new4_a = a1;
        int new4_b = b1 - b2;

        if (
            is_rect_inside_rect(a3, b3, new1_a, new1_b) || 
            is_rect_inside_rect(a3, b3, new2_a, new2_b) ||
            is_rect_inside_rect(a3, b3, new3_a, new3_b) ||
            is_rect_inside_rect(a3, b3, new4_a, new4_b)
        ) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

    } else {
        printf("NO\n");
    }
    
}
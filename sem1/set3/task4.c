#include <stdio.h>

void main() {
    int n;
    scanf("%d", &n);


    int current_sum;
    scanf("%d", &current_sum);
    int max_sum = current_sum;

    int l = 0;
    int r = 0;
    int current_l = 0;
    int amount_of_zeroes = 0;
    int zeroes_ended = 0;


    if (current_sum < 0) {
        current_sum = 0;
        current_l = 1;
    } else if (current_sum > 0) {
        zeroes_ended = 1;
    }

    for (int i = 1; i<n; i++) {
        int num;
        scanf("%d", &num);
        current_sum += num;

        if (num < 0) {
            if (current_sum >= 0 && (current_sum - num) > max_sum && zeroes_ended) {
                l = current_l;
                r = i - 1 - amount_of_zeroes;
                max_sum = current_sum - num;
            } else if (current_sum < 0 && current_sum > max_sum) {
                l = i;
                r = i;
                max_sum = current_sum; 
            }
            
            current_sum = 0;
            current_l = i + 1;
            amount_of_zeroes = 0;
        } else if (num == 0) {
            if (zeroes_ended) {
                amount_of_zeroes++;
            } else {
                current_l = i + 1;
                if (max_sum < 0) {
                    l = i;
                    r = i;
                    max_sum = 0;
                }
            }
        } else {
            amount_of_zeroes = 0;
            zeroes_ended = 1;
        }
    }
    if (current_sum > max_sum && current_sum > 0) {
        l = current_l;
        r = n - 1 - amount_of_zeroes;
        max_sum = current_sum;
    }

    printf("%d %d %d\n", l, r, max_sum);

}
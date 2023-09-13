#include <stdio.h>
#include <math.h>

void main() {
    int n;
    scanf("%d", &n);
    
    char trash;
    scanf("%c", &trash);

    int bytes_amount = ceil(n / 8.0);
    int byte_size = 256;



    for (int i = 1; i <= bytes_amount; i++) {
        if (i == bytes_amount) {
            byte_size = 2^(n % 8);
            if (byte_size == 1) {
                byte_size = 256;
            }
        }

        int current_number = 0;
        for (int j=1; j < byte_size; j *= 2) {
            char current_bit;
            scanf("%c", &current_bit);
            int int_current_bit;
            sscanf(&current_bit, "%d", &int_current_bit);

            current_number += int_current_bit * j;
        }
        printf("%d", current_number);
    }

}
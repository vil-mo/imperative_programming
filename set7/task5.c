#include <stdio.h>


int binarySearch(int *distance, int * arr, int len, int num) {
    int left = 0;
    int right = len;
    
    while (1) {
        int curr = (left + right) / 2;
        if (arr[curr] == num) {
            *distance = 0;
            return curr;
        }

        if (curr == left) {
            if ( (right == len) || (num - arr[left] < arr[right] - num) ) {
                *distance = num - arr[left];
                return left;
            } else {
                *distance = arr[right] - num;
                return right;
            }
        }

        if (arr[curr] < num) {
            left = curr;
        } else {
            right = curr;
        }
    }
}

int main() {
    int n, q;
    scanf("%d", &n);
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);

        int dist;
        int indx = binarySearch(&dist, arr, n ,x);
        
        printf("%d %d\n", indx, abs(dist));
    }



    return 0;
}

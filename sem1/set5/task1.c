#include <stdio.h>

typedef struct DateTime_s {
    int year, month, day;
    int hours, minutes, seconds;
} DateTime ;

DateTime min (const DateTime * arr , int cnt) {
    DateTime minimal = *arr;

    for (int i=1; i<cnt; i++) {
        DateTime current = *(arr + i);

        if (current.year < minimal.year) {
            minimal = current;

        } else if (current.year == minimal.year) {
            if (current.month < minimal.month) {
                minimal = current;

            } else if (current.month == minimal.month) {
                if (current.day < minimal.day) {
                    minimal = current;
                
                } else if (current.day == minimal.day) {
                    if (current.hours < minimal.hours) {
                        minimal = current;

                    } else if (current.hours == minimal.hours) {
                        if (current.minutes < minimal.minutes) {
                            minimal = current;

                        } else if (current.minutes == minimal.minutes && current.seconds < minimal.seconds) {
                            minimal = current;
                        }
                    }   
                }   
            }   
        }
    }

    return minimal;
}

int main() {
    int n;
    scanf("%d", &n);

    DateTime arr[n];

    for (int i=0; i<n; i++) {
        scanf("%d %d %d %d %d %d", &arr[i].year, &arr[i].month, &arr[i].day, &arr[i].hours, &arr[i].minutes, &arr[i].seconds);
    }

    DateTime minimal = min(arr, n);

    printf("%d %d %d %d %d %d\n", minimal.year, minimal.month, minimal.day, minimal.hours, minimal.minutes, minimal.seconds);

    return 0;
}
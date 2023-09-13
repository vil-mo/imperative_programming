#include <stdio.h>
#include <memory.h>

int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int days_since_start_of_the_year[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};



int date_to_int(int date[3]) {
    int res = date[2] * 365;
    res += date[2] / 400;
    res -= date[2] / 100;
    res += date[2] / 4;
    
    int is_leap_year = (date[2] % 400 == 0) || (date[2] % 4 == 0 && date[2] % 100 != 0);

    res += days_since_start_of_the_year[date[1] - 1];
    res += date[0];

    return res;
}

int* int_to_date(int num) {
    int date[3] = {0, 0, 0};
2
    date[2] = num / 365;
    int days_since_start_of_the_current_year = num % 365;
    int month = 0;
    while (days_since_start_of_the_year[month] < days_since_start_of_the_current_year) {
        month++;
    }
    date[1] = month;

    date[0] = days_since_start_of_the_current_year % days_since_start_of_the_year[month - 1];


    return date[2], date[1], date[0];
}

void main() {
    int date[3], k;
    scanf("%d %d %d %d", &date[0], &date[1], &date[2], &k);


    int this_date_to_int = date_to_int(date);

    int new_date[3]; memcpy(int_to_date(this_date_to_int), new_date, 3);

    printf("%d %d %d\n", new_date[0], new_date[1], new_date[3]);

}

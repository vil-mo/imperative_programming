#include <stdio.h>
#include <string.h>

int main() {
    char day[3];
    scanf("%s", day);
    

    if (strcmp(day, "Mon") == 0) {
        printf("1\n");
    } else if (strcmp(day, "Tue") == 0) {
        printf("2\n");
    } else if (strcmp(day, "Wed") == 0) {
        printf("3\n");
    } else if (strcmp(day, "Thu") == 0) {
        printf("4\n");
    } else if (strcmp(day, "Fri") == 0) {
        printf("5\n");
    } else if (strcmp(day, "Sat") == 0) {
        printf("6\n");
    } else if (strcmp(day, "Sun") == 0) {
        printf("7\n");
    }

    return 0;
}
#include <stdio.h>

typedef struct Label_s {
    char name[16];
    int age;
} Label;

typedef struct NameStats_s {
    int cntTotal;
    int cntLong;
} NameStats;

typedef struct AgeStats_s {
    int cntTotal;
    int cntAdults;
    int cntKids;
} AgeStats;

void calcStats (const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges) {
    oNames->cntLong = 0;
    oNames->cntTotal = 0;
    oAges->cntAdults = 0;
    oAges->cntKids = 0;
    oAges->cntTotal = 0;

    for (int i = 0; i < cnt; i++) {
        (oNames->cntTotal)++;
        (oAges->cntTotal)++;

        if (arr[i].age >= 18) {
            (oAges->cntAdults)++;
        } else if (arr[i].age < 14) {
            (oAges->cntKids)++;
        }

        for (int j = 0; j <= 10; j++) {
            if (arr[i].name[j] == '\0') {
                break;
            }
            if (j == 10) {
                (oNames->cntLong)++;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Label arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d let", arr[i].name, &arr[i].age);
    }

    NameStats name_stats;
    AgeStats age_stats;

    calcStats(arr, n, &name_stats, &age_stats);

    printf("names: total = %d\n", name_stats.cntTotal);
    printf("names: long = %d\n", name_stats.cntLong);
    printf("ages: total = %d\n", age_stats.cntTotal);
    printf("ages: adult = %d\n", age_stats.cntAdults);
    printf("ages: kid = %d\n", age_stats.cntKids);


    return 0;
}
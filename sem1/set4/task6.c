#include <stdio.h>

int readTime ( char * iStr , int * oHours , int * oMinutes , int * oSeconds ) {
    char symb = *iStr;
    int i = 0;

    *oHours = 0;
    if (oMinutes != NULL) {
        *oMinutes = 0;
    }
    if (oSeconds != NULL) {
        *oSeconds = 0;
    }

    int* currently_scanning = oHours;

    int return_code = 1;

    int oMinutesSecondsIfNull;

    while (symb != '\0') {
        int failed = 0;

        if (symb == ':') {
            if (currently_scanning == oHours && oMinutes != NULL) {
                currently_scanning = oMinutes;
            } else if (currently_scanning == oMinutes && oSeconds != NULL) {
                currently_scanning = oSeconds;
            } else {
                currently_scanning = &oMinutesSecondsIfNull;
                oMinutesSecondsIfNull = 0;
            }
        } else if ('0' <= symb && symb <= '9') {
            *currently_scanning *= 10;
            *currently_scanning += symb - '0';

            if ((currently_scanning == oHours && *currently_scanning >= 24) || (*currently_scanning >= 60)){
                failed = 1;
            }
        } else {
            failed = 1;
        }



        if (failed) {
            return_code = 0;

            *oHours = -1;
            if (oMinutes != NULL) {
                *oMinutes = -1;
            }
            if (oSeconds != NULL) {
                *oSeconds = -1;
            }
            break;
        }



        i++;
        symb = *(iStr + i);
    }

    return return_code;
}

int main() {

    char str[16];
    gets(str);

    int h, m, s;
    int code = readTime(str, &h, &m, &s);
    printf("%d %d %d %d\n", code, h, m, s);
    code = readTime(str, &h, &m, NULL);
    printf("%d %d %d\n", code, h, m);
    code = readTime(str, &h, NULL, NULL);
    printf("%d %d\n", code, h);
    

    return 0;
}
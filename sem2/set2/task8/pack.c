#include "pack.h"
#include <stdarg.h>
#include <string.h>


int pack(char *buffer, const char *format, ...) {
    int argc = 0;

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            argc++;
        }
    }

    va_list args;
    va_start(args, argc);

    int all_size = 0;

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            int size = 0;

            if (memcmp("%d", &format[i], 2) == 0) {
                int v = va_arg(args, int);
                size = sizeof(v);

                if (buffer != NULL) {
                    memcpy(&buffer[all_size], &v, size);
                }
            } else if (memcmp("%s", &format[i], 2) == 0) {
                char *v = va_arg(args, char *);

                for (; v[size] != '\0'; size++) {}
                size++;

                if (buffer != NULL) {
                    memcpy(&buffer[all_size], v, size);
                }
            } else if (memcmp("%lf", &format[i], 3) == 0) {
                double v = va_arg(args, double);
                size = sizeof(v);

                if (buffer != NULL) {
                    memcpy(&buffer[all_size], &v, size);
                }
            }

            all_size += size;
        }
    }

    va_end(args);

    return all_size;
}

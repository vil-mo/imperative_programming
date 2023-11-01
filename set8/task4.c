#include <stdio.h>
#include <inttypes.h>

int parseString(FILE *in, FILE *out)
{
    fprintf(out, "\"");

    char curr;
    fread(&curr, 1, 1, in);

    int lenght = 1;

    while (curr != '\0')
    {
        fprintf(out, "%c", curr);

        fread(&curr, 1, 1, in);

        lenght++;
    }
    fprintf(out, "\"");

    return lenght;
}

int main()
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "w");

    int32_t lenght;
    fread(&lenght, 4, 1, in);

    fprintf(out, "{\n");
    for (int curr = 4; curr < lenght - 1; curr++)
    {
        fprintf(out, "\t");

        int8_t type;
        fread(&type, 1, 1, in);
        curr += parseString(in, out);
        fprintf(out, ": ");

        switch (type)
        {
        case 1:
        {
            // double
            double val;
            fread(&val, 8, 1, in);
            curr += 8;
            fprintf(out, "%0.15g", val);
        }
        break;

        case 2:
        {
            // string
            int32_t len;
            fread(&len, 4, 1, in);
            curr += 4 + parseString(in, out);
        }
        break;

        case 8:
        {
            // bool
            int8_t val;
            fread(&val, 1, 1, in);
            curr += 1;
            if (val == 0)
            {
                fprintf(out, "false");
            }
            else
            {
                fprintf(out, "true");
            }
        }
        break;

        case 10:
        {
            // null
            fprintf(out, "null");
        }
        break;

        case 16:
        {
            // int32
            int32_t val;
            fread(&val, 4, 1, in);
            curr += 4;
            fprintf(out, "%d", val);
        }
        break;

        case 18:
        {
            // int64
            int64_t val;
            fread(&val, 8, 1, in);
            curr += 8;
            fprintf(out, "%ld", val);
        }
        break;

        default:
            break;
        }

        if (curr < lenght - 2)
        {
            fprintf(out, ",");
        }
        fprintf(out, "\n");
    }
    fprintf(out, "}");

    fclose(in);
    fclose(out);

    return 0;
}
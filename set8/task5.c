#include <stdio.h>
#include <inttypes.h>

int main()
{
    FILE *in = fopen("1.in", "rb");
    FILE *out = fopen("output.txt", "wb");

    int32_t n;
    fread(&n, 4, 1, in);

    int32_t l[n];
    int64_t val[n];
    for (int i = 0; i < n; i++)
    {
        fread(&l[i], 4, 1, in);

        for (int j = 0; j < l[i]; j++)
        {
            int8_t v;
            fread(&v, 1, 1, in);
            val[i] |= v << j;
        }
    }

    int8_t arr[8000000];
    int32_t arr_ind, arr_byte;

    int32_t m;
    fread(&m, 4, 1, in);

    for (int i = 0; i < m; i++)
    {
        int16_t symb;
        fread(&symb, 2, 1, in);

        int64_t symb_val = val[symb];
        for (int j = 0; j < l[symb]; j += 8)
        {
            arr[arr_ind] |= symb_val & 1;

            symb_val = symb_val << 1;
            arr[arr_ind] = arr[arr_ind] << 1;

            arr_byte++;
            if (arr_byte >= 7)
            {
                arr_byte = 0;
                arr_ind++;
            }
        }
    }

    for (int i = 0; i < arr_ind; i++)
    {
        fwrite(&arr[i], 1, 1, out);
    }
    if (arr[arr_ind] != 0) {
        fwrite(&arr[arr_ind], 1, 1, out);
    }

    fclose(in);
    fclose(out);

    return 0;
}
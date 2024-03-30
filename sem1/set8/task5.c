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
        val[i] = 0;

        for (int j = 0; j < l[i]; j++)
        {
            int8_t v;
            fread(&v, 1, 1, in);
            val[i] |= v << j;
        }
    }

    int8_t arr[8000000];
    int32_t arr_ind = 0, arr_byte = 0;
    arr[arr_ind] = 0;

    int32_t m;
    fread(&m, 4, 1, in);

    for (int i = 0; i < m; i++)
    {
        int16_t symb;
        fread(&symb, 2, 1, in);

        int64_t symb_val = val[symb];
        for (int j = 0; j < l[symb]; j++)
        {
            arr[arr_ind] = (arr[arr_ind] >> 1) & 0b01111111;
            
            arr[arr_ind] |= (symb_val & 1) << 7;;
        
            symb_val = symb_val >> 1;

            arr_byte++;
            if (arr_byte >= 8)
            {
                arr_byte = 0;
                arr_ind++;
                arr[arr_ind] = 0;
            }
        }
    }

    fwrite(arr, 1, arr_ind, out);
    
    if (arr[arr_ind] != 0) {
        int8_t b0, b1, b2, b3, b4, b5, b6, b7;

        b0 = (arr[arr_ind] & 0b00000001) << 7;
        b1 = (arr[arr_ind] & 0b00000010) << 6;
        b2 = (arr[arr_ind] & 0b00000100) << 5;
        b3 = (arr[arr_ind] & 0b00001000) << 4;
        b4 = (arr[arr_ind] & 0b00010000) >> 4;
        b5 = (arr[arr_ind] & 0b00100000) >> 5;
        b6 = (arr[arr_ind] & 0b01000000) >> 6;
        b7 = (arr[arr_ind] & 0b10000000) >> 7;

        arr[arr_ind] = b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;

        fwrite(&arr[arr_ind], 1, 1, out);
    }

    fclose(in);
    fclose(out);

    return 0;
}
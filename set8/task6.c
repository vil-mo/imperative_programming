#include <stdio.h>
#include <inttypes.h>

int main()
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int32_t symb_code = 0;
    int8_t bytes_in_symb_left = 0;
    int8_t symb_size;

    while (1)
    {
        int8_t byte;
        fread(&byte, 1, 1, in);
        if (feof(in))
        {
            goto exit;
        }

        if (bytes_in_symb_left == 0)
        {

            if ((byte & 0b10000000) == 0b00000000)
            {
                symb_code = byte & 0b01111111;
                symb_size = 1;
            }
            else
            {
                if ((byte & 0b11100000) == 0b11000000)
                {
                    symb_code = byte & 0b00011111;
                    bytes_in_symb_left = 1;
                    symb_size = 2;
                }
                else if ((byte & 0b11110000) == 0b11100000)
                {
                    symb_code = byte & 0b00001111;
                    bytes_in_symb_left = 2;
                    symb_size = 3;
                }
                else if ((byte & 0b11111000) == 0b11110000)
                {
                    symb_code = byte & 0b00000111;
                    bytes_in_symb_left = 3;
                    symb_size = 4;
                }
                else
                {
                    goto exit;
                }
            }
        }
        else
        {
            if (!((byte & 0b11000000) == 0b10000000))
            {
                goto exit;
            }

            symb_code = symb_code << 6;
            symb_code = symb_code | (byte & 0b00111111);

            bytes_in_symb_left--;
        }

        if (bytes_in_symb_left == 0)
        {
            if (
                (symb_size == 2 && symb_code <= 0x7f)
                || (symb_size == 3 && symb_code <= 0x7ff)
                || (symb_size == 4 && symb_code <= 0xffff)
                || (symb_code > 0x10ffff) 
                || (0xd800 <= symb_code && symb_code <= 0xdfff)
            )
            {
                symb_code = 0xfffd;
            }

            fwrite(&symb_code, sizeof(int32_t), 1, out);
        }
    }

exit:
    fclose(in);
    fclose(out);

    return 0;
}

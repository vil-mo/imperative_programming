#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct File
{
    char text[21];
    uint64_t size;
    uint8_t isDirectory;

    uint64_t creationMoment;
    uint64_t changeMoment;

    uint8_t hidden;
} File;

void readFile(File *file, FILE *in)
{
    fread(&file->text, 1, 21, in);
    fread(&file->size, 8, 1, in);
    fread(&file->isDirectory, 1, 1, in);

    fread(&file->creationMoment, 8, 1, in);
    fread(&file->changeMoment, 8, 1, in);

    fread(&file->hidden, 1, 1, in);
}

void writeFile(File *file, FILE *out)
{
    fwrite(&file->text, 1, 21, out);
    fwrite(&file->size, 8, 1, out);
    fwrite(&file->isDirectory, 1, 1, out);

    fwrite(&file->creationMoment, 8, 1, out);
    fwrite(&file->changeMoment, 8, 1, out);

    fwrite(&file->hidden, 1, 1, out);
}

int filesSort(File *f1, File *f2)
{
    int num = 0;
    for (int i = 0; i < 21 && num == 0; i++)
    {
        num = f1->text[i] - f2->text[i];
    }

    return num;
}


int main()
{

    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    
    uint32_t n;
    fread(&n, 4, 1, in);

    uint64_t createdLaterThen, modifiedEarlierThen;
    fread(&createdLaterThen, 8, 1, in);
    fread(&modifiedEarlierThen, 8, 1, in);

    int l = 0;
    File filteredFiles[n];
    for (int i = 0; i < n; i++)
    {
        File f;
        readFile(&f, in);

        if (!f.isDirectory && !f.hidden && (f.creationMoment >= createdLaterThen) && (f.changeMoment <= modifiedEarlierThen))
        {
            filteredFiles[l] = f;
            l++;
        }
    }


    qsort(filteredFiles, l, sizeof(File), filesSort);

    for (int i = 0; i < l; i++)
    {
        writeFile(&filteredFiles[i], out);
    }

    fclose(in);
    fclose(out);

    return 0;
}
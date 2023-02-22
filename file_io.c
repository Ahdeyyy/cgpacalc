#include "semester.h"
#include <stdio.h>

int write_semester_to_file(char *file_path, semester s)
{
    FILE *pFile;
    pFile = fopen(file_path, "ab");
    semester buf = copy_semester(s);
    if (pFile == NULL)
    {
        return -1;
    }

    fwrite(&buf, sizeof(semester), 1, pFile);

    fclose(pFile);

    return 0;
}

semester read_semester_from_file(char *file_path, int index)
{
    FILE *pFile;
    pFile = fopen(file_path, "rb");
    index--;
    semester buf;
    if (pFile == NULL)
    {
        buf = new_semester(empty_l, empty_s);
        return buf;
    }

    if (fseek(pFile, index * sizeof(semester), SEEK_SET) != 0)
    {
        buf = new_semester(empty_l, empty_s);
        return buf;
    }
    fread(&buf, 1, sizeof(semester), pFile);
    if (feof(pFile))
    {
        buf = new_semester(empty_l, empty_s);
        return buf;
    }
    return buf;
}
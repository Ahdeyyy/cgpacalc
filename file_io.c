#include "semester.h"
#include <stdio.h>
#include <stdlib.h>

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

    if (index > semester_count_in_file(file_path))
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

int edit_semester_in_file(char *file_path, semester s, int index)
{
    FILE *pFile;
    pFile = fopen(file_path, "rb");
    index--;
    int i = semester_count_in_file(file_path); // the index to use for the loop
    semester *list = malloc(sizeof(semester) * i);
    if (pFile == NULL)
    {
        return -1;
    }
    fread(list, 1, sizeof(semester) * i, pFile);

    list[index] = s;

    fclose(pFile); // closing after reading its content

    pFile = fopen(file_path, "wb");
    if (pFile == NULL)
    {
        return -1;
    }
    for (size_t j = 0; j < i; j++)
    {
        fwrite(list, sizeof(semester), 1, pFile);
        list++;
    }
    fclose(pFile);
    return 0;
}

int semester_count_in_file(char *file_path)
{

    FILE *pFile;
    pFile = fopen(file_path, "rb");
    semester x;
    int i = 0; // the index to use for the loop
    if (pFile == NULL)
    {
        return -1;
    }

    // read all the data in the file
    while (!feof(pFile))
    {
        fseek(pFile, i * sizeof(semester), SEEK_SET);
        fread(&x, 1, sizeof(semester), pFile);
        if (!feof(pFile))
        {
            i++;
        }
    }
    fclose(pFile); // closing after reading its content
    return i;
}
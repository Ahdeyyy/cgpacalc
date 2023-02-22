#include "semester.h"
#include <stdio.h>

int write_semester_to_file(char *file_path, semester s)
{
    FILE *pFile;
    semester buf = s;
    if (pFile = (fopen(file_path, "ab") == NULL))
    {
        return -1;
    }

    print_semester(buf);
    fwrite(&buf, 1, sizeof(semester), pFile);

    fclose(pFile);

    return 0;
}
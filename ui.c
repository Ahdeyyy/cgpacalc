#include <stdio.h>
#include "semester.h"
#include <stdlib.h>

void display_home_menu()
{
    int control = 0;

    char *file_path = "./results.bin";

    while (control != -1)
    {
        printf("\e[1;1H\e[2J");
        printf("\n");
        printf("-----------------------------------------------------\n");
        printf("|                 CGPA CALCULATOR                   |\n");
        printf("-----------------------------------------------------\n");
        printf("| 1 | View results                                  |\n");
        printf("-----------------------------------------------------\n");
        printf("| 2 | Add result                                    |\n");
        printf("-----------------------------------------------------\n");
        printf("| 3 | Add course                                    |\n");
        printf("-----------------------------------------------------\n");
        printf("| 4 | Delete course                                 |\n");
        printf("-----------------------------------------------------\n");
        printf("|-1 | Quit program                                  |\n");
        printf("-----------------------------------------------------\n");
        scanf_s("%d", &control);

        printf("\e[1;1H\e[2J");
        switch (control)
        {
        case -1:
            break;
        case 1:
            view_result_menu(file_path);
            break;

        default:
            break;
        }
    }
}

void view_result_menu(char *file_path)
{
    int i = semester_count_in_file(file_path);
    semester s;

    for (; i > 0; i--)
    {
        s = read_semester_from_file(file_path, i);
        print_semester(s);
    }
    system("pause");
}
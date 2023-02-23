#include "semester.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void display_home_menu()
{
    int control = 0;

    char *file_path = "./results.bin";

    while (control != -1)
    {
        // printf("\e[1;1H\e[2J");
        system("clear");
        printf("\n");
        printf("-----------------------------------------------------\n");
        printf("|                 CGPA CALCULATOR                   |\n");
        printf("-----------------------------------------------------\n");
        printf("| 1 | View results                                  |\n");
        printf("-----------------------------------------------------\n");
        printf("| 2 | Add result                                    |\n");
        printf("-----------------------------------------------------\n");
        printf("| 3 | Edit result                                   |\n");
        printf("-----------------------------------------------------\n");
        printf("| 4 | Delete result                                 |\n");
        printf("-----------------------------------------------------\n");
        printf("|-1 | Quit                                          |\n");
        printf("-----------------------------------------------------\n");
        scanf_s("%d", &control);

        // printf("\e[1;1H\e[2J");
        system("clear");
        switch (control)
        {
        case -1:
            break;
        case 1:
            view_result_menu(file_path);
            break;
        case 2:
            add_result_menu(file_path);
            break;
        case 3:
            edit_result_menu(file_path);
            break;
        case 4:
            delete_result_menu(file_path);
            break;
        default:
            break;
        }
    }
}

void view_result_menu(char *file_path)
{
    int i = semester_count_in_file(file_path);
    float gpa_acc = 0.0;
    float cgpa = 0.0;
    semester s;

    for (int j = 1; j <= i; j++)
    {
        printf("-----------------------------------------------------\n");
        printf("|                         %d                         |\n", j);
        s = read_semester_from_file(file_path, j);
        if (s.total_units != 0)
        {
            gpa_acc += (s.total_points / s.total_units);
        }
        print_semester(s);
    }
    if (gpa_acc > 0)
    {
        cgpa = gpa_acc / i;
    }
    printf("-----------------------------------------------------\n");
    printf("|                   CGPA: %.2f                      |\n", cgpa);
    printf("-----------------------------------------------------\n");
    system("pause");
}

void add_result_menu(char *file_path)
{
    int control = 0;
    while (control != -1)
    {
        printf("-----------------------------------------------------\n");
        printf("|                     ADD RESULT                    |\n");
        printf("-----------------------------------------------------\n");
        printf("| 1 | Add course to semester                        |\n");
        printf("-----------------------------------------------------\n");
        printf("| 2 | Add new semester                              |\n");
        printf("-----------------------------------------------------\n");
        printf("|-1 | Go Back                                       |\n");
        printf("-----------------------------------------------------\n");
        scanf_s("%d", &control);
        // printf("\e[1;1H\e[2J");
        system("clear");
        switch (control)
        {
        case -1:
            break;
        case 1:
            select_result_menu(file_path);
            break;
        case 2:
            add_new_semester_menu(file_path);
            break;
        default:
            break;
        }
    }
}

void select_result_menu(char *file_path)
{
    int control = 0;
    int i = semester_count_in_file(file_path);
    semester s;
    while (control != -1)
    {

        for (int j = 1; j <= i; j++)
        {
            printf("-----------------------------------------------------\n");
            printf("|                         %d                         |\n", j);
            s = read_semester_from_file(file_path, j);
            print_semester(s);
        }
        printf("-----------------------------------------------------\n");
        printf("|-1 | Go Back                                       |\n");
        printf("-----------------------------------------------------\n");
        printf("Pick a semester (-1 to go back): ");
        scanf_s("%d", &control);
        printf("\e[1;1H\e[2J");
        if (control != -1)
        {

            if (control < 0 || control > i)
            {
                printf("Pick a valid index\n");
            }
            else
            {
                s = read_semester_from_file(file_path, control);
                char grade;
                int unit = 0;
                char code[8];

                printf("Enter the course code (max of 8 characters): ");
                scanf_s("%s", code);

                printf("Enter the unit: ");
                scanf_s("%d", &unit);

                printf("Enter the grade: ");
                fflush(stdin);
                grade = getchar();

                result r;
                r.unit = unit;
                r.grade = grade;
                strcpy_s(r.code, sizeof(r.code), code);
                add_course_to_semester(&s, r);
                edit_semester_in_file(file_path, s, control);
            }
        }
    }
}

void add_new_semester_menu(char *file_path)
{
    enum levels level;
    enum semester_number semester_num;

    printf("Enter the level (100 - 500): ");
    scanf_s("%d", &level);

    printf("Enter the semester number (1st or 2nd): ");
    scanf_s("%d", &semester_num);

    semester s = new_semester(level, semester_num);

    write_semester_to_file(file_path, s);

    print_semester(s);

    system("pause");

    // printf("\e[1;1H\e[2J");
    system("clear");
}

void edit_result_menu(char *file_name)
{
    printf("coming soon...\n");
    system("pause");
    system("clear");
}

void delete_result_menu(char *file_path)
{
    int control = 0;
    int i = semester_count_in_file(file_path);
    semester s;
    while (control != -1)
    {

        // printf("\e[1;1H\e[2J");
        system("clear");
        for (int j = 1; j <= i; j++)
        {
            printf("-----------------------------------------------------\n");
            printf("|                         %d                         |\n", j);
            s = read_semester_from_file(file_path, j);
            print_semester(s);
        }
        printf("-----------------------------------------------------\n");
        printf("|-1 | Go Back                                       |\n");
        printf("-----------------------------------------------------\n");
        printf("choose a semester to delete (-1 to go back): ");
        scanf_s("%d", &control);
        // printf("\e[1;1H\e[2J");
        system("clear");
        if (control != -1)
        {

            if (control < 0 || control > i)
            {
                printf("Pick a valid index\n");
            }
            else
            {
                char choice;

                printf("Do you want to delete it [y] [n]: ");
                fflush(stdin);
                choice = getchar();

                if (choice == 'y' || choice == toupper('y'))
                {
                    if (delete_semester_in_file(file_path, control) != 0)
                    {
                        printf("error deleting the semester!\n");
                    }
                    else
                    {

                        printf("successfully deleted the semester!\n");
                        i--;
                    }
                    system("pause");
                }
            }
        }
    }
}
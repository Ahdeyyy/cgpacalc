#include "semester.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>

/// @brief add course to the given semester, returns 0 if it was successful and -1 if it failed
/// course codes must be unique
/// @param s_record
/// @param course
/// @return status
int add_course_to_semester(semester *s_record, result course)
{
    for (size_t i = 0; i < sizeof(s_record->courses) / sizeof(s_record->courses[0]); i++)
    {
        if (strcmp(s_record->courses[i].code, course.code) == 0 || strcmp(course.code, " ") == 0)
        {
            return -1;
        }
    }

    for (size_t i = 0; i < sizeof(s_record->courses) / sizeof(s_record->courses[0]); i++)
    {
        if ((strcmp(s_record->courses[i].code, " ")) == 0)
        {
            s_record->courses[i] = course;
            s_record->total_points += get_grade_point(course.grade) * course.unit;
            s_record->total_units += course.unit;
            return 0;
        }
    }
    return -1;
}

// create and initializes a new semester struct
semester new_semester(enum levels level, enum semester_number semester_num)
{
    semester s;
    s.current_semester = semester_num;
    s.s_level = level;
    s.total_points = 0.0;
    s.total_units = 0;
    for (size_t i = 0; i < sizeof(s.courses) / sizeof(s.courses[0]); i++)
    {
        strcpy(s.courses[i].code, " ");
    }

    return s;
}

/// removes specified result from the semester
/// returns 0 if successful and -1 if it fails
int remove_course_from_semester(semester *s_record, char *course_code)
{
    result s;
    for (size_t i = 0; i < sizeof(s_record->courses) / sizeof(s_record->courses[0]); i++)
    {
        if (strcmp(s_record->courses[i].code, course_code) == 0)
        {
            strcpy_s(s.code, sizeof(s.code), " ");
            s_record->total_points -= get_grade_point(s_record->courses[i].grade) * s_record->courses[i].unit;
            s_record->total_units -= s_record->courses[i].unit;
            s_record->courses[i] = s;
            return 0;
        }
    }
    return -1;
}

void print_semester(semester s)
{
    float gpa = s.total_points / s.total_units;
    char s_suffix[3];

    (s.current_semester == first) ? strcpy_s(s_suffix, sizeof(s_suffix), "st") : strcpy_s(s_suffix, sizeof(s_suffix), "nd");

    printf_s("_____________________________________________________\n");
    printf_s("|              %d Level         %d%s semester       |\n", s.s_level, s.current_semester, s_suffix);
    printf_s("_____________________________________________________\n");
    printf_s("|                    GPA: %.2f                      |\n", gpa);
    printf_s("_____________________________________________________\n");
    printf_s("| Total points: %.0f                                  |\n", s.total_points);
    printf_s("_____________________________________________________\n");
    printf_s("| Total units: %d                                    |\n", s.total_units);
    printf_s("_____________________________________________________\n");
    printf_s("|    course code   |     grade       |      unit    |\n");
    printf_s("_____________________________________________________\n");

    for (size_t i = 0; i < sizeof(s.courses) / sizeof(s.courses[0]); i++)
    {
        if (!(strcmp(s.courses[i].code, " ") == 0))
        {
            printf_s("|     %s       |       %c         |       %d      |\n", s.courses[i].code, toupper(s.courses[i].grade), s.courses[i].unit);
            printf_s("_____________________________________________________\n");
        }
    }
    printf_s("\n");
}

semester copy_semester(semester s)
{
    semester temp = new_semester(s.s_level, s.current_semester);
    result r;
    for (size_t i = 0; i < sizeof(s.courses) / sizeof(s.courses[0]); i++)
    {
        if (!(strcmp(s.courses[i].code, " ") == 0))
        {
            strcpy(r.code, s.courses[i].code);
            r.grade = s.courses[i].grade;
            r.unit = s.courses[i].unit;

            add_course_to_semester(&temp, r);
        }
    }

    return temp;
}

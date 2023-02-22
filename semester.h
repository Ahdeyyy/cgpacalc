#ifndef SEMESTER_H
#define SEMESTER_H

typedef enum levels
{
    one_hundred = 100,
    two_hundred = 200,
    three_hundred = 300,
    four_hundred = 400,
    five_hundred = 500
};

enum semester_number
{
    first = 1,
    second
};

typedef struct
{
    char grade;
    char code[8];
    int unit;
} result;

// represents a semester
typedef struct
{
    float total_points;
    int total_units;
    result courses[13];
    enum levels s_level;                   // 1-5 the 00s are added after
    enum semester_number current_semester; // first or second

} semester;

float get_grade_point(char);
int add_course_to_semester(semester *, result);
semester new_semester(enum levels, enum semester_number);
int remove_course_from_semester(semester *, char *);
void print_semester(semester);
int write_semester_to_file(char *, semester);

#endif
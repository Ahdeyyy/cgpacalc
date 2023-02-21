#include "semester.h"
#include <ctype.h>

/// @brief gets a grade and returns the point associated with the grade a -1.0 point is returned
/// if an invalid grade is given
/// a-f are the only valid grades
/// @param grade
/// @return point
float get_grade_point(char grade)
{
    switch (toupper(grade))
    {
    case 'A':
        return 5.0;
        break;

    case 'B':
        return 4.0;
        break;

    case 'C':
        return 3.0;
        break;

    case 'D':
        return 2.0;
        break;
    case 'E':
        return 1.0;
        break;
    case 'F':
        return 0.0;
        break;
    default:
        return -1.0;
    }
}

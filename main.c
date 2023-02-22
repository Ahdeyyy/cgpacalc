#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semester.h"

float get_grade_point(char grade);
void add_course();
void view_courses();
float calculate_cgpa();

// cgpa = total point( grade * unit ) / total courses * total unit

int main()
{

  semester s1 = new_semester(two_hundred, second);

  result f1 = {'a', "fsc111", 3};
  result f2 = {'a', "fsc112", 3};
  result f3 = {'a', "fsc113", 3};

  add_course_to_semester(&s1, f1);
  add_course_to_semester(&s1, f2);
  add_course_to_semester(&s1, f3);

  print_semester(s1);

  int err = write_semester_to_file("results.bin", s1);

  if (err == -1)
  {
    printf_s("error occured while writing to file");
  }

  // float cgpa;

  // // add score - unit gpa grade
  // int control = 0;

  // cgpa = calculate_cgpa();

  // while (control != -1)
  // {
  //   printf("\n");
  //   printf("|------------------------------|\n");
  //   printf("|          CGPA: %.2f          |\n", cgpa);
  //   printf("|------------------------------|\n");
  //   printf("|  1 |     Add new course      |\n");
  //   printf("|----|-------------------------|\n");
  //   printf("|  2 |     View courses        |\n");
  //   printf("|----|-------------------------|\n");
  //   printf("| -1 |     Quit program        |\n");
  //   printf("|------------------------------|\n");
  //   printf("|          Enter A Number      |\n");
  //   printf("|------------------------------|\n");
  //   scanf_s("%d", &control);
  //   printf("\e[1;1H\e[2J");
  //   switch (control)
  //   {
  //   case -1:
  //     break;
  //   case 1:
  //     add_course();
  //     cgpa = calculate_cgpa();
  //     control = 0;
  //     break;
  //   case 2:
  //     view_courses();
  //     break;
  //   default:
  //     printf("invalid command entered\n");
  //     control = 0;
  //     continue;
  //   }
  // }

  // // view stored grades show cgpa here
  return 0;
}

float calculate_cgpa()
{

  result x;
  FILE *rptr = fopen("./results.bin", "rb");
  float cgpa = 0.0;
  int t_units = 0;
  float t_points = 0.0;
  if (rptr == NULL)
  {
    return -1.0;
  }
  int index = 0;
  printf("\n");
  while (!feof(rptr))
  {
    fseek(rptr, index * sizeof(result), SEEK_SET);
    fread(&x, 1, sizeof(result), rptr);
    if (!feof(rptr))
    {
      t_points += get_grade_point(x.grade) * x.unit;
      t_units += x.unit;
      index++;
    }
  }
  cgpa = t_points / (float)t_units;
  fclose(rptr);
  return cgpa;
}

void view_courses()
{

  result x;
  FILE *rptr = fopen("./results.bin", "rb");
  int index = 0;
  printf("\n");
  printf("|------------------------------|\n");
  printf("|s/n | code \t|unit \t|grade |\n");
  printf("|------------------------------|\n");
  while (!feof(rptr))
  {
    fseek(rptr, index * sizeof(result), SEEK_SET);
    fread(&x, 1, sizeof(result), rptr);
    if (!feof(rptr))
    {
      printf("|%d   | %s \t|%d \t|%c     |\n", index + 1, x.code, x.unit,
             toupper(x.grade));
      index++;
    }
  }
  printf("|------------------------------|\n");
  fclose(rptr);
}

void add_course()
{
  char grade;
  int unit = 0;
  char code[64];

  FILE *fptr;

  if ((fptr = fopen("./results.bin", "ab")) == NULL)
  {
    return;
  }

  printf("Enter the course code (max of 8 characters): ");
  scanf_s("%s", code);

  printf("Enter the unit: ");
  scanf_s("%d", &unit);

  printf("Enter the grade: ");
  getchar(); // flushing the input stream would be a better option
  grade = getchar();

  result r;
  r.unit = unit;
  r.grade = grade;
  strcpy_s(r.code, sizeof(r.code), code);

  printf("%s %d %c\n", r.code, r.unit, r.grade);

  fwrite(&r, 1, sizeof(result), fptr);

  fclose(fptr);
}

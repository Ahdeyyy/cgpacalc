#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float get_grade_point(char grade);
void add_course();
void view_courses();
float calculate_cgpa();

typedef struct {
  char grade;
  char code[64];
  int unit;
} record;

// cgpa = total point( grade * unit ) / total courses * total unit

int main() {

  float cgpa;

  // add score - unit gpa grade
  int control = 0;

  cgpa = calculate_cgpa();

  while (control != -1) {
    printf("\n");
    printf("|------------------------------|\n");
    printf("|          CGPA: %.2f          |\n", cgpa);
    printf("|------------------------------|\n");
    printf("|  1 |     Add new course      |\n");
    printf("|----|-------------------------|\n");
    printf("|  2 |     View courses        |\n");
    printf("|----|-------------------------|\n");
    printf("| -1 |     Quit program        |\n");
    printf("|------------------------------|\n");
    printf("|          Enter A Number      |\n");
    printf("|------------------------------|\n");
    scanf_s("%d", &control);
    printf("\e[1;1H\e[2J");
    switch (control) {
    case -1:
      break;
    case 1:
      add_course();
      cgpa = calculate_cgpa();
      control = 0;
      break;
    case 2:
      view_courses();
      break;
    default:
      printf("invalid command entered\n");
      control = 0;
      continue;
    }
  }

  // view stored grades show cgpa here
  return 0;
}

float get_grade_point(char grade) {
  switch (toupper(grade)) {
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

float calculate_cgpa() {

  record x;
  FILE *rptr = fopen("./results.bin", "rb");
  float cgpa = 0.0;
  int t_units = 0;
  float t_points = 0.0;
  if (rptr == NULL) {
    return -1.0;
  }
  int index = 0;
  printf("\n");
  while (!feof(rptr)) {
    fseek(rptr, index * sizeof(record), SEEK_SET);
    fread(&x, 1, sizeof(record), rptr);
    if (!feof(rptr)) {
      t_points += get_grade_point(x.grade) * x.unit;
      t_units += x.unit;
      index++;
    }
  }
  cgpa = t_points / (float)t_units;
  fclose(rptr);
  return cgpa;
}

void view_courses() {

  record x;
  FILE *rptr = fopen("./results.bin", "rb");
  int index = 0;
  printf("\n");
  printf("|------------------------------|\n");
  printf("|s/n | code \t|unit \t|grade |\n");
  printf("|------------------------------|\n");
  while (!feof(rptr)) {
    fseek(rptr, index * sizeof(record), SEEK_SET);
    fread(&x, 1, sizeof(record), rptr);
    if (!feof(rptr)) {
      printf("|%d   | %s \t|%d \t|%c     |\n", index + 1, x.code, x.unit,
             toupper(x.grade));
      index++;
    }
  }
  printf("|------------------------------|\n");
  fclose(rptr);
}

void add_course() {
  char grade;
  int unit = 0;
  char code[64];

  FILE *fptr;

  if ((fptr = fopen("./results.bin", "ab")) == NULL) {
    return;
  }

  printf("Enter the course code (max of 64 characters): ");
  scanf_s("%s", code);

  printf("Enter the unit: ");
  scanf_s("%d", &unit);

  printf("Enter the grade: ");
  getchar(); // flushing the input stream would be a better option
  grade = getchar();

  record r;
  r.unit = unit;
  r.grade = grade;
  strcpy_s(r.code, sizeof(r.code), code);

  printf("%s %d %c\n", r.code, r.unit, r.grade);

  fwrite(&r, 1, sizeof(record), fptr);

  fclose(fptr);
}

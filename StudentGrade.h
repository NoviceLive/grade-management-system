/***************************************
 *Header name: StudentGrade.h          *
 *Author: Gu Zhengxiong                *
 *Version: 2013.11.22.2                *
 *Description:The header defines a     *
 *structure, GRADE.                    *
 ***************************************/


# ifndef STUDENT_MANAGEMENT_STUDENT_GRADE_H
# define STUDENT_MANAGEMENT_STUDENT_GRADE_H

typedef struct _StudentGrade
{
	double maths;
	double clang;
	double english;
}
GRADE,
*PGRADE;

# endif
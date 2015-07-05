/***************************************
 *Header name: Student.h               *
 *Author: Gu Zhengxiong                *
 *Version: 2013.11.27.1                *
 *Description:The header defines a     *
 *structure, STUDENT.                  *
 ***************************************/

# ifndef STUDENT_MANAGEMENT_STUDENT_H
# define STUDENT_MANAGEMENT_STUDENT_H

# include "StudentInfo.h"
# include "StudentGrade.h"

typedef struct _Student
{
	PINFO pi;
	PGRADE pg;
	void (*DisplayInfoPs)(PSTUDENT);
	void (*DisplayGradePs)(PSTUDENT);
	void (*DestroyPs)(PSTUDENT);
	void (*ModifyGrade)(PSTUDENT);
	struct _Student *pnext;
}
STUDENT,
*PSTUDENT;

enum
Mod_Type
{
	MOD_INFO = 1, MOD_GRADE
};

enum
GradeMod_Type
{
	GRADE_NOTHING = 0, GRADE_MATHS, GRADE_CLANG, GRADE_ENGLISH
};

void
DisplayInfoPs (PSTUDENT ps);
void
DisplayGradePs (PSTUDENT ps);

void
DestroyPs (PSTUDENT ps_before);

void
ModifyGrade (PSTUDENT ps);

PGRADE
ReadGrade (void);

# endif
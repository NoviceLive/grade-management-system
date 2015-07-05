/***************************************
 *File name: Student.c                 *
 *Author: Gu Zhengxiong                *
 *Version: 2013.11.27.1                *
 *Description:The file implements      *
 *functions in STUDENT.h               *
 ***************************************/

# include <stdio.h>//For printf (), scanf ()
# include <stdlib.h>//For free ()
# include <string.h>

# include "StudentInfo.h"
# include "StudentGrade.h"
# include "Student.h"
# include "MainFace.h"//For IsValidGrade ()

void
DisplayInfoPs (PSTUDENT ps)
{
	
	printf ("\n      THE STUDENT'S DETAILED INFORMATION\n");
	printf ("      NAME: %s\n", ps->pi->name);
	printf ("      NUMBER: %s\n", ps->pi->number);
	if (ps->pi->gender == 1)
		printf ("      GENDER: %s\n", "MALE");
	else
		printf ("      GENDER: %s\n", "FEMALE");
	printf ("      AGE: %d\n", ps->pi->age);
	printf ("      ADDRESS: %s\n", ps->pi->address);
}
void
DisplayGradePs (PSTUDENT ps)
{
	printf ("\n      THE STUDENT'S DETAILED GRADE\n");
	printf ("      MATHS: %g\n", ps->pg->maths);
	printf ("      CLANG: %g\n", ps->pg->clang);
	printf ("      ENGLISH: %g\n", ps->pg->english);
	printf ("      TOTAL: %g\n", ps->pg->clang + ps->pg->english + ps->pg->maths);
	printf ("      AVERAGE: %.2lf\n", (ps->pg->clang + ps->pg->english + ps->pg->maths) / 3.0);
}
void
DestroyPs (PSTUDENT ps_before)
{
	free (ps_before->pnext->pg);
	free (ps_before->pnext->pi);
	ps_before->pnext = ps_before->pnext->pnext;
}

void
ModifyGrade (PSTUDENT ps)
{
	int mod_flag;
	ps->DisplayGradePs (ps);
	printf ("\n      WHICH GRADE TO CHANGE?\n      1 FOR MATHS AND 2 FOR CLANG\n");
	printf ("      3 FOR ENGLISH AND 0 FOR NOTING\n");
	printf ("\n      ENTER A NUMBER:");
	scanf ("%d", &mod_flag);
	switch (mod_flag)
	{
		double tmp;
		case GRADE_NOTHING: break;

		case GRADE_MATHS:
			{
				printf ("\n      ENTER A NEW MATHS SCORE: ");
				scanf ("%lf", &tmp);
				while (!IsValidGrade (tmp))
				{
					printf ("\n      INVALIDE GRADE!\n      INPUT AGAIN: ");
					scanf ("%lf", &tmp);
				}
				ps->pg->maths = tmp;
				printf ("\n      CHANGE ACCOMPLISHED\n");
				Enter2Retn ();
			}
			break;

		case GRADE_CLANG:
			{
				printf ("\n      ENTER A NEW CLANG SCORE: ");
				scanf ("%lf", &tmp);
				while (!IsValidGrade (tmp))
				{
					printf ("\n      INVALIDE GRADE!\n      INPUT AGAIN: ");
					scanf ("%lf", &tmp);
				}
				ps->pg->clang = tmp;
				printf ("\n      CHANGE ACCOMPLISHED\n");
				Enter2Retn ();
			}
			break;

		case GRADE_ENGLISH:
			{
				printf ("\n      ENTER A NEW ENGLISH SCORE: ");
				scanf ("%lf", &tmp);
				while (!IsValidGrade (tmp))
				{
					printf ("\n      INVALIDE GRADE!\n      INPUT AGAIN: ");
					scanf ("%lf", &tmp);
				}
				ps->pg->english = tmp;
				printf ("\n      CHANGE ACCOMPLISHED\n");
				Enter2Retn ();
			}
			break;

		default: ShowError (IN_ERR); break;
	}
}

PGRADE
ReadGrade (void)
{
	PGRADE pg = (PGRADE)SecureMalloc (sizeof (GRADE));
	int flag = 1;
	printf ("\n      RESPECTIVELY MATHS, CLANG, ENGLISH INTERPOSED BY A BLANK\n      ENTER THE GRADE (IN 100 DEGREE): ");
	while (flag)
	{
		scanf ("%lf %lf %lf", &(pg->maths), &(pg->clang), &(pg->english));
		if (IsValidGrade (pg->maths) && IsValidGrade (pg->clang) && IsValidGrade (pg->english))
			flag = 0;
		else
			printf ("\n      LIMITS EXCEEDED! ENTER AGAIN: ");
	}
	return pg;
}
/***************************************
 *File name: Manip.c                   *
 *Author: Gu Zhengxiong                *
 *Version: 2013.11.28                  *
 *Description:The file implements      *
 *functions in MANIP                   *
 ***************************************/

# include <stdlib.h>//For malloc (), free () 
# include <stdio.h>//For printf () 
# include <string.h>//For strcpy (), strcmp () 

# include "StudentInfo.h"
# include "StudentGrade.h"
# include "Student.h"
# include "Manip.h"
# include "MainFace.h"

static PSTUDENT
Construct (void)
{
	PSTUDENT ps = (PSTUDENT)SecureMalloc (sizeof (STUDENT));//SecureMalloc @ MainFace.h 
	ps->pnext = NULL;
	return ps;
}
static void
Add (PSTUDENT phead, PINFO pi_in, PGRADE pg_in)
{
	PSTUDENT ps = (PSTUDENT)SecureMalloc (sizeof (STUDENT));
	PSTUDENT ps_tmp = phead;
	ps->pi = pi_in;
	ps->pg = pg_in;
	ps->DisplayInfoPs = DisplayInfoPs;
	ps->DisplayGradePs = DisplayGradePs;
	ps->ModifyGrade = ModifyGrade;
	ps->DestroyPs = DestroyPs;
	while (ps_tmp->pnext != NULL)
		ps_tmp = ps_tmp->pnext;
	ps_tmp->pnext = ps;
	ps->pnext = NULL;
}
static void
DisplayInfo (PSTUDENT phead)
{
	PSTUDENT ps_tmp = phead;
	char gender_buf[7];
	printf ("\n      STUDENTS' INFORMATION\n");
	printf ("      -------------------------------------------------------\n");
	printf ("      | %-16s | %-16s | %-7s | %3s |\n", "NAME", "NUMBER", "GENDER", "AGE");
	printf ("      -------------------------------------------------------\n");
	while (ps_tmp != NULL)
	{
		if (ps_tmp == phead)
			;
		else
		{
			if (ps_tmp->pi->gender == 1)
				strcpy (gender_buf, "MALE");
			else
				strcpy (gender_buf, "FEMALE");
			printf (ALL_INFO_FORMAT, ALL_INFO_PARA);
			printf ("      -------------------------------------------------------\n");
		}
			ps_tmp = ps_tmp->pnext;
	}
}
static void
DisplayGrade (PSTUDENT phead)
{
	PSTUDENT ps_tmp = phead;
	printf ("\n      STUDENTS' GRADE\n");
	printf ("      -----------------------------------------------------------------\n");
	printf ("      | %-16s | %-16s | %s | %s | %s |\n", "NAME", "NUMBER", "MATHS", "CLANG", "ENGLISH");
	printf ("      -----------------------------------------------------------------\n");
	while (ps_tmp != NULL)
	{
		if (ps_tmp == phead)
			;
		else
		{
			printf (ALL_GRADE_FORMAT, ALL_GRADE_PARA);
			printf ("      -----------------------------------------------------------------\n");
		}
			ps_tmp = ps_tmp->pnext;
	}
}
static void
AnalyzeGrade (PSTUDENT phead)
{
	PSTUDENT ps_tmp = phead->pnext;

	PSTUDENT maths_max = ps_tmp, clang_max = ps_tmp, english_max = ps_tmp;
	PSTUDENT total_max = ps_tmp;

	double maths_ave = 0, clang_ave = 0, english_ave = 0;

	int counter = 0;

	int classifier[3][3] = {0};//0 for maths, 1 for clang, 2 for english; 0 for >= 85, 1 for < 80 && >= 60, 2 for < 60

	while (ps_tmp != NULL)
	{
		counter++;

		maths_ave += ps_tmp->pg->maths;
		clang_ave += ps_tmp->pg->clang;
		english_ave += ps_tmp->pg->english;

		if (maths_max->pg->maths < ps_tmp->pg->maths)
			maths_max = ps_tmp;
		if (clang_max->pg->clang < ps_tmp->pg->clang)
			clang_max = ps_tmp;
		if (english_max->pg->english < ps_tmp->pg->english)
			english_max = ps_tmp;
		if (total_max->pg->clang + total_max->pg->english + total_max->pg->maths
			< ps_tmp->pg->clang + ps_tmp->pg->english + ps_tmp->pg->maths)
			total_max = ps_tmp;

		Classify (ps_tmp->pg->maths, classifier[0]);
		Classify (ps_tmp->pg->clang, classifier[1]);
		Classify (ps_tmp->pg->english, classifier[2]);

		ps_tmp = ps_tmp->pnext;
	}

	maths_ave /= counter;
	clang_ave /= counter;
	english_ave /= counter;

	printf ("\n      GRADE ANALYSIS\n");
	printf ("\n      HIGHEST TOTAL SCORE: \n      %-6.2lf      %s      %s\n", \
		total_max->pg->clang + total_max->pg->english + total_max->pg->maths, total_max->pi->name, total_max->pi->number);
	printf ("\n      HIGHEST MATHS SCORE: \n      %-6.2lf      %s      %s\n", \
		maths_max->pg->maths, maths_max->pi->name, maths_max->pi->number);
	printf ("\n      HIGHEST CLANG SCORE: \n      %-6.2lf      %s      %s\n", \
		maths_max->pg->clang, clang_max->pi->name, clang_max->pi->number);
	printf ("\n      HIGHEST ENGLISH SCORE: \n      %-6.2lf      %s      %s\n", \
		english_max->pg->english, english_max->pi->name, english_max->pi->number);

	printf ("\n      MATHS GRADE ANALYSIS\n");
	printf ("      MATHS AVERAGE: %.2lf\n", maths_ave);
	printf ("      FAILED STUDENT NUMBER: %d\n      PASSED STUDENT NUMBER: %d\n      EXCELLENT STUDENT NUMBER: %d\n", \
		classifier[0][2], classifier[0][1] + classifier[0][0], classifier[0][0]);
	printf ("\n      CLANG GRADE ANALYSIS\n");
	printf ("      CLANG AVERAGE: %.2lf\n", clang_ave);
	printf ("      FAILED STUDENT NUMBER: %d\n      PASSED STUDENT NUMBER: %d\n      EXCELLENT STUDENT NUMBER: %d\n", \
		classifier[1][2], classifier[1][1] + classifier[1][0], classifier[1][0]);
	printf ("\n      ENGLISH GRADE ANALYSIS\n");
	printf ("      ENGLISH AVERAGE: %.2lf\n", english_ave);
	printf ("      FAILED STUDENT NUMBER: %d\n      PASSED STUDENT NUMBER: %d\n      EXCELLENT STUDENT NUMBER: %d\n", \
		classifier[2][2], classifier[2][1] + classifier[2][0], classifier[2][0]);
}
static PSTUDENT
Inquire (PSTUDENT phead, int type, char * s)
{
	PSTUDENT ps_tmp = phead;
	while (ps_tmp != NULL)
	{
		if (ps_tmp == phead)
			;
		else
		{
			switch (type)
			{
				case SEARCH_NUM: 
								if (strcmp (s, ps_tmp->pi->number) == 0)
									return ps_tmp;
								break;
				case SEARCH_NAME:
								if (strcmp (s, ps_tmp->pi->name) == 0)
									return ps_tmp;
								break;
			}
		}
		ps_tmp = ps_tmp->pnext;
	}
	return NULL;
}
static PSTUDENT
InquireBefore (PSTUDENT phead, int type, char * s)
{
	PSTUDENT ps_tmp = phead;
	while (ps_tmp->pnext != NULL)
	{
		switch (type)
		{
			case SEARCH_NUM: 
							if (strcmp (s, ps_tmp->pnext->pi->number) == 0)
								return ps_tmp;
							break;
			case SEARCH_NAME:
							if (strcmp (s, ps_tmp->pnext->pi->name) == 0)
								return ps_tmp;
							break;
		}
	ps_tmp = ps_tmp->pnext;
	}
	return NULL;
}
static void
SSort (PSTUDENT phead, int sort_type)
{
	PSTUDENT ps_fir, ps_tmp = phead, ps_max, ps_before_max;
	switch (sort_type)
	{
		case SORT_NUMBER:
			{
				while ((ps_fir = ps_tmp->pnext) != NULL)
				{
					ps_max = ps_fir;
					while (ps_fir->pnext != NULL)
					{
						if (_atoi64 (ps_fir->pnext->pi->number) > _atoi64 (ps_max->pi->number))
							ps_max = ps_fir->pnext;
						ps_fir = ps_fir->pnext;
					}
					ps_before_max = InquireBefore (phead, SEARCH_NUM, ps_max->pi->number);
					ps_before_max->pnext = ps_max->pnext;
					ps_max->pnext = ps_tmp->pnext;
					ps_tmp->pnext = ps_max;
					ps_tmp = ps_tmp->pnext;
				}

			}
			break;
		case SORT_TOTAL:
			{
				while ((ps_fir = ps_tmp->pnext) != NULL)
				{
					ps_max = ps_fir;
					while (ps_fir->pnext != NULL)
					{
						if (ps_fir->pnext->pg->maths + ps_fir->pnext->pg->clang + ps_fir->pnext->pg->english \
							> ps_max->pg->maths + ps_max->pg->clang + ps_max->pg->english)
							ps_max = ps_fir->pnext;
						ps_fir = ps_fir->pnext;
					}
					ps_before_max = InquireBefore (phead, SEARCH_NUM, ps_max->pi->number);
					ps_before_max->pnext = ps_max->pnext;
					ps_max->pnext = ps_tmp->pnext;
					ps_tmp->pnext = ps_max;
					ps_tmp = ps_tmp->pnext;
				}
			}
			break;
		case SORT_MATHS:
			{
				while ((ps_fir = ps_tmp->pnext) != NULL)
				{
					ps_max = ps_fir;
					while (ps_fir->pnext != NULL)
					{
						if (ps_fir->pnext->pg->maths > ps_max->pg->maths)
							ps_max = ps_fir->pnext;
						ps_fir = ps_fir->pnext;
					}
					ps_before_max = InquireBefore (phead, SEARCH_NUM, ps_max->pi->number);
					ps_before_max->pnext = ps_max->pnext;
					ps_max->pnext = ps_tmp->pnext;
					ps_tmp->pnext = ps_max;
					ps_tmp = ps_tmp->pnext;
				}
			}
			break;
		case SORT_CLANG:
			{
				while ((ps_fir = ps_tmp->pnext) != NULL)
				{
					ps_max = ps_fir;
					while (ps_fir->pnext != NULL)
					{
						if (ps_fir->pnext->pg->clang > ps_max->pg->clang)
							ps_max = ps_fir->pnext;
						ps_fir = ps_fir->pnext;
					}
					ps_before_max = InquireBefore (phead, SEARCH_NUM, ps_max->pi->number);
					ps_before_max->pnext = ps_max->pnext;
					ps_max->pnext = ps_tmp->pnext;
					ps_tmp->pnext = ps_max;
					ps_tmp = ps_tmp->pnext;
				}
			}
			break;
		case SORT_ENGLISH:
			{
				while ((ps_fir = ps_tmp->pnext) != NULL)
				{
					ps_max = ps_fir;
					while (ps_fir->pnext != NULL)
					{
						if (ps_fir->pnext->pg->english > ps_max->pg->english)
							ps_max = ps_fir->pnext;
						ps_fir = ps_fir->pnext;
					}
					ps_before_max = InquireBefore (phead, SEARCH_NUM, ps_max->pi->number);
					ps_before_max->pnext = ps_max->pnext;
					ps_max->pnext = ps_tmp->pnext;
					ps_tmp->pnext = ps_max;
					ps_tmp = ps_tmp->pnext;
				}
			}
			break;
	}
}
static void
SaveToFile (PSTUDENT phead)
{
	FILE *pf = fopen ("Student", "w");
	PSTUDENT ps_tmp = phead;
	if (pf == NULL)
	{
		ShowError (FILE_ERR);
		return;
	}
	while (ps_tmp != NULL)
	{
		if (ps_tmp == phead)
			;
		else
		{
			fwrite (ps_tmp->pi, sizeof (INFO), 1, pf);
			fwrite (ps_tmp->pg, sizeof (GRADE), 1, pf);
		}
		ps_tmp = ps_tmp->pnext;
	}
	fclose (pf);
}
static int
LoadFromFile (PSTUDENT phead, int *c)
{
	FILE *pf = fopen ("Student", "r");
	PINFO pi_tmp = (PINFO)SecureMalloc (sizeof (INFO));
	PGRADE pg_tmp = (PGRADE)SecureMalloc (sizeof (GRADE));
	int absorb_flag = 1;
	if (pf == NULL)
	{
		ShowError (FILE_ERR);
		return 0;
	}
	while (fread (pi_tmp, sizeof (INFO), 1, pf) != 0 && fread (pg_tmp, sizeof (GRADE), 1, pf) != 0)
	{
		if (Inquire (phead, SEARCH_NAME, pi_tmp->name) != NULL || Inquire (phead, SEARCH_NUM, pi_tmp->number) != NULL)
		{
			if (absorb_flag == 1)
			{
				ShowExist (pi_tmp->name, pi_tmp->number);
				getchar ();//Difficult and tedious to contorl
				absorb_flag = 2;
			}
			else
				ShowExist (pi_tmp->name, pi_tmp->number);
			continue;
		}
		if (IsValidGrade (pg_tmp->clang) && IsValidGrade (pg_tmp->english) && IsValidGrade (pg_tmp->maths))
		{
			PINFO pi_real = (PINFO)SecureMalloc (sizeof (INFO));
			PGRADE pg_real = (PGRADE)SecureMalloc (sizeof (GRADE));
			*(pi_real) = *(pi_tmp);
			*(pg_real) = *(pg_tmp);
			Add (phead, pi_real, pg_real);
			(*c)++;
		}
		else
		{
			ShowError (IN_ERR);
			continue;
		}
	}
	free (pi_tmp);
	free (pg_tmp);
	fclose (pf);
	return absorb_flag;
}
static void
Destroy (PSTUDENT phead)
{
	PSTUDENT ps_tmp = phead;
	while (ps_tmp != NULL)
	{
		if (ps_tmp == phead)
			;
		else
		{	free (ps_tmp->pg);
			free (ps_tmp->pi);
		}
		ps_tmp = ps_tmp->pnext;
	}
}
PMANIP
ManipInitialize (void)
{
	PMANIP pm = (PMANIP)SecureMalloc (sizeof (MANIP));
	pm->Construct = Construct;
	pm->Add = Add;
	pm->Inquire = Inquire;
	pm->InquireBefore = InquireBefore;
	pm->SSort = SSort;
	pm->DisplayInfo = DisplayInfo;
	pm->DisplayGrade = DisplayGrade;
	pm->AnalyzeGrade = AnalyzeGrade;
	pm->SaveToFile = SaveToFile;
	pm->LoadFromFile = LoadFromFile;
	pm->Destroy = Destroy;

	return pm;
}

PINFO
ReadInfo (PSTUDENT phead)
{
	PINFO pi = (PINFO)SecureMalloc (sizeof (INFO));
	char buf[16];
	printf ("\n      ENTER THE NAME: ");
	getchar ();
	gets (buf);
	if (Inquire (phead, SEARCH_NAME, buf) != NULL)
	{
		ShowError (EXISTED);
		free (pi);
		return NULL;
	}
	strcpy (pi->name, buf);
	printf ("      ENTER THE NUMBER: ");
	scanf ("%s", buf);
	if (Inquire (phead, SEARCH_NUM, buf) != NULL)
	{
		ShowError (EXISTED);
		getchar ();
		free (pi);
		return NULL;
	}
	strcpy (pi->number, buf);
	printf ("      ENTER THE GENDER (1 FOR MALE AND 0 FOR FEMALE): ");
	scanf ("%d", &(pi->gender));
	printf ("      ENTER THE AGE: ");
	scanf ("%d", &(pi->age));
	printf ("      ENTER THE ADDRESS: ");
	getchar ();
	gets (pi->address);
	
	//Note I checked some
	
	return pi;
}

void
ModifyInfo (PSTUDENT ps, PSTUDENT phead)// I checked some
{
	int mod_flag;
	ps->DisplayInfoPs (ps);
	printf ("\n      WHICH INFORMATION TO VARY?\n      1 FOR NMAE and 2 FOR NUMBER\n");
	printf ("      3 FOR GENDER AND 4 FOR AGE\n      5 FOR ADDRESS AND 0 FOR NOTIHNG\n");
	printf ("\n      ENTER A NUMBER: ");
	scanf ("%d", &mod_flag);
	switch (mod_flag)
	{
		case INFO_NOTHING : break;

		case INFO_NAME: 
			{
				char name_buf[16];
				printf ("\n      ENTER A NEW NAME: ");
				getchar ();
				gets (name_buf);
				if (Inquire (phead, SEARCH_NAME, name_buf) != NULL)
				{
					ShowError (EXISTED);
					break;
				}
				strcpy (ps->pi->name, name_buf);
				printf ("\n      MODIFICATION OVER.\n");
				Enter2Retn1 ();
			}
			break;

		case INFO_NUMBER:
			{
				char number_buf[16];
				printf ("\n      ENTER A NEW NUMBER: ");
				scanf ("%s", number_buf);
				if (Inquire (phead, SEARCH_NUM, number_buf) != NULL)
				{
					ShowError (EXISTED);
					break;
				}
				strcpy (ps->pi->number, number_buf);
				printf ("\n      MODIFICATION OVER.\n");
				Enter2Retn ();
			}
			break;

		case INFO_GENDER:
			{
				printf ("\n      ENTER A NEW GENDER: ");
				scanf ("%d", &(ps->pi->gender));
				printf ("\n      MODIFICATION OVER.\n");
				Enter2Retn ();
			}
			break;

		case INFO_AGE:
			{
				printf ("\n      ENTER A NEW AGE: ");
				scanf ("%d", &(ps->pi->age));
				printf ("\n      MODIFICATION OVER.\n");
				Enter2Retn ();
			}
			break;

		case INFO_ADDRESS:
			{
				printf ("\n      ENTER A NEW ADDRESS: ");
				getchar ();
				gets (ps->pi->address);
				printf ("\n      MODIFICATION OVER.\n");
				Enter2Retn ();
			}
			break;

		default: ShowError (IN_ERR); break;
	}
}
void
Classify (double g, int *cl)
{
	if (g >= 85)
		cl[0]++;
	else
	{
		if (g >= 60)
			cl[1]++;
		else
			cl[2]++;
	}
}
/***************************************
 *Header name: Manip.h                 *
 *Author: Gu Zhengxiong                *
 *Version: 2013.11.28                  *
 *Description:The header defines a     *
 *structure, MANIP.                    *
 ***************************************/

# ifndef STUDENT_MANAGEMENT_MANIP_H
# define STUDENT_MANAGEMENT_MANIP_H

# include "StudentInfo.h"
# include "StudentGrade.h"
# include "Student.h"

# define ALL_INFO_FORMAT "      | %-16s | %-16s | %-7s | %-3d |\n"
# define ALL_INFO_PARA ps_tmp->pi->name, ps_tmp->pi->number, gender_buf, ps_tmp->pi->age
# define ALL_GRADE_FORMAT "      | %-16s | %-16s | %5g | %-5g | %-7g |\n"
# define ALL_GRADE_PARA ps_tmp->pi->name, ps_tmp->pi->number, ps_tmp->pg->maths, ps_tmp->pg->clang, ps_tmp->pg->english

enum
SearchType
{
	SEARCH_NUM = 1, SEARCH_NAME
};
enum
InfoMod_Type
{
	INFO_NOTHING = 0, INFO_NAME, INFO_NUMBER, INFO_GENDER, INFO_AGE, INFO_ADDRESS
};
enum
Sort_Type
{
	SORT_NUMBER = 1, SORT_TOTAL, SORT_MATHS, SORT_CLANG, SORT_ENGLISH
};

typedef struct _Manip
{
	PSTUDENT (*Construct) (void);
	void (*DisplayInfo)(PSTUDENT);
	void (*DisplayGrade) (PSTUDENT);
	void (*AnalyzeGrade) (PSTUDENT);
	void (*Add) (PSTUDENT, PINFO, PGRADE);
	PSTUDENT (*Inquire) (PSTUDENT, int, char *);
	PSTUDENT (*InquireBefore) (PSTUDENT, int, char *);
	void (*SSort)(PSTUDENT, int);
	void (*SaveToFile) (PSTUDENT);
	int (*LoadFromFile) (PSTUDENT, int *);
	void (*Destroy) (PSTUDENT);
}
MANIP,
*PMANIP;

PMANIP
ManipInitialize (void);
PSTUDENT
Construct (void);
void
DisplayInfo (PSTUDENT phead);
void
DisplayGrade (PSTUDENT phead);
void
AnalyzeGrade (PSTUDENT phead);
void
Add (PSTUDENT phead, PINFO pi, PGRADE pg);
PSTUDENT
Inquire (PSTUDENT phead, int type, char * s);
PSTUDENT
InquireBefore (PSTUDENT phead, int type, char * s);
void
SSort (PSTUDENT phead, int sort_type);
void
SaveToFile (PSTUDENT phead);
int
LoadFromFile (PSTUDENT phead, int *c);
void
Destroy (PSTUDENT ps);

PINFO
ReadInfo (PSTUDENT phead);
void
ModifyInfo (PSTUDENT ps, PSTUDENT phead);
void
Classify (double g, int *cl);

# endif
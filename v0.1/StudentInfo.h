/***************************************
 *Header name: StudentInfo.h           *
 *Author: Gu Zhengxiong                *
 *Version: 2013.11.23.1                *
 *Description:The header defines a     *
 *structure, INFO.                     *
 ***************************************/

# ifndef STUDENT_MANAGEMENT_STUDENT_INFO_H
# define STUDENT_MANAGEMENT_STUDENT_INFO_H

typedef struct _StudentInfo
{
	char name[16];
	char number[16];
	int age;
	int gender;
	char address[256];
}
INFO,
*PINFO;

#endif
/***************************************
 *Header name: MainFace.h              *
 *Author: Gu Zhengxiong                *
 *Version: 2013.11.28                  *
 *Description:The header defines       *
 *something related to the program's   *
 *interface and something else.        *
 ***************************************/

# ifndef STUDENT_MANAGEMENT_MAINFACE_H
# define STUDENT_MANAGEMENT_MAINFACE_H

# include <stdlib.h>//for size_t

enum
Selection
{
	QUIT = 9, ADD = 2, DEL = 7, LOAD = 1, TO_FILE = 8, SORT = 6,
    INQUIRE = 3, MOD = 4, DISP = 5
};
enum
Error
{
	IN_ERR = 0, UNFOUND, NO_RECORD, EXISTED, FILE_ERR
};
enum
Menu
{
	MENU_DISP = 1, MENU_MOD, MENU_SORT
};
enum
Disp_Type
{
	DISP_INFO = 1, DISP_GRADE, DISP_ANALYZE
};

int
IsNumStr (char *s);
int
IsValidGrade (double g);
void
SetCmdProperty (void);
void
ShowFace (void);
void
ShowError (int error_type);
void
ShowSubMenu (int menu_type);
void
ShowSubHead (void);
void
Enter2Retn (void);
void
Enter2Retn1 (void);
void *
SecureMalloc (size_t size);
void
ShowExist (char *s, char *s2);

# endif
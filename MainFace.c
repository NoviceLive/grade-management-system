/***************************************
 *File name: MainFace.c                *
 *Author: Gu Zhengxiong                *
 *Version: 2013.11.28                  *
 *Description:The file implements      *
 *functions in MainFace.h.             *
 ***************************************/

# include <stdio.h>//For printf () 
# include <stdlib.h>//For system (), exit (), EXIT_FAILURE 
# include <ctype.h>//For isdigit (), tolower ()
# include <string.h>//For strlen ()

# include "MainFace.h"

int
IsNumStr (char *s)
{
	unsigned int i;
	for (i = 0; isdigit (s[i]); i++)
		;
	return i == strlen (s);
}
int
IsValidGrade (double g)
{
	if (g >= 0 && g <= 100)
		return 1;
	return 0;
}
static void
SetCmdProperty (void)
{
	system ("title STUDENT INFO^&GRADE MANAGEMENT SYSTEM");
	system ("cls");
	system ("color a");
}
void
ShowFace (void)
{
	SetCmdProperty ();
	printf ("                  * * * * * * * * * * * * * * * * * * * * *\n");//18 blanks
	printf ("                  * STUDENT INFO &GRADE MANAGEMENT SYSTEM *\n");//18 blanks
	printf ("                  * * * * * * * *           * * * * * * * *\n");//18 blanks
	printf ("                                * MAIN MENU *\n");
	printf ("                                * * * * * * *\n\n");
	printf ("      * * * * * * *             * * * * * * *             * * * * * * *\n");//6 blanks
	printf ("      * 1  LOAD   *             * 2   ADD   *             * 3  SEARCH *\n");
	printf ("      * * * * * * *             * * * * * * *             * * * * * * *\n\n");
	printf ("      * * * * * * *             * * * * * * *             * * * * * * *\n");
	printf ("      * 4  MODIFY *             * 5 DISPLAY *             * 6  SORT   *\n");
	printf ("      * * * * * * *             * * * * * * *             * * * * * * *\n\n");
	printf ("      * * * * * * *             * * * * * * *             * * * * * * *\n");
	printf ("      * 7  DELETE *             * 8  SAVE   *             * 9  QUIT   *\n");
	printf ("      * * * * * * *             * * * * * * *             * * * * * * *\n\n");
}
void
ShowError (int error_type)
{
	switch (error_type)
	{
	case IN_ERR: 
		{
			printf ("\n      INPUTS ERROR!\n");
			Enter2Retn ();
		}
		break;
		case UNFOUND:
			{
				printf ("\n      NOT FOUND!\n");
				//Enter2Retn ();
				Enter2Retn1 ();
			}
			break;
		case NO_RECORD:
			{
				printf ("\n      THERE ARE NO RECORD NOW!\n      LOAD SOME OR ADD ONE.\n");
				Enter2Retn ();
			}
			break;
		case EXISTED:
			{
				printf ("\n      THIS RECORD ALREADY EXISTED!\n      INPUT ANOTHER ONE.\n");
				//Enter2Retn ();
				Enter2Retn1 ();
			}
			break;
		case FILE_ERR:
			{
				printf ("\n      FILE OPEN ERROR!\n      TRY AGAIN.\n");
				Enter2Retn ();
			}
			break;
	}
}
void
ShowSubMenu (int menu_type)
{
	ShowSubHead ();
	switch (menu_type)
	{
		case MENU_MOD: 
		 {
			printf ("      MODIFY STUDENTS' RECORD\n\n");
			printf ("      INPUT 1 TO MODIFY STUDENTS' INFO\n      INPUT 2 TO CHANGE STUDENTS'GRADE\n");
			printf ("\n      ENTER A NUMBER: ");
		 }
		 break;
		case MENU_DISP: 
		 {
			printf ("      DISPLAY STUDENTS' RECORD\n\n");
			printf ("      INPUT 1 TO DISPLAY ALL STUDENTS' INFO\n      INPUT 2 TO SHOW ALL STUDENTS'GRADE\n");
			printf ("      INPUT 3 TO SHOW ANALYSIS OF THE GRADE\n");
			printf ("\n      ENTER A NUMBER: ");
		 }
		 break;
		case MENU_SORT:
		 {
			 printf ("      SORT STUDENT'S RECORD\n\n");
			 printf ("      1 FOR SORT BASED ON NUMBER\n      2 FOR SORT BASED ON TOTAL SCORE\n");
			 printf ("      3 FOR SORT BASED ON MATHS SCORE\n      4 FOR CLANG BASED SORT\n");
			 printf ("      5 FOR ENGLISH BASED SORT\n\n      ENTER A NUMBER: ");
		 }
		 break;
	}
}
void
Enter2Retn (void)
{
	printf ("\n      PRESS ENTER TO RETURN....");
	getchar ();
	getchar ();
}
void
Enter2Retn1 (void)
{
	printf ("\n      PRESS ENTER TO RETURN....");
	getchar ();
}
void *
SecureMalloc (size_t size)
{
	void *tmp = malloc (size);
	while (tmp == NULL)
	{
		int t;
		printf ("\n      WARNING: MEMORY ALLOCATION FAILED!\n");
		printf ("\n      RETRY?\n      1 FOR RETRY;\n      0 FOR ABORT.\n      (1/0): ");
		scanf ("%d", &t);
		if (t == 1)
			tmp = malloc (size);
		else
		{
			if (t == 0)
				exit (EXIT_FAILURE);
			else
			{
				ShowError (IN_ERR);
			}
		}
	}
	return tmp;
}
void
ShowExist (char *s, char *s1)
{
	printf ("\n      RECORD NAME: %s\n      RECORD NUMBER: %s\n      ALREADY EXISTED!\n      IT WILL BE SKIPPED.\n", s, s1);
	printf ("\n      PRESS ENTER TO CONTINUE....");
	getchar ();
}
static void
ShowSubHead (void)
{
	SetCmdProperty ();
	printf ("                  * * * * * * * * * * * * * * * * * * * * *\n");//18 blanks
	printf ("                  * STUDENT INFO &GRADE MANAGEMENT SYSTEM *\n");//18 blanks
	printf ("                  * * * * * * * *           * * * * * * * *\n");//18 blanks
	printf ("                                * SUB  MENU *\n");
	printf ("                                * * * * * * *\n\n");
}

/****************************************
 *File name: main.c                     *
 *Author: Gu Zhengxiong                 *
 *Version: 2013.11.28                   *
 *Description:The file works            *
 ****************************************/

# include <stdlib.h>//For malloc (), free (), NULL, EXIT_SUCCESS
# include <stdio.h>//For printf (), scanf ()
# include <ctype.h>//For isdigit ()
# include <string.h>//For strlen ()

# include "StudentInfo.h"
# include "StudentGrade.h"
# include "Student.h"
# include "Manip.h"
# include "MainFace.h"

int save_flag = 0;

int
main (void)
{
	int record_counter = 0;//It stores how many records there are

	/*PAMNIP was defined at Manip.h
	ManipInitialize () was declared at Manip.h and was implemented at Manip.c, 
	and its function is to make all needed function well prepared
	Note the function called malloc () and its return value points to the allocated memory*/
	PMANIP wangluo2 = ManipInitialize ();

	/*PSTUDENT was defined at Student.h
	Construct () was declared at Manip.h and realized at Manip.c, 
	and it creates the first node whose members pi and pg was not allocated any memory
	But note phead points to a memory allocated by malloc()*/
	PSTUDENT phead = wangluo2->Construct ();

	while (1)//This is the main loop
	{
		int choice;

		/*ShowFace () was declared at MainFace.h and was defined at MainFace.c
		It shows the main menu*/
		ShowFace ();

		//Hints about the total records
		printf ("      THERE ARE NOW %d RECORD(S) ALTOGETHER.\n\n", record_counter);

		printf ("      ENTER A FUNCTION NUMBER( 1 ~ 9): ");
		scanf ("%d", &choice);

		if (choice > 9 || choice < 1)
			/*ShowError () and IN_ERR was declared at MainFace.h, and the former was defined at MainFace.c,
			and it shows different error information according to the input*/
			ShowError (IN_ERR);
		else
		{
			switch (choice)//Handle users legal inputs
			{
				case ADD: //ADD was defined at MainFace.h functioning as an enum constant
					{
						/*Add () was declared at Manip.h and realized at Manip.c
						It adds a student record to the end of the existing list
						ReadInfo () and ReadGrade () was declared and implemented @ respectively Student.h and Student.c*/
						PINFO pi_tmp = ReadInfo (phead);
						if (pi_tmp == NULL)//This means ReadInfo () encoutered illegal inputs
							break;
						wangluo2->Add (phead, pi_tmp, ReadGrade ());
						
						record_counter++;//Added one record

						save_flag = 1;

						printf ("\n      ADDITION FINISHED.\n");//6 blanks
						Enter2Retn ();//@ MainFace.h and MainFace.c
					}
					break;

				case LOAD:
					{
						int tmp;//Stores LoadFromFile ()'s return value, which could tell me whether to use getchar ()
						if (tmp = wangluo2->LoadFromFile (phead, &record_counter))//Either 1 or 2; It is =, not ==
						{
							save_flag = 1;
							printf ("\n      LOADING FINISHED.\n");
							if (tmp == 1)//1 means loading source has no repeated record
							{
								Enter2Retn ();
							}
							else
								if (tmp == 2)//2 means loading source has repeated record
								{
									Enter2Retn1 ();
								}
						}
						else//Neither 1 nor 2 means returned 0, it was handled by the function itself; so the outer did nothing
							break;
					}
					break;

				case DEL: //DEL was defined at MainFace.h functioning as an enum constant
					{
						char in[32];
						PSTUDENT ps_before;
						if (phead->pnext == NULL)
						{
							ShowError (NO_RECORD);
							break;
						}
						printf ("\n      ENTER THE NUMBER OR NAME: ");
						getchar ();//Absorbs character
						gets (in);
						if (IsNumStr (in))
							/*InquireBefore () searches the list for the student just before the inputted position
							It was declared at Manip.h and realized at Manip.c
							SEARCH_NUM was defined @ Manip.h and works as a flag of search mode, that is number based or name based*/
							ps_before = wangluo2->InquireBefore (phead, SEARCH_NUM, in);
						else
							ps_before = wangluo2->InquireBefore (phead, SEARCH_NAME, in);//SEARCH_NAME means search a student by name
						if (ps_before == NULL)
							ShowError (UNFOUND);//UNFOND was defined @ MainFace.h
						else
						{
							int tmp;
							printf ("\n      ARE YOU GOING TO DELETE THE RECORD: %s\n      1 FOR DELETE AND 0 FOR NOT.\n      (1 / 0): ", in);
							scanf ("%d", &tmp);
							if (tmp == 1)
							{
								/*DestroyPs ()'s declaration and definition were respectively @ Student.h and Student.c
								The function calls free () to release the dynamically allocated memory at a STUDENT struct*/ 
								ps_before->pnext->DestroyPs (ps_before);

								record_counter--;

								save_flag = 1;
								printf ("\n      DELETION COMPETED.\n");
								Enter2Retn ();
							}
							else
							{
								if (tmp == 0)
								{
									printf ("\n      DELETION CANCELLED.\n");
									Enter2Retn1 ();
									getchar ();
								}
								else
									ShowError (IN_ERR);
							}
						}
					}
					break;

				case TO_FILE: //TO_FILE was defined at MainFace.h functioning as an enum constant
					{
						if (phead->pnext == NULL)
						{
							ShowError (NO_RECORD);
							break;
						}
						wangluo2->SaveToFile (phead);
						save_flag = 0;
						printf ("\n      SAVE COMPLETED.\n");
						Enter2Retn ();
					}
					break;

				case SORT: //SORT was defined at MainFace.h functioning as an enum constant
					{
						int sort_type;
						if (phead->pnext == NULL)
						{
							ShowError (NO_RECORD);
							break;
						}
						//printf ("\n      UNSUPPORTED NOW!\n");
						ShowSubMenu (MENU_SORT);
						scanf ("%d", &sort_type);
						if (sort_type <1 || sort_type > 5)
						{
							ShowError (IN_ERR);
							break;
						}
						wangluo2->SSort (phead, sort_type);
						printf ("\n      SORT FINISHED.\n");
						save_flag = 1;
						Enter2Retn ();
					}
					break;

				case INQUIRE: //INQUIRE was defined at MainFace.h functioning as an enum constant
					{
						char in[32];
						PSTUDENT ps_tmp;
						if (phead->pnext == NULL)
						{
							ShowError (NO_RECORD);
							break;
						}
						printf ("\n      ENTER THE NUMBER OR NAME: ");
						getchar ();
						gets (in);
						if (IsNumStr (in))
							/*Inquire () searchs the designated record
							It was declared and defined respectively @ Manip.h and @ Manip.c*/
							ps_tmp = wangluo2->Inquire (phead, SEARCH_NUM, in);
						else
							ps_tmp = wangluo2->Inquire (phead, SEARCH_NAME, in);
						if (ps_tmp == NULL)
							ShowError (UNFOUND);
						else
						{
							/*Display () was declared and defined respectively @ Manip.h and @ Manip.c
							It shows all the record at one time
							It may not be good if there are too many records*/
							ps_tmp->DisplayInfoPs (ps_tmp);
							ps_tmp->DisplayGradePs (ps_tmp);
							Enter2Retn1 ();
						}
					}
					break;

				case MOD: //MOD was defined at MainFace.h functioning as an enum constant
					{
						int mod_type;
						char in[32];
						PSTUDENT ps_tmp;
						if (phead->pnext == NULL)
						{
							ShowError (NO_RECORD);
							break;
						}
						ShowSubMenu (MENU_MOD);
						scanf ("%d", &mod_type);
						if (mod_type == MOD_INFO || mod_type == MOD_GRADE)
							;
						else
						{
							ShowError (IN_ERR);
							break;
						}
						printf ("\n      ENTER THE NUMBER OR NAME: ");
						getchar ();
						gets (in);
						if (IsNumStr (in))
							/*Inquire () searchs the designated record
							It was declared and defined respectively @ Manip.h and @ Manip.c*/
							ps_tmp = wangluo2->Inquire (phead, SEARCH_NUM, in);
						else
							ps_tmp = wangluo2->Inquire (phead, SEARCH_NAME, in);
						if (ps_tmp == NULL)
							ShowError (UNFOUND);
						else
						{
							if (mod_type == MOD_INFO)
								ModifyInfo(ps_tmp, phead);
							else
								ps_tmp->ModifyGrade(ps_tmp);
						}
						save_flag = 1;
					}
					break;

				case DISP: //DISP was defined at MainFace.h functioning as an enum constant
					{
						/*DisplayGrade () was declared and defined respectively @ Manip.h and @ Manip.c
						It shows the GRADE struct of the appointed STUDENT struct*/
						int disp_type;
						if (phead->pnext == NULL)
						{
							ShowError (NO_RECORD);
							break;
						}
						ShowSubMenu (MENU_DISP);
						scanf ("%d", &disp_type);
						switch (disp_type)
						{
							case DISP_GRADE:
								{
									wangluo2->DisplayGrade (phead);
									Enter2Retn ();
								}
								break;
							case DISP_INFO:
								{
									wangluo2->DisplayInfo (phead);
									Enter2Retn ();
								}
								break;
							case DISP_ANALYZE:
								{
									wangluo2->AnalyzeGrade (phead);
									Enter2Retn ();
								}
								break;
							default: ShowError (IN_ERR); break;
						}
					}
					break;

				case QUIT: //QUIT was defined at MainFace.h functioning as an enum constant
					{
						char quit_flag;

						if (save_flag == 1)
							printf ("\n      THERE ARE SOME MODIFICATIONS MADE!\n");

						printf ("\n      YOU ARE GOING TO QUIT? (Y / N): ");
						getchar ();//Absorbs character @ buffer
						scanf ("%c", &quit_flag);
						if (quit_flag == 'Y' || quit_flag == 'y')
						{
							/*Destroy () was declared and defined respectively @ Manip.h and @ Manip.c
							It free the runtime allocated memory of INFO &GRADE for all the records in the list*/
							wangluo2->Destroy (phead);
							free (phead);
							free (wangluo2);

							printf ("\n      PRESS ENTER TO QUIT....");
							getchar ();
							getchar ();
							exit (EXIT_SUCCESS);
						}
						else
						{
							if (quit_flag == 'N' || quit_flag == 'n')
							{
								printf ("\n      QUIT CANCELLED.\n");
								Enter2Retn ();
							}
							else
								ShowError (IN_ERR);
						}
					 }
					break;

			}
		}
	}
	return EXIT_SUCCESS;
}

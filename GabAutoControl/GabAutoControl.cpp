// GabAutoControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "GabAutoControl.h"

#define MAXSTRINGLEN 255

//KEY keys[255];
KEY *keys = new KEY[255]; //allocate a buffer of KEYs

void mouseaction(DWORD flags, DWORD mouseData);
void doshit();

int main(int argc, char* argv[])
{
	char* target;
	char* action;
	char* param1;
	char* param2;
	char* syntax = "Syntax : gabac <target> <action> [<param1> [<param2> [...]]]";
	char* syntax2 = "Where <target> is :\n\nmouse\nkeyboard\nwait\n\nFor help about a specific target, type :\ngabac <target> --help";
	char* syntaxmouse = "Syntax : gabac mouse <action> [param1 [param2 [...]]]";
	char* syntaxmouse2 = "Where <action> is :\nmove <x> <y>\nclick <button>\nscroll <direction>";
	char* syntaxmousemove = "Syntax 1 : gabac mouse move <x> <y>";
	char* syntaxmousemove2 = "Where <x> and <y> represent the new cursor coordinates in the screen (x,y)";
	char* syntaxmouseclick = "Syntax 2 : gabac mouse click <button>";
	char* syntaxmouseclick2 = "Where <button> is :\nleft : left button\nmiddle : middle button\nright : right button";
	char* syntaxmousescroll = "Syntax 3 : gabac mouse scroll <direction> [<distance>]";
	char* syntaxmousescroll2 = "Where <direction> is :\nup\ndown\nleft\nright\nAnd where <distance> (optional) is the non-zero number of wheel clicks (default=500)";
	char* syntaxkeyboard = "Syntax 1 : gabac keyboard <sequence>";
	char* syntaxkeyboard2 = "Where <sequence> is a sequence of keyboard input codes.\nFor a list of all available keyboard input codes, type :\ngabac keyboard --verbose";
	char* syntaxwait = "Syntax 1 : gabac wait <duration>";
	char* syntaxwait2 = "Where <duration> is the non-zero number of milliseconds to wait";
	char* error;
	long l1;
	long l2;
	int rc = 0;
	

	size_t n;

	//if no arguments are passed, we display the syntax
	if( argc == 1 )
	{
		printf("%s\n%s\n", syntax, syntax2);
		return 0;
	}
	
	//target should not be larger than MAXSTRINGLEN (buffer overflow protection)
	n = strlen(argv[1]);
	if( n > MAXSTRINGLEN)
	{
		printf("<target> is too long !\n%s\n", syntax);
		return 1;
	}
	
	//we extract the actual target
	target = (char *)malloc(n + 1);
	strncpy(target, argv[1], n);
	target[n] = '\0';

	//we check which target we passed in argument
	if (strcmp(target, "help")==0) {
	   printf("%s\n%s\n", syntax, syntax2);
	} else if (strcmp(target, "/help")==0) {
	   printf("%s\n%s\n", syntax, syntax2);
	} else if (strcmp(target, "-help")==0) {
	   printf("%s\n%s\n", syntax, syntax2);
	} else if (strcmp(target, "--help")==0) {
	   printf("%s\n%s\n", syntax, syntax2);
	} else if (strcmp(target, "/?")==0) {
	   printf("%s\n%s\n", syntax, syntax2);
	} else if (strcmp(target, "-?")==0) {
	   printf("%s\n%s\n", syntax, syntax2);
   	} else if (strcmp(target, "mouse")==0) {
	   
		//if existing, action should not be larger than MAXSTRINGLEN (buffer overflow protection)
		if(argc >= 3)
		{
			n = strlen(argv[2]);
			if( n > MAXSTRINGLEN)
			{
				printf("<action> is too long !\n%s\n", syntaxmouse);
				rc = 11;
				goto zeend;
			}

			//we extract the actual action
			action = (char *)malloc(n + 1);
			strncpy(action, argv[2], n);
			action[n] = '\0';

			//we check which action we passed in argument
			if (strcmp(action, "--help")==0) {
			   printf("%s\n%s\n\n%s\n%s\n\n%s\n%s\n\n%s\n%s\n", syntaxmouse, syntaxmouse2, syntaxmousemove, syntaxmousemove2, syntaxmouseclick, syntaxmouseclick2, syntaxmousescroll, syntaxmousescroll2);
			} else if (strcmp(action, "move")==0) {
				
				//BEGIN MOUSE MOVE
				if (argc == 5)
				{
					//<x> parameter
					n = strlen(argv[3]);
					if( n > MAXSTRINGLEN)
					{
						printf("<x> is too long !\n%s\n%s\n", syntaxmousemove, syntaxmousemove2);
						rc = 111;
						free( action );
						goto zeend;
					}
					//we extract the <x> param
					param1 = (char *)malloc(n + 1);
					strncpy(param1, argv[3], n);
					param1[n] = '\0';

					//we check if it is a valid parameter
					l1 = strtol(param1, &error, 10);
					if (l1 == 0)
					{
						printf("<x> is not a valid integer !\n%s\n%s\n", syntaxmousemove, syntaxmousemove2);
						rc = 112;
						free( action );
						free( param1 );
						goto zeend;
					}


					//<y> parameter
					n = strlen(argv[4]);
					if( n > MAXSTRINGLEN)
					{
						printf("<y> is too long !\n%s\n%s\n", syntaxmousemove, syntaxmousemove2);
						rc = 113;
						free( action );
						goto zeend;
					}
					//we extract the <y> param
					param2 = (char *)malloc(n + 1);
					strncpy(param2, argv[4], n);
					param2[n] = '\0';

					//we check if it is a valid parameter
					l2 = strtol(param2, &error, 10);
					if (l2 == 0)
					{
						printf("<y> is not a valid integer !\n%s\n%s\n", syntaxmousemove, syntaxmousemove2);
						rc = 114;
						free( action );
						free( param2 );
						goto zeend;
					}

					//we send the new position of the mouse cursor !
					if( SetCursorPos( l1, l2 ) != 0 )
					{
						//there was an error
						rc = 115;
						free( param1 );
						free( param2 );
					}


				} else {
					printf("%s\n%s\n", syntaxmousemove, syntaxmousemove2);
				}
				//END MOUSE MOVE

			} else if (strcmp(action, "click")==0) {
			   
				//BEGIN MOUSE CLICK
				if (argc == 4)
				{
					//<button> parameter
					n = strlen(argv[3]);
					if( n > MAXSTRINGLEN)
					{
						printf("<button> is too long !\n%s\n%s\n", syntaxmouseclick, syntaxmouseclick2);
						rc = 121;
						free( action );
						goto zeend;
					}
					//we extract the <button> param
					param1 = (char *)malloc(n + 1);
					strncpy(param1, argv[3], n);
					param1[n] = '\0';

					//we check if it is a valid parameter
					if (strcmp(param1, "left")==0) {
					
						mouseaction(MOUSEEVENTF_LEFTDOWN, 0);
						mouseaction(MOUSEEVENTF_LEFTUP, 0);
						free( param1 );

					} else if (strcmp(param1, "middle")==0) {

						mouseaction(MOUSEEVENTF_MIDDLEDOWN, 0);
						mouseaction(MOUSEEVENTF_MIDDLEUP, 0);
						free( param1 );

					} else if (strcmp(param1, "right")==0) {

						mouseaction(MOUSEEVENTF_RIGHTDOWN, 0);
						mouseaction(MOUSEEVENTF_RIGHTUP, 0);
						free( param1 );

					} else {
						printf("%s\n%s\n", syntaxmouseclick, syntaxmouseclick2);
					}			

				} else {
					printf("%s\n%s\n", syntaxmouseclick, syntaxmouseclick2);
				}
				//END MOUSE CLICK

			} else if (strcmp(action, "scroll")==0) {
			   
				//BEGIN MOUSE SCROLL
				if (argc >= 4 && argc <= 5)
				{
					//<direction> parameter
					n = strlen(argv[3]);
					if( n > MAXSTRINGLEN)
					{
						printf("<direction> is too long !\n%s\n%s\n", syntaxmousescroll, syntaxmousescroll2);
						rc = 131;
						free( action );
						goto zeend;
					}
					//we extract the <direction> param
					param1 = (char *)malloc(n + 1);
					strncpy(param1, argv[3], n);
					param1[n] = '\0';

					if (argc == 5)
					{
						//<distance> parameter
						n = strlen(argv[4]);
						if( n > MAXSTRINGLEN)
						{
							printf("<distance> is too long !\n%s\n%s\n", syntaxmousescroll, syntaxmousescroll2);
							rc = 132;
							free( action );
							free( param1 );
							goto zeend;
						}
						//we extract the <direction> param
						param2 = (char *)malloc(n + 1);
						strncpy(param2, argv[4], n);
						param2[n] = '\0';

						l1 = strtol(param2, &error, 10);
						if (l1 == 0)
						{
							printf("<distance> is not a valid integer !\n%s\n%s\n", syntaxmousemove, syntaxmousemove2);
							rc = 133;
							free( action );
							free( param1 );
							free( param2 );
							goto zeend;
						}
						
					} else {
						l1 = 500; //default value = 500 wheel clicks. 1 wheel click = 120 twips
					}

					//we check if it is a valid parameter
					if (strcmp(param1, "up")==0) {
					
						mouseaction(MOUSEEVENTF_WHEEL, l1);
						free( param1 );

					} else if (strcmp(param1, "down")==0) {

						mouseaction(MOUSEEVENTF_WHEEL, l1 * -1);
						free( param1 );

					} else if (strcmp(param1, "left")==0) {

						mouseaction(MOUSEEVENTF_HWHEEL, l1 * -1);
						free( param1 );

					} else if (strcmp(param1, "right")==0) {

						mouseaction(MOUSEEVENTF_HWHEEL, l1);
						free( param1 );

					} else {
						printf("%s\n%s\n", syntaxmousescroll, syntaxmousescroll2);
					}
				} else {
					printf("%s\n%s\n", syntaxmousescroll, syntaxmousescroll2);
				}
				//END MOUSE SCROLL

			} else {
			   printf("%s\n%s\n", syntaxmouse, syntaxmouse2);
			}

			free( action );
		} else {
			printf("%s\n", syntaxmouse);
		}

	} else if (strcmp(target, "keyboard")==0) {


		//if existing, action should not be larger than MAXSTRINGLEN (buffer overflow protection)
		if(argc >= 3)
		{
			n = strlen(argv[2]);
			if( n > MAXSTRINGLEN)
			{
				printf("Sorry, <sequence> can not exceed %d characters.\n%s\n%s\n", MAXSTRINGLEN, syntaxkeyboard, syntaxkeyboard2);
				rc = 21;
				goto zeend;
			}

			if( argc > 3)
			{
				printf("Illegal <sequence> !\nCheck that your sequence is correct.\nIt should not contain any space and every opening bracket '{'\nshould have its corresponding closing bracket '}'\n");
				rc = 22;
				goto zeend;
			}

			//we extract the actual action
			action = (char *)malloc(n + 1);
			strncpy(action, argv[2], n);
			action[n] = '\0';

			//we check which action we passed in argument
			if (strcmp(action, "--help")==0) {
			   printf("%s\n%s\n", syntaxkeyboard, syntaxkeyboard2);
			} else if (strcmp(action, "--verbose")==0) {
				printf("TODO : A lot of stuff to write here.\n");
			} else {
				
				printf("NOT IMPLEMENTED\n");
				doshit();
			}
		} else {
			printf("%s\n", syntaxkeyboard);
		}


	} else if (strcmp(target, "wait")==0) {

		//if existing, action should not be larger than MAXSTRINGLEN (buffer overflow protection)
		if(argc >= 3)
		{
			n = strlen(argv[2]);
			if( n > MAXSTRINGLEN)
			{
				printf("<action> is too long !\n%s\n", syntaxwait);
				rc = 31;
				goto zeend;
			}

			//we extract the actual action
			action = (char *)malloc(n + 1);
			strncpy(action, argv[2], n);
			action[n] = '\0';

			//we check which action we passed in argument
			if (strcmp(action, "--help")==0) {
			   printf("%s\n%s\n", syntaxwait, syntaxwait2);
			} else {
				l1 = abs(strtol(action, &error, 10));
				if (l1==0)
				{
					printf("%s\n%s\n", syntaxwait, syntaxwait2);
					rc = 32;
					free( action );
				} else {
					Sleep(l1);
				}

			}
		} else {
			printf("%s\n", syntaxwait);
		}

	} else {
	   printf("%s\n%s\n", syntax, syntax2);
	}




zeend:



	//INPUT *buffer = new INPUT[3]; //allocate a buffer
	//int X;
	//int Y;
	//X = 100;
	//Y = 100;

	//buffer->type = INPUT_MOUSE;
	//buffer->mi.dx = 190*65535/ix;
	//buffer->mi.dy = 100*65535/iy;
	//buffer->mi.mouseData = 0;
	//buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
	//buffer->mi.time = 0;
	//buffer->mi.dwExtraInfo = 0;

	//(buffer+1)->type = INPUT_MOUSE;
	//(buffer+1)->mi.dx = 100;
	//(buffer+1)->mi.dy = 100;
	//(buffer+1)->mi.mouseData = 0;
	//(buffer+1)->mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	//(buffer+1)->mi.time = 0;
	//(buffer+1)->mi.dwExtraInfo = 0;

	//(buffer+2)->type = INPUT_MOUSE;
	//(buffer+2)->mi.dx = 100;
	//(buffer+2)->mi.dy = 100;
	//(buffer+2)->mi.mouseData = 0;
	//(buffer+2)->mi.dwFlags = MOUSEEVENTF_LEFTUP;
	//(buffer+2)->mi.time = 0;
	//(buffer+2)->mi.dwExtraInfo = 0;


	//SetCursorPos(X,Y);

	//SendInput(3,buffer,sizeof(INPUT));

	//delete (buffer); //clean up our messes.

	free( target );

	delete (keys);

	return 0;
}

void mouseaction(DWORD flags, DWORD mouseData = 0)
{
	INPUT *buffer = new INPUT[1]; //allocate a buffer
	POINT pt;

	GetCursorPos(&pt); // retrieves the location of the mouse cursor

	(buffer)->type = INPUT_MOUSE;
	(buffer)->mi.dx = pt.x;
	(buffer)->mi.dy = pt.y;
	(buffer)->mi.mouseData = mouseData;
	(buffer)->mi.dwFlags = flags;
	(buffer)->mi.time = 0;
	(buffer)->mi.dwExtraInfo = 0;

	SendInput(1, buffer, sizeof(INPUT));

	delete (buffer); //clean up our messes.
}

void doshit()
{
	//assign pairs of VKEY and their representation.
	(keys+0)->vkey = VK_LBUTTON;
	(keys+0)->repr = "{LBUTTON}";

	(keys+1)->vkey = VK_RBUTTON;
	(keys+1)->repr = "{RBUTTON}";

	(keys+2)->vkey = VK_CANCEL;
	(keys+2)->repr = "{CANCEL}";

	(keys+3)->vkey = VK_MBUTTON;
	(keys+3)->repr = "{MBUTTON}";

	(keys+4)->vkey = VK_XBUTTON1;
	(keys+4)->repr = "{XBUTTON1}";

	(keys+5)->vkey = VK_XBUTTON2;
	(keys+5)->repr = "{XBUTTON2}";

	(keys+6)->vkey = VK_BACK;
	(keys+6)->repr = "{BACK}";

	(keys+7)->vkey = VK_TAB;
	(keys+7)->repr = "{TAB}";

	(keys+8)->vkey = VK_CLEAR;
	(keys+8)->repr = "{CLEAR}";

	//TODO : finish this
}

int parsesequence( char* sequence)
{
	return 0;
}
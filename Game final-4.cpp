#include <iostream>
#include <math.h>
#include <windows.h>
#include <stdio.h> 
#include <unistd.h>
#include <iomanip>
#include <string>
#include <ctype.h>
#include <winuser.h>
#include <conio.h>
#include <cstdlib>
#include<algorithm>
#include "time.h"

using namespace std;

//to used for goto
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
COORD CursorPosition; // used for goto
//to set up the font colour and size in console
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); 
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

//declaring global variable
bool endgame = false;
int userInput,userInput1,userInput2,PlayerCount,Force,Rand,gamespeed = 180;
float Velocity,VelocityF,Coe,CoeWood=0.2,CoePine=0.5,CoeMaple=0.7;
string PlayerName;
int Compare[100];
string PlayerNameArray[100];

char Map01[20][67] =
{
	"                       ____________________________________",
	"                       |                                  |",
	"                       |              0 0 0 0             |",
	"                       |               0 0 0              |",
	"                       |                0 0               |",
	"                       |                 0                |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                 W                |",
	"                       |__________________________________|",
};

// to change the font size
void fontSize(int a, int b) 
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;
	lpConsoleCurrentFontEx->dwFontSize.Y = b;
	SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}

// to set up console resoluation
void consoleResolution();
//To make interative
void gotoXY(int,int);
//designing starting screen
void startScreen ();
//designing header 
void header();
//Starting sound
void sound();
//Loading
void load();
//Gaming panel-Single Player
void gameSingle();
//Gaming panel-Multi Player
void gameMulti();
//Inputs
void Inputs1();
void Inputs2();
//Input error
void error();
//end
void thank();
//welcome screen
void welcome();
//endscreen
void endScreen();
//instruction
void instructions();

VOID WINAPI SetConsoleColors(WORD attribs) 
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hOutput, &cbi);
	cbi.wAttributes = attribs;
	SetConsoleScreenBufferInfoEx(hOutput, &cbi);
}

int main()
{
	startScreen();
	
	set1:
		
	cout<<endl;
	fontSize(20, 20); 
	
	consoleResolution();
	
	header();
	
	while (!((userInput == 1) || (userInput ==2) || (userInput == 3)))
	{
		system("cls");
		error();
		Sleep(3000);
		system("cls");
		header();
		goto set1;			
	}

	switch(userInput)
	{
		case 1:
		{
 			load();
 			
			system("cls");
			
			welcome();
			
			if (userInput1==1)
			{
				Inputs2();
				gameSingle ();
			}
			if (userInput1==2)
			{
				gameMulti();
			}
			
			break;
		}
		
		case 2:
		{
			load();
			
			system("cls");
			
			SetConsoleTextAttribute(color, 7);
 			fontSize(20, 20);
			 	
			instructions();
			
			SetConsoleTextAttribute(color, 6);
			cout<<"\n\n";
			
			cout<<"Press R to Return to main menu : "<<endl;
			
			char k;
			cin>>k;
				
			while(!((k == 'R') || (k == 'r')))
			{
				cout<<"                 Error!!!  Invalid Input\n"<<endl;
				cout<<"                 Try again\n"<<endl;
				cout<<"                 Press R : "<<endl;
				cin>>k;
			}
				
			system("cls");
			goto set1;	
		}
				
		case 3:
		{
			system("cls");
			
			thank();
			
			Sleep(2000);
			system("cls");
			system("pause");
		}		
	}
}

void consoleResolution()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); // obtain console's initial dimensions
	MoveWindow(console, r.left, r.top, 1920, 1080, TRUE); // set the console to full HD
}

void startScreen()
{
	fontSize(90, 90);
	SetConsoleTextAttribute(color, 3);
	
	cout<<"\n\n\n\n              BOWLING";
	sound();
	
	Sleep(3000);
	system("cls");
	
	Inputs1();
	
	if (userInput1==1)
	{
		system("cls");
		fontSize(50, 50);
		
		cout<<"\n\n\n\n\n\tEnter Your Name To Begin:";
		cin>>PlayerName;
		
		system("cls");
		fontSize(90, 90);
		
		cout<<"\n\n\n\tWelcome "<<PlayerName;
		
		cin.clear();
		Sleep(3000);
		system("cls");
	}
	
	if (userInput1==2)
	{
		system("cls");
		fontSize(50, 50);
		
		cout<<"\n\n\n\n\n\tEnter the number of players:";
		cin>>PlayerCount;
		
		system("cls");
		
		for (int i=0;i<PlayerCount;i++)
		{
			SetConsoleTextAttribute(color, 6);
			cout<<"\n\n\n\tEnter the name of the "<<i+1<<" Player:";
			cin>>PlayerNameArray[i];
		}
		
		system("cls");
		fontSize(40, 40);
		
		for (int i=0;i<PlayerCount;i++)
		{
			SetConsoleTextAttribute(color, 1);
			fontSize(100, 100);
			cout<<"\n\n\n\tWelcome  "<<PlayerNameArray[i]<<endl;
			Sleep(1000);
			system("cls");
		}
		fontSize(30, 30);
		cin.clear();
		//Sleep(3000);
		//system("cls");
	}	
}

void sound()
{
	Beep(523,500);  // 523 hertz (C5) for 500 milliseconds
 	Beep(587,500);
 	Beep(659,500);
 	Beep(698,500);
	Beep(784,500);
}

void header()
{
	fontSize(40, 40);
	SetConsoleTextAttribute(color, 11);
	
	cout<<" _______________________________________________________________________________________________________\n";
	cout<<"|                                                                                                       |\n";
	cout<<"|                                          BOWLING GAME CONSOLE                                         |\n";
	cout<<"|_______________________________________________________________________________________________________|\n";
	cout<<endl;
	
	SetConsoleTextAttribute(color, 4);
	
	int menu_item=0, run, x=12;
	bool running = true;
	
	fontSize(40, 40);
	
	gotoXY(43,10); cout << "Main Menu";
	fontSize(40, 40);
	SetConsoleTextAttribute(color, 6);
	gotoXY(40,12); cout << "->";
	
	while(running)
	{
        SetConsoleTextAttribute(color, 2);
		gotoXY(42,12);  cout << "Start the Game";
		
		SetConsoleTextAttribute(color, 5);
		gotoXY(42,13);  cout << "Instructions";
		
		SetConsoleTextAttribute(color, 7);
		gotoXY(42,14);  cout << "Exit";

		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 14) //down button pressed
		{
			gotoXY(40,x); cout << "  ";
			x++;
			
			SetConsoleTextAttribute(color, 6);
			gotoXY(40,x); cout << "->";
			
			menu_item++;
			continue;		
		}
			
		if(GetAsyncKeyState(VK_UP) && x != 12) //up button pressed
		{
			gotoXY(40,x); cout << "  ";
			x--;
			
			SetConsoleTextAttribute(color, 6);
			gotoXY(40,x); cout << "->";
			
			menu_item--;
			continue;
		}
			
		if(GetAsyncKeyState(VK_RETURN))// Enter key pressed
		{ 	
			switch(menu_item)
			{	
			case 0: 
			{	
				gotoXY(20,16);
				userInput=1;
				running = false;
				break;
			}				
			case 1: 
			{
				gotoXY(20,16);
				userInput=2;
				running = false;
				break;
			}		
			case 2: 
			{
				gotoXY(20,16);
				userInput=3;
				running = false;
				break;
			}	
			}		
		}		
	}
	gotoXY(20,21);
	SetConsoleTextAttribute(color, 7);
	cout<<"_________________________________________________________________________________________________________\n";
}

void gotoXY(int x, int y) 
{ 
	CursorPosition.X = x; 
	CursorPosition.Y = y; 
	SetConsoleCursorPosition(console,CursorPosition); 
}

void Inputs1()
{
	int menu_item=0, run, x=12;
	bool running = true;
	
	fontSize(40, 40);
	SetConsoleTextAttribute(color, 4);
	gotoXY(43,10); cout << "Select the Mode";
	
	fontSize(40, 40);
	
	SetConsoleTextAttribute(color, 6);
	gotoXY(40,12); cout << "->";
	
	while(running)
	{
        SetConsoleTextAttribute(color, 2);
		gotoXY(42,12);  cout << "Sigle-Player Mode";
		SetConsoleTextAttribute(color, 5);
		gotoXY(42,13);  cout << "Multiplayer Mode";

		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 13) //down button pressed
		{
			gotoXY(40,x); cout << "  ";
			x++;
			
			SetConsoleTextAttribute(color, 6);
			gotoXY(40,x); cout << "->";
			
			menu_item++;
			continue;		
		}
			
		if(GetAsyncKeyState(VK_UP) && x != 12) //up button pressed
		{
			gotoXY(40,x); cout << "  ";
			x--;
			
			SetConsoleTextAttribute(color, 6);
			gotoXY(40,x); cout << "->";
			
			menu_item--;
			continue;
		}
			
		if(GetAsyncKeyState(VK_RETURN)) // Enter key pressed
		{ 	
			switch(menu_item)
			{	
			case 0: 
			{	
				gotoXY(20,16);
				userInput1=1;
				running = false;
				break;
			}				
			case 1: 
			{
				gotoXY(20,16);
				userInput1=2;
				running = false;
				break;
			}		
			case 2: 
			{
				gotoXY(20,16);
				userInput1=3;
				running = false;
				break;
			}	
			}		
		}		
	}
	gotoXY(20,21);
	
}
void Inputs2()
{
	int menu_item=0, run, x=6;
	bool running = true;
	
	fontSize(40, 40);
	SetConsoleTextAttribute(color, 4);
	gotoXY(42,4); cout << "Choose a Floor";
	fontSize(40, 40);
	SetConsoleTextAttribute(color, 6);
	gotoXY(40,6); cout << "->";
	
	while(running)
	{
        SetConsoleTextAttribute(color, 2);
		gotoXY(42,6);  cout << "Pine Floor";
		SetConsoleTextAttribute(color, 5);
		gotoXY(42,7);  cout << "Maple Floor";
		SetConsoleTextAttribute(color, 7);
		gotoXY(42,8);  cout << "Synthetic Floor";

		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 8) //down button pressed
		{
			gotoXY(40,x); cout << "  ";
			x++;
			
			SetConsoleTextAttribute(color, 6);
			gotoXY(40,x); cout << "->";
			
			menu_item++;
			continue;		
		}
			
		if(GetAsyncKeyState(VK_UP) && x != 6) //up button pressed
		{
			gotoXY(40,x); cout << "  ";
			x--;
			
			SetConsoleTextAttribute(color, 6);
			gotoXY(40,x); cout << "->";
			
			menu_item--;
			continue;
		}
			
		if(GetAsyncKeyState(VK_RETURN))// Enter key pressed
		{ 	
			switch(menu_item)
			{		
			case 0: 
			{	
				gotoXY(20,10);
				userInput2=1;
				Coe=CoePine;
				cout<<"Enter the force that you are going to apply:";
				cin>>Force;
				gotoXY(20,12);
				cout<<"Enter the initial velocity:";
				cin>>Velocity;
				running = false;
				break;
			}				
			case 1: 
			{
				gotoXY(20,10);
				userInput2=2;
				Coe=CoeMaple;
				cout<<"Enter the force that you are going to apply:";
				cin>>Force;
				gotoXY(20,12);
				cout<<"Enter the initial velocity:";
				cin>>Velocity;
				running = false;
				break;
			}		
			case 2: 
			{
				gotoXY(20,10);
				userInput2=3;
				Coe=CoeWood;
				cout<<"Enter the force that you are going to apply:";
				cin>>Force;
				gotoXY(20,12);
				cout<<"Enter the initial velocity:";
				cin>>Velocity;
				running = false;
				break;
			}	
			}		
		}		
	}
	gotoXY(20,21);
	
}

void welcome()
{
	system("cls");
	fontSize(30, 30);
	SetConsoleTextAttribute(color, 14);
	cout<<"\n\n\n\n\n\n\n";
	
	cout<<" _______________________________________________________________________________________________________\n";
	cout<<"|                                                                                                       |\n";
	cout<<"|                                    WELCOME TO BOWLING GAME PLATFORM                                   |\n";
	cout<<"|_______________________________________________________________________________________________________|\n";
	cout<<endl;
	
	Sleep(3000);
	system("cls");
}

void gameSingle()
{
	fontSize(30, 30);
	VelocityF=pow((pow(Velocity,2)+(2*(Force-(Coe*0.5*9.81))/0.5)*10),0.5);
	Rand=rand()%int(VelocityF);
	while(Rand>=10)
	{
		Rand/=10;
	}
	Rand=(Rand/2) +2;
	
	int Remaining=3,GamePoints=0;
	
	SetConsoleTextAttribute(color, 7);
	
	for (int m=0; m<35; m++)
	{
		cout<<Map01[m]<<endl;
	}
		
	while (endgame == false) 
	{	
		system("cls");
		
		for (int y = 0; y < 20; y++) 
		{
			cout <<"                    " <<Map01[y] << endl;
		}		

		for (int y = 0; y < 20; y++) 
		{
			for (int x = 0; x < 67; x++) 
			{
				switch (Map01[y][x]) 
				{		
				case 'W':

				if (GetAsyncKeyState(VK_LEFT) != 0) 
				{
					Sleep(50);
					int newX = x - 1;

					switch (Map01[y][newX]) 
					{

						case ' ':
						Map01[y][x] = ' ';
						x--;
						Map01[y][newX] = 'W';

						break;

					}
				}

				if (GetAsyncKeyState(VK_RIGHT) != 0) 
				{
					Sleep(50);
					int newX = x + 1;

					switch (Map01[y][newX]) 
					{

						case ' ':
						Map01[y][x] = ' ';
						x++;
						Map01[y][newX] = 'W';

						break;
					}
				}

				if (GetAsyncKeyState(VK_SPACE) != 0) 
				{
					Sleep(20);
					y--;
					Map01[y][x] = 'O';
					Remaining=Remaining-1;
				}

				break;

				case 'O':

				Map01[y][x] = ' ';
				y--;

				if (Map01[y][x] != '0' && Map01[y][x] != '_') 
				{
					Map01[y][x] = 'O';
				}
				
				else if (Map01[y][x] == '0') 
				{
					Map01[y][x] = ' ';
	
					for (int i=1;i<Rand;i++)
					{
						if (Map01[y-i][x-i] == '0')
						{
							Map01[y-i][x-i] = ' ';
							GamePoints=GamePoints+1;
						}
						if (Map01[y-i][x+i]=='0')
						{
							Map01[y-i][x+i] = ' ';
							GamePoints=GamePoints+1;
						}
						
					}
					
					GamePoints=GamePoints+1;
					cout << "\a";
				}
				break;	
				}
			}
		}
		SetConsoleTextAttribute(color, 11);
		cout << "\n			    Total Points  "; SetConsoleTextAttribute(color, 2);cout << GamePoints; SetConsoleTextAttribute(color, 11); cout << " / 10" << endl;
		
		SetConsoleTextAttribute(color, 11);
		cout << "			    Remaining        "; SetConsoleTextAttribute(color, 4);cout << Remaining; SetConsoleTextAttribute(color, 11); cout << " /3 " ;
		
		time_t t = time(NULL);
	    tm* tPtr = localtime(&t);
		cout << "\n\n  Current Date	: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 ;
		cout << "                       Current Time	: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << ":" << (tPtr->tm_sec) << endl;
		
		if (Remaining<0)
		{
			endgame = true;
		}
		
		if (GamePoints==10)
		{
			endgame = true;
		}
		
		endgame==true;
		
		Sleep(500);
	}
	
	Sleep(gamespeed);
	system("cls");
	cout<<"Player name: "<<PlayerName <<"\t\tTotal Points:"<<GamePoints <<endl;
	Sleep(2000);
	system("cls");
	if (GamePoints==10)
	{
		fontSize(90, 90);
		SetConsoleTextAttribute(color, 7);
		cout<<"CONGRATULATIONS "<< PlayerName<<endl;
		Sleep(2000);
	}
	else
	{
		fontSize(90, 90);
		SetConsoleTextAttribute(color, 7);
		cout<<"NICE TRY! "<< PlayerName <<endl;
	}
	thank();
	system("PAUSE");
}

void gameMulti()
{
	fontSize(30, 30);
	for (int i=0;i<PlayerCount;i++)
	{
	fontSize(60, 60);

	cout<<"\n\n\n                 Your turn  "<<PlayerNameArray[i]<<endl;
	Sleep(2000);
	system("cls");
	
	Inputs2();
	fontSize(30, 30);
	VelocityF=pow((pow(Velocity,2)+(2*(Force-(Coe*0.5*9.81))/0.5)*10),0.5);
	Rand=rand()%int(VelocityF);
	while(Rand>=10)
	{
		Rand/=10;
	}
	Rand=(Rand/2) +2;
	
	char Map01[20][67] =
	{
	"                       ____________________________________",
	"                       |                                  |",
	"                       |              0 0 0 0             |",
	"                       |               0 0 0              |",
	"                       |                0 0               |",
	"                       |                 0                |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                                  |",
	"                       |                 W                |",
	"                       |__________________________________|",
	};
			
	endgame = false;
	
	int Remaining=3,GamePoints=0;
	
	SetConsoleTextAttribute(color, 7);
	
	for (int m=0; m<35; m++)
	{
		cout<<Map01[m]<<endl;
	}
		
	while (endgame == false) 
	{	
		system("cls");
		
		for (int y = 0; y < 20; y++) 
		{
			cout <<"                    " <<Map01[y] << endl;
		}		

		for (int y = 0; y < 20; y++) 
		{
			for (int x = 0; x < 67; x++) 
			{
				switch (Map01[y][x]) 
				{		
				case 'W':

				if (GetAsyncKeyState(VK_LEFT) != 0) 
				{
					Sleep(50);
					int newX = x - 1;

					switch (Map01[y][newX]) 
					{
						case ' ':
						Map01[y][x] = ' ';
						x--;
						Map01[y][newX] = 'W';

						break;
					}
				}

				if (GetAsyncKeyState(VK_RIGHT) != 0) 
				{
					Sleep(50);
					int newX = x + 1;

					switch (Map01[y][newX]) 
					{
						case ' ':
						Map01[y][x] = ' ';
						x++;
						Map01[y][newX] = 'W';

						break;
					}
				}

				if (GetAsyncKeyState(VK_SPACE) != 0) 
				{
					Sleep(20);
					y--;
					Map01[y][x] = 'O';
					Remaining=Remaining-1;
				}

				break;

				case 'O':

				Map01[y][x] = ' ';
				y--;

				if (Map01[y][x] != '0' && Map01[y][x] != '_') 
				{
					Map01[y][x] = 'O';
				}
				
				else if (Map01[y][x] == '0') 
				{
					Map01[y][x] = ' ';
					
					for (int i=1;i<Rand;i++)
					{
						if (Map01[y-i][x-i] == '0')
						{
							Map01[y-i][x-i] = ' ';
							GamePoints=GamePoints+1;
						}
						if (Map01[y-i][x+i]=='0')
						{
							Map01[y-i][x+i] = ' ';
							GamePoints=GamePoints+1;
						}	
					}
					
					GamePoints=GamePoints+1;
					cout << "\a";
				}
				break;	
				}
			}
		}
		
		SetConsoleTextAttribute(color, 11);
		cout <<"\nPlayerName:"<< PlayerNameArray[i]<<"\t			    Total Points  "; SetConsoleTextAttribute(color, 2);cout << GamePoints; SetConsoleTextAttribute(color, 11); cout << " / 10" << endl;
		
		SetConsoleTextAttribute(color, 11);
		cout << "\t\t			    Remaining        "; SetConsoleTextAttribute(color, 4);cout << Remaining; SetConsoleTextAttribute(color, 11); cout << " /3 " ;
		
		if (Remaining<0)
		{
			endgame = true;
		}
		
		if (GamePoints==10)
		{
			endgame = true;
		}
		
		endgame==true;
		Sleep(500);
	}
	
	Sleep(gamespeed);
	system("cls");

	Compare[i]=GamePoints;    // COMPARING THE HIGHEST
	}
	fontSize(50, 50);
	SetConsoleTextAttribute(color, 6);
	cout<<"Final Results"<<endl;
	
	for (int i=0;i<PlayerCount;i++)
	{
		
		cout<<"Player name: "<<PlayerNameArray[i] <<"\t\tTotal Points:"<<Compare[i] <<endl;
		cout<<endl;
	}
	Sleep(2000);
	//int Win=max_element(Compare,Compare+PlayerCount)-Compare;
	system("cls");
	fontSize(80, 80);
	SetConsoleTextAttribute(color, 5);
	//cout<<"\n\n\n\tCONGRATULATIONS "<< PlayerNameArray[Win]<<endl;
	
	int Win= 0;
	
	for (int i = 0; i < PlayerCount; i++)
    {
        if (Compare[Win] < Compare[i])
        {
            Win = i;
        }
    }
    
    for (int i = 0; i < PlayerCount; i++)
	{
    	if (Compare[Win] == Compare[i]) //compare which indexes have the same value
    	{
        	cout<<"\n\n\n\tCONGRATULATIONS "<< PlayerNameArray[i]<<endl; //print all positions that have max value
    	}
	}
	
	
	Sleep(2000);
	thank();
	fontSize(30, 30);
}

void error()
{
	fontSize(30, 30);
	SetConsoleTextAttribute(color, 8);
	cout<<"\n\n\n\n";
	cout<<"                  ERROR!!! Invalid Input\n\n";
	cout<<"                  Try Again";
	Sleep(3000);
	system("cls");
}

void instructions()
{
	fontSize(30, 30);
	SetConsoleTextAttribute(color, 15);
	cout<<" _______________________________________________________________________________________________________\n";
	cout<<"|                                                                                                       |\n";
	cout<<"|                                             INSTRUCTIONS                                              |\n";
	cout<<"|_______________________________________________________________________________________________________|\n";
	
	SetConsoleTextAttribute(color, 2);
	
	cout<<"\n\n\n*All selections can done using the arrow keys.\n\n";
	cout<<"*User has to select Single Player Mode or Multi Player Mode.\n\n";
	cout<<"*In single player mode the person who drops all the cones will win the game.\n\n";
	cout<<"*In multiplayer mode the one who get the higest points will win.\n\n";
	cout<<"*Amount of dropped cones will be based on the the final velocity.\n\n";
	cout<<"*Points will calculate propotionally to the dropped cones.\n\n";
	cout<<"*User has to select the floor and Force.\n\n";
	cout<<"*User can move the ball side ways at the begining by using arrow keys.\n\n";
	cout<<"*Player can shoot the ball by pressing Space Bar.\n\n";
	
	cout<<endl;
}

void load()
{
	int i = 0; 
 	char load[26]; 
 				
 	while(i < 25) 
 	{ 
 		system("cls"); 
		fontSize(50, 50);
		SetConsoleTextAttribute(color, 2);
 		cout<<"\n\n\n\n\n\n";
 		
 		load[i++] = '>'; 
 		load[i] = '\0';
 		cout<<"\n"; 
		printf("\t\t                        Loading..."); 
  		printf("\n\n                                 %-25s", load); 
 		usleep(100000); 
 	} 
}
void thank()
{
	fontSize(30, 30);
	SetConsoleTextAttribute(color, 5);
	cout<<"\n\n\n\n\n";
	
	cout<<" _______________________________________________________________________________________________________\n";
	cout<<"|                                                                                                       |\n";
	cout<<"|                                             SEE YOU AGAIN                                             |\n";
	cout<<"|_______________________________________________________________________________________________________|\n";
	cout<<endl;
}

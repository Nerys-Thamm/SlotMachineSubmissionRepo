// Slots - Nerys (Bryn) Thamm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <string>

using namespace std;

string Indent = "||                  "; //String prefixed to other strings to indent them when being printed to console

void gotoxy(int x, int y) //Function to set the console cursor to specified xy coordinates
{
	COORD coords = { x,y };//Creates new COORD with x and y specified by parameters
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);//Gets the output handler and coordinates and use them to set the cursor position
}

void NewInputPrompt(string _prompt)//Used to create a menu prompt, parameter is the message displayed by the prompt
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//Sets console text colour to white //Sets text colour to white
	gotoxy(74, 14);//sets cursor coordinates
	cout << "______________________________________________";//print to console, overwrites any text that may be there
	gotoxy(74, 14);//sets cursor coordinates
	cout << _prompt;//prints prompt to console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow//resets text colour to yellow
}

class SlotMachine
{
public:
	float Credit = 2000.0f;//stores player credit
	float betAmount;//stores the current bet the player is making
	int slotArr[3];//int array stores result of slot spin
	int Jackpot[3] = { 7, 7, 7 };//stores results for jackpot, for comparison to actual result to find jackpots

	bool checkJackpot(int inpArr[])//function to check result for being a jackpot
	{
		return (inpArr[0] == Jackpot[0] && inpArr[1] == Jackpot[1] && inpArr[2] == Jackpot[2]);//returns true if indexes 0 1 2 of inpArr and Jackpot are the same
	}
	bool checkTriples(int inpArr[])//check if results is triples
	{
		return (inpArr[0] == inpArr[1] && inpArr[0] == inpArr[2] && inpArr[0] != 7);//returns true if all are the same, but not 7
	}
	bool checkDoubles(int inpArr[])//check if the result is 'doubles'
	{
		return ((inpArr[0] == inpArr[1]) || (inpArr[0] == inpArr[2]) || (inpArr[1] == inpArr[2]));//check if 2 but not 3 numbers of the result are the same
	}
	bool validateInput(float input)//used to validate user bets
	{
		return (input >= 0.01f && input <= Credit);//returns true if the bet is 1 cent or greater, and equal to or lesser than the players credit
	}

	void Spin(int slot1, int slot2, int slot3)//takes three integers as param
	{
		slotArr[0] = slot1;//Sets first index in slotArr to the 1st param... 
		slotArr[1] = slot2;
		slotArr[2] = slot3;
	}

	bool Bet(float _betAmount)//responsible for handling player bets
	{
		if (validateInput(_betAmount))//checks validity of bet
		{
			betAmount = _betAmount;//sets betAmount to param
			Credit -= betAmount;//removes bet amount from player credit
			return true;//returns true
		}
		else
		{
			NewInputPrompt("-{ Invalid Bet! Please try again: >");//prints to console
			cin.clear();//clears buffer
			cin.ignore(1000, '\n');
			return false;//returns false
		}
	}

	void Play()//method responsible for generating final result and calculating win states
	{
		Spin(rand() % (6) + 2, rand() % (6) + 2, rand() % (6) + 2);//generates 3 random numbers between 2 and 7 inclusive and passes to Spin()
		gotoxy(0, 25);//moves cursor

		if (checkJackpot(slotArr))//checks if result is a jackpot
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);//sets colour
			betAmount *= 10.0f;//multiplies player bet by 10 
			cout << Indent << "  _    __    __    _     ___   ___  _____  __ " << 
			endl << Indent << " | |  / /\\  / /`  | |_/ | |_) / / \\  | |  |_/ " << 
			endl << Indent << "\_|_| /_/--\\ \\_\\_, |_| \\ |_|   \\_\\_/  |_|  (_) \n";//prints to console the "Jackpot" notification
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
		}
		else if (checkTriples(slotArr))//if not, checks if result is triples
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);//sets colour
			betAmount *= 5.0f;//multiplies player bet by 5
			cout << Indent << "_____  ___   _   ___   _     ____  __   __ " << 
			endl << Indent << " | |  | |_) | | | |_) | |   | |_  ( (` |_/ " << 
			endl << Indent << " |_|  |_| \\ |_| |_|   |_|__ |_|__ _)_) (_) \n";//prints to console the "Triples" notification
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
		}
		else if (checkDoubles(slotArr))//if not, checks if result is doubles
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);//sets colour
			betAmount *= 3.0f;//multiplies player bet by 3
			cout << Indent << " ___   ___   _     ___   _     ____  __   __ " << 
			endl << Indent << "| | \\ / / \\ | | | | |_) | |   | |_  ( (` |_/ " << 
			endl << Indent << "|_|_/ \\_\\_/ \\_\\_/ |_|_) |_|__ |_|__ _)_) (_) \n";//prints to console the "Doubles" notification
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
		}
		else//if not, do this
		{
			betAmount = 0.0f;//sets player bet to 0 as they have lost
			cout << Indent << "                                             " << 
			endl << Indent << "                                               " << 
			endl << Indent << "                                                    ";//primts blank lines to console
		}
		Credit += betAmount;//adds the respective bet amount back to the players credit
	}
	void DisplayTitle()//method to display the title
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
		cout << "\n||                    /$$$$$$  /$$             /$$                        =========================\n||                   /$$__  $$| $$            | $$                        || Your Credit is: $" << Credit
		<< "        \n||                  | $$  \\__/| $$  /$$$$$$  /$$$$$$   /$$$$$$$           =========================\n||                  |  $$$$$$ | $$ /$$__  $$|_  $$_/  /$$_____/\n||                   \\____  $$| $$| $$  \\ $$  | $$   |  $$$$$$ \n||                   /$$  \\ $$| $$| $$  | $$  | $$ /$$\\____  $$\n||                  |  $$$$$$/| $$|  $$$$$$/  |  $$$$//$$$$$$$/\n||                   \\______/ |__/ \\______/    \\___/ |_______/ \n";
		cout << "||                  -By Nerys" << endl << Indent << endl << Indent << endl << Indent << endl;//Prints to console the title, the players current credit.
	}
	void DisplayNum(int _pos, int _num)//displays a textart number in one of 3 positions in the slot machine art
	{
		int Xpos;//integer variable storing the x coordinate value to draw the number art at
		switch (_pos)//switch case for position param
		{
		case 1:
			Xpos = 25;
			break;
		case 2:
			Xpos = 39;
			break;
		case 3:
			Xpos = 53;
			break;
		}
		switch (_num)//switch case for number param, this decides which textart to print depending on what number is provided in the param
		{
		case 2:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
			gotoxy(Xpos, 15);
			cout << "  ___    ";
			gotoxy(Xpos, 16);
			cout << " |_  )   ";
			gotoxy(Xpos, 17);
			cout << "  / /  ";
			gotoxy(Xpos, 18);
			cout << " /___|";//prints the textart 2
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
			break;
		case 3:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			gotoxy(Xpos, 15);
			cout << "  ____   ";
			gotoxy(Xpos, 16);
			cout << " |__ /   ";
			gotoxy(Xpos, 17);
			cout << "  |_ \\ ";
			gotoxy(Xpos, 18);
			cout << " |___/";//prints the textart 3
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
			break;

		case 4:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			gotoxy(Xpos, 15);
			cout << "  _ _    ";
			gotoxy(Xpos, 16);
			cout << " | | |   ";
			gotoxy(Xpos, 17);
			cout << " |_  _| ";
			gotoxy(Xpos, 18);
			cout << "   |_| ";//prints the textart 4
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
			break;

		case 5:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			gotoxy(Xpos, 15);
			cout << "  ___   ";
			gotoxy(Xpos, 16);
			cout << " | __|  ";
			gotoxy(Xpos, 17);
			cout << " |__ \\ ";
			gotoxy(Xpos, 18);
			cout << " |___/";//prints the textart 5
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
			break;
		case 6:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
			gotoxy(Xpos, 15);
			cout << "   __    ";
			gotoxy(Xpos, 16);
			cout << "  / /    ";
			gotoxy(Xpos, 17);
			cout << " / _ \\ ";
			gotoxy(Xpos, 18);
			cout << " \\___/";//prints the textart 6
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
			break;
		case 7:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			gotoxy(Xpos, 15);
			cout << "  ____   ";
			gotoxy(Xpos, 16);
			cout << " |__  |  ";
			gotoxy(Xpos, 17);
			cout << "   / /  ";
			gotoxy(Xpos, 18);
			cout << "  /_/  ";//prints the textart 7
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
			break;
		}
	}
};

void ResetScreen()//resets cursor position
{
	gotoxy(0, 0);//sets cursor position to origin
}

int main()
{
	system("color 06");//Sets text colour to yellow

	cout << Indent << "       $$$$$                                                                       \n"; //Prints title screen to console
	cout << Indent << "       $:::$                                                                       \n";
	cout << Indent << "   $$$$$:::$$$$$$ lllllll                           tttt                           \n";
	cout << Indent << " $$::::::::::::::$l:::::l                        ttt:::t                           \n";
	cout << Indent << "$:::::$$$$$$$::::$l:::::l                        t:::::t                           \n";
	cout << Indent << "$::::$       $$$$$l:::::l                        t:::::t                           \n";
	cout << Indent << "$::::$             l::::l    ooooooooooo   ttttttt:::::ttttttt        ssssssssss   \n";
	cout << Indent << "$::::$             l::::l  oo:::::::::::oo t:::::::::::::::::t      ss::::::::::s  \n";
	cout << Indent << "$:::::$$$$$$$$$    l::::l o:::::::::::::::ot:::::::::::::::::t    ss:::::::::::::s \n";
	cout << Indent << " $$::::::::::::$$  l::::l o:::::ooooo:::::otttttt:::::::tttttt    s::::::ssss:::::s\n";
	cout << Indent << "   $$$$$$$$$:::::$ l::::l o::::o     o::::o      t:::::t           s:::::s  ssssss \n";
	cout << Indent << "            $::::$ l::::l o::::o     o::::o      t:::::t             s::::::s      \n";
	cout << Indent << "            $::::$ l::::l o::::o     o::::o      t:::::t                s::::::s   \n";
	cout << Indent << "$$$$$       $::::$ l::::l o::::o     o::::o      t:::::t    ttttttssssss   s:::::s \n";
	cout << Indent << "$::::$$$$$$$:::::$l::::::lo:::::ooooo:::::o      t::::::tttt:::::ts:::::ssss::::::s\n";
	cout << Indent << "$::::::::::::::$$ l::::::lo:::::::::::::::o      tt::::::::::::::ts::::::::::::::s \n";
	cout << Indent << " $$$$$$:::$$$$$   l::::::l oo:::::::::::oo         tt:::::::::::tt s:::::::::::ss  \n";
	cout << Indent << "      $:::$       llllllll   ooooooooooo             ttttttttttt    sssssssssss    \n";
	cout << Indent << "      $$$$$                                                                        \n";

	cout << endl << endl << endl << "                                                 Press any key to play...";
	_getch();//Waits for key press
	system("CLS");//clears console screen
	srand(time(NULL));//Initialise random seed based on system time
	char menuChoice;//stores user key press for menu navigation
	SlotMachine Slots;//creates new SlotMachine object
	bool GameRunning = true;//bool gamerunning is true while the game is running, false when the user selects exit
	while (GameRunning)//loop containing main game code, repeats until user chooses to exit
	{
		if (Slots.Credit <= 0)//Checks users balance every iteration, balance of 0 or less triggers lose condition
		{
			system("CLS");//clear screen
			Slots.DisplayTitle();//Display the title Ascii art
			cout << "\nIt looks like you've run out of Credit! Goodbye for now.\nInput any key to continue...";//print to console
			_getch();//waits for keypress
			GameRunning = false;//causes game loop to end
			return 0;//returns main(), ceasing execution
		}

		ResetScreen();//resets the screen to blit GUI
		Slots.DisplayTitle();//prints title to console
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//Sets console text colour to white//change colour to white
		gotoxy(74, 10);//change cursor position
		cout << "-{ Would you like to Spin(1),";//print to console
		gotoxy(74, 11);//change curson position
		cout << "-{ collect your winnings(2),";//print to console
		gotoxy(74, 12);//change cursor position
		cout << "-{ or view the credits(3)?";//print to console
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow//change colour to yellow
		NewInputPrompt("");//creates new empty input prompt for user to choose option from menu
		menuChoice = _getch();//waits for keypress, sets menuChoice to the char of the key
		bool valid = false;//initialises variable used for validation loop
		switch (menuChoice)//switch statement based on value of menuChoice
		{
		case '1'://if user presses '1'
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//Sets console text colour to white
			NewInputPrompt("-{ How much would you like to bet? >");//creates new input prompt in menu
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//Sets console text colour to yellow
			float input;// creates new variable to store player input for their bet
			while (!valid)//while valid is false
			{
				cin >> input;//get user input to 'input'
				cout << Indent << "\n";//print an indent
				valid = Slots.Bet(input);//set valid equal to the return of Slots.Bet with users bet as param
			}

			ResetScreen();//resets screen for new blit
			Slots.DisplayTitle();//prints title to console
			cout << Indent << "|/o=====\\/=====||=====\\/=====||=====\\/=====o\\|" << endl;//prints the slot machine ascii art to console
			cout << Indent << "|\\||           ||            ||           ||/|  " << endl;
			cout << Indent << "|/||           ||            ||           ||\\|   __" << endl;
			cout << Indent << "|\\||           ||            ||           ||/|  (__)" << endl;
			cout << Indent << "|/||           ||            ||           ||\\|   ||" << endl;
			cout << Indent << "|\\||           ||            ||           ||/|   ||" << endl;
			cout << Indent << "|/||           ||            ||           ||\\|   //" << endl;
			cout << Indent << "|\\||           ||            ||           ||/|  //" << endl;
			cout << Indent << "|/o=====/\\=====||=====/\\=====||=====/\\=====o\\| //" << endl;
			cout << Indent << "|____________________________________________|//" << endl;
			cout << Indent << "[][][][][][][][][][][][][][][][][][][][][][][]_)" << endl;
			cout << Indent << "||==========================================||" << endl;
			gotoxy(0, 25);//changes cursor position
			cout << Indent << "                                             " << endl << Indent << "                                               " << endl << Indent << "                                                    ";
			for (int i = 0; i < 20; i++)//displays random numbers in the slot machine art to simulate spinning
			{
				Slots.DisplayNum(1, rand() % (6) + 2);//generates random number between 2 and 7, displays in position 1 (1st reel) in slot machine art
				Sleep(10 + (i * 6));//pauses execution for 10 + i times 6 milliseconds, creates slowing down effect as delay increases every iteration
				Slots.DisplayNum(2, rand() % (6) + 2);
				Sleep(10 + (i * 6));
				Slots.DisplayNum(3, rand() % (6) + 2);
				Sleep(60 + (i * 6));
			}
			Slots.Play();//generates final slot result and stores in slotArr
			Sleep(130);//delay for 130 milliseconds
			Slots.DisplayNum(1, Slots.slotArr[0]);//display 1st actual result in 1st reel...
			Sleep(130);
			Slots.DisplayNum(2, Slots.slotArr[1]);
			Sleep(130);
			Slots.DisplayNum(3, Slots.slotArr[2]);

			NewInputPrompt("");//create empty input prompt in menu

			break;//breaks out of switch statement

		case '2'://if user presses '2'
			system("CLS");//clears the screen
			Slots.DisplayTitle();//prints title to screen
			cout << Indent << "-{ You collect $" << Slots.Credit << " in winnings! Input anything to continue: >";//prints to console

			_getch();//waits for key press
			GameRunning = false;//ends game loop
			return 0;//returns main to end program

		case '3'://if user presses '3'
			ResetScreen();//resets screen
			system("CLS");//clears console

			for (int i = 25; i > 0; i--)//do this 25 times
			{
				gotoxy(0, i);//set cursor to position dictated by i, this makes the cursor go up a row every iteration as i decrements
				cout << "||                 ||               O==============================================O               ||                 ||";
				gotoxy(0, i + 1);
				cout << "||                 ||               -{You are playing Slots, by Nerys (Bryn) Thamm}-               ||                 ||";
				gotoxy(0, i + 2);
				cout << "||                 ||                       -{Made for Media Design School}-                       ||                 ||";
				gotoxy(0, i + 3);
				cout << "||                 ||                                  -{c2020}-                                   ||                 ||";
				gotoxy(0, i + 4);
				cout << "||                 ||               O==============================================O               ||                 ||";
				gotoxy(0, i + 5);
				cout << "||                 ||                             ||               ||                              ||                 ||";
				Sleep(300);//delay for 300 milliseconds
			}
			_getch();//wait for keypress
			system("CLS");//clear screen
			break;//break out of switch statement
		default:
			//does nothing if invalid key inputted
			break;
		}
	}

	return 0;
}
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <ctype.h>
using namespace std;

bool randoms = 1; // global variable used throughout the program
int computer_call[2]; // store the row and column once the computer get a hit
int player_points = 0; // count the player's points
int computer_points = 0; // count the computer's points
char computer_grid[20][20]; // the computer's grid 
bool north = 1, west = 0, south = 0, east = 0; // to check which direction the computer has to go to
int computer_call_1[2]; // store the row and column and used later as it doesnt change 
char user_grid[20][20]; // abstract grid to check if the computer is calling out the same coordinates
int A=0, B=0, C=0, D=0, E=0; // counter for checking which ship has been hit

void fill_computer_grid(char arr[][20]); // to file the computer grid with x
void place_computer_ships(char arr[][20]); // place the ships
void print_grid(char arr [][20]); // print any grid
int check_overlap(char arr[][20], int boat_number, int voh, int row, int col); // check if the boat placed is overlapping other boats in computer's grid
void player_turn(char computer_grid[][20], char display_grid[][20], int &player_points); // player's turn
void computer_turn();
void computer_hit_direction(int computer_call[]); // check which direction to go after the computer gets a hit
void hit_or_sunk(int row, int col); // see if its hit or hit and sunk
void exit_game(); // if the user exits the game

int main()

{
	srand(time(NULL)); // create different random numbers everytume

	char display_grid[20][20];  // a grid shown on the screen 
	fill_computer_grid(computer_grid); // fill the grid with x 
	fill_computer_grid(user_grid); // fill user's grid with x , just an abstract grid , not shown 
	fill_computer_grid(display_grid); // fill the display grid with Xs too
	place_computer_ships(computer_grid); // place the ships for computer randomly
	cout << endl << endl;
	
	while(player_points <=17 && computer_points <= 17) // while the game doesnt get a winner 
	{
		cout << setw(25) << "BATTLESHIP" << endl << endl;
		print_grid(display_grid); // print the display grid
		cout << endl;
		player_turn(computer_grid, display_grid, player_points); // palyer's turn , passing the compuetr grid to check the placements of boats
		cout << endl << endl;
		computer_turn(); // computer's turn
		cout << endl << endl;
		
		system("cls"); // clear the screen
			
	}
	

	if(player_points == 17) // see who is the winner
	 {
		print_grid(display_grid);
		cout << "YOU WON . CONGRATULATION" << endl;
	 }
	else
		cout << "YOU LOSE. COMPUTER WON. BETTER LUCK NEXT TIME" << endl;
	

	system("pause");
	return 0;
}



void fill_computer_grid(char arr[][20]) // filling the computer grid with x
{
	for(int i=0; i<20; i++)
	{
		for(int j=0; j<20; j++)
		{
			arr[i][j]='X';
		}
	}
}



void place_computer_ships(char arr[][20]) // placing the ships on the computer grid
{
	int boats_number[] = {5,4,3,3,2}; // the size of each of the ship
	int boats_space[] = {15, 16, 17, 17, 18}; 
	char letters[] = {'A','B','C','D','E'}; // different letters for different ships

	for(int i=0; i<5; i++) // creat random numbers for all the 5 ships
	 {
			int voh = rand()%2+1; // to randomly have the ships placed vertically or horizontally
			int row = rand()%boats_space[i]; // randomly create a row and column
			int col = rand()%boats_space[i];

		

			if (voh == 1) // if its vertical
			{
				while(check_overlap(arr,boats_number[i],voh,row,col)==1) // keep generating random row, column and alignment while its true
				{
					int voh = rand()% 2+1 ;
					int row = rand()%boats_space[i];// randomly create a row and column
					int col = rand()%boats_space[i];
				}

				for(int row1=row; row1<(row+boats_number[i]); row1++) // place the ships
				{
						arr[row1][col]= letters[i];
				}

			}

			else // if its horizontal
			{
				while(check_overlap(arr,boats_number[i],voh,row,col)==1) // keep generating random row, column and alignment while its true
				{
					int voh = rand()%2 + 1;
					int row = rand()%boats_space[i];// randomly create a row and column
					int col = rand()%boats_space[i];
				}

				for(int col1=col; col1<(col+boats_number[i]); col1++) // place the ships
				{
						arr[row][col1]=letters[i]; // place the letters accordingly
				}
			}
	 }
				
}


int check_overlap(char arr[][20], int boat_number,int voh, int row, int col) //to check whether the number generated by the random function 
																			 // leads to overlapping
{
	if (voh == 1) // if its vertical
	 {
		for(int row1=row; row1<(row+boat_number); row1++) // keep going up till the size of the ship
		 {
			if(arr[row1][col] !='X') // return true if there is a boat already
				return 1;
		 }

	 return 0;

	 }

	else  //if its horizontal
	 {
		 for(int col1=col; col1<(col+boat_number); col1++)  // start increamenting the column
		 {
			if(arr[row][col1]!='X')
				 return 1;
		 }

	return 0;

	}
}


void print_grid(char arr[][20]) //function to print any grid
{
	cout << "   ";

	for(char alpha = 'A'; alpha < 'U'; alpha++) // name of the column
		cout << alpha << " "; // letters to be printed

	cout << endl;

	for(int i=0; i<20; i++)
	{
		cout << setw(2) << setfill(' ') << i+1 << " "; // print row numbers

		for(int j=0; j<20; j++)
		{
			cout << arr[i][j] << " "; // print the element
		}

		cout << endl;
	}	
}



void player_turn(char computer_grid[][20],char display_grid[][20], int &player_points)
{
	char column;
	int col;
	int row;
	cout << "SELECT A COLUMN(A-T) AND ROW(1-20) [ ENTER X TO EXIT]: "; 
	cin >> column; // get the column

	if(column == 'X' || column == 'x') // if its an x then exit
	{
		exit_game(); // call the exit function
		cout << "SELECT A COLUMN(A-T) AND ROW(1-20) : "; //
		cin >> column;
	}

		cin >> row; // get the row

	while(cin.fail()) // to check if the input by the user is invalid
	{
		cout << "INVALID . ENTER AGAIN : ";
		cin.clear();
		cin.ignore(256,'\n');
		cin >> column;

		while(isdigit(column)) // check if its a digit
	    {
			cout << "INVALID . ENTER AGAIN : ";
			cin.clear();
			cin.ignore(256,'\n');
			cin >> column;
	    }

		cin >> row;

	}

	row = row-1; // decreament the row
	column = toupper(column); 
	col = (int) column - 65; // change the column to an integer


	while(display_grid[row][col] == 'M' || display_grid[row][col] == 'H' || column > 'T' || column < 'A' || row >= 20 || row < 0  ) // if the user enters invalid coordinates
	{
		if(column > 'T' || column < 'A' || row >= 20 || row <0 )
		     cout << "INVALID COORDINATES. ENTER AGAIN:  ";

		else 
		cout << "the coordinate has already been called out . please enter another column and row : "; // if the user enters the same coordinates

		cin >> column; // ask for the row and column again
		column = toupper(column);
		col = (int) column - 65;
		cin >> row;
		row = row-1;
	}

	
	if(computer_grid[row][col] != 'X') // if the cordinates doesn't have an X
	{
		hit_or_sunk(row,col); // check if its just hit ot hit and sunk
		player_points ++; // increament the player points
		display_grid[row][col] = 'H'; // put an H in the display grid
		computer_grid[row][col] = 'H'; // put an H in the computer's grid
	}

	else // if there is no boat
	{
		cout << "MISS" << endl; // its a miss
		display_grid[row][col] = 'M'; //put an M in the display grid
	}

}


void computer_turn()
{
	if(randoms == 1) // if the computer is suppose to call random row and column
	{
		char column, hom;
		int row = rand()%20; // generate random numbers from 0 to 19
		int col = rand()%20;

		while (user_grid[row][col] == 'H') // if its already being called out , generate different row and column
		{
			int row = rand()%20;
			int col = rand()%20;
		}

		user_grid[row][col] = 'H'; // place a H in the user's grid(which is abstract)
		computer_call[0]= row; // store the row and column in an array
		computer_call[1]= col;
		computer_call_1[0] = computer_call[0]; // store it again so that it could be user later
		computer_call_1[1] = computer_call[1];
		column = (char) col + 65; // convert the integer to a letter

		cout << "COMPUTER'S CALL : ";
		cout << column; // print the coordinate
		cout << row+1;
		cout << endl << "ENTER h (hit) or m (miss) or s (hit and sunk) : ";
		cin >> hom;
		hom = tolower(hom);

		if(hom != 'h' && hom != 'm' &&  hom != 's' ) // check if the user enters invalid letter
		{ 
			cout << "please enter again : ";
			cin >> hom;
			hom = tolower(hom);
		}
		
 
		if(hom == 'h') // if its a hit 
		{
			randoms = 0; // stop calling random numbers
		north = 1, west = 0, south = 0, east = 0; // start going north
		computer_points++; //increament computer
		} 

	}


	else if (randoms == 0) // if random numbers are not generated
	{
		if(computer_call[0] == 0) //if the row is 0 then dont go north and go south
		{
			north = 0;
			south = 1;
			computer_call[0] = computer_call_1[0];
			computer_call[1] = computer_call_1[1];
		}

		if(computer_call[0] == 19) // if the row is 19 then dont go south
		{
			south = 0;
			east=1;
			computer_call[0] = computer_call_1[0];
			computer_call[1] = computer_call_1[1];
		}

		if(computer_call[1] == 19) // if the column is 19 , dont go east
		{
			east = 0;
			west = 1;
			computer_call[0] = computer_call_1[0];
			computer_call[1] = computer_call_1[1];
		}

		if(computer_call[1] == 0) // if the column is 0 then dont go west
		{
			west = 0;
			computer_call[0] = computer_call_1[0];
			computer_call[1] = computer_call_1[1];
		}
		computer_hit_direction(computer_call); // call the function to go around the coordinate

	}
}


void computer_hit_direction(int computer_call[])
{

	if(north == 1) // if its north
	{ 
		char hom;
		int row = --computer_call[0]; //go north
		int col = computer_call[1];
		while(user_grid[row][col] == 'H') //see if its already been called out
		{
			row = --computer_call[0];
			col = computer_call[1];
		}
		user_grid[row][col] = 'H'; //put a H in user grid's so that the computer doesn't call the same coordinate
		cout << "COMPUTER'S CALL : ";
		char column = (char) col + 65; //convert the column to a letter and print
		cout << column;
		cout << row+1;
		cout << endl << "ENTER h(hit) or m(miss) or s(hit and sunk) : "; // ask the user whether its a hit or a miss
		cin >> hom;
		hom = tolower(hom);

		if(hom == 'h') //if its a hit
		{
			computer_points++; //increament the computer's points
		}

		else if (hom == 'm') 
		{
			south = 1; // start going south from next turn
			north = 0;
			computer_call[0] = computer_call_1[0]; // get the pointer back from where it started going north
			computer_call[1] = computer_call_1[1];
		}

		else if (hom == 's') 
		{
			randoms = 1; //if its sunk , start calling random coordinate again
			computer_points++;
		}
	}


	else if(east == 1) // if its going east
	{
		char hom;
		int row = computer_call[0];
		int col = ++computer_call[1];
		while(user_grid[row][col] == 'H') // check if its already called out
		{
			row = computer_call[0];
			col = ++computer_call[1];
		}
		user_grid[row][col] ='H'; //put a H in the user'd grid
		cout << "COMPUTER'S CALL : ";
		char column = (char) col + 65; // same as above
		cout << column;
		cout << row+1;
		cout << endl << "ENTER h(hit) or m(miss) or s(hit and sunk) : ";  // same as above
		cin >> hom;
		hom=tolower(hom);

		if(hom == 'h') //if its a hit keep going east
		{
			east=1;
			computer_points++;

		}

		else if (hom == 'm') //if its a miss start going west
		{
			east = 0;
			west = 1;
			computer_call[0] = computer_call_1[0]; // from the point where it started
			computer_call[1] = computer_call_1[1];
		}

		else if (hom == 's') //if its sunk then start creating random number
		{
			randoms = 1; // start calling random numbers again 
			computer_points++;
		}
	}


	else if(south == 1) //if its south
	{
		char hom;
		int row = ++computer_call[0];
		int col = computer_call[1];

		while(user_grid[row][col] == 'H') // check if its already been called hit
		{
			row = computer_call[0];
			col = ++computer_call[1];
		}

		user_grid[row][col] = 'H'; // assign an h
		cout << "COMPUTER'S CALL : "; // same as above
		char column = (char) col + 65;
		cout << column;
		cout << row+1;
		cout << endl << "ENTER h(hit) or m(miss) or s(hit and sunk) : "; // same as above
		cin >> hom;
		hom=tolower(hom);

		if(hom == 'h') // if its a hit , keep going south
		{
			south=1;
			computer_points++;
		}

		else if (hom == 'm') // if its a miss start going east from the point where it started
		{
			east = 1;
			south = 0;
			computer_call[0] = computer_call_1[0];
			computer_call[1] = computer_call_1[1];
		}

		else if (hom == 's') // if its sunk , increament the points and start random number 
		{
			randoms = 1;
			computer_points++;
		}
	}


	else if(west == 1)  // start going west
	{
		char hom; // same as above
		int row = computer_call[0];
		int col = --computer_call[1];
		while(user_grid[row][col] == 'H') // check if its already been called hit
		{
			row = computer_call[0];
			col = ++computer_call[1];
		}
		user_grid[row][col] ='H';
		cout << "COMPUTER'S CALL : ";
		char column = (char) col + 65;
		cout << column;
		cout << row+1;
		cout << endl << "ENTER h(hit) or m(miss) or s(hit and sunk) : ";
		cin >> hom;
		hom=tolower(hom);

		if(hom == 'h')
		{
			computer_points++;
		}

		else if (hom == 'm') // if its a miss start calling random numbers again
		{
			randoms = 1;
			computer_call[0] = computer_call_1[0];
			computer_call[1] = computer_call_1[1];
		}

		else if (hom == 's')// even if its sunk , start random number
		{
			randoms = 1;
			computer_points++;
		}
	}

}


void hit_or_sunk(int row, int col) // this function shows if its a hit or hit and sunk
{
	if (computer_grid[row][col]=='A') // check if the hit position has boat A
	{ 
		A++; // if it does then increament A
		if(A==5) // if it hit all the 5 parts then display hit and sunk
			cout << "CARRIER HAS BEEN HIT AND SUNK" << endl;
		else
			cout << "HIT" << endl; // or else just show that its a hit
	}

	if (computer_grid[row][col]=='B') // check if the hit position has boat B
	{
		B++; // same as above
		if(B==4)
			cout << "BATTLESHIP HAS BEEN HIT AND SUNK" << endl;
		else
			cout << "HIT" << endl;
	}

	if (computer_grid[row][col]=='C') // check if the hit position has boat C
	{
		C++;
		if(C==3)
			cout << "CRUISER HAS BEEN HIT AND SUNK" << endl;
		else
			cout << "HIT" << endl;
	}

	if (computer_grid[row][col]=='D') // check if the hit position has boat D
	{
		D++;
		if(D==3)
			cout << "SUBMARINE HAS BEEN HIT AND SUNK" << endl;
		else
			cout << "HIT" << endl;
	}

	if (computer_grid[row][col]=='E') // check if the hit position has boat E
	{
		E++;
		if(E==2)
			cout << "DESTROYER HAS BEEN HIT AND SUNK" << endl;
		else
			cout << "HIT" << endl;
	}
}


void exit_game() // the function is called when the user enters X
{
	char ans;
	cout << " ARE YOU SURE THAT YOU WANT TO EXIT (y/n): "; // ask the user again
	cin >> ans;
	if(ans == 'y' || ans == 'Y') // if its a yes
	{
		cout << endl << "you can see the computer's grid and the points below : " << endl << endl;
		print_grid(computer_grid); // show the computer's grid with all the boats and the hits
		cout << endl << " (A - CARRIER , B - BATTLESHIP , C - CRUISER , D - SUBMARINE , E - DESTRYOER , H - HIT)" << endl;
		cout << endl << endl;
		cout << "THE COMPUTER'S POINTS : " << computer_points << endl; // print the points
		cout << "THE PLAYER'S POINTS : " << player_points << endl;

		if(computer_points > player_points) // check who is the winner
			cout << "COMPUTER WINS" << endl;

		else if(player_points > computer_points)
			cout << "YOU WIN" << endl;

		else
			cout << "IT'S A TIE" << endl;


		exit(0); // exit
	}
}


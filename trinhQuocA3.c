/************************trinhQuocA3.c **************
 Student Name: Quoc (Tony) Trinh 			Email Id: trinhq@uoguelph.ca
 Date: November 28th, 2018					Course Name: CIS 1500
 I have exclusive control over this submission via my password.
 By including this statement in this header comment, I certify that:
 1) I have read and understood the University policy on academic integrity;
 2) I have completed the Computing with Integrity Tutorial on Moodle; and
 3) I have achieved at least 80% in the Computing with Integrity Self Test.
 I assert that this work is my own. I have appropriately acknowledged any and all material (data, images, ideas or words) that I have used,
 whether directly quoted or paraphrased.
 Furthermore, I certify that this assignment was prepared by me specifically for this course.
 ***********************************************************/


/**********************************************************
   Compiling the program
 *********************************************************
 The program should be compiled using the following flags:
 -std=c99
 -Wall
 compiling: gcc trinhQuocA3.c -std=c99 -Wall -o trinhQuocA3
 **********************************************************
 Running the Program
 **********************************************************
 running: ./trinhQuocA3
 User is prompted to enter in row and column numbers to place an X on the respective cell. User plays Tic Tac Toe against the computer.
 **********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

// Function Prototypes
int isInputValid(int, int, int);
int isBoardFull(char [N][N]);
void createInitialBoard(char [N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int computerPlaysToWin(char [N][N], int * , int * );
void computerPlaysRandom(int * , int * , int , int );
void sumAllDimensions(char [N][N], int [N], int [N], int *, int *);
int memberOf(int , int [N]);
int computerPlaysToBlock(char [N][N], int * , int * );

int main()
{
  int userRow, userCol, computerRow, computerCol;
  int taken;
  char board[N][N];
  char winner = 'N';

  srand(time(NULL));

  printf("This tic-tac-toe board is of size %d by %d\n", N, N);

  printf("Player symbol: X \nComputer symbol: O\n\n");

  printf("Here is the board - spaces are indicated by a ?\n");

  createInitialBoard(board); // create a 3 X 3 board with '?' in each cell

  while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
  {
    taken = 0;

    while (!(taken)) // loop used to accept valid row and col values from the user
    {
      readUserMove(&userRow, &userCol); //get user's move
      printf("You chose row %d and column %d \n", userRow, userCol);

      while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
      {
        printf("That's is an invalid row or column number - try again\n");
	readUserMove(&userRow, &userCol);
	printf("You chose row %d and column %d \n", userRow, userCol);
      }

      if (board[userRow-1][userCol-1] == '?')// if cell is unoccupied
      {
        board[userRow-1][userCol-1] = 'X';  // store an X there
	taken = 1;
      }
      else
      {
        taken = 0; // otherwise inform the user to enter values again
	printf("That spot is taken - please try another one\n");
      }

    } //end of while (!taken)

    if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
    {
      printf("Congrats - you won against the computer :)\n");
      winner = 'Y';
    }
    else  if (!(isBoardFull(board))) //check if the board is already full
    {
      taken = 0;

      while (!(taken))
      {
	getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col

	if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
	{
	  board[computerRow][computerCol] = 'O';
	  taken = 1;
        }
	else
	{
	  taken = 0; //That spot is taken - computer - try another one
	}
      }

      printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);

      if (gameWon(board, 'O')) // check if the computer wins - game must end if it does
      {
        printf("Oh the computer won this time :(( think hard next time\n");
	winner = 'Y';
      }
    }

    printCurrentBoard(board);

    printf("\nPress enter to continue \n");
    getchar();
  } //end of while

  if (winner != 'Y')
    printf("Game was a tie - no winner!\n\n");

  return 0;
}

/******
 isInputValid: Takes in entered and checks if this variable is between minimum and maximum
 In: int entered, int minimum, int maximum
 Out: int
 Post: Returns 1 if entered is between minimum and maxiumum, returns 0 otherwise
*******/
int isInputValid(int entered, int minimum, int maximum)
{
  // 1st Condition which checks if entered is greater than or equal to minimum and entered is less than or equal to maximum
  if ((entered >= minimum) && (entered <= maximum))
  {
    // Returns 1 if entered is between minimum and maximum
    return 1;
  }
  else
  {
    // Returns 0 as entered is not between minimum and maximum and entered is therefore not a valid input
    return 0;
  }
  
}
/******
 isBoardFull: Takes in the board array and checks if the board is full or not 
 In: char board[N][N]
 Out: int
 Post: Returns 1 if the board is full, returns 0 otherwise
*******/
int isBoardFull(char board[N][N])
{
  // Creates i and j as counter variables
  int i;
  int j;
  
  // 1st loop which checks the rows of the board array
  for (i = 0; i < N; i++)
  {
    // 2nd loop which checks the columns of the board array
    for (j = 0; j < N; j++)
    {
      // Conditional statement if there is an empty cell on the board
      if (board[i][j] == '?')
      {
	// Returns 0 to indicate that the board is not full
        return 0;
      }
    }
  }

  // The function will only reach here if the board is full
  return 1;
}
/******
 createInitialBoard: Takes in the board array and creates the initial starting board for the game 
 In: char board[N][N]
 Out: None
 Post: The board is printed to the output and the game can now be played 
*******/
void createInitialBoard(char board[N][N])
{
  // Creates 2 counter variables to be used in the following loops to print out the board
  int i;
  int j;

  // 1st loop which follows the row index of the board array
  for (i = 0; i < N; i++)
  {
    // 2nd loop which follows the column index of the board array
    for (j = 0; j < N; j++)
    {
      // Sets the current index of the board array to be '?'
      board[i][j] = '?';
    }
  }

  // Following print statements prints out the board to the output
  printf("%c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
  printf("----------\n");
  printf("%c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
  printf("----------\n");
  printf("%c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
  printf("\n");
  
  return;
}
/******
 readUserMove: Prompts the user to input a value for row and column to place the X on the board
 In: int * userRow, int * userCol
 Out: None
 Post: The userRow and userCol are pointers and get sent back to main and the user's move will be used in other functions
*******/
void readUserMove(int * userRow, int * userCol)
{
  // Prompts the user to enter a value between 1 and 3 as the row and column values
  printf("Your move - enter numbers between 1 and 3\n");
  // Gets the row number from the user
  printf("Enter row number: ");
  scanf("%d", userRow);
  // Gets the column number from the user 
  printf("Enter column number: ");
  scanf("%d", userCol);

  return;
}
/******
 printCurrentBoard: Prints the current board to the output using a nested loop
 In: char board[N][N]
 Out: None
 Post: The board is printed out to the console and the user can see the current board with the most recent move
*******/
void printCurrentBoard(char board[N][N])
{
  // Creates 2 counter variables to be used in the following loops
  int i;
  int j;

  printf("\nCurrent board now is:\n\n");

  // 1st loop which follows the row index of the board array
  for (i = 0; i < N; i++)
  {
    // 2nd loop which follows the column index of the board array
    for (j = 0; j < N; j++)
    {
      // Prints the current index of the board array 
      printf("%c", board[i][j]);

      // If the index is the last cell in the row it will go into this condition
      if(j == 2)
      {
	// Prints out a newline and prints out the --- line underneath
	printf("\n");
	printf("----------\n");
      }
      // Otherwise it will go into this condition
      else
      {
	// Prints out the | which separates each cell
	printf(" | ");
      }	
    }
  }
  
  return;
}
/******
 getComputerMove: Generates the move for the computer's turn 
 In: char board[N][N], int * computerRow, int * computerCol, int userRow, userCol
 Out: int
 Post: This function will call computerPlaysToWin, computerPlaysRandom or computerPlaysToBlock to generate the move for the computer's turn
*******/
int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol)
{
/*
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

  int winningSpot = 0;
  int blocked = 1;           

  winningSpot = computerPlaysToWin(board, computerRow, computerCol);

  if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user
  {
    computerPlaysRandom(computerRow, computerCol, userRow, userCol);

    blocked = computerPlaysToBlock(board, computerRow, computerCol);
    if (blocked == 0)
      computerPlaysRandom(computerRow, computerCol, userRow, userCol);
  }

  return winningSpot;
}
/******
 gameWon: Checks the right and left diagonal, all the columns and rows to see if there is a 3 in anyline and returns 1 if there is a winner
 In: char board[N][N], char symbol
 Out: int
 Post: Returns 1 if there is a winner and returns 0 if there is not a winner 
*******/
int gameWon(char board[N][N], char symbol)
{
  // Creates and initializes sumR, sumC, sumLD and sumRd to be 0 to be used in calling the sumAllDimensions Function
  int sumR[N] = {0, 0, 0};
  int sumC[N] = {0, 0, 0};
  int sumLD;
  sumLD = 0;
  int sumRd;
  sumRd = 0;

  // Calls in the sumAllDimensions function to use the values created from the function to test if there is a winner
  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRd);
  // The 12 means that there are 3 O's in that line
  // The 3 means that there are 3 X's in that line

  // If the symbol is O it will go into this condition
  if(symbol == 'O')
  {
    // Calls in the memberOf function to check whether if 12 is apart of the sumR array
    if(memberOf(12, sumR) == 1)
    {
      // Returns 1 indicating that there is a winner
      return 1;
    }
    
    // Calls in the memberOf function to check whether if 12 is apart of the sumC array
    if(memberOf(12, sumC) == 1)
    {
      // Returns 1 indicating that there is a winner
      return 1;
    }
    
    // Checks if either sumLD or sumRd is equal to 12 
    if((sumLD == 12) || (sumRd == 12))
    {
      // Returns 1 indicating that there is a winner
      return 1; 
    }
  }
  // If the symbol is X it will go into this condition
  else if(symbol == 'X')
  {
    // Calls in the memberOf function to check whether if 3 is apart of the sumR array
    if(memberOf(3, sumR) == 1)
    {
      // Returns 1 indicating that there is a winner
      return 1;
    }
    
    // Calls in the memberOf function to check whether if 3 is apart of the sumC array
    if(memberOf(3, sumC) == 1)
    {
      // Returns 1 indicating that there is a winner
      return 1;
    }
    
    // Checks if either sumLD or sumRd is equal to 3 
    if((sumLD == 3) || (sumRd == 3))
    {
      // Returns 1 indicating that there is a winner
      return 1; 
    }
  }
  
  // Returns 0 at the very end indicating that there is no winner
  return 0;
}
/******
 computerPlaysToWin: Checks if the computer can play to win in this turn by checking if there are 2 O's in anyline
 In: char board[N][N], int * cRow, int * cCol
 Out: int
 Post: Returns 1 if the computer can win in this step. Returns 0 otherwise
*******/
int computerPlaysToWin (char board[N][N], int * cRow, int * cCol)
{
  // Creates and initilizaes sumR, sumC, sumLD and sumRd to be 0 to be used in calling the sumAllDimensions Function 
  int sumR[N] = {0, 0, 0};
  int sumC[N] = {0, 0, 0};
  int sumLD;
  sumLD = 0;
  int sumRd;
  sumRd = 0;
  // Creates i and j as counter variables 
  int i;
  int j;

  // Calls in the sumAllDimensions function to use the values created from the function to test if there are 2 O's in anyline
  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRd);

  // The 8 indicates that there are 2 O's in that particular line
  // Calls in the memberOf function to see if 8 is in the sumR array
  if(memberOf(8, sumR) == 1)
  {
    // For loop with i matching the index of the sumR array and row index of the board array
    for(i = 0; i < N; i++)
    {
      // Checks if the current index of the sumR array is equal to 8 
      if(sumR[i] == 8)
      {
	// For loop with j matching the column index of the board array
        for(j = 0; j < N ; j++)
	{
	  // If the cell is unoccupied it will go into this condition
          if(board[i][j] == '?')
	  {
	    // Sets the computer's row and col move as equal to the position of the unoccupied cell
            *cRow = i;
	    *cCol = j;
	    // Returns 1 indicating that the computer can win in this turn
	    return 1;
	  }
	}
      }
    }
  }
  // calls in the memberOf function to see if 8 is in the sumC array
  else if(memberOf(8, sumC) == 1)
  {
    // For loop with j matching the index of the sumC array and column index of the board
    for(j = 0; j < N; j++)
    {
      // Checks if the current index of the sumC array is equal to 8
      if(sumC[j] == 8)
      {
	// For loop with i matching the row index of the board array
        for(i = 0; i < N; i++)
	{
	  // If the cell is unoccupied it will go into this condition
          if(board[i][j] == '?')
	  {
	    // Sets the computer's row and col move as equal to the position of the unoccupied cell
            *cRow = i;
	    *cCol = j;
	    // Returns 1 indicating that the computer can win in this turn
	    return 1;
	  }
	}
      }
    }
  }
  // Checks if the sumLD is equal to 8
  else if(sumLD == 8)
  {
    // For loop with i matching the row and column index of the left diagonal of the board array
    for(i = 0; i < N; i++)
    {
      // If the cell is unoccupied it will go into this condition
      if(board[i][i] == '?')
      {
	// Sets the computer's row and col move as equal to the position of the unoccupied cell
        *cRow = i;
	*cCol = i;
	// Returns 1 indicating that the computer can win in this turn
	return 1;
      }
    }
  }
  // Checks if the sumRd is equal to 8
  else if(sumRd == 8)
  {
    // For loop with i matching the row and column index of the right diagonal of the board array
    for(i = 0; i < N; i++)
    {
      // If the cell is unoccupied it will go into this condition
      if(board[2 - i][i] == '?')
      {
	// Sets the computer's row and col move as equal to the position of the unoccupied cell
        *cRow = 2 - i;
	*cCol = i;
	// Returns 1 indicating that the computer can win in this turn
	return 1;
      }
    }
  }

  // If it goes through all of the above conditions without triggering them it means that the computer does not have 2 O's in anyline
  // In that case we will return 0 indicating that the computer cannot win in this turn
  return 0;
  
}
/******
 computerPlaysRandom: This function gets called in when the computer can't win in this turn. This function gets a random move based on the user's move
 In: int * cRow, int *cCol, int uRow, int uCol
 Out: None
 Post: Finds a random computer move based on the user's move and then the computer move gets sent back to main to be used in other functions
*******/
void computerPlaysRandom(int * cRow, int * cCol, int uRow, int uCol)
{
  // Creates randomNum to hold the value that represents if the computer will match the user's row, column, left diagonal or right diagonal
  int randomNum;
  // Creates randomCoordinate to hold the random coordinate generated 
  int randomCoordinate;
  // Calls in srand with the time to make sure the randomly generated number is based on the time
  srand(time(NULL));
  // Assigns randomNum as equal to mod 3 of a randomly generated number
  // This will cause the range of the random number to be between 0 - 2
  randomNum = rand() % 3;

  // If the randomNum is equal to 0 (Same row as the user)
  if(randomNum == 0)
  {
    // We will match the computer's random move based on the user's row
    // Assigns the computer's row value as equal to the user's row value
    *cRow = uRow;
    // Get a random number between 0 - 2 to be assigned as the computer's column value
    randomCoordinate = rand() % 3;
    *cCol = randomCoordinate;
  }
  // If the randomNum is equal to 1 (Same column as the user)
  else if(randomNum == 1)
  {
    // We will match the computer's random move based on the user's column
    // Assigns the computer's column value as equal to the user's column value
    *cCol = uCol;
    // Gets a random number between 0 - 2 to be assigned as the computer's row value
    randomCoordinate = rand() % 3;
    *cRow = randomCoordinate;
  }
  // If the randomNum is equal to 2 (Same diagonal as the user)
  else if(randomNum == 2)
  {
    // If the user's row and column are the same we will use the Left Diagonal for the computer's move
    if(uRow == uCol)
    {
      // Gets a random number between 0 - 2 to be assigned as the computer's row and column value
      randomCoordinate = rand() % 3;
      *cRow = randomCoordinate;
      *cCol = randomCoordinate;
    }
    // The else conditional means that we will use the Right Diagonal for the computer's move 
    else
    {
      // Gets a random number between 0 - 2 to be assigned as the computer's row and column value
      randomCoordinate = rand() % 3;
      // Because it is the Right Diagonal we have to set the cRow as equal to 2 - randomCoordinate
      *cRow = 2 - randomCoordinate;
      *cCol = randomCoordinate;
    }
  }

  return;
}
/******
 sumAllDimensions: It computes the score of the diagonals, rows and columns to be used by other functions
 In: char board[N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRd
 Out: None
 Post: Sets 'O' as 4 and 'X' as 1 and computes the scores for the diagonals, rows and columns. Used as a utility function.
*******/
void sumAllDimensions(char board[N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRd)
{
  // Creates 2 counter variables to be used in the following loops
  int i;
  int j;
  
  // Checks the sum of the columns and rows
  // For loop with i matching the row index of the board array
  for(i = 0; i < N; i++)
  {
    // For loop with j matching the column index of the board array
    for(j = 0; j < N; j++)
    {
      // If the current cell is an O
      if(board[i][j] == 'O')
      {
	// Adds 4 to the total of sumR[currentRow] based on the i counter
        sumR[i] = sumR[i] + 4;
	// Adds 4 to the total of sumC[currentColumn] based on the j counter
	sumC[j] = sumC[j] + 4;
      }
      // If the current cell is an X
      else if(board[i][j] == 'X')
      {
	// Adds 1 to the total of sumR[currentRow] based on the i counter
	sumR[i] = sumR[i] + 1;
	// Adds 1 to the total of sumC[currentColumn] based on the j counter
	sumC[j] = sumC[j] + 1;
      }
    }
  }

  // Checks the sum of the left diagonal
  for(i = 0; i < N; i++)
  {
    // If the cell is an O
    if(board[i][i] == 'O')
    {
      // Adds 4 to the total of sumLD
      *sumLD = *sumLD + 4;
    }
    // Else if the cell is an X
    else if(board[i][i] == 'X')
    {
      // Adds 1 to the total of sumLD
      *sumLD = *sumLD + 1;
    }
  }

  // Checks the sum of the right diagonal
  for(i = 0; i < N; i++)
  {
    // If the cell is an O
    if(board[2 - i][i] == 'O')
    {
      // Adds 4 to the total of sumRd
      *sumRd = *sumRd + 4;
    }
    // If the cell is an X
    else if(board[2 - i][i] == 'X')
    {
      // Adds 1 to the total of sumRd
      *sumRd = *sumRd + 1;
    }
  }

  
  return;
}
/******
 memberOf: Checks to see if aNum is a member of the someArray[N] array
 In: int aNum, int someArray[N]
 Out: int
 Post: If aNum is a member of someArray[N] it will return 1, otherwise it will return 0
*******/
int memberOf(int aNum, int someArray[N])
{
  // Create a counter variable to be used in the following loop
  int i;

  // Loop checks aNum among the indexes of someArray[N]
  for(i = 0; i < N; i++)
  {
    // If aNum is one of the indexes of someArray
    if(aNum == someArray[i])
    {
      // Returns 1 back to main
      return 1;
    }
  }

  // Function will go here if aNum is not a member of someArray[N]
  // Returns 0 back to main
  return 0;
}
/******
 computerPlaysToBlock: This function will check if there are 2 X's in anyline. If there is, the computer will block the win
 In: char board[N][N], int * cRow, int * cCol
 Out: int
 Post: Finds if there are 2 X's in anyline for the computer to block the opponent's win. Returns 1 if it can block, returns 0 otherwise
*******/
int computerPlaysToBlock (char board[N][N], int * cRow, int * cCol)
{
  // Creates and initializes sumR, sumC, sumLD and sumRd to be 0 to be used in calling the sumAllDimensions Function 
  int sumR[N] = {0, 0, 0};
  int sumC[N] = {0, 0, 0};
  int sumLD;
  sumLD = 0;
  int sumRd;
  sumRd = 0;
  // Creates i and j as counter variables 
  int i;
  int j;

  // Calls in the sumAllDimensions function to use the values created from the function to test if there are 2 X's in anyline
  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRd);
  // The 2 indicates that there are 2 X's

  // Calls in the memberOf function to check if there is a 2 in the sumR array
  if(memberOf(2, sumR) == 1)
  {
    // For loop with i matching the index of the sumR array and the row index of the board array
    for(i = 0; i < N; i++)
    {
      // Checks if the current index of sumR is equal to 2 
      if(sumR[i] == 2)
      {
	// For loop with j matching the column index of the board array
        for(j = 0; j < N ; j++)
	{
	  // If the current cell is unoccupied 
          if(board[i][j] == '?')
	  {
	    // Assigns the computer's row and column value as equal to the unoccupied spot
            *cRow = i;
	    *cCol = j;
	    // Returns 1 indicating that the computer can block in this turn
	    return 1;
	  }
	}
      }
    }
  }
  // Calls in the memberOf function to check if there is a 2 in the sumC array
  else if(memberOf(2, sumC) == 1)
  {
    // For loop with j matching the index of the sumC array and the column index of the board array
    for(j = 0; j < N; j++)
    {
      // Checks if the current index of sumC is equal to 2 
      if(sumC[j] == 2)
      {
	// For loop with i matching the row index of the board array
        for(i = 0; i < N; i++)
	{
	  // If the current cell is unoccupied
          if(board[i][j] == '?')
	  {
	    // Assigns the computer's row and column value as equal to the unoccupied spot
            *cRow = i;
	    *cCol = j;
	    // Returns 1 indicating that the computer can block in this turn
	    return 1;
	  }
	}
      }
    }
  }
  // If the sumLD is equal to 2
  // Left Diagonal
  else if(sumLD == 2)
  {
    // For loop with i matching the row and column index of the board array
    for(i = 0; i < N; i++)
    {
      // If the cell is unoccupied
      if(board[i][i] == '?')
      {
	// Assigns the computer's row and column value as equal to the unoccupied spot 
        *cRow = i;
	*cCol = i;
	// Returns 1 indicating that the computer can block in this turn
	return 1;
      }
    }
  }
  // If the sumRd is equal to 2
  // Right Diagonal
  else if(sumRd == 2)
  {
    // For loop with i matching the row and column index of the board array
    for(i = 0; i < N; i++)
    {
      // If the cell is unoccupied
      if(board[2 - i][i] == '?')
      {
	// Assigns the computer's row and column value as equal to the unoccupied spot
        *cRow = 2 - i;
	*cCol = i;
	// Returns 1 indicating that the computer can block in this turn
	return 1;
      }
    }
  }

 
  // If the function goes through all the conditions and the computer cannot block this turn, it will return 0
  return 0;
}

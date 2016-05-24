// Name: Ben Wilfong
// File Name: nqueens.cpp
// Date: 31 Oct, 2014
// Program Description :
// Uses a templatized linked-list stack to find a solution
// for the n-queens problem with a given n. The n-queens problem
// is a puzzle in which n queens must be placed on a chess board
// with n rows and n columns. No queens on the board can be in a
// position to overtake another queen (same column, row, or diagonal).
// The solution is implemented using backtracking.

#include <iostream>

using namespace std;

#include "stack.h"

template <class T>
bool solve(int, Stack<T>*);
bool confrontation(Position*, Position&, int, int);
bool isDiagonal(Position, Position);
template <class T>
void displayBoard(bool, Stack<T>*, int);

int main()
{

    int n; //this number will represent the max number of queens, rows, and columns

    cout << "Enter number of queens: ";
    cin >> n;

    Stack<Position>* myStack = new Stack<Position>();

    displayBoard(solve(n, myStack), myStack, n);// this line will see if the number provides a solvable puzzle.
                                                // if so, solve() will return true and the board will be
                                                // displayed using the stack. If not, false will be passed
                                                // and an error message will be displayed.
}

/*
   The solve() function will dynamically create an array of positions
   to store the data for each queen that has been place. (This way,
   we will be able to access the index of ALL queens, not just the first).
   We start by adding a queen with an index (0,0), then incrementing
   the row to start processing for a valid position. We increment the row
   because we know there are n rows and n queens, so no queen can be on the
   same row. When the new queen is made, it will be sent through a loop
   to find a spot to where it is not confronting with any of the existing
   queens. If there is a valid place with no confrontation, then the queen's
   position is saved into pArray and temp is pushed onto the stack. The confrontation
   function will also stop if the columnar index has been pushed out of the board's
   bounds. If this happens, the previous queen is popped off the stack, then that
   queen's columnar index is used until a new valid index is found.
   This process will repeat until one of two situations occur:

   1) The queen in row 0's columnar index is out of bounds. If this happens,
      we have nothing left to increment, and since there are n queens and n
      rows, we cannot push any queen to a different row. This situation
      indicates an unsolvable puzzle. The function returns false
      and an appropriate error message is displayed.

   2) The number of queens (myStack->count) is equal to n, meaning that
      we were able to successfully place n queens on the board without
      confrontation. If this is the case, then solve() will return true,
      then an appropriate message will be displayed along with the
      solved-configuration of the board!
*/

template <class T>
bool solve(int n, Stack<T>* myStack)
{
    Position* pArray = new Position[n];
    Position  temp;

    temp.row    = 0;
    temp.column = 0;

    myStack->push(temp); // first queens starts at (0,0)

    while(myStack->count < n) // iterate until n-queens are placed
    {
        temp.row++; // start checking after the first row

        while(confrontation(pArray, temp, myStack->count, n)); // confrontation runs until
                                                               // OOB or valid spot is found

        if (temp.row > n-1 || temp.column > n-1) // if the queen is out-of-bounds in any way
        {
            if (myStack->isEmpty())
                return false; // If the stack is empty, the first queen was not able to proceed
                              // and was popped off, indicating the puzzle is unsolvable.

            else
            {
                myStack->pop(temp); // If the current queen is OOB, then we just find the last queen
                temp.column++;      // placed a new position, then move on from there.

                if (temp.row == 0)  // Row 0 is a special case because (0,0) is added before the loop.
                {
                    if(temp.row == 0 && temp.column > n-1)
                        return false; // this is a guard to make sure that if the queen is OOB
                                      // in row 0, the function should terminate.

                    pArray[myStack->count] = temp;
                    myStack->push(temp); //push the bottom queen back on the stack
                    temp.row++;
                    temp.column = 0;     //reset the new queen to be compared to the 1st queen
                }

                temp.row--; //this decrement is done to guard against the auto-increment done in the beginning
            }
        }

        else // If a valid queen index is found
        {
            pArray[myStack->count] = temp;
            myStack->push(temp);
            temp.column = 0; // Row will be automatically incremented, but column needs reset.
        }
    }

    return true; // The loop has finished with n-queens on the board, return true
}


/*
   confrontation() works by accepting the array of positions, the temporary
   (or current) queen position (it is passed by reference because it needs
   to be changed while the function executes), the number of queens currently
   in place (so we know which queens to check for confrontation with) and the
   boundaries of the board. It first begins by making sure that the temp
   queen is NOT out of bounds. If so, confrontation() stops and the temp
   queen will be handled in solve(). Assuming the boundaries are OK, a for
   loop iterates, checking for diagonal confronation and columnar confrontation
   between the potential new queen and the existing queens on the board.
   Note that we do not check if the queen is on-top of another queen or
   if they are in the same row. This is because, the way I have written this code,
   there should NEVER be a queen in the same row (which would eliminate the
   possibility of the queen being on-top). The function check for confrontation.
   If there is, the queen's column gets incremented, the function will
   return false. Since this is done in a while() loop, this function continues
   to execute until it returns true, even if the queen goes OOB. BUT- if the
   queen goes OOB, the code in solve() handles it.
*/


bool confrontation(Position* pArray, Position& temp, int queenCount, int n)
{

    if (temp.column > n-1 || temp.row > n-1)
        return false;

    for(int i = queenCount - 1; i >= 0; i--)
    {
        if(pArray[i].column == temp.column ||
           isDiagonal(pArray[i], temp))
        {
            temp.column++;
            return true;
        }
    }
}

/*
   The way isDiagonal() works is by RECURSION!!
   The way this program is written, no two
   queens will ever be created in the same row. That
   being said, isDiagonal() takes two queen
   positions and compares their columnar index.
   If the columnar index of the new queen is
   higher than the existing, the queen's position
   will move in the northwest direction until its
   columnar index is the same as the existing queen.
   If the row index eventually matches up when the
   columnar index does, then the queen was diagonal
   to the previous! If not, they were not diagonal.
   The methods are the same if the existing queen's
   columnar index is higher than the new queen's;
   it will move in the NE direction.

   Note that both variables are passed by value so nothing
   actually changes with the real positions.
*/

bool isDiagonal(Position existing, Position newQueen)
{
    if (existing.column == newQueen.column)
    {
        if (existing.row == newQueen.row)
            return true;

        else
            return false;
    }                       // base case: if they match they were diagonal,
                            // if not, they were not diagonal.

    else if (existing.column < newQueen.column)
    {
        newQueen.column--;
        newQueen.row--;
        return isDiagonal(existing, newQueen);
    }                       // general case: the new queen is to the right of
                            // the old queen.(move northwest)

    else if (existing.column > newQueen.column)
    {
        newQueen.column++;
        newQueen.row--;
        return isDiagonal(existing, newQueen);
    }                       // general case 2: the new queen is
                            // to the left of the old queen (move northeast)
}

/*
   Finally, the displayBoard function will display
   the board based off whether the puzzle was solved
   or not (boolean returned by solve()). If so,
   a temporary new array is created to store
   the values held in the stack of positions, then
   a nested for loop is run, displaying a 'Q' whenever
   the index of the for loop matches the row/column
   index of the queen's position. If it does not match,
   simply, a '-' character is displayed.

   If the puzzle was NOT solved, an appropriate error
   message is displayed.
*/


template <class T>
void displayBoard(bool solved, Stack<T>* myStack, int n)
{
    if(solved)
    {
        cout << "Solution found!" << endl << endl;

        Position* displayArray = new Position[n];

        for (int i = n - 1; i >= 0; i--)
            myStack->pop(displayArray[i]); // populate array with Positions
                                           // from stack, done backwards
                                           // because of the LIFO nature
                                           // of the stack.

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (displayArray[i].row == i &&
                    displayArray[i].column == j)
                    cout << "Q";

                else
                    cout << "-";
            }

            cout << endl;
        }
    }

    else
        cout << "No solution!" << endl;
}

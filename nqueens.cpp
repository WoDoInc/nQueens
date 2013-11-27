/**
 * N Queens refresher using Object Oriented Programming in C++.
 *
 * @author akaszczuk
 */
#include <stdio.h>
#include <string>
#include <sstream>

const int TRUE  = 1;
const int FALSE = 0;

/**
 * Define Queens class fields and methods.
 */
class Queens
{
   private:
      /* Fields */
      int BOARD_SIZE;
      int *chessboard;
      std::string SUCCESS_BOARDS;

      /* Methods */
      void enumerate(int);
      int isSafe(int);
      void getQueens(void);

   public:
      /* Constructor/Destructor */
      Queens(int boardSize);
      ~Queens();

      /* Methods */
      void enumerate();
      std::string getResults(void);
};

/**
 * Queens object constructor. Allocate memory space for the chessboard.
 * 
 * @arg: int board_size - Specifies the size of the board we are attempting to solve.
 */
Queens::Queens(int boardSize)
{
   BOARD_SIZE = boardSize;
   chessboard = new int[BOARD_SIZE];
}

/**
 * Queens object destructor. Deallocate memory space for the chessboard.
 */
Queens::~Queens(void)
{
   delete []chessboard;
}

/**
 * Checks to see if position is safe.
 *
 * @arg: int position - The position to examine.
 * @returns int - Boolean value for TRUE (1) or FALSE (0).
 */
int Queens::isSafe(int position)
{
   for (int i = 0; i < position; i++)
   {
      if (chessboard[i] == chessboard[position]) // same column
         return FALSE;
      if ((chessboard[i] - chessboard[position]) == (position - i)) // major diagonal
         return FALSE;
      if ((chessboard[position] - chessboard[i]) == (position - i)) // minor diagonal
         return FALSE;
   }
   
   return TRUE;
}

/**
 * Enumerate call, starts from initial point zero.
 */
void Queens::enumerate()
{
   enumerate(0);
}

/**
 * Enumerate all sub-cases.
 *
 * @arg: int position - The position to examine.
 */
void Queens::enumerate(int position)
{
   if (position == BOARD_SIZE)
      getQueens();
   else
   for (int i = 0; i < BOARD_SIZE; i++)
   {
      chessboard[position] = i;
      if (isSafe(position) == TRUE)
         enumerate(position + 1);
   }
}  

/**
 * Get the queens for this board and append the results string.
 */
void Queens::getQueens(void)
{
   for (int i = 0; i < BOARD_SIZE; i++)
   {
      for (int j = 0; j < BOARD_SIZE; j++)
      {
         if (chessboard[i] == j) 
            SUCCESS_BOARDS.append("Q ");
         else
            SUCCESS_BOARDS.append("* ");
      }
      SUCCESS_BOARDS.append("\n");
   }  
   SUCCESS_BOARDS.append("\n");
}

/**
 * Return the resulting boards if available.
 */
std::string Queens::getResults(void)
{
   return SUCCESS_BOARDS;
}

/**
 * Main function.
 */
int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        std::istringstream iss(argv[1]);
        int val;

        if (iss >> val)
        {
           Queens NQueens(val);
           NQueens.enumerate();
           printf("%s", NQueens.getResults().c_str());

           return 0;
        }
    }

    printf("Invalid Argument(s). Please execute with a single parameter \
dictating the number of queens to solve for. \n\
Example: ./nQueens 8 \n");
    return 1;
}

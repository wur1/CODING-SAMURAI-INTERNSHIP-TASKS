#include <iostream>
using namespace std;

// Function to initialize the game board
void initializeBoard(char board[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Function to display the game board
void displayBoard(char board[3][3])
{
    cout << "  1 2 3" << endl; //*
    for(int i = 0; i < 3; i++)
    {
        cout << i + 1 << " ";
        for(int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if(j < 2)
            {
                cout << "|";
            }
        }
        cout << endl;
        if(i < 2)
        {
            cout << "  -+-+-" << endl;
        }
    }
    cout << endl;
}

// Function to check if a player has won
bool checkWin(char board[3][3], char player)
{
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true; // Horizontal win
        }
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return true; // Vertical win
        }
    }
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true; // Diagonal win (top-left to bottom-right)
    }
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true; // Diagonal win (top-right to bottom-left)
    }
    return false;
}

// Function to check if the game is a draw
bool checkDraw(char board[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                return false; // Empty cell found, game is not a draw
            }
        }
    }
    return true; //All cells are filled, game is a draw
}

// Function to handle a player's move
bool makeMove(char board[3][3], int row, int col, char player)
{
    if(row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
    {
        board[row][col] = player;
        return true; // Move is valid
    }
    return false; // Move is invalid
}

int main(void)
{
    char board[3][3];
    char currentPlayer = 'X';
    char playAgain = 'y'; // Initialize with 'y' to start the game
    bool gameover = false;

    while(playAgain == 'y' || playAgain == 'Y')
    {

        initializeBoard(board);

        cout << "Welcome to Tic-Tac-Toe!" << endl;

        while(!gameover)
        {
            displayBoard(board);
            cout << "Player" << currentPlayer << ", Enter your move (row and column): ";
            int row, col;
            cin >> row >> col;

            if(makeMove(board, row - 1, col - 1, currentPlayer))
            {
                if(checkWin(board, currentPlayer))
                {
                    displayBoard(board);
                    cout << "Player" << currentPlayer << " Wins!" << endl;
                    gameover = true;
                }
                else if(checkDraw(board))
                {
                    displayBoard(board);
                    cout << "Its a Draw!" << endl;
                    gameover = true;
                }
                else
                {
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
            }
        }

        cout << "Do you want to play game again? (y/n): ";
        char playAgain;
        cin >> playAgain;

        if(playAgain == 'y' || playAgain == 'Y')
        {
            //initializeBoard(board);
            gameover = false;
            currentPlayer = 'X'; // Reset the current player
        }
        else
        {
            cout << "Thanks for playing! Goodbye." << endl;
            break; // Exit the game loop
        }
    }

    return 0;
}

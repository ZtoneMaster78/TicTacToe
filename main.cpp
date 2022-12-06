/*
    Instruction of the Tic Tac Toe Program

    1. Gets user's input of how big will the displayBoard be. At least 3 x 3
    2. Function to print the displayBoard
    3. Use a matrix to identify players' pieces
    4. Make a function that can detect wether there is a 3-in-a-row
    5. Every time a player gives an input, clear screen and show updated displayBoard.
       If the displayBoard has already been input, say it has already input and try something else.
       Example of players' input: 2 3 that means matrix[1][2]
    6. Repeat until there is a winner, then stop and give output winner
*/

#include <iostream>
#include <vector>
#define ln std::endl
using std::cout;
using std::cin;
using std::vector;

const int lineLength = 40;
const char empty = ' ';
const char playerOne = 'X';
const char playerTwo = 'O';

void line();
int isThereWinner(int boardSize, vector<vector<char>> playerPiece);
void displayBoard(int boardSize, vector<vector<char>> playerPiece);

int main() {
    int boardSize, changeRow, changeCol, winner;
    bool playerTurn = false; // Player 1 = false; Player 2 = true

    cout << "Input displayBoard size: ";
    cin >> boardSize;
    line();

    // Checks if the the board's size is smaller than 3 or not
    while (boardSize < 3) {
        cout << "Board size must be at least 3" << ln;
        cout << "Input displayBoard size: ";
        cin >> boardSize;
        line();
    }

    // Matrix to store players' pieces
    // empty = ' '; player 1 = 'X'; player 2 = 'O'
    vector<char> oneRow(boardSize, empty);
    vector<vector<char>> playerPiece(boardSize, oneRow);

    do {
        displayBoard(boardSize, playerPiece);

        cout << "Input the row and col that you choose" << ln;
        cout << "Example: 3 4" << ln;
        cout << "This means that player will get row 3 col 4" << ln << ln;

        if (!playerTurn) { // Player 1
            cout << "Player 1's Turn" << ln;
            cin >> changeRow >> changeCol;

            while (((changeRow > boardSize || changeRow < 1) || (changeCol > boardSize || changeCol < 1))
                    || (playerPiece[changeRow - 1][changeCol - 1] != empty)) {
                cout << "Row " << changeRow << " col " << changeCol << " doesn't exist or has already been taken" << ln;
                cout << "Try again" << ln;
                cin >> changeRow >> changeCol;
            }

            playerPiece[changeRow - 1][changeCol - 1] = playerOne;
            playerTurn = true;
        } else { // Player 2
            cout << "Player 2's Turn" << ln;
            cin >> changeRow >> changeCol;

            while (((changeRow > boardSize || changeRow < 1) || (changeCol > boardSize || changeCol < 1))
                    || (playerPiece[changeRow - 1][changeCol - 1] != empty)) {
                cout << "Row " << changeRow << " col " << changeCol << " doesn't exist or has already been taken" << ln;
                cout << "Try again" << ln;
                cin >> changeRow >> changeCol;
            }

            playerPiece[changeRow - 1][changeCol - 1] = playerTwo;
            playerTurn = false;
        }

        winner = isThereWinner(boardSize, playerPiece);
        line();
    } while (winner == 0);

    displayBoard(boardSize, playerPiece);
    line();

    cout << "Player " << winner << " wins" << ln;

    return 0;
}

void line() {
    for (int i = 0; i < lineLength; i++) {
        cout << "=";
    } cout << ln << ln;
}

int isThereWinner (int boardSize, vector<vector<char>> playerPiece) {
    int horizontalOne, horizontalTwo, row, col, diagonalOne, diagonalTwo;
    vector<int> verticalOne(boardSize, 0);
    vector<int> verticalTwo(boardSize, 0);

    // Check All Horizontal and Vertical
    for (int i = 0; i < boardSize; i++) {
        horizontalOne = 0; horizontalTwo = 0;

        for (int j = 0; j < boardSize; j++) {
            if (playerPiece[i][j] == empty) {
                horizontalOne = 0;
                horizontalTwo = 0;
                verticalOne.at(j) = 0;
                verticalTwo.at(j) = 0;
            } else if (playerPiece[i][j] == playerOne) {
                horizontalOne++;
                horizontalTwo = 0;
                verticalOne.at(j)++;
                verticalTwo.at(j) = 0;

                if (horizontalOne > 2 || verticalOne.at(j) > 2) return 1;
            } else if (playerPiece[i][j] == playerTwo) {
                horizontalOne = 0;
                horizontalTwo++;
                verticalOne.at(j) = 0;
                verticalTwo.at(j)++;

                if (horizontalTwo > 2 || verticalTwo.at(j) > 2) return 2;
            }
        }
    }

    // Check All Main Diagonal
    for (int i = 0; i < 2 * (boardSize - 3) + 1; i++) {
        diagonalOne = 0;
        diagonalTwo = 0;

        if (i < boardSize - 2) {
            row = boardSize - i - 3;
            col = 0;
        } else {
            row = 0;
            col = i - (boardSize - 3);
        }
        
        while (row < boardSize && col < boardSize) {
            if (playerPiece[row][col] == empty) {
                diagonalOne = 0;
                diagonalTwo = 0;
            } else if (playerPiece[row][col] == playerOne) {
                diagonalOne++;
                diagonalTwo = 0;

                if (diagonalOne > 2) return 1;
            } else {
                diagonalOne = 0;
                diagonalTwo++;

                if (diagonalTwo > 2) return 2;
            }

            row++;
            col++;
        }
    }

    // Check All Secondary Diagonal
    for (int i = 0; i < 2 * (boardSize - 3) + 1; i++) {
        diagonalOne = 0;
        diagonalTwo = 0;

        if (i < boardSize - 2) {
            row = boardSize - i - 3;
            col = boardSize - 1;
        } else {
            row = 0;
            col = 2 * boardSize - i - 4;
        }
        
        while (row < boardSize && col >= 0) {
            if (playerPiece[row][col] == empty) {
                diagonalOne = 0;
                diagonalTwo = 0;
            } else if (playerPiece[row][col] == playerOne) {
                diagonalOne++;
                diagonalTwo = 0;

                if (diagonalOne > 2) return 1;
            } else {
                diagonalOne = 0;
                diagonalTwo++;

                if (diagonalTwo > 2) return 2;
            }

            row++;
            col--;
        }
    }

    return 0;
}

void displayBoard(int boardSize, vector<vector<char>> playerPiece) {
    for (int i = 1; i <= 4 * boardSize - 1; i++) {
        for (int j = 1; j <= 4 * boardSize - 1; j++) {
            if (i % 4 == 0) cout << "=";
            else if (j % 4 == 0) cout << "|";
            else if ((i - 1) % 4 == 1 && (j - 1) % 4 == 1) cout << playerPiece[(i - 1) / 4][(j- 1) / 4];
            else cout << " ";
        } cout << ln;
    }
}

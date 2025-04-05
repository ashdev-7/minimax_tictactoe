#include <iostream>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE] = {
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' }
};

char PLAYER = 'O';
char COMPUTER = 'X';

// Draws the current board state
void drawBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j];
            if (j < SIZE - 1) cout << " |";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Checks if anyone has won
char checkWinner() {
    for (int i = 0; i < SIZE; i++) {
        // Check rows
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return board[i][0];
        // Check columns
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return board[0][i];
    }

    // Check diagonals
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return board[0][0];

    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return board[0][2];

    return ' ';
}

bool isBoardFull() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

int minimax(bool isComputerTurn) {
    char winner = checkWinner();
    if (winner == COMPUTER) return 1;
    if (winner == PLAYER) return -1;

    int bestScore = isComputerTurn ? -1000 : 1000;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = isComputerTurn ? COMPUTER : PLAYER;
                int score = minimax(!isComputerTurn);
                board[i][j] = ' ';

                if (isComputerTurn)
                    bestScore = max(score, bestScore);
                else
                    bestScore = min(score, bestScore);
            }
        }
    }

    return bestScore;
}

// best move for the computer
void computerPlay() {
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int score = minimax(false);
                board[i][j] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    board[moveRow][moveCol] = COMPUTER;
}

// Gets the player's move
void playerPlay() {
    int row, col;
    while (true) {
        cout << "Your move (row and column from 1 to 3): ";
        cin >> row >> col;
        row--; col--;
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
            board[row][col] = PLAYER;
            break;
        } else {
            cout << "That spot is either taken or out of bounds. Try again.\n";
        }
    }
}


int main() {
    cout << "Welcome to Tic-Tac-Toe!\nYou = O, Computer = X\n";
    drawBoard();

    while (true) {
        playerPlay();
        drawBoard();

        if (checkWinner() == PLAYER) {
            cout << "You win! \n";
            break;
        } else if (isBoardFull()) {
            cout << "It's a draw. \n";
            break;
        }

        cout << "Computer's turn...\n";
        computerPlay();
        drawBoard();

        if (checkWinner() == COMPUTER) {
            cout << "Computer wins! \n";
            break;
        } else if (isBoardFull()) {
            cout << "It's a draw. \n";
            break;
        }
    }

    return 0;
}

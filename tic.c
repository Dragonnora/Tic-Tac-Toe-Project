#include <stdio.h>
#include <stdlib.h>

// ****************** STRUCTURES ********************************************* // 

// Enumeration for players
enum Player {
    PLAYER_X = 'X',
    PLAYER_O = 'O',
    NO_PLAYER = ' ' // Use this for empty spaces on the board
};

// Structure to represent a move
struct Move {
    enum Player player;
    int row;
    int col;
    int round;
    struct Move* next;
};

// ****************** FUNCTIONS ********************************************* //


// Function to display the board
void displayBoard(char board[4][4]) {
    printf("\n\n");
    printf("    1   2   3   4 \n");
    printf("  |---|---|---|---|\n");

    for (int i = 0; i < 4; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < 4; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n  |---|---|---|---|\n");
    }
}

// Function to check for game end conditions
int endConditions(const char board[4][4], enum Player player) {
    // Checks rows and columns for a win
    for (int i = 0; i < 4; i++) {
        if ((board[i][0] == (char)player && board[i][1] == (char)player &&
             board[i][2] == (char)player && board[i][3] == (char)player) ||
            (board[0][i] == (char)player && board[1][i] == (char)player &&
             board[2][i] == (char)player && board[3][i] == (char)player)) {
            return 1; // Win in row or column
        }
    }

    // Checks diagonals for a win
    if ((board[0][0] == (char)player && board[1][1] == (char)player &&
         board[2][2] == (char)player && board[3][3] == (char)player) ||
        (board[0][3] == (char)player && board[1][2] == (char)player &&
         board[2][1] == (char)player && board[3][0] == (char)player)) {
        return 1; // Win in diagonals
    }

    // Checks for a tie
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == ' ') {
                return 0; // The game is still ongoing
            }
        }
    }

    return -1; // It's a tie
}

// Function to add a move to the linked list
void addMove(struct Move** head, enum Player player, int row, int col, int round) {
    struct Move* newMove = (struct Move*)malloc(sizeof(struct Move));
    newMove->player = player;
    newMove->row = row;
    newMove->col = col;
    newMove->round = round;
    newMove->next = *head;
    *head = newMove;
}

// Function to display the move sheet
void displayMoveSheet(struct Move* head) {
    printf("~ STATS ~\n\n");

    while (head != NULL) {
        printf("Player %c moved to row %d, column %d in round %d\n", (head->player == PLAYER_X) ? 'X' : 'O', head->row, head->col, head->round);
        head = head->next;
    }
}

// Function to free the allocated memory for the move list
void freeMoves(struct Move* head) {
    while (head != NULL) {
        struct Move* temp = head;
        head = head->next;
        free(temp);
    }
}

// ********************* MAIN FUNCTION ************************************** //

int main() {
    
    int round = 1;
    struct Move* moveList = NULL;

    // Initializes the board
    char board[4][4] = { { ' ', ' ', ' ', ' ' },
                        { ' ', ' ', ' ', ' ' },
                        { ' ', ' ', ' ', ' ' },
                        { ' ', ' ', ' ', ' ' } };

    // Game loop
    while (1) {
        // Displays the current board
        displayBoard(board);

        // Gets move from the user
        enum Player player = (round % 2 == 1) ? PLAYER_X : PLAYER_O;
        int row, col;
        int condition = 0;
        printf("Player %c, enter your move:\n", (player == PLAYER_X) ? 'X' : 'O');

    // ********* INPUT VALIDATION ********* //
        
        // Input validation for the row
        do {
            // Gets input from the user
            printf("Row (1-4): ");

            // Checks if the input is an integer
            if (scanf("%d", &row) == 1 && row >= 1 && row <= 4) {
                condition = 1; // Input is valid, exit the loop
            } else {
                printf("Invalid input. Enter an integer between 1 and 4.\n");

                // Clears input buffer
                while (getchar() != '\n');

                // Set condition to 0 to continue the loop
                condition = 0;
            }

        } while (condition == 0);

        // Input validation for the column
        do {
            // Gets input from the user
            printf("Column (1-4): ");

            // Checks if the input is an integer
            if (scanf("%d", &col) == 1 && col >= 1 && col <= 4) {
                condition = 1; // Input is valid, exit the loop
            } else {
                printf("Invalid input. Enter an integer between 1 and 4.\n");

                // Clears input buffer
                while (getchar() != '\n');

                // Sets condition to 0 to continue the loop
                condition = 0;
            }

        } while (condition == 0);
        
        
    // ******************************* // 
        
        // Verifies if the spot is already marked
        if (row >= 1 && row <= 4 && col >= 1 && col <= 4 && board[row - 1][col - 1] == ' ') {
            board[row - 1][col - 1] = (char)player;
            addMove(&moveList, player, row, col, round);
            round++;
        } else {
            printf("Invalid move. Try again.\n");
        }

        // Checks for game end conditions
        int outcome = endConditions(board, player);
        if (outcome == 1) {
            printf("Player %c WINS!\n", (player == PLAYER_X) ? 'X' : 'O');
            displayMoveSheet(moveList);
            freeMoves(moveList);
            return 0;
        } else if (outcome == -1) {
            printf("It's a TIE!\n");
            displayMoveSheet(moveList);
            freeMoves(moveList);
            return 0;
        }
    }

    return 0;
}

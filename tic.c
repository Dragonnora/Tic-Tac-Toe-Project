#include <stdio.h>
#include <stdlib.h>


// ****************** ENUMERATION & STRUCTURE ********************************* // 

// Enumeration for players
enum Player {
    PLAYER_X = 'X',
    PLAYER_O = 'O',
    NO_PLAYER = ' ' // For empty spaces on the board
};

// Structure to represent a move
struct Move {
    enum Player player;
    int row;
    int col;
    int round;
    struct Move* next;
};

// ********************* PROTOTYPES ****************************************** //

// Prototypes
void drawBoard(char [4][4]);
int gameOutcomes(const char [4][4], enum Player);
int rowOutcomes(const char [4][4], enum Player);
int colOutcomes(const char [4][4], enum Player);
int diagOutcomes(const char [4][4], enum Player);
void addMove(struct Move**, enum Player, int, int, int);
void displayMoveSheet(struct Move*);
void freeMoves(struct Move*);


// ********************* MAIN FUNCTION ************************************** //

int main() {
    // Makes the output blue!
    system("COLOR 9A");
    
    char playAgain = 'y';
    
     // Game loop 
    do{ 
    
    int round = 1;
    struct Move* moveList = NULL;

    // Initializes the board
    char board[4][4] = { { ' ', ' ', ' ', ' ' },
                        { ' ', ' ', ' ', ' ' },
                        { ' ', ' ', ' ', ' ' },
                        { ' ', ' ', ' ', ' ' } };
     
        
        while (1) {
            // draws the current board
            drawBoard(board);
    
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
    
            // Checks for game outcomes
            int outcome = gameOutcomes(board, player);
            if (outcome == 1) {
                printf("\n\nPlayer %c wins!\n\n\n", (player == PLAYER_X) ? 'X' : 'O');
                displayMoveSheet(moveList);
                freeMoves(moveList);
                break;
                
            } else if (outcome == -1) {
                printf("\n\nNo one wins!\n");
                displayMoveSheet(moveList);
                freeMoves(moveList);
                break; 
            }
        }
        
        printf("\n\nPlay again? (y/n): ");
        scanf(" %c", &playAgain);
        getchar(); // Consume the newline character
        
    } while (playAgain == 'y' || playAgain == 'Y'); 
    
        
    return 0;
}

// ****************** OTHER FUNCTIONS ***************************************** //


// Function to draw the board
void drawBoard(char board[4][4]) {
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

// Function that checks game outcomes
int gameOutcomes(const char board[4][4], enum Player player) {
    if (rowOutcomes(board, player) || colOutcomes(board, player) || diagOutcomes(board, player)) {
        return 1; // Win
    }

    // Check for a tie
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == ' ') {
                return 0; // The game is still ongoing
            }
        }
    }

    return -1; // It's a tie
}

// Function to see if rows have a winning outcome
int rowOutcomes(const char board[4][4], enum Player player) {
    for (int i = 0; i < 4; i++) {
        if (board[i][0] == (char)player && board[i][1] == (char)player &&
            board[i][2] == (char)player && board[i][3] == (char)player) {
            return 1; // Win in row
        }
    }
    return 0;
}

// Function to see if columns have a winning outcome 
int colOutcomes(const char board[4][4], enum Player player) {
    for (int i = 0; i < 4; i++) {
        if (board[0][i] == (char)player && board[1][i] == (char)player &&
            board[2][i] == (char)player && board[3][i] == (char)player) {
            return 1; // Win in column
        }
    }
    return 0;
}

// Function to see if diagonals have a winning outcome
int diagOutcomes(const char board[4][4], enum Player player) {
    if ((board[0][0] == (char)player && board[1][1] == (char)player &&
         board[2][2] == (char)player && board[3][3] == (char)player) ||
        (board[0][3] == (char)player && board[1][2] == (char)player &&
         board[2][1] == (char)player && board[3][0] == (char)player)) {
        return 1; // Win in diagonals
    }
    return 0;
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
    printf("~ MOVE SHEET ~\n\n");

    int count = 0;
    struct Move* temp = head;

    // Count the number of moves
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    // Create an array to store moves
    struct Move** movesArray = malloc(count * sizeof(struct Move*));
    if (movesArray == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Copy moves to the array
    int i = 0;
    while (head != NULL) {
        movesArray[i] = head;
        head = head->next;
        i++;
    }

    // Print moves in reverse order
    for (int j = i - 1; j >= 0; j--) {
        printf("Player %c moved to row %d, column %d in round %d\n", 
            (movesArray[j]->player == PLAYER_X) ? 'X' : 'O', 
            movesArray[j]->row, movesArray[j]->col, movesArray[j]->round);
    }

    // Free the array
    free(movesArray);
}

// Function to free the allocated memory for the move list
void freeMoves(struct Move* head) {
    while (head != NULL) {
        struct Move* temp = head;
        head = head->next;
        free(temp);
    }
}

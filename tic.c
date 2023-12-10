#include <stdio.h>
#include <stdlib.h>

// ****************** STRUCTURE ********************************************* // 

// Structure to represent a move
struct Move {
    char player;
    int position;
    int round;
    struct Move* next;
};

// ****************** FUNCTIONS ********************************************* //  


// Function to add a move to the linked list
void addMove(struct Move** head, char player, int position, int round) {
    struct Move* newMove = (struct Move*)malloc(sizeof(struct Move));
    newMove->player = player;
    newMove->position = position;
    newMove->round = round;
    newMove->next = *head;
    *head = newMove;
}

// Function to check for game end conditions
int endConditions(const char board[4][4], char player) {
    // Check rows and columns for a win
    for (int i = 0; i < 4; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player && board[i][3] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player && board[3][i] == player)) {
            return 1; // Win in row or column
        }
    }

    // Check diagonals for a win
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player && board[3][3] == player) ||
        (board[0][3] == player && board[1][2] == player && board[2][1] == player && board[3][0] == player)) {
        return 1; // Win in diagonals
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


// Function to display the move sheet
void displayMoveSheet(struct Move* head) {
    printf("~ STATS ~\n\n");

    while (head != NULL) {
        printf("Player %c moved to position %d in round %d\n", head->player, head->position, head->round);
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
    // Initialize the board
    char board[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = ' ';
        }
    }
    
    struct Move* moveList = NULL;

    // Game loop
    int round = 1;
    while (1) {
        // Display the current board
        printf("Round %d\n", round);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                printf("| %c ", board[i][j]);
            }
            printf("|\n");
        }
        printf("\n");
        
        
        // Get move from the user
        char player = (round % 2 == 1) ? 'X' : 'O';
        int position;
        printf("Player %c, enter your move (1-16): ", player);
        scanf("%d", &position);

        // Update the board and move list
        int row = (position - 1) / 4;
        int col = (position - 1) % 4;

        if (board[row][col] == ' ') {
            board[row][col] = player;
            addMove(&moveList, player, position, round);
            round++;
        } else {
            printf("Invalid move. Try again.\n");
        }

        // Check for game end conditions
        int outcome = endConditions(board, player);
        if (outcome == 1) {
            printf("Player %c WINS!\n", player);
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


    

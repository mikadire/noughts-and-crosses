#include <stdbool.h>
#include <stdio.h>

//function declaration
char *place_X(char *board);
char *place_O(char *board);
char *player(int n, char *board);
void print_board(const char board[]);
char check_win(const char board[]);
int eval(const char board[]);
int minimax(char board[], int depth, int alpha, int beta, bool is_maxing);
char *computer_move(char *board);

//Constant values for 3 possible values of a square
const char HUMAN = 'X';
const char COMPUTER = 'O';
const char EMPTY = '-';
//Positions calculated counter
long int POS = 0, TOTAL;
	
int main() {
	
	int n = 0, total = 0;
	char board[9];
	
	//board initialised to dashes
	for (int i = 0; i < 9; i++) {
		board[i] = EMPTY;
	}
	
	printf("Welcome to noughts and crosses!\n");
	printf("\n");
	print_board(board);

	//play while not a win or draw
	while (!check_win(board)) {
		
		//alternates player
		player(n, board);
		
		printf("\n");
		print_board(board);
		
		n++;
	}
	

	if (check_win(board) == EMPTY) {
		printf("Game over. It's a draw!\n\n");
	} else if (check_win(board) == HUMAN ) {
		printf("Game over. You have won!\n\n");
	} else {
		printf("Game over. The computer has won!\n\n");
	}
	
	printf("The computer calculated a total of %ld positions!\n\n", TOTAL);
	
	return 0;
}

char *place_X(char *board) {
	
	int pos_X;
	
	printf("Choose a position from 1-9 to place your X: ");
	
	scanf("%d", &pos_X);
	
	if (board[pos_X-1] != EMPTY) {
		printf("This position has already been filled, please try another.\n");
		place_X(board);
	} else {
		board[pos_X-1] = HUMAN;
	}
	
	return board;
}

//Function for second player
char *place_O(char *board) {
	
	int pos_O;
	
	printf("Choose a position from 1-9 to place your O: ");
	
	scanf("%d", &pos_O);
	
	if (board[pos_O-1] != EMPTY) {
		printf("This position has already been filled, please try another.\n");
		place_O(board);
	} else {
		board[pos_O-1] = COMPUTER;
	}
	
	return board;
}

//Alternates between players (assuming n is iterated)
char *player(int n, char *board) {
	if (n % 2 == 0) {
		return place_X(board);
	} else {
		return computer_move(board);
	}
}

void print_board(const char board[]) {
	
	for (int i = 0; i < 9; i++) {
		printf("%c ", board[i]);
		//new line every third square
		if ((i+1)%3 == 0)
			printf("\n");
	}
	printf("\n");	
}

char check_win(const char board[]) {
	
	char flag = 0;
	
	//Check row
	for (int i = 0; i <= 6; i += 3) {
		if (board[i] != EMPTY && board[i] == board[i+1] && board[i] == board[i+2]) {
			//set flag to winning player
			flag = board[i];
		}
	}
	
	//Check column
	for (int i = 0; i < 3; i++) {
		if (board[i] != EMPTY && board[i] == board[i+3] && board[i] == board[i+6]) {
			//set flag to winning player
			flag = board[i];
		}
	}
	
	//Check diagonal left to right
	if (board[0] != EMPTY && board[0] == board[4] && board[0] == board[8]) {
		//set flag to winning player
		flag = board[0];
	}
	
	//Check diagonal right to left
	if (board[2] != EMPTY && board[2] == board[4] && board[2] == board[6]) {
		//set flag to winning player
		flag = board[2];
	}
	
	//check draw
	int space = 0;
	
	for (int i = 0; i < 9; i++) {
		//Empty square means no draw
		if (board[i] == EMPTY) {
			space++;
		}
	}

	//return flag for win, EMPTY for draw, 0 for no result
	if (flag != 0) {
		return flag;
	} else if (space == 0) {
		return EMPTY;
	} else {
		return 0;
	}
}


//Only call if check_win != 0. HUMAN/X = 10, COMPUTER/O = -10, DRAW = 0
int eval(const char board[]) {
	
	const char winner = check_win(board);
	
	if (winner == HUMAN) {
		return 10;
	} else if (winner == COMPUTER) {
		return -10;
	}
	return 0;
}

int minimax(char board[], int depth, int alpha, int beta, bool is_maxing) {
	
	//Counts calls. Used in computer_move
	POS++;
	
	//If game is over, return result as score 
	if (check_win(board)) {
		return eval(board);
	}
	
	int bestScore, score;
	
	//Maximising player - X
	if (is_maxing) { 

		//bestScore set low as player is trying to ger high score
        	bestScore = -100;
        	
        	for (int i = 0; i < 9; i++) {
			//If spot is empty, place X there and run minimax for minimising player
        		if (board[i] == EMPTY) {
        			board[i] = HUMAN;
        			score = minimax(board, depth + 1, alpha, beta, false) - depth;
        			//If this move leads to a better result, update bestScore
				if (score > bestScore) {
            				bestScore = score;
            			}
				//Undo move
            			board[i] = EMPTY;
            		}
            		if (alpha < bestScore) {
            			alpha = bestScore;
            		}
       			if (beta <= alpha) {
       				break;
            		}
            	}
        	return bestScore;
	//Minimising player - O. Same code as above except lower is better
	} else {
        	
        	bestScore = 100;
        
        	for (int i = 0; i < 9; i++) {
        		if (board[i] == EMPTY) {
        			board[i] = COMPUTER;
        			score = minimax(board, depth + 1, alpha, beta, true) + depth;
        			if (score < bestScore) {
            				bestScore = score;
            			}
            			board[i] = EMPTY;
            		}
            		if (beta > bestScore) {
       				beta = bestScore;
       			}
            		if (beta <= alpha) {
            			break;
            		}
            	}
       		return bestScore;	
	}
}

char *computer_move(char *board) {
	
	//Computer is the minimising player to bestScore high
	int bestScore = 100, score, move;

	//Incremented in minimax (counts call). Reset after each move
	POS = 0;
	
	for (int i = 0; i < 9; i++) {
        	if (board[i] == EMPTY) {     			      		
			board[i] = COMPUTER;
        		score = minimax(board, 0, -100, 100, true);       		
			if (score < bestScore) {
        			bestScore = score;
				//Save the move if it leads to a better result
        			move = i;
        		}
        		board[i] = EMPTY;
        	}
        }
        
        //Add positions calculated for last move to total
	TOTAL += POS;
	
	printf("I calculated %ld positions to find this move!\n", POS);
	
        board[move] = COMPUTER;   
             
        return board;
}

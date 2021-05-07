#include <stdbool.h>
#include <stdio.h>

//function declaration
char *place_X(char *board);
char *place_O(char *board);
char *player(int n, char *board);
void print_board(const char board[]);
char check_win(const char board[]);
int eval(const char board[]);
int MinMax(char board[], bool isMaxing);
char *computerMove(char *board);

//Constant values for 3 possible values of a square
const char HUMAN = 'X';
const char COMPUTER = 'O';
const char EMPTY = '-';
	
int main() {
	
	int n = 0;
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
	} else {
		printf("Game over. %c has won!\n\n", check_win(board));
	}
	
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
		return computerMove(board);
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


//Only call if check_win != 0. HUMAN/X = 1, COMPUTER/O = -1, DRAW = 0
int eval(const char board[]) {
	
	int score;
	
	if (check_win(board) == HUMAN) {
		score = 1;
	} else if (check_win(board) == COMPUTER) {
		score = -1;
	} else {
		score = 0;
	}
	
	return score;
}

int MinMax(char board[], bool isMaxing) {
	
	//If game is over, return result as score (1,0,-1)
	if (check_win(board)) {
		return eval(board);
	}
	
	int bestScore, score;
	
	//Maximising player - X
	if (isMaxing) { 

		//bestScore set low as player is trying to ger high score
        	bestScore = -100;
        	
        	for (int i = 0; i < 9; i++) {
			//If spot is empty, place X there and run MinMax for minimising player
        		if (board[i] == EMPTY) {
        			board[i] = HUMAN;
        			score = MinMax(board, false);
        			//If this move leads to a better result, update bestScore
				if (score > bestScore) {
            				bestScore = score;
            			}
				//Undo move
            			board[i] = EMPTY;
            		}
            	}
        	return bestScore;
	//Minimising player - O. Same code as above except lower is better
	} else {
        	
        	bestScore = 100;
        
        	for (int i = 0; i < 9; i++) {
        		if (board[i] == EMPTY) {
        			board[i] = COMPUTER;
        			score = MinMax(board, true);
        			if (score < bestScore) {
            				bestScore = score;
            			}
            			board[i] = EMPTY;
            		}
            	}
       		return bestScore;	
	}
}

char *computerMove(char *board) {
	
	//Computer is the minimising player to bestScore high
	int bestScore = 100, score, move;
	
	for (int i = 0; i < 9; i++) {
        	if (board[i] == EMPTY) {     			
        		board[i] = COMPUTER;
        		score = MinMax(board, true);
        		if (score < bestScore) {
        			bestScore = score;
				//Save the move if it leads to a better result
        			move = i;
        		}
        		board[i] = EMPTY;
        	}
        }
        board[move] = COMPUTER;
        
        return board;
}

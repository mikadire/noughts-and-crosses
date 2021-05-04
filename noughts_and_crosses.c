#include <stdio.h>

//function declaration
void print_board(const char *board);
char three_in_row(const char *board);
int is_draw(const char *board);
char *place_X(char *board);
char *place_O(char *board);
char *player(int n, char *board);

//Constant values for 3 possible values of a square
const char NOUGHTS = 'O';
const char CROSSES = 'X';
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
	while (!three_in_row(board) && !is_draw(board)) {
		
		player(n, board);
		
		printf("\n");
		print_board(board);
		
		n++;
	}
	
	//winner set to flag value in three_in_row 
	char winner = three_in_row(board);
	
	if (is_draw(board)) {
		printf("Game over. It's a draw!\n\n");
	} else {
		printf("Game over. %c has won!\n\n", winner);
	}
	
	return 0;
}

char *place_O(char *board) {
	
	int pos_O;
	
	printf("Choose a position from 1-9 to place your O: ");
	
	scanf("%d", &pos_O);
	
	if (board[pos_O-1] != EMPTY) {
		printf("This position has already been filled, please try another.\n");
		place_O(board);
	} else {
		board[pos_O-1] = NOUGHTS;
	}
	return board;
}

char *place_X(char *board) {
	
	int pos_X;
	
	printf("Choose a position from 1-9 to place your X: ");
	
	scanf("%d", &pos_X);
	
	if (board[pos_X-1] != EMPTY) {
		printf("This position has already been filled, please try another.\n");
		place_X(board);
	} else {
		board[pos_X-1] = CROSSES;
	}
	return board;
}

//Alternates between Xs and Os
char *player(int n, char *board) {
	if (n % 2 == 0) 
		return place_O(board);
	else	
		return place_X(board);
}

void print_board(const char *board) {
	
	for (int i = 0; i < 9; i++) {
		printf("%c ", board[i]);
		//new line every third square
		if ((i+1)%3 == 0)
			printf("\n");
	}
	printf("\n");	
}

char three_in_row(const char *board) {
	
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
	return flag;
}

int is_draw(const char *board) {
	for (int i = 0; i < 9; i++) {
		//Empty square means no draw
		if (board[i] == EMPTY)	return 0;
	}
	return 1;
}

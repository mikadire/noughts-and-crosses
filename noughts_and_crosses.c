#include <stdio.h>

//function declaration
void print_board(const char *board);
char three_in_row(const char *board);
int is_draw(const char *board);
char *place_X(char *board);
char *place_O(char *board);

const char NOUGHTS = 'O';
const char CROSSES = 'X';
const char EMPTY = '-';
	
int main() {
	//board initialised to 0s
	char board[9];
	
	for (int i = 0; i < 9; i++) {
		board[i] = '-';
	}
	
	printf("\n");
	print_board(board);
	
	//First player places 0
	place_O(board);
	printf("\n");
	print_board(board);
	
	//play while not a win or draw
	while (!three_in_row(board) && !is_draw(board)) {
		
		place_X(board);
		printf("\n");
		print_board(board);
		
		place_O(board);
		printf("\n");
		print_board(board);
	}
	
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

//choose player
/*char *player(parameter) {

}*/

void print_board(const char *board) {
	
	for (int i = 0; i < 9; i++) {
		printf("%c ", board[i]);
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
			flag = board[i];
		}
	}
	
	//Check column
	for (int i = 0; i < 3; i++) {
		if (board[i] != EMPTY && board[i] == board[i+3] && board[i] == board[i+6]) {
			flag = board[i];
		}
	}
	
	//Check diagonal left to right
	if (board[0] != EMPTY && board[0] == board[4] && board[0] == board[8]) {
		flag = board[0];
	}
	
	//Check diagonal right to left
	if (board[2] != EMPTY && board[2] == board[4] && board[2] == board[6]) {
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

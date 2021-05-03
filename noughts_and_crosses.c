#include <stdio.h>
#include <stdbool.h>


//function declaration
void print_board(int *board);
int three_in_row(int *board);
int is_draw(int *board);
int *place_X(int *board);
int *place_O(int *board);

const int NOUGHTS = 1;
const int CROSSES = 2;
const int EMPTY = 0;
	
int main() {
	//board initialised to 0s
	int board[9] = {0}
	
	printf("\n");
	print_board(board);
	
	//play while not a win or draw
	while (!three_in_row(board) && !is_draw(board)) {

	}
	
	if (three_in_row) {
		printf("Game over. %d has won!", winner);
	} else {
		printf("Game over. It's a draw!);
	}
	
	return 0;
}

int *place_O(int *board) {
	
	int pos_O;
	
	printf("Choose a position from 1-9 to place your O.\n");
	
	scanf("%d", &pos_O);
	
	if (board[pos_O-1] != 0) {
		printf("This position has already been filled, please try another.\n");
		place_O(board);
	} else {
		board[pos_O-1] = NOUGHTS;
	}
	return board;
}

int *place_X(int *board) {
	
	int pos_X;
	
	printf("Choose a position from 1-9 to place your X.\n");
	
	scanf("%d", &pos_X);
	
	if (board[pos_X-1] != 0) {
		printf("This position has already been filled, please try another.\n");
		place_X(board);
	} else {
		board[pos_X-1] = CROSSES;
	}
	return board;
}

void print_board(int *board) {
	
	for (int i = 0; i < 9; i++) {
		printf("%d ", board[i]);
		if ((i+1)%3 == 0)
			printf("\n");
	}
	printf("\n");	
}

int three_in_row(int *board) {
	
	int flag = 0;
	
	for (int i = 0; i <= 6; i + 3) {
		if (board[i] == board[i+1] && board[i] == board[i+2]) {
			flag = 1;
		}
	}
	
	for (int i = 0; i < 3; i++) {
		if (board[i] == board[i+3] && board[i] == board[i+6]) {
			flag = 1;
		}
	}
	
	if (board[0] == board[4] && board[0] == board[8])	flag = 1;
	if (board[2] == board[4] && board[2] == board[6])	flag = 1;
	
	return flag;
}

int is_draw(int *board) {
	for (int i = 0; i < 9; i++) {
		if (board[i] == EMPTY)	return 0;
	}
}

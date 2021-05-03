#include <stdio.h>



void print_board(const int *board) {
}

int check_win(/*board??*/) {
}

void place_X () {
	
	int pos_X;
	
	printf("Choose a position from 1-9 to place your X.");
	
	scanf("%d", &pos_X);
	
	if (board[pos_X-1] != 0) {
		printf("This position has already been filled, please try another.");
		place_X();
	}
	
	board[pos_X-1] = 1;
}

void place_O () {
	
	int pos_O;
	
	printf("Choose a position from 1-9 to place your O.");
	
	scanf("%d", &pos_O);
	
	if (board[pos_O-1] != 0) {
		printf("This position has already been filled, please try another.");
		place_O();
	}
	
	board[pos_O-1] = 1;
}

int main() {

	int board[9] = {0};
	
	const int NOUGHTS = 1;
	const int CROSSES = 2;
	const int EMPTY = 0;
	
	

	return 0;
}

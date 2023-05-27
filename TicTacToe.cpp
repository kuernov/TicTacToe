#include <iostream>
#include <string>

#define PLAYER1 1
#define PLAYER2 2
#define PLAYER1MOVE 'x'
#define COMPUTERMOVE 'o'
#define BOARDSIZE 3

using namespace std;

char board[BOARDSIZE][BOARDSIZE];
struct Move {
	int row, column;
};

void showBoard(char board[BOARDSIZE][BOARDSIZE])
{
	printf("\n\n");

	printf("\t\t\t  %c | %c  | %c  \n", board[0][0],
		board[0][1], board[0][2]);
	printf("\t\t\t--------------\n");
	printf("\t\t\t  %c | %c  | %c  \n", board[1][0],
		board[1][1], board[1][2]);
	printf("\t\t\t--------------\n");
	printf("\t\t\t  %c | %c  | %c  \n\n", board[2][0],
		board[2][1], board[2][2]);

	return;
}

void showInstructions()
{
	printf("\t\t\t  Tic-Tac-Toe\n\n");
	printf("Choose a cell numbered from 1 to 9 as below"
		" and play\n\n");

	printf("\t\t\t  1 | 2  | 3  \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t  4 | 5  | 6  \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t  7 | 8  | 9  \n\n");

	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");

	return;
}

void createBoard() {
	for (size_t w = 0; w < BOARDSIZE; w++)
	{
		for (size_t k = 0; k < BOARDSIZE; k++) {
			board[w][k] = '  ';
		}
	}
}


bool isGameOver(char player) {
	for (size_t w = 0; w < BOARDSIZE; w++)
	{
		if (board[w][0] == player && board[w][1] == player && board[w][2] == player)
			return true;
	}
	for (size_t k = 0; k < BOARDSIZE; k++)
	{
		if (board[0][k] == player && board[1][k] == player && board[2][k] == player)
			return true;
	}
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
		return true;
	if (board[0][2] == player && board[2][2] == player && board[2][0] == player)
		return true;
	return false;
}

int evaluate(char board[BOARDSIZE][BOARDSIZE]) {
	for (size_t col = 0; col < BOARDSIZE; col++)
	{
		if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
			if (board[0][col] == COMPUTERMOVE)
				return -10;
			else if (board[0][col] == PLAYER1MOVE)
				return 10;
		}
	}
	for (size_t r = 0; r < BOARDSIZE; r++)
	{
		if (board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
			if (board[r][0] == COMPUTERMOVE)
				return -10;
			else if (board[r][0] == PLAYER1MOVE)
				return 10;
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		if (board[0][0] == COMPUTERMOVE)
			return -10;
		else if (board[0][0] == PLAYER1MOVE)
			return 10;
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
		if (board[0][2] == COMPUTERMOVE)
			return -10;
		else if (board[0][2] == PLAYER1MOVE)
			return 10;
	}
	return 0;
}
bool isBoardFull() {
	for (size_t w = 0; w < BOARDSIZE; w++)
	{
		for (size_t k = 0; k < BOARDSIZE; k++) {
			if (board[w][k] == ' ')
				return false;
		}
	}
	return true;
}

int minmax(int depth, bool isMinimazing, int alpha, int beta) {
	int result = evaluate(board);
	int best;
	if (result == -10)
		return result+depth;
	if (result == 10)
		return result- depth;

	if (isBoardFull())
		return 0;
	if (isMinimazing) {
		best =INT_MAX;
		for (size_t r = 0; r < BOARDSIZE; r++)
		{
			for (size_t c = 0; c < BOARDSIZE; c++)
			{
				if (board[r][c] == ' ') {
					board[r][c] = COMPUTERMOVE;
					best = min(best, minmax(depth + 1, false, alpha, beta));
					board[r][c] = ' ';
					beta = min(beta, best);
					if (beta <= alpha)
						break;
				}
			}
		}
		return best + depth;
	}
	else if (!isMinimazing) {
		best = INT_MIN;
		for (size_t r = 0; r < BOARDSIZE; r++)
		{
			for (size_t c = 0; c < BOARDSIZE; c++)
			{
				if (board[r][c] == ' ') {
					board[r][c] = PLAYER1MOVE;
					best = max(best, minmax(depth + 1, true, alpha, beta));
					board[r][c] = ' ';
					alpha = max(alpha, best);
					if (beta <= alpha)
						break;
				}
			}
		}
		return best - depth;
	}

	
}



bool isLegalMove(int row, int column) {
	if (row < 0 || row>2 || column < 0 || column>2)
		return false;
	if (board[row][column] != ' ')
		return false;
	return true;
}

void playerMove(int row, int column, char player) {
	board[row][column] = player;
}

Move findBestMove() {
	int bestValue = INT_MAX;
	Move bestMove;
	bestMove.row = -1;
	bestMove.column = -1;
	for (size_t r = 0; r < BOARDSIZE; r++)
	{
		for (size_t c = 0; c < BOARDSIZE; c++)
		{
			if (board[r][c] == ' ') {
				board[r][c] = COMPUTERMOVE;
				int moveValue = minmax(0,false,INT_MIN,INT_MAX);
				board[r][c] = ' ';
				if (moveValue < bestValue) {
					bestMove.column = c;
					bestMove.row = r;
					bestValue = moveValue;
				}
			}
		}
	}
	cout << bestValue << endl;
	return bestMove;
}

void playGame(int whoseTurn) {
	int option= -1;
	int move;
	int row, column;
	while (option != 0) {
		cout << "1. Play the game." << endl;
		cout << "0. Exit" << endl;
		cout << "Choose: ";
		cin >> option;
		cout << endl;
		switch (option){
		case 1:
			createBoard();
			showInstructions();
			while (!isGameOver(PLAYER1MOVE) && !isGameOver(COMPUTERMOVE) && !isBoardFull()) {
				if (whoseTurn == PLAYER1) {
					cout << "Wprowadz swoj ruch: ";
					cin >> move;
					cout << endl;
					row = (move - 1) / BOARDSIZE;
					column = (move - 1) % BOARDSIZE;
					if (!isLegalMove(row, column)) {
						cout << "Niepoprawny ruch!" << endl;
						continue;
					}
					playerMove(row, column, PLAYER1MOVE);
					showBoard(board);
					whoseTurn = PLAYER2;
				}
				else if (whoseTurn == PLAYER2) {
					Move move = findBestMove();
					playerMove(move.row, move.column, COMPUTERMOVE);
					showBoard(board);
					whoseTurn = PLAYER1;
				}
			}
			if (!isGameOver(PLAYER1MOVE) && !isGameOver(COMPUTERMOVE) && isBoardFull())
				cout << "Draw!" << endl;
			else if (isGameOver(PLAYER1MOVE))
				cout << "Player 1 won!" << endl << endl << endl << endl;
			else if (isGameOver(COMPUTERMOVE))
				cout << "Computer won!" << endl<<endl<<endl<<endl;
			break;
		default:
			break;
		}
	}
	return;
}

int main() {
	playGame(PLAYER1);
	return 0;
}
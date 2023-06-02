#include <iostream>
#include <string>

#define PLAYER1 1
#define PLAYER2 2
#define PLAYER1MOVE 'x'
#define COMPUTERMOVE 'o'
//#define BOARDSIZE 4
//#define pointsToWin 4
#define MAX_DEPTH 6

using namespace std;



//char board[BOARDSIZE][BOARDSIZE];
struct Move {
	int row, column;
};



void showBoard(char** board, int size)
{
	cout << endl << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << "\t\t\t  ";
		for (size_t j = 0; j < size; j++)
		{
			cout << board[i][j];
			if (j < size - 1) {
				cout << " | ";
			}
		}
		cout << endl;
		if (i < size - 1) {
			cout << "\t\t\t";
			for (size_t k = 0; k < size; k++)
			{
				cout << "----";
			}
			cout << endl;
		}
	}
	return;
}

void showInstructions(int size)
{
	cout << "\t\t\t  Tic-Tac-Toe" << endl << endl;
	cout << "Choose a cell numbered from 1 to 9 as below"
		" and play" << endl << endl;
	int k = 1;
	cout << endl << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << "\t\t\t  ";
		for (size_t j = 0; j < size; j++)
		{
			cout << k++;
			if (j < size - 1) {
				cout << " | ";
			}
		}
		cout << endl;
		if (i < size - 1) {
			cout << "\t\t\t";
			for (size_t k = 0; k < size; k++)
			{
				cout << "----";
			}
			cout << endl;
		}
	}
	return;
}

void setBoard(char**board, int size) {
	for (size_t w = 0; w < size; w++)
	{
		for (size_t k = 0; k < size; k++) {
			board[w][k] = ' ';
		}
	}
}


bool isGameOver(char** board, int size, int pointsToWin, char player) {
	int streak = 0;
	for (size_t r = 0; r < size; r++)
	{
		for (size_t c = 0; c < size; c++)
		{
			if (board[r][c] == player)
				streak++;
			else
				streak = 0;
			if (streak == pointsToWin)
				return true;
		}
		streak = 0;
	}
	for (size_t c = 0; c < size; c++)
	{
		for (size_t r = 0; r < size; r++) {
			if (board[r][c] == player)
				streak++;
			else
				streak = 0;
			if (streak == pointsToWin)
				return true;
		}
		streak = 0;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (board[i][i] == player)
			streak++;
		else
			streak = 0;
		if (streak == pointsToWin)
			return true;
	}
	streak = 0;
	int j = size - 1;
	for (size_t i = 0; i < size; i++)
	{
		if (board[i][j] == player)
			streak++;
		else
			streak = 0;
		if (streak == pointsToWin)
			return true;
		j--;
	}
	return false;
}

int evaluate(char** board, int size, int pointsToWin, bool isComputer) {
	int streak = 0;
	char player;
	if (isComputer)
		player = COMPUTERMOVE;
	else if (!isComputer)
		player = PLAYER1MOVE;
	for (size_t r = 0; r < size; r++)
	{
		for (size_t c = 0; c < size; c++)
		{
			if (board[r][c] == player)
				streak++;
			else
				streak = 0;
			if (streak == pointsToWin) {
				if (isComputer)
					return -size * size - 1;
				else if (!isComputer)
					return size * size + 1;
			}
		}
		streak = 0;
	}

	for (size_t c = 0; c < size; c++)
	{
		for (size_t r = 0; r < size; r++) {
			if (board[r][c] == player)
				streak++;
			else
				streak = 0;
			if (streak == pointsToWin)
			{
				if (isComputer)
					return -size * size - 1;
				else if (!isComputer)
					return size * size + 1;
			}
		}
		streak = 0;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (board[i][i] == player)
			streak++;
		else
			streak = 0;
		if (streak == pointsToWin)
		{
			if (isComputer)
				return -size * size - 1;
			else if (!isComputer)
				return size * size + 1;
		}
	}
	streak = 0;
	int j = size - 1;
	for (size_t i = 0; i < size; i++)
	{
		if (board[i][j] == player)
			streak++;
		else
			streak = 0;
		if (streak == pointsToWin)
		{
			if (isComputer)
				return -size * size - 1;
			else if (!isComputer)
				return size * size + 1;
		}
		j--;
	}
	return 0;
}
bool isBoardFull(char** board, int size) {
	for (size_t w = 0; w < size; w++)
	{
		for (size_t k = 0; k < size; k++) {
			if (board[w][k] == ' ')
				return false;
		}
	}
	return true;
}

int minmax(char** board, int size,int pointsToWin, int depth, bool isMinimazing, int alpha, int beta) {
	int result = evaluate(board, size, pointsToWin, !isMinimazing);
	int best;
	if (result == -size*size-1)
		return result+depth;
	if (result == size * size +1)
		return result-depth;

	if (isBoardFull(board, size) || depth == MAX_DEPTH)
		return 0;
	if (isMinimazing) {
		best = INT_MAX;
		for (size_t r = 0; r < size; r++)
		{
			for (size_t c = 0; c < size; c++)
			{
				if (board[r][c] == ' ') {
					board[r][c] = COMPUTERMOVE;
					best = min(best, minmax(board, size, pointsToWin, depth + 1, false, alpha, beta));
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
		for (size_t r = 0; r < size; r++)
		{
			for (size_t c = 0; c < size; c++)
			{
				if (board[r][c] == ' ') {
					board[r][c] = PLAYER1MOVE;
					best = max(best, minmax(board, size, pointsToWin, depth + 1, true, alpha, beta));
					board[r][c] = ' ';
					alpha = max(alpha, best);
					if (beta <= alpha)
						break;
				}
			}
		}
		return best - depth;
	}
	return 0;
}



bool isLegalMove(int row, int column, char** board, int size) {
	if (row < 0 || row>size - 1 || column < 0 || column>size - 1)
		return false;
	if (board[row][column] != ' ')
		return false;
	return true;
}

void playerMove(int row, int column, char player, char** board) {
	board[row][column] = player;
}

Move findBestMove(char** board, int pointsToWin, int size) {
	int bestValue = INT_MAX;
	Move bestMove;
	bestMove.row = -1;
	bestMove.column = -1;
	for (size_t r = 0; r < size; r++)
	{
		for (size_t c = 0; c < size; c++)
		{
			if (board[r][c] == ' ') {
				board[r][c] = COMPUTERMOVE;
				int moveValue = minmax(board, size, pointsToWin, 0, false, INT_MIN, INT_MAX);
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

void playGame(int whoseTurn, char** board, int size, int pointsToWin) {
	int option = -1;
	int move;
	int row, column;
	while (option != 0) {
		cout << "1. Play the game." << endl;
		cout << "0. Exit" << endl;
		cout << "Choose: ";
		cin >> option;
		cout << endl;
		switch (option) {
		case 1:
			setBoard(board,size);
			showInstructions(size);
			whoseTurn = PLAYER1;
			while (!isGameOver(board, size, pointsToWin, PLAYER1MOVE) && !isGameOver(board, size, pointsToWin, COMPUTERMOVE) && !isBoardFull(board, size)) {
				if (whoseTurn == PLAYER1) {
					cout << "Wprowadz swoj ruch: ";
					cin >> move;
					cout << endl;
					row = (move - 1) / size;
					column = (move - 1) % size;
					if (!isLegalMove(row, column, board, size)) {
						cout << "Niepoprawny ruch!" << endl;
						continue;
					}
					playerMove(row, column, PLAYER1MOVE, board);
					showBoard(board, size);
					whoseTurn = PLAYER2;
				}
				else if (whoseTurn == PLAYER2) {
					Move move = findBestMove(board, size, pointsToWin);
					playerMove(move.row, move.column, COMPUTERMOVE, board);
					showBoard(board, size);
					whoseTurn = PLAYER1;
				}
			}
			if (!isGameOver(board, size, pointsToWin, PLAYER1MOVE) && !isGameOver(board, size, pointsToWin, COMPUTERMOVE) && isBoardFull(board, size))
				cout << "Draw!" << endl;
			else if (isGameOver(board, size, pointsToWin, PLAYER1MOVE))
				cout << "Player 1 won!" << endl << endl << endl << endl;
			else if (isGameOver(board, size, pointsToWin, COMPUTERMOVE))
				cout << "Computer won!" << endl << endl << endl << endl;
			break;
		default:
			break;
		}
	}
	return;
}

void setGameSettings() {


}

void test() {
	char testBoard[3][3];
	testBoard[0][0] = 'x';
	testBoard[0][1] = 'o';
	testBoard[0][2] = ' ';
	testBoard[1][0] = 'o';
	testBoard[1][1] = 'o';
	testBoard[1][2] = 'x';
	testBoard[2][0] = 'x';
	testBoard[2][1] = 'x';
	testBoard[2][2] = ' ';
	Move m;
	//m = findBestMove(testBoard);
	//cout << m.row << " " << m.column << endl;
	//showBoard(testBoard);
	//if (m.row == 2 && m.column == 2)
	////	return true;
	//else
	//	return false;
}

int main() {
	int size;
	int streak;
	cout << "Choose size of the board:  ";
	cin >> size;
	cout << endl;
	cout << "Choose how many points in row gives victory: ";
	cin >> streak;
	cout << endl;
	char** board = new char * [size];
	for (size_t i = 0; i < size; i++)
	{
		board[i] = new char[size];
	}
	playGame(PLAYER1,board, size, streak);
	//cout<<test();
	return 0;
}
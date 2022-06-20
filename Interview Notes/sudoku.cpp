#include <vector>
using namespace std;

bool solvePartialSudoku(int row, int col, vector<vector<int>> &board);

bool isValidAtPos(int value, int row, int col, vector<vector<int>> &board) {
	for (int i = 0; i < board[row].size(); i++) {
		if (board[row][i] == value) {
			return false;
		}
	}
	
	for (int i = 0; i < board.size(); i++) {
		if (board[i][col] == value) {
			return false;
		}
	}
	
	int subGridX = row / 3, subGridY = col / 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[subGridX * 3 + i][subGridY * 3 + j] == value) {
				return false;
			}
		}
	}
	
	return true;
}

bool tryDigits(int row, int col, vector<vector<int>> &board) {
	for (int i = 1; i <= 9; i++) {
		if (isValidAtPos(i, row, col, board)) {
			board[row][col] = i;
			if (solvePartialSudoku(row, col+1, board)) {
				return true;
			}
		}
	}
	board[row][col] = 0;
	return false;
}

bool solvePartialSudoku(int row, int col, vector<vector<int>> &board) {
	int curRow = row, curCol = col;
	if (curCol == board[curRow].size()) {
		curCol = 0;
		curRow++;
		if (curRow == board.size()) {
			return true;
		}
	}
	
	if (board[curRow][curCol] == 0) {
		return tryDigits(curRow, curCol, board);
	}
	
	return solvePartialSudoku(curRow, curCol+1, board);
}

vector<vector<int>> solveSudoku(vector<vector<int>> board) {
  solvePartialSudoku(0, 0, board);
	return board;
}
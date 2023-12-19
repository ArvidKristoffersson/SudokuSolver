#include <iostream>
#include <vector>

using namespace std;

bool isVisited[10];

pair<int, int> nextEmpty(int board[9][9], int row, int col) {
	int indexNext = 82;
	for (int i = row * 9 + col + 1; i < 81; i++) {
		if (board[i / 9][i % 9] == 0) {
			indexNext = i;
			break;
		}
	}
	return { indexNext / 9, indexNext % 9 };
}

bool isLegal(int board[9][9], int row, int col, int n) {
	if (board[row][col] != 0)return false;
	int x = (col / 3) * 3;
	int y = (row / 3) * 3;
	for (int i = 0; i < 9; i++) {
		if (board[row][i] == n || board[i][col] == n || board[y + i / 3][x + i % 3] == n) {
			return false;
		}
	}
	return true;
}

int solutionBoard[9][9];

void addToSol(int board[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			solutionBoard[i][j] = board[i][j];
		}
	}
}

vector<int> validNums(int board[9][9], int row, int col) {
	vector<int> ret;
	for (int i = 1; i < 10; i++) {
		if (isLegal(board, row, col, i)) {
			ret.push_back(i);
		}
	}
	return ret;
}


int recursion(int board[9][9], int x, int y) {
	int sum = 0;
	if (x == 9) {
		addToSol(board);
		return 1;
	}
	if (board[x][y] != 0) {
		pair<int, int> p = nextEmpty(board, x, y);
		return recursion(board, p.first, p.second);
	}

	vector<int> legalMoves = validNums(board, x, y);

	for (auto& e : legalMoves) {
		board[x][y] = e;
		pair<int, int> p = nextEmpty(board, x, y);
		sum += recursion(board, p.first, p.second);
		board[x][y] = 0;
	}

	return sum;
}



int main(){
	cout << "Print sudoku board: " << endl;
	int board[9][9];
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)cin >> board[i][j];
	}

	recursion(board, 0, 0);
	cout << "------------SUDOKU SOLVED------------" << endl;
	for (int i = 0; i < 9; i++) {
		cout << "| ";
		for (int j = 0; j < 9; j++) {
			cout << solutionBoard[i][j] << " | ";	
		}
		if (i%3 == 2)cout << endl << "-------------------------------------" << endl;
		else cout << endl;
		
	}


	return 0;
}

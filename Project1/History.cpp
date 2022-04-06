#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	_rows = nRows;
	_cols = nCols;
	for (int r = 0; r < _rows; r++) {
		for (int c = 0; c < _cols; c++) {
			_history[r][c] = '@';
		}
	}
}

bool History::record(int r, int c) {
	if (r <= _rows && r >= 0) {
		if (c <= _cols && c >= 0) {

			if (_history[r - 1][c - 1] != 'Z') {
				_history[r - 1][c - 1] += 1;
			}
			return true;

		}
	}
	return false;
}

void History::display() const {
	clearScreen();
	for (int r = 0; r < _rows; r++) {
		for (int c = 0; c < _cols; c++) {
			if (_history[r][c] == '@')
				cout << ".";
			else
				cout << _history[r][c];
		}
		cout << '\n';
	}
	cout << endl;
}

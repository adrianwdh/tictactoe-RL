#include <iostream>
using namespace std;

/* Prints grid to the screen */
void displayGrid(int grid) {
	char p1, p2, p3, p4, p5, p6, p7, p8, p9;   // Positions 1-9
	int d;

	p1 = p2 = p3 = p4 = p5 = p6 = p7 = p8 = p9 = ' ';

	d = grid / 100000000;
	if (d == 1)
		p1 = 'X';
	else if (d == 2)
		p1 = 'O';

	d = grid / 10000000 % 10;
	if (d == 1)
		p2 = 'X';
	else if (d == 2)
		p2 = 'O';

	d = grid / 1000000 % 10;
	if (d == 1)
		p3 = 'X';
	else if (d == 2)
		p3 = 'O';

	d = grid / 100000 % 10;
	if (d == 1)
		p4 = 'X';
	else if (d == 2)
		p4 = 'O';

	d = grid / 10000 % 10;
	if (d == 1)
		p5 = 'X';
	else if (d == 2)
		p5 = 'O';

	d = grid / 1000 % 10;
	if (d == 1)
		p6 = 'X';
	else if (d == 2)
		p6 = 'O';

	d = grid / 100 % 10;
	if (d == 1)
		p7 = 'X';
	else if (d == 2)
		p7 = 'O';

	d = grid / 10 % 10;
	if (d == 1)
		p8 = 'X';
	else if (d == 2)
		p8 = 'O';

	d = grid % 10;
	if (d == 1)
		p9 = 'X';
	else if (d == 2)
		p9 = 'O';

	cout << " " << p1 << " | " << p2 << " | " << p3 << endl;
	cout << "---+---+---" << endl;
	cout << " " << p4 << " | " << p5 << " | " << p6 << endl;
	cout << "---+---+---" << endl;
	cout << " " << p7 << " | " << p8 << " | " << p9 << endl;
}

/* Returns true if position pos of grid is already marked by a player; returns
false otherwise. */
bool isMarked(int grid, int pos) {
	// Shift position pos to the units-digit
	for (int i = 0; i < 9 - pos; i++)
		grid /= 10;
	return (grid % 10 != 0);
}

/* Performs the task of Player p putting his mark in position pos of grid. The
grid should get updated, and the function should return the new grid
configuration. */
int updateGrid(int grid, int pos, char p) {
	int cnt = 100000000;
	for (int i = 1; i < pos; i++)      //Calculate the position of the digit
		cnt /= 10;
	if (p == 'O')
		grid += cnt * 2;                 // Player O updates as "2"
	else
		grid += cnt * 1;                // Player X updates as "1"
	return grid;
}

/* Returns an integer 0, 1, 2, or 3, denoting the game state of grid listed
below:
0: Game is finished and is a draw.
1: Gmae is finished and Player X wins.
2: Game is finished and Player O wins.
3: Game is not yet finished. */
int gameState(int grid) {
	int number[9] = { 0 };
	int count = 100000000;
	for (int i = 0; i < 9; i++){
		number[i] = grid / count % 10;                          // Store 9 digits into array
		count /= 10;
	}
	for (int j = 1; j < 3; j++){
		for (int i = 0; i < 3; i++){
			if ((number[i] == j && number[i + 3] == j&& number[i + 6] == j) ||                      // Vertical
				(number[3 * i] == j&& number[1 + 3 * i] == j&& number[2 + 3 * i] == j))         // Horizontal
				return j;
		}
		if ((number[0] == j&& number[4] == j&& number[8] == j) || (number[2] == j&& number[4] == j&& number[6] == j))return j;   // Diagonal
	}
	for (int i = 1; i < 10; i++)
		if (isMarked(grid, i) == 0) return 3;
	return 0;                                            // If the grid is full(no zero), the game draws.
}

void train_policy() {

}

int main() {
	int grid = 0, input = 0, status;
	char player = 'X';                  // Player X starts first
	bool end = 0;                       // if End=1, then terminate the game

	displayGrid(grid);
	while (end == 0){
		cout << "Player " << player << ", make your move (1-9): ";
		cin >> input;
		while ((input < 1 || input >9) || isMarked(grid, input) == 1){          // Valid input range and the specified grid is not marked 
			cout << "Invalid move. Try again!\n";
			cout << "Player " << player << ", make your move (1-9): ";
			cin >> input;
		}
		grid = updateGrid(grid, input, player);
		displayGrid(grid);
		if (player == 'X') player = 'O'; else player = 'X';            // Swap player
		status = gameState(grid);
		if (status != 3) {                                           // If status is 3, the game continues
			end = 1;
			if (status == 0) cout << "Draw game!\n";
			else if (status == 1) cout << "Player X wins!\n";
			else cout << "Player O wins!\n";
		}		
	}
	return 0;
}

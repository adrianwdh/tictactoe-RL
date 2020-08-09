
#include "player.h"
#include <cmath>


Player::Player(bool coop, ValTbl* vt){	
	_coop = coop;
	_vt = vt;
}

Player::~Player(){}

bool isMarked(int grid, int pos) {
	/* Returns true if position pos of grid is already marked by a player; returns
false otherwise. */

	// Shift position pos to the units-digit
	for (int i = 0; i < 9 - pos; i++)
		grid /= 10;
	return (grid % 10 != 0);
}

int Player::GetState() {
	/* Returns an integer 0, 1, 2, or 3, denoting the game state of grid listed
	below:
	0: Game is finished and is a draw.
	1: Gmae is finished and Player X wins. (Number 1)
	2: Game is finished and Player O wins.	(Number 2)
	3: Game is not yet finished. 
	*/
	int number[9] = { 0 };
	int count = 100000000;
	for (int i = 0; i < 9; i++) {
		number[i] = grid / count % 10;                          // Store 9 digits into array
		count /= 10;
	}
	for (int j = 1; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			if ((number[i] == j && number[i + 3] == j && number[i + 6] == j) ||                      // Vertical
				(number[3 * i] == j && number[1 + 3 * i] == j && number[2 + 3 * i] == j))         // Horizontal
				return j;
		}
		if ((number[0] == j && number[4] == j && number[8] == j) || (number[2] == j && number[4] == j && number[6] == j))return j;   // Diagonal
	}
	for (int i = 1; i < 10; i++)
		if (isMarked(grid, i) == 0) return 3;
	return 0;                                            // If the grid is full(no zero), the game draws.
}

bool Player::IsWin()
{
	if (GetState(this->grid) == 1)
		return true;
	else 
		return false;
}

bool Player::IsDraw()
{
	if (GetState(this->grid) == 0)
		return true;
	else
		return false;
}

vector<Grid> Player::GetPossibleMoves(const Grid current) {
	vector<Grid> list;
	long denom = 100000000;
	int d;

	for (int i = 0; i < 10; i++)
	{
		d = grid / denom % 10;
		if (d == 0)
		{
			Grid g = current;
			g = current + denom;
			list.push_back(g);
		}
		denom /= 10;
	}
	return list;
}

Grid Player::NextMove()
{
	if (_coop)
		return NextMove_Greedy();
	else
		return NextMove_Human();
}

Grid Player::NextMove_Greedy() {
	vector<Grid> list = GetPossibleMoves(grid);
	vector<Grid> bestState;
	float maxVal = 0;
	float curVal;

	for (Grid g : list)
	{
		curVal = _vt->GetValue(g);
		if (curVal > maxVal)
		{
			maxVal = curVal;
			bestState.clear();
			bestState.push_back(g);
		}
		else if (curVal == maxVal)
			bestState.push_back(g);
	}

	random_device rd;
	default_random_engine e(rd());
	uniform_int_distribution<int> d(0, bestState.size() - 1);

	int idx = d(e);
	return bestState[idx];
}


Grid Player::NextMove_Random()
{
	vector<Grid> list = GetPossibleMoves(grid);	
	random_device rd;
	default_random_engine e(rd());
	uniform_int_distribution<int> d(0, list.size() - 1);
	
	int idx = d(e);	
	return list[idx];
}


Grid Player::NextMove_Human(int playerNo)
{
	Grid temp = grid;
	int input;

	cout << "Player " << playerNo << ", make your move (1-9): ";
	cin >> input;
	while ((input < 1 || input >9) || isMarked(temp, input)) {          // Valid input range and the specified grid is not marked 
		cout << "Invalid move. Try again!\n";
		cout << "Player " << playerNo << ", make your move (1-9): ";
		cin >> input;
	}
	return temp;
}


void Player::UpdateGrid(Grid g)
{
	this->gridOld = this->grid;	
	this->grid = g;
}

void Player::UpdateEndValue(float reward) {
	_vt->UpdateEndValue(grid, reward);
}

void Player::UpdateValue(float alpha) {
	_vt->UpdateValue(gridOld,grid, alpha);
}

Grid Player::SwapPlayer(Grid grid) {	
	int d;
	Grid output = 0; 
	
	long denom = 1;

	for (int i = 0; i < 10; i++)
	{
		d = grid / denom % 10;
		if (d == 1)
			output += denom * 2;
		else if (d == 2)
			output += denom;
		d *= 10;
	}
	return output;
}

int Player::ConvertGridToValTblIndex(Grid g) {
	int d;
	long output = 0;
	long denom = 1;

	for (int i = 0; i < 10; i++)
	{
		d = grid / denom % 10;
		output += pow(3, i) * d;
	}
	return output;

}
Grid Player::ConvertValTblIdxtoGrid(int idx) {


}
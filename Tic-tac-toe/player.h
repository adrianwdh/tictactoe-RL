#pragma once

#include "intro.h"
#include "qval.h"

class Player 
{
private:	
	bool _coop;
	ValTbl* _vt;
	Grid gridOld;
	Grid grid;
	
public:

	Player(bool coop, ValTbl* vt);
	~Player();	//Deconstruct player
	bool IsWin();
	bool IsDraw();
	int GetState();

	
	vector<Grid> GetPossibleMoves(const Grid current);	
	Grid NextMove();
	Grid NextMove_Greedy();
	Grid NextMove_Random();
	Grid NextMove_Human(int playerNo);
	void UpdateGrid(Grid g);
	void UpdateEndValue(float reward);
	void UpdateValue(float alpha);
	Grid SwapPlayer(Grid grid);
	int ConvertGridToValTblIndex(Grid g);
	Grid ConvertValTblIdxtoGrid(int idx);	
	
	
};

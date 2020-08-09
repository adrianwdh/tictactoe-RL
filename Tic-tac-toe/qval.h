#pragma once

#include "intro.h"

class ValTbl
{
private:
	QValue qValArr;

public:
	
	ValTbl();
	ValTbl(const ValTbl& vt);
	void InsertTrained(QValue vs);
	~ValTbl();
	QValue GetAll();
	float GetValue(const Grid& g);	
	int ConvertToIndex(const Grid& g);
	void UpdateEndValue(const Grid& g,float reward, int playerIdx);
	void UpdateValue(const Grid& pre, const Grid& post,float alpha, int playerIdx);

};
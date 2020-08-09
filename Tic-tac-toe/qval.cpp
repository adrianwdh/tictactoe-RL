#include "qval.h"


ValTbl::ValTbl() {
	qValArr.fill(0.5);
}

ValTbl::ValTbl(const ValTbl& vt) {
	this->qValArr = vt.qValArr;
}

void ValTbl::InsertTrained(QValue vs) {
	this->qValArr = vs;
}


ValTbl::~ValTbl() {}

int ValTbl::ConvertToIndex(const Grid& g) {
	int sum=0;
	
	for (int i = 0; i < g.size(); i++)
		sum += g[i] * pow(3, i);

	return sum;

}

float ValTbl::GetValue(const Grid& g) {
	int index = ConvertToIndex(g);
	return qValArr[index];
}

void ValTbl::UpdateEndValue(const Grid& g, float reward, int playerIdx) {
	int index = ConvertToIndex(g);
	qValArr[index] = reward;
}


void ValTbl::UpdateValue(const Grid& pre, const Grid& post, float alpha, int playerIdx) {
	int indexPre = ConvertToIndex(pre);
	int indexPost = ConvertToIndex(post);

	qValArr[indexPre] += alpha*(qValArr[indexPost]-qValArr[indexPre]);
}

QValue ValTbl::GetAll() {
	return this->qValArr;
}
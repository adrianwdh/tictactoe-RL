#pragma once

#include "intro.h"
#include "qval.h"
#include "player.h"

void save_trained(ValTbl* vs1);
void train(ValTbl* vs1, ValTbl* vs2, int iterTimes = 5000);
QValue get_trained(string s)
#include "network.h"


void save_trained(ValTbl* vs1) {
	QValue x = vs1->GetAll();

	ofstream myfile("network.txt");
	if (myfile.is_open())	
	{
		for (int count = 0; count < total_state; count++) {
			myfile << x[count] << " ";
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

ValTbl train(ValTbl vs1, int iterTimes = 5000) {

	Player* playerArr[2];
	Grid newG;	//new grid
	Grid newG_swapped;	//new grid
	bool end; // if End=1, then terminate the game
	bool cont = true;
	int playerIdx;
	int gameState;

	float eps = 0.2;
	float alpha = 0.2;
	float rnd;
	bool greedy;

	Player p1(false, &vs1);
	Player p2(false, &vs1);
	playerArr[0] = &p1;
	playerArr[1] = &p2;

	for (int i = 0; i < iterTimes; i++) {

		end = false;		
		playerIdx = 0;

		while (!end)
		{
			random_device rd;
			default_random_engine e(rd());
			uniform_real_distribution<float>  d(0, 1);
			rnd = d(e);

			if (rnd < eps)
			{
				greedy = false;
				newG = playerArr[playerIdx]->NextMove_Random();
			}
			else
			{
				greedy = true;
				newG = playerArr[playerIdx]->NextMove_Greedy();
			}
			//displayHand(newG);
			playerArr[playerIdx]->UpdateGrid(newG);
			newG_swapped = playerArr[1-playerIdx]->SwapPlayer(newG);
			playerArr[1- playerIdx]->UpdateGrid(newG_swapped);

			end = true;		//check if the game ended
			gameState = playerArr[playerIdx]->GetState;
			if (gameState == 1)
			{
				playerArr[playerIdx]->UpdateEndValue(1);
			} else if (gameState == 2)
			{
				playerArr[playerIdx]->UpdateEndValue(0);
			}
			else if (playerArr[playerIdx]->IsDraw())
			{
				playerArr[playerIdx]->UpdateEndValue(0.25);
				playerArr[1 - playerIdx]->UpdateEndValue(0.25);
			}
			else
				end = false;

			if (greedy)
			{
				playerArr[playerIdx]->UpdateValue(alpha);
				playerArr[1 - playerIdx]->UpdateValue(alpha);
			}

			playerIdx = 1 - playerIdx;
		}
	}

	save_trained(&vs1);

}

QValue get_trained(string s) {
	QValue temp;
	temp.fill(0.5);
	ifstream inputFile(s + ".txt");        // Input file stream object
		// Check if exists and then open the file.
	if (inputFile.good()) {
		int i = 0;
		// Push items into a vector
		float current_number = 0;
		while (inputFile >> current_number) {
			temp[i] = (current_number);
			i++;
		}

		// Close the file.
		inputFile.close();
	}
	else {
		cout << "Error!";
	}
	return temp;
}
*/
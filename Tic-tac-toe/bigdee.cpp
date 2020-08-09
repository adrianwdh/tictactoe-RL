#include "player.h"
#include "intro.h"
#include <iostream>
#include <fstream>

string convertCardName(int no) {
	string s;
	int t;
	s = to_string(no / 13 + 1);
	t = no % 4;
	if (t == 0)
		s = s + "D";
	else if (t == 1)
		s = s + "C";
	else if (t == 2)
		s = s + "H";
	else
		s = s + "S";
	return s;
}

/* Prints grid to the screen */
void displayHand(const PokerAll& allHand) {
	string s1 = "P1: \n";
	string s2 = "P2: \n";
	string s3 = "P3: \n";
	string s4 = "P4: \n";

	for (int i = 0; i < 52; i++)
		if (allHand[i] == 1)
			s1 = s1 + convertCardName(i) + " ";
		else if (allHand[i] == 2)
			s2 = s2 + convertCardName(i) + " ";
		else if (allHand[i] == 3)
			s3 = s3 + convertCardName(i) + " ";
		else
			s4 = s4 + convertCardName(i) + " ";

	cout << s1 << s2 << s3 << s4;
	
}

/*
void savetrained(ValTbl* vs1, string s) {
	const int size = 19683;
	QValue x = vs1->GetAll();


	ofstream myfile(s + ".txt");
	if (myfile.is_open())
	{
		//myfile << "This is a line.\n";
		//myfile << "This is another line.\n";
		for (int count = 0; count < size; count++) {
			myfile << x[count] << " ";
		}
		myfile.close();
	}
	else cout << "Unable to open file";

}

void train(ValTbl* vs1, ValTbl* vs2, int iterTimes=5000) {
	
	Player* playerArr[2];
	Hand newG;
	bool end; // if End=1, then terminate the game
	bool cont = true;
	int playerIdx;

	//int iterTimes = 5000;
	float eps = 0.2;
	float alpha = 0.2;
	float rnd;
	bool greedy;

	for (int i=0;i<iterTimes;i++){

		end = false;
		Player p1(1,false,vs1);
		Player p2(2, false,vs2);
		playerArr[0] = &p1;
		playerArr[1] = &p2;
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
			playerArr[0]->UpdateHand(newG);
			playerArr[1]->UpdateHand(newG);

			end = true;
			if (playerArr[playerIdx]->IsWon()) 
			{
				playerArr[playerIdx]->UpdateEndValue(1);
				playerArr[1 - playerIdx]->UpdateEndValue(0);
			}
			else if (playerArr[playerIdx]->IsFull())
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

	savetrained(vs1, "Player1");
	savetrained(vs2, "Player2");
}

QValue gettrained(string s) {
	QValue temp;
	temp.fill(0.5);
	ifstream inputFile(s + ".txt");        // Input file stream object
		// Check if exists and then open the file.
	if (inputFile.good()) {
		int i= 0;
		// Push items into a vector
		float current_number = 0;
		while (inputFile >> current_number) {
			temp[i]= (current_number);
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

int main() {
	
	//Player* playerArr[2];	
	Hand newG;
	bool end; // if End=1, then terminate the game
	bool cont = true;
	bool hasSaved = false;
	int playerIdx;
	int trainTime=5000;
	Poker gamePoker(true);
	//ValTbl w1, w2;

	/*cout << "Has saved data (1: Yes; 0: No)? \n";
	cin >> hasSaved;
	if (hasSaved) {
		QValue p1, p2;
		p1 = gettrained("Player1");
		p2 = gettrained("Player2");
		w1.InsertTrained(p1);
		w2.InsertTrained(p2);

		cout << "Retrained ? (1: Yes; 0: No)? \n";
		cin >> hasSaved;
		if (hasSaved) {
			cout << "Time ? (1: Yes; 0: No)? \n";
			cin >> trainTime;
			train(&w1, &w2, trainTime);
		}
	}
	else{
		train(&w1, &w2, trainTime);
	}	

	*/

	float alpha = 0.2;

	while (cont) {
		
		end = false;
		/*
		Player p1(1,true);
		Player p2(2, false,&w2);
		playerArr[0] = &p1;
		playerArr[1] = &p2;
		playerIdx = 0;
		*/
		PokerAll p;
		p = gamePoker->GetState;
		displayHand();

		while (!end) {
			newG = playerArr[playerIdx]->NextMove();
			displayHand(newG);
			playerArr[0]->UpdateHand(newG);
			playerArr[1]->UpdateHand(newG);

			end = 1;
			if (playerArr[playerIdx]->IsWon())
			{
				cout << "Player " << playerArr[playerIdx]->GetPlayerNo() << " wins.\n";
				//if (playerIdx == 0 )
				//	playerArr[1]->UpdateEndValue(0);
			}

			else if (playerArr[playerIdx]->IsFull())
			{
				cout << "Draw.\n"; 
				//playerArr[1]->UpdateEndValue(0.75);
			}	
			else
				end = 0;

			//playerArr[1]->UpdateValue(alpha);
			
			playerIdx = 1 - playerIdx;
			}		
		
		cout << "Continue (1: Yes; 0: No)? \n";
		cin >> cont;
	}
	return 0;
}
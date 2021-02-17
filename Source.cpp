#include <string>
#include <algorithm>
#include <stdlib.h>
#include<iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;


class Card {

private:
	int Number;
	string Color;
	string Suit;

public:

	//Default Constructor
	Card();

	//Constructor
	Card(int number, string color, string suit) {
		Number = number;
		Color = color;
		Suit = suit;
	}

	//setters
	void SetNumber(int number) { Number = number; }
	void SetColor(string color) { Color = color; }
	void SetSuit(string suit) { Suit = suit; }

	//getters
	int GetNumber() { return Number; }
	string getColor() { return Color; }
	string getSuit() { return Suit; }

	void getInfo() {
		cout << Number <<" "<<Color<<" "<<Suit<<" "<< endl;
	}

};


void AddCards(vector<Card> &deck,string color,string suit) {

	for (int i = 1; i <= 13; i++) {
		Card create(i, color, suit);
		deck.push_back(create);
	}
}


//Add card to player hand
//if the value of the card is J,Q,K set value to 10
void AddPlayer(vector<Card> &player, vector<Card> deck, int &position) {
	if (deck.at(position).GetNumber() > 10) {
		deck.at(position).SetNumber(10);
	}
	player.push_back(deck.at(position));
	position++;
}


void printBoard(vector<Card> player1,vector<Card> player2,int &totalP1, int &totalP2) {

	//Clear Screen
	system("CLS");

	//Reset totals(used when user HITS)...Room for improvement
	totalP1 = 0;
	totalP2 = 0;



	//BOARD
	cout << "*************************GAME OF BLACKJACK(21)****************************************" << endl;
	cout << endl << endl;
	cout << "				Player1" << endl;



	cout << "				";
	for (int i = 0; i < player1.size(); i++) {
		cout << player1.at(i).GetNumber() << " ";
		totalP1 = totalP1 + player1.at(i).GetNumber();
	}
	cout << endl<<"				Total: " << totalP1;

	cout << endl << endl;
	cout << endl << endl << endl;
	cout << "				Player2" << endl;

	cout << "				";
	for (int i = 0; i < player2.size(); i++) {
		cout << player2.at(i).GetNumber() << " ";
		totalP2 = totalP2 + player2.at(i).GetNumber();
	}
	cout <<endl<< "				Total: " << totalP2;

	cout << endl << endl;
	cout << endl << endl;
	cout << "**************************************************************************************" << endl;

}


int main() 
{
	
	vector<Card> deck;
	vector<Card> player1;
	vector<Card> player2;
	int count = 0;
	int totalP1 = 0;
	int totalP2 = 0;
	char gameContinue='y';
	string p1 = "Player 1";
	string p2 = "Player 2";
	/*vector<vector<Card>> board{
		{deck.at(0),deck.at(1),deck.at(2),deck.at(3),deck.at(4),deck.at(5),deck.at(6)},
		{0,deck.at(0),deck.at(0),deck.at(0),deck.at(0),deck.at(0),deck.at(0) },
		{0,0,deck.at(0),deck.at(0),deck.at(0),deck.at(0),deck.at(0) },
		{0,0,0,deck.at(0),deck.at(0),deck.at(0),deck.at(0) },
		{0,0,0,0,deck.at(0),deck.at(0),deck.at(0) },
		{0,0,0,0,0,deck.at(0),deck.at(0) },
		{0,0,0,0,0,0,deck.at(0) },



	};
	*/

	
	AddCards(deck, "red", "diamonds");
	AddCards(deck, "black", "clubs");
	AddCards(deck, "red", "hearts");
	AddCards(deck, "black", "spades");


	//Shuffle deck.
	// get a time-based seed
	//Source for seed:https://www.techiedelight.com/shuffle-vector-cpp/
	unsigned seed = std::chrono::system_clock::now()
		.time_since_epoch()
		.count();
	shuffle(deck.begin(), deck.end(),default_random_engine(seed));

	//Print results of deck(Shuffle)
	/*for (int i = 0; i < deck.size(); i++) {
	deck.at(i).getInfo();
	}*/

	char hit = 'n';
	while (gameContinue != 'n'&& count<=45) {

		//DRAW FIRST CARD FOR PLAYER 1 AND 2
		AddPlayer(player1, deck, count);
		AddPlayer(player2, deck, count);

		//DRAW SECOND CARD FOR PLAYER 1 AND 2
		AddPlayer(player1, deck, count);
		AddPlayer(player2, deck, count);

		//DISPLAY BOARD WITH NUMBERS
		printBoard(player1, player2,totalP1,totalP2);

		cout << p1 << " Do you want to HIT y/n" << endl;
		cin >> hit;
		while (hit == 'y'&&totalP1<=21) {
			AddPlayer(player1, deck, count);
			printBoard(player1, player2, totalP1, totalP2);
			if (totalP1 > 21) {
				cout << "Player 1 BUST" << endl << endl;
				hit = 'n';
			}
			else {
				cout << p1 << " Do you want to HIT y/n" << endl;
				cin >> hit;
			}
			
		}


		cout << p2 << " Do you want to HIT y/n" << endl;
		cin >> hit;
		while (hit == 'y'&&totalP2<=21) {
			AddPlayer(player2, deck, count);
			printBoard(player1, player2, totalP1, totalP2);

			if (totalP2 > 21) {
				cout << "Player 2 BUST" << endl << endl;
				hit = 'n';
			}
			else {
				cout << p2 << " Do you want to HIT y/n" << endl;
				cin >> hit;
			}
			
		}


		//Decide Winners

		//Player 1 wins
		if ((totalP1 <= 21 && totalP1 > totalP2)||(totalP1<=21&&totalP2>21)) {
			cout << "Winner is:	Player 1: Total " <<totalP1<< endl;
		}

		//Player 2 wins
		else if ((totalP2 <= 21 && totalP2 > totalP1)||(totalP2<=21&&totalP1>21)) {
			cout << "Winner is:	Player 2: Total " <<totalP2<< endl;
		}

		//Draw
		else if(totalP1==totalP2&&(totalP1<=21)){
			cout << "DRAW" << endl;
		}

		//No winners
		else{
			cout << "No Winners" << endl;
		}

		//Clear players hands
		player1.clear();
		player2.clear();
		cout << "Continue Game y/n" << endl;
		cin >> gameContinue;

	}






	system("pause");
	return 0;
}



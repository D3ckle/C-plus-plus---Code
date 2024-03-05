# include <iostream>
# include <vector> // allow vectors
# include <time.h> // improved randomness using eecution based on time 

using namespace std;

//Project Name : Double Sixes
//Donald Alan Newandee
//Due: march 11th, 2020
//
//Program Description :
//The goal of the program is to simulate playing dominoes between 2 players. (DONE)
//The rules of the game will follow a 28 set with double 6’s.  (DONE)
//The players will alternate playing a tile if possible on either end of the tiles on the board,  (DONE)
//otherwise they will have to take the tiles from the“bazaar”. (DONE)
//The board of dominoes must always be visible and you should (DONE)
//show one of the player’s hand depending on the turn but never both. (DONE)
//You should show the number of pieces the other player has, however. (DONE)
//
//L1 Students have to keep track of if the game is “closed” (DONE)
//as well as tell the user that they have no choice but to take stones from the bazaar. //line 330
//
//Specifications / Notes:
//-Build 4 vectors representing the 2 player hands, the “bazaar” and the pieces on the board. (DONE)
//- The main function should only have the main loops everything else should be in functions (DONE)
//- Display the dominoes in a clear to understand way and use characters to separate the 2 numbers as well as the whole domino (DONE)
//- Make sure to dummy proof ever getting an out of bounds error. (DONE)
//- Make sure to properly align the dominoes depending on the connecting number e.g. (1 | 0 - 0 | 2 - 2 | 3 etc.) (DONE)
//- The game needs to be replayable (DONE)


//all program functions
void createdominoes(vector<int>& v) // generating the list of all 28 dominoes; 
{
	for (int i = 0; i < 5; i++) { // happens 7 times, 0 - 6
		for (int j = i; j < 5; j++) { // happens 7 times also; 0 - 6
			v.push_back(i * 10 + j); // adding dominoes and adding them by 2 increments of 1 until 6, 7 times (0 - 6)
		}
	}
}
void shuffle(vector<int>& v) { // randomizes the dominoes ot make them in a random order
	for (int i = 0; i < v.size(); i++) //does this for the size of the array you put in
	{
		int randomspot = rand() % v.size(); // gets a random size from 0 to the number of items in the vector
		//swap
		int temp = v[i]; //temporarily saves the variable youre switching in for
		v[i] = v[randomspot]; // replaces the value as youve copied it to be replaced
		v[randomspot] = temp; // overides the value youve already copied over for the value copied temporarily
	}
}
void displayboard(vector<int>& v) {
	cout << "Board:\n"; // commnicates that this is the board line segment; following line will be the dominoes on the board
	int number1 = v[0] / 10; // second number ; left most
	int number2 = v[0] % 10; // first number; right most
	if (v.size() > 1 && number1 == v[1] / 10) // does this so long as there is atleaat 1 domino in the vector
	{//swap the numbers in the digit spots
		int temp = number1;
		number1 = number2;
		number2 = temp;
		v[0] = number1 * 10 + number2; //fixes the value to be back to what it was before as we ust modified it to compare it
	}
	cout << "-" << number1 << "|" << number2 << "-"; //writing out the first domino

	for (int i = 1; i < v.size(); i++) { // does this to each following 
		number1 = v[i] / 10; // second number ; left most
		number2 = v[i] % 10; // first number; right most
		if (number1 != v[i - 1] % 10) //checks the single digit of the domino before it
		{//swap the digits if the tenth digit doesnt equal the first digit of the domino before; swap
			int temp = number1;
			number1 = number2;
			number2 = temp;
			v[i] = number1 * 10 + number2; //fixes the adjusted number
		}
		cout << number1 << "|" << number2 << "-"; // seperates the numbers for a single domino to look nicer
	}
	cout << endl << endl;
}
void dealdominoes(vector<int>& v, vector<int>& dominoes) { // adds a hand of 7 random dominoes for a player
	for (int i = 0; i < 5; i++) { // happens 7 times
		v.push_back(dominoes[dominoes.size() - 1]); // clones the domino into another array
		dominoes.pop_back(); // gets rid of the address of the domino in the list; added to a player's hand
	}
}
void display(vector<int>& v) { // displays any player's hand of dominoes
	for (int i = 0; i < v.size(); i++) {
		int number1 = v[i] / 10; // second number ; left most
		int number2 = v[i] % 10; // first number; right most
		cout << number1 << "|" << number2 << "  ";
	}
	cout << endl;
	cout << " ";
	for (int i = 0; i < v.size(); i++) { // labels each domino so when later the user chooses that number, ill use that to track the domino to be used
		if (i < 10) // single digit numbered domino calls
			cout << i << "    ";
		else
			cout << i << "   "; // 2 digit numbered domino calls; 1 less space; looks nicer and easier for user to understand
	}
	cout << endl;
}
void takefrombazaar(vector<int>& v, vector<int>& dominoes) { // tkaes 2 dominoes from the bazaar and puts them into the hand of the player
	if (dominoes.size() > 2) { // only allow taking if there is more than 2 dominoes left in the bazaar
		for (int i = 0; i < 2; i++) {
			v.push_back(dominoes[dominoes.size() - 1]); //adding the last domino in the list to the 

			dominoes.pop_back(); // push_back adds an element, pop back removes the last element in the vector
		}
	}
	else {// prevent the user from taking form the bazaar when there is 2 dominoes left
		cout << "You can not take from the bazaar anymore. You must play a domino or pass your turn.\n";
		system("pause");
	}
	cout << "Dominoes left in the bazaar: "; // outputs the amount of domineos left in the bazaar
	cout << dominoes.size();
	cout << endl;
	cout << "(Once the Bazaar has 2 dominoes or less, you can not take form it anymore.)\n"; // tells user that they cant take anymore
	system("pause");
}
bool makemove(vector<int>& board, vector<int>& player) { // checks if the move is a valid move to play 
	int piece = 0;

	do {
		if (piece >= player.size() || piece < 0)
			cout << "Invalid Number. You must use a number shown with a domino.\n";
		cout << "Enter the number below the domino you want to use.\n";
		display(player); // displays the player's hand
		cin >> piece;

	} while (piece >= player.size() || piece < 0);// dummy proof

	int side;
	if (board.size() == 0) { // special case, when this is the first domino to be played
		//simply takes the domino and puts it onto the board
		board.insert(board.begin(), player[piece]); // adds the domino; spit sceond of 2 of the same domino
		player.erase(player.begin() + piece); // instantly removes the domino

		return true; //break out, dominoe is added to board
	}
	else {
		if (board[board.size() - 1] % 10 == board[0] / 10) { // if both ends of the domino line are the same, then it doesnt matter which end you choose, skips asking; convenient
			side = 2; // defualt to the end of the line cause it looks cleaner that way (in my opinion)
		}
		else { // asks whcih end you want to place the domino
		cout << "which side do you want to connect to? Enter 1 for the left side, Enter 2 for the right side.\n";
		cout << "(You can enter anything else to quit using a domino)\n";
		cin >> side;
		}

	}

	if (side == 1) { //beginning of the line of dominoes
		if (player[piece] / 10 == board[0] / 10 || board[0] / 10 == player[piece] % 10) { // if either digit is the same as the second digit of the domino on the board
			board.insert(board.begin(), player[piece]);
			player.erase(player.begin() + piece);
			return true;
		}
		cout << "You can not play that domino there. Try a different domino.\n";
		system("pause");
		return false; // doesnt match
	}
	else if (side == 2) { // end of the domino line
		if (player[piece] / 10 == board[board.size() - 1] % 10 || board[board.size() - 1] % 10 == player[piece] % 10) { // if either digit is the same as the first digit of the domino on the board
			board.push_back(player[piece]);
			player.erase(player.begin() + piece);
			return true;
		}
		cout << "You can not play that domino there. Try a different domino.\n";
		system("pause");
		return false; // doesnt match
	}
	else
		return false;
}
void countdots(vector<int>& v1, vector<int>& v2, int& p1score, int& p2score) { // during a closed game, count
	int v1count = 0; int v2count = 0; // variables counting the 
	//add the digit value oif all the dominoes of a player's had, and campare the hands, the player with the least amount wins
	// ex: 1 - 2 domino = 3; 0 - 6 = 6; 4 - 6 = 10;
	for (int i = 0; i < v1.size(); i++) { //adds up all the dots of all the dominoes of the first player's hand
		int number1 = v1[i] / 10;
		int number2 = v1[i] % 10;
		v1count = v1count + number1 + number2;
	}
	for (int i = 0; i < v2.size(); i++) { //adds up all the dots of all the dominoes of the second player's hand
		int number1 = v1[i] / 10;
		int number2 = v1[i] % 10;
		v2count = v2count + number1 + number2;
	}
	if (v2count > v1count) { //if the first player's dot / pit count is less than player 2
		cout << "The closed game ended with player 1 winning.\n";
		cout << endl;
		p1score++;
	}
	else if (v2count < v1count) { // closed game, player 2 had less pits on their dominoes
		cout << "The closed game ended with player 2 winning.\n";
		cout << endl;
		p2score++;
	}
	else {// if (v1count == v2count) // a tie; the game is closed and both players have the same # of pits on their dominoes
		cout << "The closed game ended with both players tied.\n";
		cout << endl;
	}

	//tells each player's score in the case of a closed game
	cout << "Player 1 had a total pit count of: ";
	cout << v1count << endl;

	cout << "Player 2 had a total pit count of: ";
	cout << v2count << endl << endl;
}
void wincommunication(vector<int> p1, vector<int> p2, int& p1score, int& p2score) {
	system("cls");
	if (p1.size() == 0) {
		cout << "Player 1 wins.\n";// player 1 has used all their dominoes
		p1score++;
	}
	else if (p2.size() == 0) {
		cout << "Player 2 wins.\n"; // i will be defaulting to this a lot during texting
		p2score++;
	}
	else { // player 2 won
		countdots(p1, p2, p1score, p2score); // tells the users when they closed the game who won
	}
	//tells how many times each of the players have won
	if (p1score == 1)
		cout << "Player 1 won once.\n"; // pl1
	else
		cout << "Player 1 won a total of " << p1score << " times.\n"; // pl1
	cout << endl;

	if (p2score == 1)
		cout << "Player 2 won once.\n"; // pl2
	else
		cout << "Player 2 won a total of " << p2score << " times.\n"; // pl2
	cout << endl;
}
void resetgame(vector<int>& dominoes, vector<int>& player1, vector<int>& player2, vector<int>& board) {
	dominoes.clear();
	player1.clear();
	player2.clear();
	board.clear();

	createdominoes(dominoes);
	//dominoes[0] = 11; //for easy testing if the program can see that there is a closed game; keep createdominoes 
	//dominoes[1] = 11; // do not use a '1-1' domino, use 0-0 and the program will see that there are no dominoes that connect to it
	//dominoes[2] = 11; 
	//dominoes[3] = 11; //there is STILL an issue with when testing, and i still cant seem to find it; only been able to produce during testing, so it should be fine
	//dominoes[4] = 11;		//cout << "blah" << endl;
	//						//system("Pause");
	//dominoes[5] = 11;
	//dominoes[6] = 11;
	//dominoes[7] = 11;
	//dominoes[8] = 11;
	//dominoes[9] = 11;
	//dominoes[10] = 0; 
	//dominoes[11] = 11;
	//dominoes[12] = 11;
	//dominoes[13] = 11;
	//dominoes[14] = 11;

	//shuffle(dominoes); // shuffling the dominoes
//for (int i = 0; i < dominoes.size(); i++) // displaying the original list of dominoes
//	cout << dominoes.at(i) << endl;
}
bool checkclosed(vector<int>& board, vector<int>& p1, vector<int>& p2, vector<int>& bazaar) {
	if (board.size() < 1) //makes sure there is atleast 1 domino to compare to in the board
		return false;
	if (bazaar.size() > 2) { // checks the bazaar if you cna take from the bazaar still
		for (int i = 0; i < bazaar.size(); i++) {
			if (bazaar[i] / 10 == board[board.size() - 1] % 10 || board[board.size() - 1] % 10 == bazaar[i] % 10 || bazaar[i] / 10 == board[0] / 10 || board[0] / 10 == bazaar[i] % 10) { // end of the domino line
				return false;
			}
		}
	}
	for (int i = 0; i < p1.size(); i++) { // check player1's hand 
		if (p1[i] / 10 == board[board.size() - 1] % 10 || board[board.size() - 1] % 10 == p1[i] % 10 || p1[i] / 10 == board[0] / 10 || board[0] / 10 == p1[i] % 10) { // end of the domino line
			return false;
		}
	}
	for (int i = 0; i < p2.size(); i++) { // checks player2's hand if they have a domino 
		if (p2[i] / 10 == board[board.size() - 1] % 10 || board[board.size() - 1] % 10 == p2[i] % 10 || p2[i] / 10 == board[0] / 10 || board[0] / 10 == p2[i] % 10) { // end of the domino line
			return false;
		}
	}
	return true; // it is in fact a closed game; kick out of the game
}
bool isadominopplayable(vector<int>& v, vector<int>& board) { //checks if the dominoes of a player's hand can be used to play onto the board
	
	if (board.size() == 0) //kick out when the board has no dominoes
		return false;
	for (int i = 0; i < v.size(); i++) { // checks all dominoes of the plyaer's hand
		//if a domino can be played, function returns false 
		
		if (v[i] / 10 == board[board.size() - 1] % 10 || board[board.size() - 1] % 10 == v[i] % 10 || v[i] / 10 == board[0] / 10 || board[0] / 10 == v[i] % 10)
			return false;
	}
	return true;	//if none of the dominoes can be played, return false
}


int main() { //main function
	srand(time(NULL)); //adds a time based randomizer

	//identifying the variables
	int player1score = 0; int player2score = 0; // keeps track of how many games each player has won
	bool keepplaying = 0; // bool variable used to see if the user wants to play another game
	vector<int> dominoes; // vector of dominoes; list of all remaining dominoes in the game
	vector<int> player1; vector<int> player2; vector<int> board; // vectors for player's hand and the vector for all domineos that have been played
	//bool hard1pass = false; bool hard2pass = false; // variable detailing that a player has to pass because they cant play a domino nopr take from bazaar; both true then closed game
	int choice = 0; // variable used for deciding what the user wants to do
	int check; // the variable that will allow players to do more things if they try to make an invalid domino place

	//cout << "Welcome to Dominoes!\n"; // introduction
	//cout << "Each player will take turns using dominoes in attempt to get rid of all of their dominoes.\n";
	//cout << "The point of the game is to get rid of all the dominoes in your hand before the other player does.\n";
	//cout << "In the event of a tie, (a closed game where no one can play)\n";
	//	cout << "Whoever's hand has the least amount of dots will be the winner.\n";
	//	cout << endl;
	//cout << "Do you think you can win?\n";
	//system("pause");
	//system("cls");

	do {
		cout << "Player 1 Always goes first.\n"; // tells the players that plyr 1 always goes first
		resetgame(dominoes, player1, player2, board); // resets the vectors and re-establishes them for any time youre playing again

		dealdominoes(player1, dominoes); // gives each player their 7 dominoes; player 1
		dealdominoes(player2, dominoes); // player 2; both players have 7 and currently the bazaar has 14; 6 allowable takes from bazaar

		bool player1pass = false; bool player2pass = true; // play, go to bazaar, or pass; if they pass, then their bool switches to true
		
		do {
			if (board.size() == 0) // tells player 1 that they need to place a domino on the board
				cout << "The board has yet to be created. Player 1 must decide the first domino to play.\n" << endl;
			if (isadominopplayable(player1, board) && !player1pass && dominoes.size() > 2) { //forces the player to take from the bazaar if they cant pass nor can they play a domino; on player 1's turn
				cout << "You have no choice but to go to the bazaar.\n";
				cout << endl;
			}
			else if (isadominopplayable(player2, board) && !player2pass && dominoes.size() > 2) {//forces the player to take from the bazaar if they cant pass nor can they play a domino; on player 2's turn
				cout << "You have no choice but to go to the bazaar.\n";
				cout << endl;
			}
			//program makes the player take form the bazaar and then lets them carry on wiht the game
			
			if (board.size() > 0) //this will break if there are no values inside it first
				displayboard(board); // show the domines that have been used; shows the ends of the dominoes that you can use to connect more
			if (player1pass == false) {
				cout << "player 1 hand: \n";
				display(player1);
				cout << "Other player's hand size: "; // tells the player how many dominoes the other player has
				cout << player2.size();
				if (player2.size() > 1) // grammar
					cout << " dominoes." << endl << endl;
				else
					cout << " domino." << endl << endl;

			}
			else if (player2pass == false) {
				cout << "player 2 hand: \n";
				display(player2);
				cout << "Other player's hand size: "; // tells the player how many dominoes the other player has
				cout << player1.size();
				if (player1.size() > 1) // grammar
					cout << " dominoes." << endl << endl;
				else
					cout << " domino." << endl << endl;
			}
			if (dominoes.size() <= 2) { // tells the user that they have the option of a pass
				cout << "What do you want to do? (Enter 1 to use a domino or anything else to pass your turn.)\n"; //goes to function where they can choose what to do
				cin >> choice;
				if (choice == 1) { // use a domino
					if (player1pass == false) {
						check = makemove(board, player1);
						if (check) { //swap turns if adding domino is successful
							player1pass = true;
							player2pass = false;
						}
					}
					else {// if (player2pass == false)
						check = makemove(board, player2);
						if (check) { //swap turns if adding domino is successful
							player2pass = true;
							player1pass = false;
						}
					}
				}
				else { // pass your turn over to the other player , 0 or 3 and greater input
					if (board.size() == 0) {
						cout << "You can not pass when no one has played a domino yet. Please place a domino first.\n";
						system("pause");
					}
					else if (dominoes.size() <= 2) { // only allowed to pass if there are 2 or less dominoes in bazaar
						if (player1pass == false) {
							player1pass = true;
							player2pass = false;
						}
						else {//if (player2pass == false) {
							player2pass = true;
							player1pass = false;
						}
						system("cls"); // clear
					}

					else { // prevent passing a player's turn
						cout << "You are not allowed to pass. You can either go ot the bazaar or place a domino.\n";
						system("pause");
					}
				}
			}
			else { // does not prompt a 'pass' until the bazaar is empty
				cout << "What do you want to do? (Enter 1 to use a domino or enter anything else to take from the bazaar.)\n"; //goes to function where they can choose what to do
				cin >> choice;

				//prevent use of passing when you cant pass
				if (choice == 1) { // use a domino
					if (player1pass == false) {
						check = makemove(board, player1); // adding dominoes
						if (check) { //swap turns if adding domino is successful
							player1pass = true;
							player2pass = false;
						}
					}
					else {// if (player2pass == false)
						check = makemove(board, player2); // adding dominoes
						if (check) { //swap turns if adding domino is successful
							player2pass = true;
							player1pass = false;
						}
					}
				}
				else { //(choice == 2) { // go to the bazaar and get 2 dominoes
					if (player1pass == false)
						takefrombazaar(player1, dominoes);
					else // if (player2pass == false)
						takefrombazaar(player2, dominoes);
				}
			}
			if (checkclosed(board, player1, player2, dominoes)) //when no one can play a domino, the game is closed and then then the loopp will end
				break;
			system("cls"); // clear the board for when switching between player's turns
		} while (player1.size() != 0 && player2.size() != 0); // plays until someone has ran out of dominoes

		wincommunication(player1, player2, player1score, player2score); //win communication
		cout << "The board ended up looking like this:\n";
		displayboard(board);
		cout << endl;
		cout << "Player 1's hand was as follows:\n"; // display the player's hands at the end of the game so the player's can see closed games if it occurs
		display(player1);
		cout << "Player 2's hand was as follows:\n";
		display(player2);

		int play; // for dumby proofing
		cout << "Do you want to play again?\n";
		cout << "enter 0 to keep playing, anything else to quit.";
		cin >> play;
		if (play != 0) // turn all numbers to 1 if it doesnt equal 0, the other choice.
			keepplaying = 1;
		system("cls"); // clears the text asking if you want to quit if they continue to play
	} while (!keepplaying); // replays the game until the user wants to stop playing

	cout << "Thank you for playing.\n"; // outro
	system("pause");
	return 0; // end program
}


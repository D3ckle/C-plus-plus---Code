//Project Name : Set
//Donald Newandee
//Project Due: Friday May 8th, 2020
//
//
//Program Description :
//The goal of the program is to play the game of Set in the C++ console.  (done)
//A board of 12 cards will be shown and the user will identify 3 cards (done)
//which they think is a set and the program will properly communicate the (done)
//outcome and deal out 3 more cards if it’s a set. (done)
//The user will keep playing until all 81 cards are dealt out in which case the user will win.  (done)
//A user will enter their guess with spaces separating the numbered guesses(e.g.“1 5 12”). (done)
//The user can also type in two numbers and the program will output a card that will complete the set.  (done)
//The user will be able to exit the game in the middle with the “exit” keyword. (done)
//The final option is the user can type “more cards” one time to get 3  (Done)
//additional cards if they’re struggling to find a set. (Done)
//A class of SetCard needs to be created which will have the 4 (done)
//characteristics of a set card, char Shape, int count, int foreground color, int background color.(Done)
//You can then create a vector of all set cards in the main function (done)
//and draw the first 12 onto to the screen and start the game. (done)
//
//L1 Students will also communicate to the user if a board doesn’t have a set  (Done)
//as well as provide a hint of one of the cards that will lead to a set if they type “hint”. (Done)
//The game is only won if there are no sets left on the board. (does this mean that if there is no sets left, but cards are left, the player wins?)
//
//Specifications / Notes:
//-The set class will need to have functions of getters, setters,  (done)
//display as well as a bool function that checks the card against 2 (done)
//other cards to see if it’s a set. (done)
//- Another function that will take in another card and will return a 3 rd card which will complete the set. (done)
//- Make sure the game is repayable.  (done)
//- shuffle the vector after creation. (done)
//- When dealing 3 more cards to replace the 3 that were used to make a set make sure to add them in the same spots (done)
//- Use a vector of the deck of cards as well as a vector of the cards on the board. (done)
//- You can take vectors from the deck and add them to the board. (done)
//- Create another function that is outside of the class which will take (Done)
//in a vector of set cards and output messages if there’s any parameter  (Done)
//that’s missing(e.g.“There are no red cards on this board”). This will be a void. (Done)

using namespace std;

#include<iostream> //libraries
#include<vector>
#include<string>
#include<time.h>
#include<cmath>
#include<windows.h>



//formating / adding color
void setcolor(int color) { // changes the color of the foreground and backgronud text
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color); // changes the color of the console
}
void changewindow(int width, int height) { //resizes the window tab based on input
	HWND console = GetConsoleWindow();
	RECT r; // create a rectanlge, r
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE); //adjusts the size of the window
}

class setcard { // special class of objects with 4 characteristics of that of a card from the game: set
private:
	int foregroundcolor; // the foreground color of the object
	int backgroundcolor;// the background color of the object
	int count;// the # of symbols in the object
	char symbol;// the type of symbol of the object
public:
	void set(int f, int b, int c, char s) { // creates a setcard object accourding to the given parameters
		foregroundcolor = f; backgroundcolor = b; count = c; symbol = s;
	}
	int getforegroundcolor() { return foregroundcolor; } // gets the foreground color value only
	int getbackgroundcolor() { return backgroundcolor; }// gets the background color value only
	int getcount() { return count; }// gets the count only
	int getsymbol() { return symbol; }// gets the symbol only

	void display() { // displays a single setcard object
		setcolor(backgroundcolor * 16 + foregroundcolor); // sets the colors of the object
		for (int i = 0; i < count; i++) { // writes out each symbol based on the count
			cout << symbol;
		}
		setcolor(15); // returns the color back to normal; black bg on white text
	}

	bool isaset(setcard cardtwo, setcard cardthree) { // checks if the given cards is a set or not
		bool fcheck = false; bool bcheck = false; bool ccheck = false; bool scheck = false; // checkpoint variables to see if all characterisitcs are the same / all different

		if (foregroundcolor == cardtwo.getforegroundcolor() && foregroundcolor == cardthree.getforegroundcolor()) // if the foreground color is all the same
			fcheck = true;
		if (foregroundcolor != cardtwo.getforegroundcolor() && foregroundcolor != cardthree.getforegroundcolor() && cardtwo.getforegroundcolor() != cardthree.getforegroundcolor())// if the foreground colors are all different
			fcheck = true;
		if (backgroundcolor == cardtwo.getbackgroundcolor() && backgroundcolor == cardthree.getbackgroundcolor())// if the background color is all the same
			bcheck = true;
		if (backgroundcolor != cardtwo.getbackgroundcolor() && backgroundcolor != cardthree.getbackgroundcolor() && cardtwo.getbackgroundcolor() != cardthree.getbackgroundcolor()) // if the foreground color is all different
			bcheck = true;
		if (count == cardtwo.getcount() && count == cardthree.getcount())// if the count is all the same
			ccheck = true;
		if (count != cardtwo.getcount() && count != cardthree.getcount() && cardtwo.getcount() != cardthree.getcount())// if the count is all different
			ccheck = true;
		if (symbol == cardtwo.getsymbol() && symbol == cardthree.getsymbol())// if the symbol is all the same
			scheck = true;
		if (symbol != cardtwo.getsymbol() && symbol != cardthree.getsymbol() && cardtwo.getsymbol() != cardthree.getsymbol())// if the symbol is all different
			scheck = true;

		if (fcheck && bcheck && ccheck && scheck)//if bools all are true, it is a set
			return true;
		else // not a set
			return false;
	}
};

vector<setcard> generatedeck() { // generate all 81 cards in the deck, wtih all cards different from each other
	setcard temp;
	vector<setcard> deck;
	for (int i = 0; i < 3; i++) { //background color
		int backcolor;
		if (i == 0)
			backcolor = 6;// yellow
		else if (i == 1)
			backcolor = 10;// green
		else
			backcolor = 8;// gray
		for (int j = 0; j < 3; j++) {// foreground color
			int forecolor;
			if (j == 0)
				forecolor = 15;//white
			else if (j == 1)
				forecolor = 4;//red
			else
				forecolor = 1;// blue
			for (int x = 1; x < 4; x++) { // count
				for (int z = 0; z < 3; z++) { // symbol
					char symbol;
					if (z == 0)
						symbol = '&';
					else if (z == 1)
						symbol = '$';
					else //2
						symbol = '@';
					temp.set(forecolor, backcolor, x, symbol); // creating the card (temporarily)
					deck.push_back(temp); // adding the card to the deck (vector)
				}
			}
		}
	}
	return deck; // 3^4 = 81 cards total
}
void shuffle(vector<setcard>& v) { // randomizes the cards to make them in a random order
	for (int i = 0; i < v.size(); i++) //does this for the size of the array you put in
	{
		int randomspot = rand() % v.size(); // gets a random size from 0 to the number of items in the vector
		//swap
		setcard temp = v[i]; //temporarily saves the variable youre switching in for
		v[i] = v[randomspot]; // replaces the value as youve copied it to be replaced
		v[randomspot] = temp; // overides the value youve already copied over for the value copied temporarily
	}
}
void displayboard(vector<setcard>& board) { // displays the useable cards for the player to choose form to make a set
	for (int i = 0; i < board.size(); i++) { // display the board
		cout << i << " ";
		board[i].display();
		cout << "\n";
	}
}
bool updateboard(vector<setcard>& board, vector<setcard>& deck, int set[]) {
	if (board.size() == 15) {
		for (int i = 0; i < 3; i++) {
			board[set[i]].set(-1, -1, -1, '_'); //NULL values to make it unrecognized by program, only recognized to be removed
		}
		for (int i = 0; i < board.size(); i++) { // search the board
			if (board[i].getbackgroundcolor() == -1) { // if a NULL value created from previous for loop has been found
				board.erase(board.begin() + i); // remove the NULL value created in previous for loop
				i--; //now the size has been changed, shift i back by one to prevent skipping & deleting wrong objects
			}
		}
		return true;
	}
	else {
		if (deck.size() >= 3) { // so long as there are cards left to be used
			for (int i = 0; i < 3; i++) { // remove cards from board and take 3 cards from deck vector to replace
				board.erase(board.begin() + set[i]);
				board.insert(board.begin() + set[i], deck[deck.size() - 1]);
				deck.pop_back();
			}
			return true; // successfully updated with new cards
		}
		else
			return false; // dont update board
	}

}
void specialcommunication(vector<setcard> deck) { // tells us some aspects of the cards on the board
	//bgc: yellow, green, gray
	//fgc: white, red, blue
	//count: 1, 2, 3
	//symbol: &, $, @
	//alll the bools for the different aspects/types of a card
	bool hascharacteristic[12];
	for (int i = 0; i < 12; i++) { // turning all 12 characteristics to false
		hascharacteristic[i] = false; // false unless proven true
	}
	//bgc: yellow, green, gray
	//fgc: white, red, blue
	//count: 1, 2, 3
	//symbol: &, $, @
	//alll the bools for the different aspects/types of a card
	for (int i = 0; i < deck.size(); i++) {
		if (deck[i].getbackgroundcolor() == 6) // is there yellow
			hascharacteristic[0] = true;
		if (deck[i].getbackgroundcolor() == 10) // is there green
			hascharacteristic[1] = true;
		if (deck[i].getbackgroundcolor() == 8) // is there gray
			hascharacteristic[2] = true;
		if (deck[i].getforegroundcolor() == 15) // is there white
			hascharacteristic[3] = true;
		if (deck[i].getforegroundcolor() == 4) // is there red
			hascharacteristic[4] = true;
		if (deck[i].getforegroundcolor() == 1) // is there blue
			hascharacteristic[5] = true;
		if (deck[i].getcount() == 1) // is there 1 symbol
			hascharacteristic[6] = true;
		if (deck[i].getcount() == 2) // is there 2 symbols
			hascharacteristic[7] = true;
		if (deck[i].getcount() == 3) // is there 3 symbols
			hascharacteristic[8] = true;
		if (deck[i].getsymbol() == '&') // is there &
			hascharacteristic[9] = true;
		if (deck[i].getsymbol() == '$') // is there $
			hascharacteristic[10] = true;
		if (deck[i].getsymbol() == '@') // is there @
			hascharacteristic[11] = true;
	}

	if (!hascharacteristic[0]) // yellow has not been found
		cout << "There are no yellow cards on this board.\n";
	if (!hascharacteristic[1]) // green has not been found
		cout << "There are no green cards on this board.\n";
	if (!hascharacteristic[2]) // gray has not been found
		cout << "There are no gray cards on this board.\n";
	if (!hascharacteristic[3]) // white has not been found
		cout << "There are no white cards on this board.\n";
	if (!hascharacteristic[4]) // red has not been found
		cout << "There are no red cards on this board.\n";
	if (!hascharacteristic[5]) // blue has not been found
		cout << "There are no blue cards on this board.\n";
	if (!hascharacteristic[6]) // 1 symbol has not been found
		cout << "There are no single symbol cards on this board.\n";
	if (!hascharacteristic[7]) // 2 symbols has not been found
		cout << "There are no double symbol cards on this board.\n";
	if (!hascharacteristic[8]) // 3 symbols has not been found
		cout << "There are no triple smybol cards on this board.\n";
	if (!hascharacteristic[9]) // & symbol has not been found
		cout << "There are no & cards on this board.\n";
	if (!hascharacteristic[10]) // $ symbol has not been found
		cout << "There are no $ cards on this board.\n";
	if (!hascharacteristic[11]) // @ symbol has not been found
		cout << "There are no @ cards on this board.\n";
}
int* doessetexist(vector <setcard> board) { //checking if there is a set on the board
	int set[] = { -1, -1, -1 };
	//check all combinations of the cards on the board
	for (int i = 0; i < board.size(); i++) {
		for (int j = i + 1; j < board.size(); j++) { // check the card after i
			for (int k = j + 1; k < board.size(); k++) {// check the card after j
				if (board[i].isaset(board[j], board[k])) { // if a set is found, return the set
					set[0] = i; // save the addresses of the cards in the set
					set[1] = j;
					set[2] = k;
					//cout << set[0] << endl;
					//cout << set[1] << endl;
					//cout << set[2] << endl;
					//set[0] = board[i]; // save the cards in the set
					//set[1] = board[j];
					//set[2] = board[k];
				}
			}
		}
	}

	return set; // return the addresses of the cards in the set
}

int main() { // main function
	srand(time(NULL)); // time randomizer

	//for (int i = 0; i < 16; i++) { // shows all the color combinations
	//	for (int j = 0; j < 16; j++) {
	//		setcolor(i * 16 + j);
	//		cout << i << " " << j << ") " << "hello world\n";
	//	}
	//}

	//introduction
	cout << "Welcome to Set!\n\n";
	//instructions
	cout << "In the game Set, you need to match sets of 3 cards that have the same type of characteristics,\n";
	cout << "or a different type of characteristic (e.g. back / foreground color, # of symbols, count).\n";
	cout << "Do you think you can win?\n";
	system("pause");
	system("cls");

	bool keepplaying = true; // bool variable to play a game or not
	do {
		vector<setcard> deck = generatedeck(); // create the deck of 81 unique cards
		//vector<setcard> deck;
		//setcard temp;
		//temp.set(1, 1, 1, '1');
		//deck.push_back(temp);
		//temp.set(1, 1, 1, '1');
		//deck.push_back(temp);
		//temp.set(1, 1, 1, '1');
		//deck.push_back(temp);
		//temp.set(1, 1, 1, '1');
		//deck.push_back(temp);
		//temp.set(1, 1, 1, '1');
		//deck.push_back(temp);


		//for (int i = 0; i < deck.size(); i++) { // display the entire deck; or all cards not being used yet
		//	deck[i].display();
		//	cout << "\t";
		//	if (i % 3 == 2)
		//		cout << endl;
		//}

		shuffle(deck); // shuffles the deck

		vector<setcard> board; // vector holding all the useable cards; the board
		//for (int i = 0; i < 5; i++) { // create the board; for testing
		for (int i = 0; i < 12; i++) { // create the board
			board.push_back(deck[deck.size() - 1]); // adds a card from the deck
			deck.pop_back();// removes the card added to the board, from the deck
		}
		int card1 = 0; int card2 = 0; int card3 = 0; // addresses of all 3 cards that will make up the set
		//int card1int = 0; int card2int = 0; int card3int = 0;
		string str; // string used later get input of player if they want to play the game again or not
		string inputstr; // string taken form user to use as their choice, in use for finding the cards they chose / using one of the functions
		bool stop = false; // bool variable used in the 
		do {
			bool useableset = true; // reset bool for each loop, prevent issues with functions not working after one use
			int firstspace = 0;
			int lastspace = 0;
			do { // asking for cards to check that is a set
				useableset = true;
				int* setonboard = doessetexist(board); // checks if there is a set with the cards on the board
				if (setonboard[0] == -1) { // telling user there are no sets in the board; default -1 so no hcange to the set array = no set
					if (deck.size() == 0) { // there is no more cards left
						stop = true;
						inputstr = "exit"; // use the exit function to leave the loop and 'quit' the game
					}
					else //there is not a set on the board
						cout << "There is NOT a set on the board.\n";
				}

				else // there is a set
					cout << "There IS a set on the board.\n";

				if (inputstr != "exit") { // outputs this so long as the player doesnt quit or hasnt won yet
					cout << "Board: (Size: " << board.size() << ")\n";
					displayboard(board);
					//cout << "deck size: " << deck.size() << endl; // tell the deck size
					specialcommunication(board); // writes the missing characteristics of the cards of the board
					cout << endl;

					//communicate to the player the directions / options
					cout << "Which cards are a set?\n";
					cout << "Enter the cards in the format shown: \"1 2 3\"\n";
					cout << "Enter \"exit\" to quit the game and or restart.\n";
					cout << "Enter \"hint\" to get a hint for a set.\n";
					cout << "Enter \"more cards\" to get 3 additional cards to use (maximum of 15).\n";
					cout << "Only enter 2 cards to find the 3rd card that makes a set.\n";
					cout << "Cards: ";

					getline(cin, inputstr); //e.g. : "1 2 3" space delimiter or one of the functions; hint, more cards, exit, "1 2"
				}

				if (inputstr == "exit") { // leave the loop and takes user to the restart screen; exit function
					break;
				}
				else if (inputstr == "hint") { // give the player a hint to a set
					int* hintset = doessetexist(board);
					if (hintset[0] == -1) {// null, no set has been found
						cout << "There is no set on this board. Try getting more cards or exit the game.\n";
					}
					else // a set has been found
						cout << "One card that finishes the set is card: " << hintset[0] << ".\n";
					useableset = false; // restart the do while loop
					system("pause");
					system("cls");
				}
				else if (inputstr == "more cards") { // gets 3 more cards from the board

					if (board.size() <= 12 && deck.size() >= 3) { // make sure there is "space" on the board and that there are cards left to use
						for (int i = 0; i < 3; i++) { // adding three cards to the board from the deck
							board.push_back(deck[deck.size() - 1]);
							deck.pop_back();
						}
						useableset = false; // restart the loop
						system("cls");
					}
					else { //there is an issue with getting cards
						if (board.size() > 12) { // prevents taking more from the board
							cout << "You can not have more than 15 cards on the board at a time.\n";
							useableset = false; // restart the loop
							system("pause");
							system("cls");
						}
						else { // not more remaining cards in the leftover deck
							cout << "There are no more cards left in the deck to get more cards.\n";
							useableset = false; // restart the loop
							system("pause");
							system("cls");
						}
					}
				}
				else {
					firstspace = inputstr.find_first_of(' '); // finding first occurance of a space
					lastspace = inputstr.find_last_of(' ');// finding last occurance of a space
					if (firstspace == lastspace && firstspace != -1) { //find last card function; input wiht only 2 space, first & last space == eachother
						card1 = stoi(inputstr.substr(0, firstspace)); //first #
						card2 = stoi(inputstr.substr(lastspace, inputstr.size() - lastspace)); // second #

						if (card1 > board.size() - 1 || card2 > board.size() - 1 || card1 < 0 || card2 < 0) {// using a card outside the range of the board
							useableset = false; // restart the loop
							cout << "you can not choose cards outside of the ones shown.\n";
							system("pause");
						}
						if (card1 == card2) { // using the same card
							useableset = false; // restart the loop
							cout << "you must use different cards.\n";
							system("pause");
						}
						if (!useableset) // clears the error message if there is one
							system("cls");
						else {
							bool found = false; // bool to tell if the 3rd card of a set is found
							for (int card3 = 0; card3 < board.size(); card3++) { // find the 3rd card on the board first if there is one
								if (card3 != card1 && card3 != card2) {
									if (board[card1].isaset(board[card2], board[card3])) {
										cout << " The 3rd card is on the board, and is card " << card3 << " that looks like ";
										board[card3].display();
										cout << ".\n";
										found = true; // a 3rd card is found
									}
								}
							}
							for (int card3 = 0; card3 < deck.size(); card3++) { // if the 3rd card is not found in board, check the deck
								if (board[card1].isaset(board[card2], deck[card3])) {
									cout << " The 3rd card is in the deck, and looks like ";
									deck[card3].display();
									cout << ".\n";
									found = true; // a 3rd card is found
								}
							}
							if (!found) { // there is no matching set in the rest fo the remaining cards; communicates
								cout << "There are no remaining cards that matches to make a set with ";
								board[card1].display();
								cout << " and ";
								board[card2].display();
								cout << ".\n";
							}
							system("pause");
							system("cls");
							useableset = false; // restart the loop
						}
					}
					else if (firstspace != lastspace) { //use 3 cards as normal, 2 spaces seperating the 3 numbers
						card1 = stoi(inputstr.substr(0, firstspace)); // gather address of first card
						card2 = stoi(inputstr.substr(firstspace, lastspace)); // gather address of second card
						card3 = stoi(inputstr.substr(lastspace, inputstr.size() - lastspace));// gather address of third card
						//dummyproofing
						if (card1 > board.size() - 1 || card2 > board.size() - 1 || card3 > board.size() - 1 || card1 < 0 || card2 < 0 || card3 < 0) {// using a card outside the range of the board
							useableset = false; // restart the loop
							cout << "you can not choose cards outside of the ones shown.\n";
							system("pause");
						}
						if (card1 == card2 || card1 == card3 || card3 == card2) { // using the same card twice or more
							useableset = false; // restart the loop
							cout << "you must use 3 different cards.\n";
							system("pause");
						}
						if (!useableset)
							system("cls");
					}
					else { // errors in the input
						useableset = false; // restart the loop
						cout << "That is an invalid input.\n";
						system("pause");
						system("cls");
					}
				}
			} while (!useableset); // gets 3 useable cards to check if it is a set

			int set[] = { card1, card2, card3 }; // chosen cards for the set

			if (inputstr != "exit" && inputstr != "hint" && inputstr != "more cards") {
				//we found 3 useable cards, that are different
				if (board[card1].isaset(board[card2], board[card3])) { // the set used is an actual set
					cout << "it is a set\n";

					if (!updateboard(board, deck, set)) { // returned false, deck size is less than 3
						for (int i = 0; i < 3; i++) {
							board[set[i]].set(-1, -1, -1, '_'); //NULL values to make it unrecognized by program, only recognized to be removed
						}
						for (int i = 0; i < board.size(); i++) { // search the board
							if (board[i].getbackgroundcolor() == -1) { // if a NULL value created from previous for loop has been found
								board.erase(board.begin() + i); // remove the NULL value created in previous for loop
								i--; //now the size has been changed, shift i back by one to prevent skipping & deleting wrong objects
							}
						}
					}
				}
				else { // the set used is not a set
					cout << "that is not a set.\n";
				}
				system("pause"); // pause and clear to update the console
				system("cls");
			}
			else
				break;
		} while (board.size() >= 3 && deck.size() != 0 || !stop); // break when there are no sets left
		if (deck.size() == 0) // outputs a win message if there are no more cards left in the deck
			cout << "There are no more sets left, you win!\n";
		cout << "enter 1 to try again, anything else to quit.\n";
		getline(cin, str);
		if (str != "1") { // input of '1' to play again
			keepplaying = false;
		}
		else
			system("cls");
	} while (keepplaying); // loop to play the entire game

	cout << "thank you for playing!\n"; // outro

	system("pause");
	return 0; // end program
}

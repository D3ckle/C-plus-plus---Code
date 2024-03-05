//Donald Newandee

using namespace std;

#include<iostream> //libraries
#include<vector>
#include<string>
#include<time.h>
#include<cmath>
#include<windows.h>



//formating / adding color
void setColor(int color) { // changes the color of the foreground and backgronud text
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color); // changes the color of the console
}
void changewindow(int width, int height) { //resizes the window tab based on input
	HWND console = GetConsoleWindow();
	RECT r; // create a rectanlge, r
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE); //adjusts the size of the window
}

void displayBag(int** arr2d, int x, int y) { //x left to right, y up and down
	for (int row = 0; row < x; row++) {
		for (int col = 0; col < y; col++) {
			cout << arr2d[row][col] << "\t";
			if ((row * 10 + col + 1) % x == 0) // end the line to end the row; continue next row on next line
				cout << endl;
		}
	}
	cout << endl;
}
int** boardcreate(int x, int y) {// x = # of columns, y = # of rows
	int** board = new int* [x]; // creating pointers with pointers in each pointer
	for (int row = 0; row < x; row++) { // assigning 
		board[row] = new int[y]; // x rows, each with 10 columns
		for (int col = 0; col < y; col++)
			if (col != 10)
				board[row][col] = 0;
			else
				board[row][col] = 1; //row * y + col; // adding the values in the 2d board
	}
	return board;
}
bool allnumbers(string& str) { // checks if the string is all numbers
	int decimalptcount = 0; //int for counting the # of decimals
	int commacount = 0;
	if (str[0] == '-') {// if its a negative number
		for (int i = 1; i < str.length(); i++) {
			if (str[i] == '-') // if a second dash is found, error
				return false;
			else if (str[i] == '.') { // decimal point, only 1 is allowed to be found, and after a comma if there is one
				decimalptcount++;
				if (decimalptcount > 1) {
					return false;
				}
				//else if (str[i] == ',') { // 'comma, more than one is allowed but there must be a 3 digits beteen each comma
				//}
				else if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.')
					return false;
			}
		}
		return true;
	}
	else { // positive numbers
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '.') { // decimal point, only 1 is allowed to be found, and after a comma if there is one
				decimalptcount++;
				if (decimalptcount > 1) {
					return false;
				}
			}
			//else if (str[i] == ',') { // 'comma, more than one is allowed but there must be a 3 digits beteen each comma
			//}
			else if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.')
				return false;
		}
		return true;
	}
}
class POKEMON //sets up the class for the player's pokemon
{
private:
	//defining variables
	int level, hp, currentEXP, currentHP, subHP, currentSubHP, totalEXP; float att, def, agi; string trait, ability; vector<string> moveSet, movePool;

public:
	//functions for getting the information for their stats
	int getLevel() { return level; }
	int getTotalHP() { return hp; }
	int getAtt() { return att; }
	int getDef() { return def; }
	int getAgi() { return agi; }
	int getCurrentEXP() { return currentEXP; }
	int getTotalEXP() { return totalEXP; }
	int getCurrentHP() { return currentHP; }
	int getSize() { return moveSet.size(); }
	int getSizePool() { return movePool.size(); }
	int getSubCurrentHP() { return currentSubHP; }
	int getSubTotalHP() { return subHP; }
	string getMove(int spot)
	{
		if (moveSet.size() > 0)
			return moveSet[spot];
	}
	string getMoveFromPool(int spot)
	{
		if (movePool.size() > 0)
			return movePool[spot];
	}
	string getAbility() { return ability; }
	string getTrait() { return trait; }
	void setCurrentHP(int health) { currentHP = health; }
	void setUp() //sets up the stats, traits, and initial moves for the pokemon
	{
		//sets up the base stats
		level = 1;
		currentHP = 10;
		hp = 10;
		currentEXP = 0;
		totalEXP = 10;
		att = 5;
		def = 5;
		agi = 5;
		subHP = 0;
		currentSubHP = 0;
		srand(time(NULL)); //setting the randomness for the game
		int traitNumber = rand() % 5;
		if (traitNumber == 0)
			trait = "strong-willed";
		else if (traitNumber == 1)
			trait = "innocent";
		else if (traitNumber == 2)
			trait = "agressive";
		else if (traitNumber == 3)
			trait = "care-free";
		else if (traitNumber == 4)
			trait = "cheerful";
		//puts in the pokemon's current move set
		moveSet.push_back("Slap");
		moveSet.push_back("Stare");
		moveSet.push_back("None");
		moveSet.push_back("None");
	}

	void setStats(int newLevel, int newHP, int newAtt, int newDef, int newAgi) //forcibly set the stats for a pokemon
	{
		//setting stats to the inputted values
		level = newLevel;
		hp = newHP;
		currentHP = newHP;
		att = newAtt;
		def = newDef;
		agi = newAgi;
	}
	void resetSubHP()
	{
		currentSubHP = 0;
		subHP = 0;
	}
	void fullHeal() { currentHP = hp; } //full heals the pokemon (purely for testing purposes)
	void setEXP(int newEXP) { currentEXP = newEXP; } //sets the EXP for the pokemon(purely for testing purposes)

	void randomizeStats(POKEMON p) //used for the scaling of enemies
	{
		if (p.level == 1)
			setUp();
		//50% chance to be 1 level lower than the player's pokemon
		else if (rand() % 2 == 0)
		{
			level = p.level - 1;
			hp = 10 * p.level - 10 - (rand() % 3);
			currentHP = hp;
			att = 5 * p.level - 5 - (rand() % 3);
			def = 5 * p.level - 5 - (rand() % 3);
			agi = 5 * p.level - 5 - (rand() % 3);
		}
		else //50% chance to be 1 level higher than the player's pokemon
		{
			level = p.level + 1;
			hp = 10 * p.level + (rand() % 5);
			currentHP = hp;
			att = 5 * p.level + (rand() % 5);
			def = 5 * p.level + (rand() % 5);
			agi = 5 * p.level + (rand() % 5);
		}
	}

	void copyStats(POKEMON p) //this is for convenience and copies one pokemon's stats onto another
	{
		level = p.level + 1;
		hp = p.hp;
		currentHP = p.hp;
		att = p.att;
		def = p.def;
		agi = p.agi;
	}

	//changes the characteristics of the pokemon after they have leveled up
	void setLevel(int newLevel) { level = newLevel; } //this is just to cheat to test things
	void gainEXP(int eLevel) { currentEXP = currentEXP + 2 * eLevel; }
	void levelUp()
	{
		level++;
		att = att + 5;
		def = def + 5;
		agi = agi + 5;
		hp = hp + 10;
		currentEXP = 0;
		totalEXP = pow(level, 3) + 10;
	} //makes the pokemon level up
	void changeTrait(string newTrait) { trait = newTrait; }
	void learnMove(string newMove, int spot) { moveSet[spot - 1] = newMove; }
	void createMovePool() //creates the move pool for the player's pokemon
	{
		movePool.push_back("Perfect Alibi");
		movePool.push_back("Serious Punch");
		movePool.push_back("Poker Face");
		movePool.push_back("Kick");
		movePool.push_back("Concentrate");
	}
	void removeFromPool() { movePool.pop_back(); } //removes the last move in the vector
	void pokerFace() //corresponds to the moves and decreases all stats of the pokemon
	{
		//poker face permenantly decreases all of the pokemon's current stats by 10%
		att = att - (0.1 * att);
		def = def - (0.1 * def);
		agi = agi - (0.1 * agi);
	}

	void perfectAlibi() //creates a subsitute of the character
	{
		//defines the alibi's HP
		subHP = 10;
		currentSubHP = subHP;
		//adds it to the pokemon's HP
		//on the screen it will be shown as separate but in code it is combined
		/*hp = hp + subHP;
		currentHP = currentHP + currentSubHP;*/
	}

	void stare() { def = def - ceil(def * 0.30); }//decreases the enemy's current defense by about 30%

	void displayStats() //displays all stats of the pokemon
	{
		cout << "Pokemon Stats:\n\n";
		cout << "Level: " << level << endl;
		cout << "Health Points: " << hp << endl;
		cout << "Attack: " << att << endl;
		cout << "Defense: " << def << endl;
		cout << "Agility: " << agi << endl;
		cout << "Trait: " << trait << endl;
		cout << "EXP: " << currentEXP << "/" << totalEXP << endl << endl;
	}

	void takeDamage(int damage) { currentHP = currentHP - damage; } //makes the pokemon take damage
	void damageAlibi(int damage) { currentSubHP = currentSubHP - damage; } //damages the alibi
};
class trainer {
private:
	//int x; int y; // specs of the item bag size
	int nature; int exp; int money; int** itembag;
public:
	//getter functions
	int getnature() { return nature; }
	int getexpirence() { return exp; }
	int getmoney() { return money; } // wasnt added in originally
	int** getitembag() { return itembag; }
	//setterfunctions
	void settrainer(int n, int e, int m, int** t) { nature = n; exp = e; money = m; itembag = t; }
	void setnature(int n) { nature = n; }
	void setexpirence(int e) { exp = e; }
	void setmoney(int m) { money = m; }
	void setexpirence(int** t) { itembag = t; }

	//bag functions
	bool addtobag(int item) { // takes an item that will be added to the player's bag
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 10; y++) {
				if (itembag[x][y] == 0) { // empty slot in the bag
					itembag[x][y] = item; // replace the spot with the item being added
					return true; // end funtion and 
				}
			}
		}
		cout << "the bag is full.\n";
		return false;
	}
	bool useitem(POKEMON& p, int item) { // finds the first instance of an item, and removes it from the bag to be used
		bool found = false; // variable to show that the item we're looking for is found in the bag
		int index1; int index2;
		//int x = 0; int y = 0; // locations used to find the itmes in the bag
		for (int x = 0; x < 2; x++) { // search by row of the bag
			for (int y = 0; y < 10; y++) { // search by column of the bag
				if (itembag[x][y] == item) { // looking for the item in the bag
					index1 = x;
					index2 = y;
					found = true; // if found, set bool to true
					break; // break out of loop (find first, or find last: remove this line)
				}
			}
		}
		if (found) { // remove the item and then trigger the item use
			itemaffect(p, itembag[index1][index2]); // not created yet
			itembag[index1][index2] = 0; // set the item being used to 0,
			system("pause");
			return true;
		}
		else {
			cout << "item not found in bag / ERROR\n";
			system("pause");
			return false;
		}
	}
	bool isiteminbag(int item, int x, int y) { // searches for an item to see if it is in the bag
		for (int row = 0; row < x; row++) {
			for (int col = 0; col < y; col++) {
				if (itembag[row][col] == item)
					return true;
			}
		}
		return false;
	}
	void removeitem(int item, int x, int y) { // removes an item from the bag
		for (int row = 0; row < x; row++) {
			for (int col = 0; col < y; col++) {
				if (itembag[row][col] == item) {
					itembag[row][col] = 0; // remove the item
					row = x; // ends the loop
					col = y;
				}
			}
		}

	}

	void itemaffect(POKEMON& p, int item) { // adds the affect of the item to the pokemon e.g. heal for 20 hp, boost attack by 10 points, etc.
		//change variable name to the variable of the 
		if (item == 1) {// small potion
			if (p.getCurrentHP() + 20 > p.getTotalHP())
				p.fullHeal();
			else
				p.setCurrentHP(p.getCurrentHP() + 20);
			cout << "pokemon has been healed.\n";
			system("pause");
			system("CLS");
		}
		else if (item == 2) // rare candy
			p.levelUp();
		else {
			cout << "Invalid item use\n";
			system("pause");
			system("CLS");
		}
	}
};
//functions for casino
void shuffle(vector<int>& v) { // randomizes the cards to make them in a random order
	for (int i = 0; i < v.size(); i++) //does this for the size of the array you put in
	{
		int randomspot = rand() % v.size(); // gets a random size from 0 to the number of items in the vector
		//swap
		int temp = v[i]; //temporarily saves the variable youre switching in for
		v[i] = v[randomspot]; // replaces the value as youve copied it to be replaced
		v[randomspot] = temp; // overides the value youve already copied over for the value copied temporarily
	}
}
vector<int> creatcarddeck() {
	// 4 of each
	// 2, 3, 4, 5, 6, 7, 8, 9, 10,
	//jack x 4, queen x 4, king, x 4 = 10 each
	//ace = 1 OR 11, whichever is better for the hand

	vector<int> deck; // standard deck of 52 cards (ignoring the symbol of the chard)
	int x = 0;
	for (int i = 0; i < 4; i++) { // 4 of each card in a card deck
		for (int j = 0; j < 13; j++) { // 13, each card per suite
			if (j != 0 && j < 11)
				deck.push_back(j); // all of the #ed cards, including ace
			else
				deck.push_back(10); // jack, queen and or king card; hit for 0, 11, 12 and 13
		}
	}
	//cout << "count:" << x << endl;
	return deck;
}
vector<int> dealfirst2cards(vector<int>& v) { // gives the first 2 cards to the dealer / player at the start of the round from the deck
	vector<int> hand;
	for (int i = 0; i < 2; i++) { // 2 cards
		hand.push_back(v[v.size() - 1]); // add to the hand
		v.pop_back(); // remove the card from the deck
	}
	return hand;
}
bool acefound(vector<int>& v) { //checks for special case: an ace, which could count as 1 point or 11, whatever is more favorable
	for (int i = 0; i < v.size(); i++)
		if (v[i] == 1) // if a card with value of 1 is found
			return true; // an ace has been found
	return false; // no ace is found
}
void casino(trainer& player) //simulates the casino location for the game
{
	//intro
	setColor(12);
	cout << "You Are At The Casino!\n";
	cout << "At The Casino, You Can Irresonsibly Earn Or Lose Large Amounts of Money Here!\n";
	cout << "Mother Probably Would Not Want Me To Be At The Casino . . .\n\n";
	setColor(14);
	//blackjack

	cout << "How to play BlackJack:\n";//directions / instructions
	cout << "The goal of Blackjack is to beat the Dealer.\n";
	setColor(10);
	cout << "to win you must either:\n";
	cout << "1) get a blackjack (an ace card and any 10 value card) where you get a 150% of your bet as a reward\n";
	cout << "OR\n";
	cout << "2) Get closer to 21 than the dealer without going over.\n";
	setColor(11);
	cout << "You may ask for cards until your hand exceeds the 21 point bust limit, which you will loose.\n";
	cout << "the dealer shows only 1 card, and will draw cards until they exceed 17 after your turn.\n";
	cout << "If you have equal points to the dealer, you play a new round.\n\n";
	setColor(14);
	cout << "all face cards = 10 points\n";
	cout << "ace cards = 1 OR 11\n";
	cout << "numbered cards = equal to the number on their card.\n";
	setColor(15);
	system("pause");
	system("cls");
	bool playagain = true; // bool variable for playing again
	string str; // input string used for getting input from user
	do { // play blackjack again loop

		bool turnend = false; // bool for when the player chooses to stop taking cards and end their turn to have the dealer start his turn
		double betdb = 0; // double variable to hold the amount to bet
		do {
			do {
				setColor(14);
				cout << "current Funds: " << player.getmoney() << " Gold\n"; //shows player their money
				setColor(12);
				cout << "How much do you want to bet?\n"; //ask for the bet value; make sure it doesn't exceed current money
				setColor(15);
				cout << "If you do not wish to play, enter '0' to quit Blackjack.\n";
				getline(cin, str);
				//dummyproofing
				if (!allnumbers(str) || str.length() == 0) { // if there is a letter in th input or no input; error
					setColor(12);
					cout << "That is not an apporpriate value to use. PLease Enter a numerical value.\n";
					system("pause");
					system("cls");
					setColor(15);
				}
			} while (!allnumbers(str) || str.length() == 0); // dummy proofing; prevent a letter / symbol when convertting str to int
			betdb = stoi(str);

			//betdb = 1;
			//dummy proofing

			//more dummy proofing
			if (betdb > player.getmoney()) { // betting more than what they have
				setColor(12);
				cout << "You can not bet more than the amount you currently have.\n";
				system("pause");
				system("cls");
				setColor(15);
			}
			else if (betdb < 0) { // betting less money than 0
				setColor(12);
				cout << "You can not bet less than 0.\n";
				system("pause");
				system("cls");
				setColor(15);
			}
			else if (betdb == 0) { // no bet, dont play the game, kick to ask if they want to play again
				turnend = true;
				break;
			}
		} while (betdb > player.getmoney() || betdb < 0); // makes sure to have a valid amount that the player is able to bet

		if (betdb > 0) { // so long as there is a bet
			do {
				vector<int> deck = creatcarddeck(); // creating the deck of cards, where face cards are given the value of 10
				shuffle(deck); // shuffle the deck

				vector<int> dealerhand = dealfirst2cards(deck);//dealdealer

				//dealerhand[0] = 1;
				//dealerhand[1] = 10;

				vector<int> playerhand = dealfirst2cards(deck);//dealplayer

				//playerhand[0] = 1;
				//playerhand[1] = 10;

				int playerpoint = playerhand[0] + playerhand[1]; // adding the int values of both the cards together of the player's hand
				int dealerpoint = dealerhand[0] + dealerhand[1]; // add both cards up of the dealer's hand
				do {
					//ask player if they want to draw more cards or end their turn
					string str;
					do { // make sure to get a valid input of '1' or '2'
						system("cls");
						setColor(12);
						cout << "Dealer's first card: " << dealerhand[0] << endl; //show 1 card of 2, draw the card but dont show it
						cout << endl;
						setColor(10);
						cout << "Player's Hand:\n"; // shows the player's cards
						for (int i = 0; i < playerhand.size(); i++)//show both cards
							cout << "Card " << i + 1 << ") " << playerhand[i] << endl;

						cout << "Player's Total points: " << playerpoint;
						if (acefound(playerhand)) // if there is an ace, then the point value could potentially be 10 points higher, tell user that
							cout << "( + 10)";
						cout << endl << endl;
						setColor(11);
						cout << "What would you like to do?\n"; // instructions for the turn
						cout << "Enter '1' to Draw a card.\n";
						cout << "OR\n";
						cout << "Enter '2' to End your turn.\n";
						getline(cin, str);
						//dummyproofing
						if (str != "1" && str != "2") { // doesnt enter in 1 or 2
							setColor(12);
							cout << "please Enter '1' or '2'.\n";
							system("pause");
							system("cls");
							setColor(15);
						}
					} while (str != "1" && str != "2"); // makes sure the player chooses an option

					if (str == "1") { // inputy to draw a card from the deck
						playerhand.push_back(deck[deck.size() - 1]); // take from deck
						deck.pop_back(); // remove the card just taken from the deck
						setColor(10);
						playerpoint += playerhand[playerhand.size() - 1]; // add the value of the new card
						for (int i = 0; i < playerhand.size(); i++)//show both cards
							cout << "Card " << i + 1 << ") " << playerhand[i] << endl; // rewrite all the cards

						cout << "Player's Total points: " << playerpoint; // tells player their new point value
						if (acefound(playerhand)) // if there is an ace, then the point value could potentially be 10 points higher, tell user that
							cout << "( + 10)";
						cout << endl << endl;
						setColor(15);
					}
					else { //(str == "2") // ends the turn
						if (acefound(playerhand) && playerpoint + 10 == 21) // if any of the cards is an ace, find best scenario to win, either ace = 1, or ace = 11
							playerpoint = 21; // if it is an ace and 1 rest sum of 10 / 10 point card, then win; if ace being 11 points wins, then ace = 11
						turnend = true; // swtihc bool to end the turn
						system("cls");
					}

				} while (!turnend && playerpoint < 21); // either until player ends turn or their hand exceeds 21 points
				int i = 0; // used to track the # of cards
				setColor(12);
				cout << "Dealer's Hand:\n"; //reveal dealer's hand
				for (i = 0; i < dealerhand.size(); i++)//show both cards
					cout << "Card " << i + 1 << ") " << dealerhand[i] << endl;
				setColor(15);
				if (playerpoint <= 21) { // wont execute if the player already lost, direct to lose text
					system("pause");
					if (acefound(dealerhand) && dealerpoint + 10 == 21) // if any of the cards is an ace, find best scenario to win, either ace = 1, or ace = 11
						dealerpoint = 21; // if it is an ace and 1 rest sum of 10 / 10 point card, then win; if ace being 11 points wins, then ace = 11

					if (dealerpoint <= 17) { // prevents taking from deck if already above 17
						//skip loop if already 21
						do {// dealer draw cards until over 17
							i++; // add to the card count
							dealerhand.push_back(deck[deck.size() - 1]); // add a card to the dealer's hand
							deck.pop_back(); // remove the card from the deck
							dealerpoint += dealerhand[dealerhand.size() - 1];
							setColor(12);
							cout << "Card " << i << ") " << dealerhand[dealerhand.size() - 1] << endl; // the new card the dealer drew
							if (acefound(dealerhand) && dealerpoint + 10 == 21) // if any of the cards is an ace, find best scenario to win, either ace = 1, or ace = 11
								dealerpoint = 21; // if it is an ace and 1 rest sum of 10 / 10 point card, then win; if ace being 11 points wins, then ace = 11
							system("pause");
							setColor(15);
						} while (dealerpoint <= 17); // dealer draws until theyre over 17 points
					}
				}
				else { // the player's points is already over 21, a bust so they already lose
					setColor(12);
					cout << "The dealer doesn't need to draw Because the player already lost.\n";
				}

				setColor(15);
				if (acefound(dealerhand) && dealerpoint + 10 <= 21) // aces, if it is favorable for ace = 11, then ace = 11
					dealerpoint += 10;
				if (acefound(playerhand) && playerpoint + 10 <= 21)// aces, if it is favorable for ace = 11, then ace = 11
					playerpoint += 10;

				//dealerpoint = 21;
				setColor(12);
				cout << "Dealer's Total points: " << dealerpoint << endl; // updated dealer's points
				setColor(10);
				cout << "Player's Total points: " << playerpoint << endl << endl; // updated dealer's points
				setColor(14);
				cout << "Player's Current Funds: " << player.getmoney() << endl; // tells the current money before the affects of the game outcome
				//win/loose communication
				if (playerpoint > 21) { //playerpint exceeds 21
					setColor(12);
					cout << "You've exceeded 21 points, You loose!\n";
					player.setmoney(player.getmoney() - betdb); // keep all valeus the same but change the money
					turnend = true; // in the case where player exceeds 21, losing but it doesnt end their turn and causes them to play again
				}
				else if (dealerpoint > 21 && playerpoint <= 21) { // dealer exceeds 21 points, but since player always goes first, if theyre still <= 21 as well
					setColor(10);
					cout << "The Dealer exceeded 21 points, You Win!\n";
					if (acefound(playerhand) && playerhand.size() == 2) {// blackjack
						setColor(10);
						cout << "You got a blackjack! Your reward money has been increased by 150%\n";
						betdb = 1.5 * betdb; // bonus 
					}
					turnend = true;
					player.setmoney(player.getmoney() + betdb); // add the win bonus to the player's money
				}
				else if (playerpoint == 21 && playerpoint == dealerpoint) {// both players equal 21
					setColor(11);
					cout << "You've tied with the dealer, You get to play again, free of charge!\n";
					turnend = false;
					system("pause");
					system("cls");

				}
				else if (playerpoint == 21 && dealerpoint != 21) { // the player got exactly 21m while the dealer did not
					setColor(10);
					cout << "You got exactly 21 points while the dealer didn't, You Win!\n";
					turnend = true;
					if (acefound(playerhand) && playerhand.size() == 2) {// blackjack
						setColor(10);
						cout << "You got a blackjack! Your reward money has been increased by 150%\n";
						betdb = 1.5 * betdb; // bonus 
					}
					player.setmoney(player.getmoney() + betdb);// add the win bonus to the player's money
				}
				else if (dealerpoint == 21 && playerpoint != 21) { // dealer got exactly 21 and player did not
					setColor(12);
					cout << "The Dealer Got exactly 21, while you did not, You Loose!\n";
					turnend = true;
					player.setmoney(player.getmoney() - betdb);// add the win bonus to the player's money
				}
				else { // other win cases
					int premainder = 21 - playerpoint; // used to see which person (player or dealer) was closest to 21 in the event that no one gets 21 exactly
					int dremainder = 21 - dealerpoint;

					if (dealerpoint != 21 && playerpoint != 21) { // if no one has 21 points exactly
						if (dremainder < premainder) { // if the player is closer to 21 than player is
							setColor(12);
							cout << "The dealer wins. you loose your bet.\n";
							player.setmoney(player.getmoney() - betdb); //remove the moeny from the player's money
							turnend = true;
						}

						else if (dremainder > premainder) {// if the dealeris closer to 21 than player is
							setColor(10);
							cout << "The player wins. You won your bet.\n";
							if (acefound(playerhand) && playerhand.size() == 2) {// blackjack
								setColor(10);
								cout << "You got a blackjack! Your reward money has been increased by 150%\n";
								betdb = 1.5 * betdb; // bonus 
							}
							player.setmoney(player.getmoney() + betdb);// add the win bonus to the player's money
							turnend = true;
						}
					}
					if (playerpoint <= 21 && playerpoint == dealerpoint) { //both dealer and player tie, but <= 21; replay the game
						setColor(11);
						cout << "You've tied with the dealer, You get to play again, free of charge!\n";
						turnend = false;
						system("pause");
						system("cls");
					}
				}

				if (playerpoint != dealerpoint) { // so long as there is not a tie, tell the outcome and changes of money
					setColor(14);
					cout << "You're money has been displaced by " << betdb << " Gold.\n"; // telling amount lsot or gained
					cout << "Player's new Funds: " << player.getmoney() << endl; // tell player their money now
					system("pause");
					system("cls");
				}

			} while (!turnend); // an entire game of blackjack has been played, where result is nto a tie
		}


		//play again prompt
		setColor(12);
		cout << "Do you want to play again?\n";
		setColor(15);
		cout << "Enter '1' to play BlackJack again or anything else to leave the casino.\n";
		getline(cin, str);
		//str = 1;
		if (str != "1") { // if its not 1, then end the loop
			playagain = false;
			setColor(14);
			cout << "Thank you for Coming to the Casino!\n";
			system("Pause");

		}
		system("cls");
		setColor(15);
	} while (playagain); // loop to play again if the player wants to

}

int main() {
	//defining variables
	string location;
	POKEMON p; //the player's pokemon
	string input;
	trainer player;// creating the variable for the trainer
	srand(time(NULL)); //setting the randomness for the game

	//defining and resetting variables when player wants to restart
	int counter = 0;
	bool gameOver = false;
	p.fullHeal();
	p.setLevel(10); //sets the level to 10 for testing purposes
	int x = 2; int y = 10; // specs of the size of the item bag
	int** board = boardcreate(x, y);
	player.settrainer(1, 0, 10000, board); // adding the specs of a newly minted trainer

	casino(player);

	//for (int i = 0; i < 20; i++)
	//	player.addtobag(i + 1);
		//bag(player, p);

		//int** board2 = creat2d(10, board);
		//display(board2, 6, 10);

	system("pause");
	return 0;
}
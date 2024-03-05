//Jason Zhou & Donald Newandee
//CP2 Final Project
//Lvl 1

//donald: add in trainer characteristics / nature
// level requirement for accessing casino
// add in interaction between pokemon nature and trainer nature
//trainer expirence?
// fix dummy proofing of normal "check bag" during going to locations
//
//
// both: add in ability to use items inside and outside of battle
//
//jason: getting money after battles / fights
//reset pokemon and or trainer to lvl 1 when done
// add in ability to use bag udring a battle

using namespace std;

//Libraries
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include<math.h>

void setColor(int color)// for changing color outside function
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
void displayBag(int** arr2d, int x, int y) { //x left to right, y up and down
	for (int row = 0; row < x; row++) { //prints the row
		for (int col = 0; col < y; col++) { //prints the column
			cout << arr2d[row][col] << "\t";
			if ((row * 10 + col + 1) % x == 0) // end the line to end the row; continue next row on next line
				cout << endl;
		}
	}
	cout << endl;
	//item list
	//outputs the item IDs for each item
	cout << "Item List    (Item ID)\n";
	cout << "Small Potion   (ID: 1)\n";
	cout << "Rare Candy     (ID: 2)\n";
	cout << "Dumbbell       (ID: 3)\n";
	cout << "Teddy Bear     (ID: 4)\n";
	cout << "Brass Knuckles (ID: 5)\n";
	cout << "Fabreeze       (ID: 6)\n";
	cout << "Daisy          (ID: 7)\n";
	cout << "Medium Potion  (ID: 8)\n";
	cout << "Large Potion   (ID: 9)\n\n";
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
	//sets the current hp
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
		if (traitNumber == 0) //if 0, then their trait is strong-willed
			trait = "strong-willed";
		else if (traitNumber == 1) //if 1, then their trait is innocent
			trait = "innocent";
		else if (traitNumber == 2) //if 2, then their trait is aggressive
			trait = "aggressive";
		else if (traitNumber == 3) //if 3, then their trait is care-free
			trait = "care-free";
		else if (traitNumber == 4) //if 4, then their trait is care-free
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
	void changeTrait(string newTrait) { trait = newTrait; }//allows the user to change the trait of their pokemon

	void resetSubHP() //resets the hp of the alibi
	{
		//sets the sub hp to 0
		currentSubHP = 0;
		subHP = 0;
	}
	void fullHeal() { currentHP = hp; } //full heals the pokemon (purely for testing purposes)
	void setEXP(int newEXP) { currentEXP = newEXP; } //sets the EXP for the pokemon(purely for testing purposes)

	void randomizeStats(POKEMON p) //used for the scaling of enemies
	{
		if (p.level == 1) //if the pokemons level is 1, then just make the enemy have the same stats
			setUp();
		//50% chance to be 1 level lower than the player's pokemon
		else if (rand() % 2 == 0)
		{
			//sets up stats for a pokemon that is one level lower than the player's pokemon
			level = p.level - 1;
			hp = 10 * p.level - 10 - (rand() % 3);
			currentHP = hp;
			att = 5 * p.level - 5 - (rand() % 3);
			def = 5 * p.level - 5 - (rand() % 3);
			agi = 5 * p.level - 5 - (rand() % 3);
		}
		else //50% chance to be 1 level higher than the player's pokemon
		{
			//sets up stats for a pokemon that is one level higher than the player's pokemon
			level = p.level + 1;
			hp = 10 * p.level + (rand() % 5);
			currentHP = hp;
			att = 5 * p.level + (rand() % 5);
			def = 5 * p.level + (rand() % 5);
			agi = 5 * p.level + (rand() % 5);
		}
	}

	//changes the characteristics of the pokemon after they have leveled up
	void setLevel(int newLevel) { level = newLevel; } //this is just to cheat to test things
	void gainEXP(int eLevel) { currentEXP = currentEXP + 2 * eLevel; } //adds exp to the pokemon's exp
	void levelUp() //this function levels up the pokemon
	{
		//first increase the stats by a base amount, modify later
		level++;
		att = att + 5;
		def = def + 5;
		agi = agi + 5;
		hp = hp + 10;
		currentEXP = 0;
		totalEXP = pow(level, 3) + 10;
		//modifies the stats differently depending on the pokemon's nature
		if (trait == "strong-willed") //if strong-willed, add more points to hp and less to agility
		{
			hp = hp + 5;
			agi = agi - 2;
		}
		else if (trait == "innocent") //if innocent, add more points to defense and less to attack
		{
			att = att - 2;
			def = def + 3;
		}
		else if (trait == "aggressive") //if aggressive, add more points to defense and less to defense
		{
			att = att + 3;
			def = def - 2;
		}
		else if (trait == "care-free") //if care-free, add more points to agility to and less to defense
		{
			agi = agi + 3;
			def = def - 2;
		}
		else if (trait == "cheerful") //if cheerful, increase all stats by a minimum amount
		{
			//This trait is an all-rounder
			//this trait also fills 20% of your new EXP bar upon level up
			att++;
			def++;
			agi++;
			hp = hp + 3;
			if (level != 10) //only give EXP if the level is not 10(b/c 10 is the max)
				currentEXP = totalEXP / 5;
		}


	} //makes the pokemon level up
	//void changeTrait(string newTrait) { trait = newTrait; }
	void learnMove(string newMove, int spot) { moveSet[spot - 1] = newMove; }
	void createMovePool() //creates the move pool for the player's pokemon
	{
		//adding the moves to the move pool
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
	}

	void stare() { def = def - ceil(def * 0.30); }//decreases the enemy's current defense by about 30%

	void displayStats() //displays all stats of the pokemon
	{
		//displaying the stats of the pokemon
		cout << "Pokemon Stats:\n\n";
		cout << "Level: " << level << endl;
		cout << "Health Points: " << currentHP << "/" << hp << endl;
		cout << "Attack: " << att << endl;
		cout << "Defense: " << def << endl;
		cout << "Agility: " << agi << endl;
		cout << "Trait: " << trait << endl;
		cout << "EXP: " << currentEXP << "/" << totalEXP << endl << endl;

		//gives a description of the moves
		cout << "Move Descriptions(Current Moves): \n\n";
		for (int i = 0; i < moveSet.size(); i++)
		{
			if (moveSet[i] != "None") //for any move that is not 'none', output a description
			{
				//gives a description of each move if the player has it
				if (moveSet[i] == "Stare") //describes stare
					cout << "Stare: Reduces The Enemy's Defense by 30%. Stacks.\n";
				else if (moveSet[i] == "Slap")//describes slap
					cout << "Slap: Slaps The Enemy Across The Face. Power 20\n";
				else if (moveSet[i] == "Concentrate")//describes concentrate
					cout << "Concentrate: The Next Attack Will Deal 2.5 Times More Damage. Does Not Stack.\n";
				else if (moveSet[i] == "Poker Face")//describes poker face
					cout << "Poker Face: Attack, Defense, Agility, All Decreased by 10%. Stacks.\n";
				else if (moveSet[i] == "Kick")//describes kick
					cout << "Kick: Enemy takes a kick to their no-no square. Power 70\n";
				else if (moveSet[i] == "Serious Punch")//describes serious
					cout << "Serious Punch: Punches the In The Face. Power 100\n";
				else if (moveSet[i] == "Perfect Alibi")//describes punch
					cout << "Perfect Alibi: Create A Clone Of Your Pokemon That Will Temporarily Tkae Hits For You\n\n";

			}

		}

	}

	void takeDamage(int damage) //makes the pokemon take damage
	{
		if (currentHP - damage < 0) //if they go below 0 hp, then just set their hp to 0
			currentHP = 0;
		else //makes the pokemon take damage
			currentHP = currentHP - damage;
	}
	void damageAlibi(int damage) //makes the alibi take damage
	{
		if (currentSubHP - damage < 0) //if they go below 0 hp, then just set their hp to 0
			currentSubHP = 0;
		else //makes the alibi take damage
			currentSubHP = currentSubHP - damage;//damages the alibi
	}
};
void checkForLevelUp(POKEMON& p)
{
	//defnining variables
	string input;
	bool error = false;
	int spot;

	if (p.getCurrentEXP() >= p.getTotalEXP()) //if the current exp is equal to or over the needed exp to level, then level up
	{
		p.levelUp(); //level up the pokemon
		system("CLS");
		cout << "Congratulations! Your Pokemon Just Leveled Up!\n\n";
		system("Pause");

		cout << endl;

		if (p.getLevel() == 2) //if the pokemon reaches level 2, then tell the player that the PokeMart has been unlocked
		{
			cout << "You Have Unlocked The PokeMart!\n\n";
			system("Pause");
		}
			
		else if (p.getLevel() == 4) //if the pokemon reaches level 3, then tell the player that the Casino has been unlocked
		{
			cout << "You Have Unlocked The Casino!\n\n";
			system("Pause");
		}
			
		else if (p.getLevel() == 5) //if the pokemon reaches level 5, then tell the player that the Fight Club has been unlocked
		{
			cout << "You Have Unlocked The Fight Club!\n\n";
			system("Pause");
		}
			
		else if (p.getLevel() == 8) //if the pokemon reaches level 8, then tell the player that the Gym has been unlocked
		{
			cout << "You Have Unlocked The Gym!\n";
			cout << "You Have Now Earned The Right To Challenge The Gym Leader!\n\n";
			system("Pause");
		}

		
		system("CLS");

		if (p.getLevel() % 2 == 0) //if the pokemon's level is an even number, let them know that they can learn a new move
		{
			cout << "Your Pokemon Can Learn The Move . . . " << p.getMoveFromPool(p.getSizePool() - 1) << "!\n\n";
			cout << "~~ Move Description ~~\n";
			//gives a move description of the move that could be learned
			if (p.getMoveFromPool(p.getSizePool() - 1) == "Concentrate") //describes concentrate
				cout << "Concentrate: Your Next Attack Will Deal 2.5 Times More Damage. Does Not Stack\n\n";
			else if (p.getMoveFromPool(p.getSizePool() - 1) == "Kick")//describes kick
				cout << "Kick: Enemy takes a kick to their no-no square. Power 70\n\n";
			else if (p.getMoveFromPool(p.getSizePool() - 1) == "Poker Face")//describes poker face
				cout << "Poker Face: Attack, Defense, Agility, All Decreased by 10%. Stacks.\n\n";
			else if (p.getMoveFromPool(p.getSizePool() - 1) == "Serious Punch") //describes serious punch
				cout << "Serious Punch: Punches the In The Face. Power 100\n\n";
			else if (p.getMoveFromPool(p.getSizePool() - 1) == "Perfect Alibi")//describes perfect alibi
				cout << "Perfect Alibi: Create A Clone Of Your Pokemon That Will Temporarily Take Hits For You\n\n";

			//displays the current move set to the player
			cout << "Current Move Set: \n\n";
			cout << "1: " << p.getMove(0) << "		2: " << p.getMove(1) << endl;
			cout << "3: " << p.getMove(2) << "		4: " << p.getMove(3) << endl << endl;

			cout << "Would You Like Your Pokemon To Learn " << p.getMoveFromPool(p.getSizePool() - 1) << "(1 = Yes, Anything Else = No): "; //prompt the player
			getline(cin, input);

			if (input == "1") //if inputted, then let the player learn a new move
			{
				do //repeat as long as the user makes an error while inputting
				{
					system("CLS");
					//displays the current move set to the player
					cout << "Current Move Set: \n\n";
					cout << "1: " << p.getMove(0) << "		2: " << p.getMove(1) << endl;
					cout << "3: " << p.getMove(2) << "		4: " << p.getMove(3) << endl << endl;

					if (error) //if they made an error, let them know
					{
						setColor(12);
						cout << "That is an Invalid Response! Please Input A Valid Response!\n\n";
						error = false;
						setColor(15);
					}

					//prompt them for a resposne
					cout << "Which Move Slot Would You Like To Place It In(1, 2, 3, or 4)\n(Choosing a Slot That Has An Existing Move Will Replace It): ";
					getline(cin, input);

					if (input != "1" && input != "2" && input != "3" && input != "4") //if it is not 1, 2, 3, or 4, then trigger an error
						error = true;
					else
					{//if there is no error, have them learn the move
						spot = stoi(input);
						p.learnMove(p.getMoveFromPool(p.getSizePool() - 1), spot);
						p.removeFromPool(); //removes from the move pool
					}

				} while (error); //loop as long as there is an error
			}
			else //if they do not input '1', then tell them the move was not learned
			{
				system("CLS");
				cout << "The Move Was Not Learned\n\n"; //tells them the move was not learned
				system("Pause");
			}
		}
		
	}
}
class trainer {
private:
	//int x; int y; // specs of the item bag size
	int nature; int exp; int rank = 1; int battles = 0; int money; int** itembag; bool win = false;
public:
	//getter functions
	int getnature() { return nature; }
	int getexpirence() { return exp; }
	int getmoney() { return money; } // wasnt added in originally
	int** getitembag() { return itembag; }
	int getRank() { return rank; }
	bool getWin() { return win; } //returns if 'win' is true or false
	//setterfunctions
	void settrainer(int n, int e, int m, int** t) { nature = n; exp = e; money = m; itembag = t; }
	void setnature(int n) { nature = n; }
	void setexpirence(int e) { exp = e; }
	void setmoney(int m) { money = m; }
	void setexpirence(int** t) { itembag = t; }
	void rankUP() { rank++; } //increases the players rank
	void increaseBattles() { battles++; }
	void beatGym() { win = true; } //if the player beats the gym leader, switch the variable to true

	//checks if the player is able to rank up
	void checkForRankUP()
	{
		if (battles % 10 == 0 && battles != 0) //for every 10 battles, the player's rank will increase by 1
		{
			rankUP(); //rank the player up
			battles = 0;
			system("CLS");
			//congratulate the plauyer
			cout << "Congratulations!\n";
			cout << "Your Player Rank Has Increased!\n\n";
			cout << "Your Player Rank is Now " << rank << "!\n\n"; //display their rank
			system("System");
		}
	}

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
		else { //give them an error message
			cout << "itme not found in bag / ERROR\n";
			system("pause");
			return false; 
		}
	}
	bool isiteminbag(int item, int x, int y) { // searches for an item to see if it is in the bag
		for (int row = 0; row < x; row++) { //scans rows
			for (int col = 0; col < y; col++) { //scan columns
				if (itembag[row][col] == item)
					return true;
			}
		}
		return false;
	}
	void removeitem(int item, int x, int y) { // removes an item from the bag
		for (int row = 0; row < x; row++) { //scans rows
			for (int col = 0; col < y; col++) { //scans columns
				if (itembag[row][col] == item) { //if the item is present, remove it and end the loop
					itembag[row][col] = 0; // remove the item
					row = x; // ends the loop
					col = y;
				}
			}
		}

	}

	int earnMoney(POKEMON e) //calculates and gives a certain amount of money to the player after a fight
	{
		int gold = pow(e.getLevel() * 2, 2);
		return gold;
	}

	void itemaffect(POKEMON& p, int item) { // adds the affect of the item to the pokemon e.g. heal for 20 hp, boost attack by 10 points, etc.
		//change variable name to the variable of the 
		if (item == 1) {// small potion
			if (p.getCurrentHP() + 20 > p.getTotalHP()) //if the health goes over the max, set it back to the max
				p.fullHeal();
			else //if it does not go over, then just heal for the specified amount
				p.setCurrentHP(p.getCurrentHP() + 20);
			cout << "pokemon has been healed.\n"; //let the player know
			system("pause");
			system("CLS");
		}
		else if (item == 2) // rare candy
		{
			p.setEXP(p.getTotalEXP()); //sets the EXP to the total exp so that the level up can occur
			checkForLevelUp(p); //checks for the level up
		}
			
		else if (item == 3) //dumbbell, changes the trait of the pokemon to strong-willed
			p.changeTrait("strong-willed");
		else if (item == 4) //teddy bear, changes the trait of the pokemon to innocent
			p.changeTrait("innocent");
		else if (item == 5) //brass-knuckles, changes the trait of the pokemon to aggressive
			p.changeTrait("aggressive");
		else if (item == 6) //fabreeze, changes the trait of the pokemon to care-free
			p.changeTrait("care-free");
		else if (item == 7) //daisy, changes the trait of the pokemon to cheerful
			p.changeTrait("cheerful");
		else if (item == 8) {// medium potion potion
			if (p.getCurrentHP() + 30 > p.getTotalHP()) //if the health goes over the max, set it back to the max
				p.fullHeal();
			else //if it does not go over, then just heal for the specified amount
				p.setCurrentHP(p.getCurrentHP() + 30);
			cout << "pokemon has been healed.\n";
			system("pause");
			system("CLS");
		}
		else if (item == 9) {// large potion potion
			if (p.getCurrentHP() + 40 > p.getTotalHP()) //if the health goes over the max, set it back to the max
				p.fullHeal();
			else //if it does not go over, then just heal for the specified amount
				p.setCurrentHP(p.getCurrentHP() + 40);
			cout << "pokemon has been healed.\n"; //let the player know
			system("pause");
			system("CLS");
		}
		else { //if there was no input that matched the ones above, tell the user there was an input error
			cout << "Invalid item use\n";
			system("pause");
			system("CLS");
		}
	}
};
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
					//if it is not 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, and ., then return false
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
void bag(trainer player, POKEMON& p)
{
	//defining variables
	string str; int item = 0;
	//do {
	do {
		system("CLS");
		displayBag(player.getitembag(), 2, 10); // board on console; shows the items in the bag
		cout << "What item do you want to use?\n";
		cout << "Enter '0' to stop looking at your bag.\n";

		getline(cin, str); // gets the int value that is associated with an item

		if (!allnumbers(str) || str.length() == 0) { //if the input is not valid, give them an error message
			cout << "That is not a numerical value. Please enter a number.\n";
			system("pause");
			system("cls");
		}
		else //else convert the string into an integer
			item = stoi(str); // converts the string to int
			//cout << str.length() << endl;
		if (!player.isiteminbag(item, 2, 10)) {
			cout << "That item can not be found inside the bag.\n";
			system("pause");
			system("cls");
		}
	} while (!allnumbers(str) || str.length() == 0 || !player.isiteminbag(item, 2, 10)); //keep looping as long as there is an input error



	if (item != 0 && player.isiteminbag(item, 2, 10)) //if the item value is not 0 and is in the bag, use it
		player.useitem(p, item); // use the item and modify the pokemon
	system("cls");
	//} while (item != 0 || !player.isiteminbag(item, 2, 10));
}

void pokemonSetUp(POKEMON& p) //creates everything for the initial pokemon
{
	//sets up the stats for the pokemon
	p.setUp();
	p.createMovePool(); //creates the move pool
}
void motherAdvice(int& counter) //contains the advice that mother can give
{
	//cycles through the advice that mother can give based on how many times you have asked for advice
	//Basically, gives different advice everytime you ask, until it loops back
	if (counter == 8) //if the counter goes to 7, then reset it back to 0
		counter = 0;

	if (counter == 0) //tells the player what sleeping does
		cout << "Sleeping At Home Will Restore Your Pokemon's HP.\n\n";
	else if (counter == 1) //tell the player about a pokemon's trait
	{
		cout << "A pokemon's stats can be affected differently by its trait.\n";
		cout << "For example, the trait can raise its attack while lowering its defense.\n\n";
	}
	else if (counter == 2) //tells the player about a player's rank
	{
		cout << "Your rank is basically your social status.\n";
		cout << "You may be able to do things you were not able to do before with a higher rank.\n\n";
	}
	else if (counter == 3) //tells the player about new moves
		cout << "Your Pokemon can learn a new move every other level.\n\n";
	else if (counter == 4) //tells the player about the PokeMart
		cout << "You can go to the PokeMart to buy items like potions.\n\n";
	else if (counter == 5) //tells the player about the gym leader
		cout << "You can challenge the gym leader once your pokemon is level 7 or above.\n\n";
	else if (counter == 6) //tells the player about the fight club
	{
		cout << "I hear there's a fight club you can go to where you can battle strong trainors.\n";
		cout << "If you win a fight there, you earn a lot of EXP and money.\n\n";
	}
	else if (counter == 7) //tells the player about the casino
	{
		cout << "Going to a casino is a way to quickly multiply the amount of money you have.\n";
		cout << "That being said, it is also a place where you can quickly lose money.\n";
		cout << "However, it is only available when your pokemon is a higher level.\n";
		cout << "As your mother, I do not want to see you at a casino!\n\n";
	}

	counter++; //increase the counter

}
string playerInput(string& input, POKEMON p) //sets their location to what they input
{
	system("CLS");
	for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
		if (input[i] != ' ') //if the index is not a space, then capitalize it
			input[i] = toupper(input[i]);

	if (input == "HOME") //if they typed "HOME", then go home
		return "HOME";
	else if (input == "TRAINING GROUNDS")//if they typed "TRAINING GROUNDS", then go to the training grounds
		return "TRAINING GROUNDS";
	else if (input == "CASINO" && p.getLevel() > 3) //if they typed "CASINO", then go to the casino
		return "CASINO";
	else if (input == "POKEMART" && p.getLevel() > 1) //if they typed "POKEMART", then go to the PokeMart
		return "POKEMART";
	else if (input == "FIGHT CLUB" && p.getLevel() > 4)//if they typed "FIGHT CLUB", then go to the fight club 
		return "FIGHT CLUB";
	else if (input == "GYM" && p.getLevel() > 6)//if they typed "GYM", then go to the gym
		return "GYM";
	else if (input == "CHECK BAG") //sends the player to the bag screen
		return "CHECK BAG";
	else if (input == "DISPLAY STATS") //sends the player to the stats screen
		return "DISPLAY STATS";
	else if (input == "TUTORIAL")
		return "TUTORIAL";
	else //if it returns invalid, that means there was an invalid response
		return "INVALID";
}
bool playAgain() //prompts the player if they want to play again, then returns true or false
{
	system("CLS");
	string tryAgain;
	cout << "Congratulations!\nAs A Result of Beating the Gym Leader, You've Beaten The Game!\n\n"; //congratulate the player
	cout << "Would You Like To Play Again Again(1 = Yes, Anything Else = No): "; //prompt player
	cin >> tryAgain;
	cin.ignore();
	if (tryAgain == "1") //if input is equal to 1, return true
		return true;
	else //if it not equal to 1, return false
		return false;
}
void home(POKEMON& p) //simulates the home location for the game
{
	int counter = 0;
	system("CLS");
	//defining variables
	bool stayhome = true;
	do {
		string input;
		bool error = false;
		do //loop as long the player wants to stay home
		{
			if (error) //if there was an error, let the player know and set 'error' back to false
			{
				cout << "Your Response Was Invalid! Please Input a Valid Response!\n\n";
				cout << "Please enter the following inputs:\n";
				cout << "TALK TO MOM\n";
				cout << "SLEEP\n";
				cout << "LEAVE\n\n";
				error = false; //switch back to false
				system("pause");
				system("cls");
			}

			//tell the player they are at the house
			cout << "You Are At Your House.\n";
			cout << "Would You Like To 'Talk To Mom', 'Sleep', or 'Leave': ";
			getline(cin, input);

			for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
				input[i] = toupper(input[i]);

			if (input != "TALK TO MOM" && input != "SLEEP" && input != "LEAVE") { // none of the allowed inputs, so run again
				error = true;
			}

		} while (error); //as long as there is an error, keep looping the inside code

		if (input == "TALK TO MOM") { //if they talk to mom, give them advice
			motherAdvice(counter);
			system("pause");
			system("cls");
		}
		else if (input == "SLEEP") { //if they sleep, restore the pokemon's hp
			cout << "You and your pokemon Feel Very well rested.\n";
			cout << "Your Pokemon have been restored to full health!\n";
			//cout << p.getTotalHP() << endl;
			p.fullHeal();
			//cout << p.getCurrentHP() << endl;
			system("pause");
			system("cls");
		}
		else { //if (input == "LEAVE") {
			stayhome = false;
		}
	} while (stayhome); //as long as the player is at home and doesnt leave, loop the logic
}
void healthBar(double currentHealth, double totalHealth, bool alibi) //displays the health bar of a pokemon
{
	double percentageHealth = 1.0 * currentHealth / totalHealth; //calculates the percentage of health remaining
	double healthBar = 20; //this variable indicates how much current health the pokemon has remaining

	//NOTE: if 'alibi' is true, it will create the alibi's health bar instead of the pokemons
	if (!alibi) //if there is no alibi, set the color to be green
		setColor(10);
	else //if there is an alibi, set the color to be yellow
		setColor(14);

	healthBar = ceil(healthBar * percentageHealth); //calculates the health bar
	for (int i = 0; i < 20; i++) //creates the health bar with the correct proportions of health
	{
		if (i > healthBar - 1) //if 'i' goes over the 'health bar', turn the color to red
			setColor(12);
		else
			if (!alibi) //if there is no alibi, turn the color to green
				setColor(10);
			else //if there is an alibi, turn the color to yellow
				setColor(14);
		cout << "/";
	}

	setColor(15);
}
void experienceBar(float currentEXP, float totalEXPRequired) //displays the EXP bar for the pokemon
{
	//defining variables
	float percentageEXP = currentEXP / totalEXPRequired;
	float expBar = 20;

	expBar = ceil(expBar * percentageEXP); //calculates how many bars should be filled

	//sets the color to blue
	setColor(11);
	for (int i = 0; i < 20; i++) //prints the exp bar
	{
		if (i > expBar - 1) //if the 'i' exceeds the exp bar, then turn the color to white
			setColor(15);
		cout << "=";

	}

	cout << endl;
	setColor(15);
}
void displayBattle(POKEMON p, POKEMON e) //displays the battle screen for the player
{
	//displays the screen
	system("CLS");
	cout << "Screen:\n\n";
	//displays the enemy health and level
	cout << "Enemy Level: " << e.getLevel() << endl;
	cout << "Enemy HP(" << e.getCurrentHP() << "/" << e.getTotalHP() << ") >> ";
	healthBar(e.getCurrentHP(), e.getTotalHP(), false);
	cout << endl << endl;
	//displays the "pokemon"
	setColor(207);
	cout << "		E\n\n";
	setColor(252);
	cout << "		Q\n\n";
	setColor(15);
	cout << "Your Level: " << p.getLevel() << endl; //displays level

	if (p.getSubCurrentHP() > 0) //only run if the alibi has health
	{
		cout << "Alibi HP(" << p.getSubCurrentHP() << "/" << p.getSubTotalHP() << ") >> ";
		healthBar(p.getSubCurrentHP(), p.getSubTotalHP(), true);
		cout << endl;
	}

	cout << "Your HP(" << p.getCurrentHP() << "/" << p.getTotalHP() << ") >> "; //displays health
	healthBar(p.getCurrentHP(), p.getTotalHP(), false); //displays the health bar
	cout << endl << "EXP   	       >> "; //displays the EXP
	experienceBar(p.getCurrentEXP(), p.getTotalEXP()); //displays the EXP bar
	cout << endl << endl;
	//displays the pokemon's moveset
	cout << "Moves: \n\n";
	cout << "1: " << p.getMove(0) << "		2: " << p.getMove(1) << endl;
	cout << "3: " << p.getMove(2) << "		4: " << p.getMove(3) << endl;

	//sets the color to red
	setColor(9);
	cout << endl << "RUN";
	//sets the color to purple
	setColor(5);
	cout << "		BAG";
	cout << endl;
	setColor(15);
	cout << endl;
}
void simulateBattle(POKEMON& AttPok, POKEMON& DefPok, string& input, bool& concentrate)
{
	//defining variables
	int spot = -1;
	int power = 0;
	float modifier = 1;
	float damage = 0;

	if (concentrate && input != "Enemy") //if concentrate is true, then turn the modifier to be 2.5
		modifier = 2.5;

	if (input == "1" || input == "2" || input == "3" || input == "4") //if the player inputs a 1,2,3, or 4, then convert into an integer
		spot = stoi(input);
	else if (input == "Enemy") //if the input is 'Enemy' then set the power to their level * 10(enemy is attacking)
		power = AttPok.getLevel() * 10;

	/*cout << endl << AttPok.getMove(spot - 1) << endl;
	system("Pause");*/
	if (spot != -1) //only do this if the player is attacking
	{
		if (AttPok.getMove(spot - 1) == "Slap") //if it is slap, set the pwoer to 40
		{
			power = 40;
			//system("Pause");
		}

		else if (AttPok.getMove(spot - 1) == "Kick") //if they use kick, set the power to 70
			power = 70;
		else if (AttPok.getMove(spot - 1) == "Serious Punch") //if they use Serious Punch, set the power to 100
			power = 100;
		else if (AttPok.getMove(spot - 1) == "Concentrate") //if they use Serious Punch, set the power to 100
			concentrate = true;
		else if (AttPok.getMove(spot - 1) == "Poker Face") //if they use Serious Punch, set the power to 100
		{
			DefPok.pokerFace();
			cout << endl << "The Enemy Pokemon finds Your Facial Expressions Confusing(ALL STATS DOWN FOR ENEMY).\n\n";
		}
		else if (AttPok.getMove(spot - 1) == "Perfect Alibi") //if they use Serious Punch, set the power to 100
		{
			AttPok.perfectAlibi();
			cout << endl << "Your Pokemon Sets Up A Dummy!\n\n";
		}
		else if (AttPok.getMove(spot - 1) == "Stare") //if they use Serious Punch, set the power to 100
		{
			DefPok.stare();
			cout << endl << "Staring At The Enemy Pokemon makes Them Uncomfortable(DEFENSE DOWN FOR ENEMY).\n\n";
		}

	}

	if (power > 0) //only calculate damage if the power of the move is greater than 0
		damage = (ceil((((((((2 * 1.0 * AttPok.getLevel())) / (5 * 1.0)) + 2) * power * 1.0 * ((1.0 * AttPok.getAtt()) / (1.0 * DefPok.getDef()))) / 50 * 1.0) + 2) * modifier)); //this is the actual formula that pokemon uses to calculate damage
	//dont ask me why its so complicated cuz tbh idk

	if (damage > 0) //if the player did damage, let them know how much damage they did
	{
		if (input == "Enemy")//if the enemy is attacking, display this message
			cout << endl << "The Attack Dealt . . . " << damage << " Damage!\n"; //tells the player how much damage they dealt
		else //else display how much damage the player did
			cout << endl << "Your Attack Dealt . . . " << damage << " Damage!\n"; //tells the player how much damage they dealt


		if (DefPok.getSubCurrentHP() > 0) //as long as the alibi has hp, deal damage to it
			DefPok.damageAlibi(damage);
		else //else deal damage to the defending pokemon
		{
			DefPok.takeDamage(damage); //has the defending pokemon take damage
			if (DefPok.getSubCurrentHP() <= 0) //if the alibi is dead, reset the stats to 0
				DefPok.resetSubHP();
		}

		if (input != "Enemy") //if it is not the enemies turn(player's turn), switch concentrate to false
			concentrate = false; //switches concentrate off
	}

	if (concentrate && input != "Enemy") //lets the player know that concentrate is in effect
		cout << endl << "Your Next Attack Will Be 2.5 Times Stronger!\n\n";
}

bool spotCheck(int playerLocation, string input) //checks if the player is able to move to that spot(prevents them from moving off the board in the trainig grounds)
{//if the function returns true, the player is able to move to that spot, if false, that spot is invalid(does not exist)

	if (input == "LEFT" && playerLocation == 0) //if they are at the very left side of the board, return false
		return false;
	else if (input == "RIGHT" && playerLocation == 24) //if they are at the very right of the board, return false
		return false;
	else if (input == "DOWN" && playerLocation >= 20) //if they are at the very bottom of the board, return false
		return false;
	else if (input == "UP" && playerLocation <= 4) //if they are at the top of the board, return false
		return false;
	else //if there is no error, return true(it is safe to move to this spot without breaking the game)
		return true;
}
void trainingGrounds(POKEMON& p, trainer& player) //simulates the training grounds for the game
{
	//defining variables for the function
	POKEMON e;
	bool startBattle = false;
	vector<int> spots;
	string enemy = "Enemy";
	int levelRange = 2;
	bool leave = false;
	bool concentrate = false;
	bool error = false;
	bool battleError = false;
	bool spotError = false;
	int response = 0;
	bool inputError = false;

	for (int z = 0; z < 25; z++) //formats the spots for the training grounds
		spots.push_back(0);

	//keep in mind when the training ground is generated, the location of the player is random
	int playerLocation = rand() % 25; //determines the location of the player
	spots[playerLocation] = 1;

	do //loop the training ground logic until the player decides to leave
	{
		checkForLevelUp(p); //check for a level up
		player.checkForRankUP(); //check for a rank up
		//p.fullHeal();
		startBattle = false;
		
		system("CLS");
		//let the player know he is at the training grounds
		cout << "You Are at The Training Grounds!\n";
		cout << "You Can Train Your Pokemon In The Wild Here!\n\n";

		setColor(10);
		int count = 0;

		//creates the board for the training grounds
		for (int i = 0; i < 5; i++) //creates the rows
		{
			for (int j = 0; j < 5; j++) //creates the columns
			{
				if (spots[count] == 0) //if the index contains a 0, then put a #(tall grass)
					cout << " #";
				else //if it does not contain a 0, then put a O(represents the player)
				{
					setColor(12);
					cout << " O";
					setColor(10);
				}
				count++; //increases the count for every interation
			}
			cout << endl;
		}

		cout << endl;
		setColor(15);

		if (error) //if there is an error, let the player know
		{
			setColor(12);
			cout << "That was an Invalid Input! Please Input A Valid Response!\n\n";
			error = false; //switches it back to false
			setColor(15);
		}


		if (spotError) //if there is an error with a spot, let the player know
		{
			setColor(12);
			cout << "You Cannot Move Off The Board! Please Input A Valid Response!\n\n";
			spotError = false;
			setColor(15);
		}


		string input;
		cout << "What Would You Like To Do(Left, Right, Up, Down, Leave): "; //prompts the user
		getline(cin, input);

		for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
			if (input[i] != ' ') //if the index is not a space, then capitalize it
				input[i] = toupper(input[i]);

		//takes user input from the player that tells the program how to move the player
		if (input == "LEFT") //moves the player left on the board
		{
			if (spotCheck(playerLocation, input)) //if spotCheck is true, then proceed as normal
			{
				spots[playerLocation] = 0;
				playerLocation = playerLocation - 1;
				spots[playerLocation] = 1;
			}
			else //if false, switch 'spotError' to true
				spotError = true;

		}
		else if (input == "RIGHT") //moves the player right on the board
		{
			if (spotCheck(playerLocation, input)) //if spotCheck is true, then proceed as normal
			{
				spots[playerLocation] = 0;
				playerLocation = playerLocation + 1;
				spots[playerLocation] = 1;
			}
			else //if false, switch 'spotError' to true
				spotError = true;
		}
		else if (input == "UP") //moves the player up on the board
		{
			if (spotCheck(playerLocation, input)) //if spotCheck is true, then proceed as normal
			{
				spots[playerLocation] = 0;
				playerLocation = playerLocation - 5;
				spots[playerLocation] = 1;
			}
			else //if false, switch 'spotError' to true
				spotError = true;

		}
		else if (input == "DOWN") //moves the player down on the board
		{
			if (spotCheck(playerLocation, input)) //if spotCheck is true, then proceed as normal
			{
				spots[playerLocation] = 0;
				playerLocation = playerLocation + 5;
				spots[playerLocation] = 1;
			}
			else //if false, switch 'spotError' to true
				spotError = true;
		}
		else if (input == "LEAVE") //makes the player leave the training grounds
			leave = true;
		else //if none of the above were satisfied, then switch it to true(there is an error)
			error = true;

		if (rand() % 3 == 1 && !leave && !spotError && !error) //has a 33% chance to encounter a wild pokemon, if they role a 1, then initiate a fight
		{
			//e.setStats(10, 10, 10, 10, 10); //int newLevel, int newHP, int newAtt, int newDef, int newAgi
			e.randomizeStats(p);
			startBattle = true;
			//displayBattle(p, e);
		}
		while (startBattle) //loops the battle until one side wins/runs away(running away not implemented yet)
		{
			do
			{
				displayBattle(p, e); //displays the battle screen

				if (battleError)//if there is a battle error, then let the player know
				{
					setColor(12);
					cout << "That Was Not A Valid Input! Please Input A Move or BAG or RUN!\n\n";
					setColor(15);
					battleError = false;
				}

				if (inputError) //if they choose None, let them know that they cannot
				{
					setColor(12);
					cout << "You Cannot Choose A Move Slot That Has Nothing In It!\n";
					cout << "Please Input A Valid Response!\n\n";
					setColor(15);
					inputError = false;
				}

				cout << "What Would You Like To Do(Input A Move or BAG or RUN): "; //prompt the player for a move
				getline(cin, input);

				if (input == "1" || input == "2" || input == "3" || input == "4")
				{
					response = stoi(input);
					if (p.getMove(response - 1) == "None")
						inputError = true;
				}
			} while (inputError); //if they choose 'none' as a move, raise an error and loop back
			

			for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
				if (input[i] != ' ') //if the index is not a space, then capitalize it
					input[i] = toupper(input[i]);

			if (input == "1" || input == "2" || input == "3" || input == "4")
			{
				if (p.getAgi() >= e.getAgi()) //if your pokemon has a higher agility stat, then it will attack first
				{
					//your pokemon attack
					simulateBattle(p, e, input, concentrate); //simulates the battle and has the pokemon take damage

					//enemy attack
					system("Pause");
					displayBattle(p, e);
					if (e.getCurrentHP() > 0) //only has the enemy attack if there health is above 0
					{
						cout << endl << "The enemy pokemon used Smack!\n";
						simulateBattle(e, p, enemy, concentrate);
					}

				}
				else if ((p.getAgi() < e.getAgi())) //if the enemy has a higher agility stat, then it will attack first
				{
					//enemy attack
					cout << endl << "The enemy pokemon used Smack!\n";

					simulateBattle(e, p, enemy, concentrate);
					system("Pause");
					displayBattle(p, e);

					//your pokemon attack
					if (p.getCurrentHP() > 0) //only has the player attack if the pokemon has above 0 HP
						simulateBattle(p, e, input, concentrate); //simulates the battle and has the pokemon take damage
				}

				system("Pause");
				displayBattle(p, e); //updates the screen


				if (e.getCurrentHP() <= 0) //if the enemy faints, then break out of the loop
				{
					if (p.getLevel() != 10)
					{
						p.gainEXP(e.getLevel()); //gives the pokemon the earned EXP
						cout << endl << "Your Pokemon Gained " << e.getLevel() * 2 << " Experience!\n";
					}

					p.resetSubHP(); //resets the alibi
					cout << "You Earned " << player.earnMoney(e) << " Gold From the Fight!\n\n";
					player.setmoney(player.getmoney() + player.earnMoney(e)); //adds the money to the players account
					player.increaseBattles();
					concentrate = false;
					system("Pause");
					break;
				}
				else if (p.getCurrentHP() <= 0) //if your pokemon faints, thats GAME OVER
				{
					system("CLS");
					cout << "Your Pokemon Has Fainted!\n";
					cout << "Your Pokemon's HP will be restored to full HP\n\n";
					system("Pause");
					concentrate = false;
					p.fullHeal(); //full heals the pokemon
					break;
				}
			}
			else if (input == "BAG") //if BAG, go into the bag
				bag(player, p);
			else if (input == "RUN") //if the player decides to run, then break out of the loop
			{
				system("CLS");
				cout << "You Ran Away From The Fight . . .\n\n";
				system("Pause");
				break;
			}
			else //if they inputted something that wasnt a spot or RUN, switch on the variable for an error
				battleError = true;
		}


	} while (!leave);
}
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
		for (int j = 0; j < 13; j++) {
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

//necessary functions for the pokemart
void buyingitem(trainer& player, int itemprice, int itemID, int x, int y) { // function for buying an item from the pokemart
	if (player.isiteminbag(0, x, y) && player.getmoney() >= itemprice) { // has enough mopney and the space for the item
		player.setmoney(player.getmoney() - itemprice); // take the amount to pay for the pruchase of the item
		cout << "Thank you for your purchase, " << itemprice << "G has been taken from your wallet.\n"; // tell user amount to be paid
		player.addtobag(itemID); // add the item to the player's bag
		system("pause");
		system("cls");
	}
	//dummyproofing
	else if (!player.isiteminbag(0, x, y)) { //there is no '0' spot, meaning that the bag is full
		cout << "You do not have space for this item. please sell some of your items to make room.\n";
		system("pause");
		system("cls");
	}
	else { // not enough money to buy the item
		cout << "You do not have enough money to pruchase this item. Please come back with more money.\n";
		system("pause");
		system("cls");
	}
}
void sellitem(trainer& player, int itemprice, int itemID, int x, int y) { // sells an item from the player's bag
	if (player.isiteminbag(itemID, x, y)) { // if the pplayer has the item theyre trying to sell
		player.removeitem(itemID, x, y); // removes the item theyre selling from theyre bag
		player.setmoney(player.getmoney() + (itemprice / 2)); // gives the player back half the normal price

		cout << "You've gained " << (itemprice / 2) << "$ back for your sale.\n"; // tells player how much they made
		cout << "Your New Balence: " << player.getmoney() << endl; // tells the player how much money they have now
		system("pause");
		system("cls");
	}
	else { // invalid input / can not find the item theyre trying to sell
		cout << "This item can not be found in your bag. Please enter a valid item.\n";
		system("pause");
		system("cls");
	}
}
void PokeMart(trainer& player, int x, int y) //simulates the PokeMart location for the game
{
	cout << "You Are At The PokeMart.\n"; // intro to the pokemart
	cout << "Here, You Can Buy Items That You Need For Battling Here At The PokeMart!\n\n";

	// create a screen that will show off the items nicely for the user to buy

	bool stay = true; // bool to keep the player into the pokemart screen until they want to leave
	do {
		//defining the prices for the items
		int item1p = 20; // price of item 1
		int item2p = 2000; // price of item 2
		int item3p = 1000;
		int item4p = 1000;
		int item5p = 1000;
		int item6p = 1000;
		int item7p = 1000;
		int item8p = 30;
		int item9p = 40;

		//directions to lead to buy / selling screen / leave pokemart
		cout << "Enter '1' if you're looking to buy items\n";
		cout << "OR\n";
		cout << "Enter '2' if you're looking to sell items from your bag.\n\n";
		cout << "Enter anything else if you are ready to leave." << endl;
		string str; // input string
		getline(cin, str);

		if (str == "1") { // buying section of pokemart
			system("cls");
			bool buying = true; // bool to keep player in buying section of pokemart
			do {
				//directions
				cout << "Enter the Number (Item ID) associated with the item to buy it." << endl;
				cout << "Enter '0' when you are done buying items.\n\n";
				//item list; items for sale currently
				cout << "Items for sale:\n";
				cout << "Small Potion 20G (ID: 1)\n";
				cout << "Rare Candy 2000G (ID: 2)\n";
				if (player.getRank() >= 2)//if the player rank is 2 or above, display the trait-changing items
				{
					cout << "Dumbbell 1000G (ID: 3)\n";
					cout << "Teddy Bear 1000G (ID: 4)\n";
					cout << "Brass Knuckles 1000G (ID: 5)\n";
					cout << "Fabreeze 1000G (ID: 6)\n";
					cout << "Daisy 1000G (ID: 7)\n";
				}
				if (player.getRank() >= 4) //if the player rank is 4 or above, display the medium potion
					cout << "Medium Potion 30G (ID: 8)\n";
				if (player.getRank() >= 5)//if the player rank is 5 or above, display the large potion
					cout << "Large Potion 40G (ID: 9)\n";

				cout << endl;
				cout << "Current Balence: " << player.getmoney() << endl; // current money of the player
				getline(cin, str);

				if (str == "0") // leave buying section of pokemart
					buying = false;
				else if (str == "1") { // buying item 1; small potion
					buyingitem(player, item1p, 1, x, y);
				}
				else if (str == "2") { // buying rare candy
					buyingitem(player, item2p, 2, x, y);
				}
				// add on here for more items to add into the shop
				else if (str == "3" && player.getRank() >= 2) //if 3 and they have the required rank, buy the item
					buyingitem(player, item3p, 3, x, y);
				else if (str == "4" && player.getRank() >= 2)//if 4 and they have the required rank, buy the item
					buyingitem(player, item4p, 4, x, y);
				else if (str == "5" && player.getRank() >= 2)//if 5 and they have the required rank, buy the item
					buyingitem(player, item5p, 5, x, y);
				else if (str == "6" && player.getRank() >= 2)//if 6 and they have the required rank, buy the item
					buyingitem(player, item6p, 6, x, y);
				else if (str == "7" && player.getRank() >= 2)//if 7 and they have the required rank, buy the item
					buyingitem(player, item7p, 7, x, y);
				else if (str == "8" && player.getRank() >= 4)//if 8 and they have the required rank, buy the item
					buyingitem(player, item8p, 8, x, y);
				else if (str == "9" && player.getRank() >= 5)//if 9 and they have the required rank, buy the item
					buyingitem(player, item9p, 9, x, y);
				else { // error; not a valid input of an item# or 0
					cout << "Please choose a valid item to buy from the store or enter 0 to stop shopping.\n"; // invaid input
					system("pause");
					system("cls");
				}
			} while (buying); //as long as they are buying, loop the logic
			system("cls");
		}
		else if (str == "2") { // sell items from bag
			bool selling = true; // bool ot keep player into the selling section of the pokemart
			do {
				system("cls");
				//directions
				cout << "Enter in the item ID of the item that you want to sell.\n";
				cout << "Enter '0' when you are done selling your items.\n\n";
				//item list and their prices for selling
				cout << "Item List:\n";
				cout << "Small Potion 10$ (ID: 1)\n";
				cout << "Rare Candy 1000$ (ID: 2)\n";
				cout << endl;
				cout << "Current Balence: " << player.getmoney() << endl << endl; // current $

				displayBag(player.getitembag(), x, y); // shows the entire bag
				getline(cin, str);

				if (str == "0") // leave selling section
					selling = false;
				else if (str == "1") { // sell small potion
					sellitem(player, item1p, 1, x, y);
				}
				else if (str == "2") { // sell rare candy
					sellitem(player, item2p, 2, x, y);
				}
				// add on here for more items to add into the shop
				else { // cant find item to sell
					cout << "Please choose an item that is in your bag, or enter '0' to stop selling.\n"; // invaid input
					system("pause");
					system("cls");
				}
			} while (selling); //as long as they are selling, loop the logic
			system("cls");
		}
		else { // leave the pokemart
			stay = false; //switch to false
			cout << "Thank you for shopping at PokeMart! Please come again!\n";
			system("Pause");
			system("cls");
		}
	} while (stay); //as long as they stay, loop the logic
}
void fightClub(POKEMON& p, trainer& player) //simulates the fight club location for the game
{
	//defining variables
	//creates the types of pokemon you can face in the fight club
	POKEMON e1; //specializes in attacking
	e1.setStats(p.getLevel() + 1, p.getTotalHP() + rand() % 10, p.getAtt() + 10, p.getDef() - 5, p.getAgi() + 5); //int newLevel, int newHP, int newAtt, int newDef, int newAgi
	POKEMON e2; //specializes in defence
	e2.setStats(p.getLevel() + 1, p.getTotalHP() + rand() % 10, p.getAtt() - 5, p.getDef() + 10, p.getAgi() - 5);
	POKEMON e3; //all around good, but will always lose in agility
	e3.setStats(p.getLevel() + 1, p.getTotalHP() + rand() % 10, p.getAtt() + 5, p.getDef() + 5, p.getAgi());

	vector<POKEMON> list;
	list.push_back(e1);
	list.push_back(e2);
	list.push_back(e3);

	bool startBattle = false;
	bool battleError = false;
	bool concentrate = false;
	bool inputError = false;
	int response = 0;
	string enemy = "Enemy";

	int spot = rand() % 3; //determines which pokemon us used

	//prompts the user
	cout << "You Are At The Fight Club!\n";
	cout << "Here You Can Test Your Skills Against Other Trainors and Earn Big Rewards!\n\n";

	string input;
	cout << "Would You Like To Fight A Trainer(1 = Yes, Anything Else = Leave): "; //prompt the user for an input
	getline(cin, input);

	if (input == "1")//if the player inputs 1, initiate the battle
	{
		system("CLS");

		//cout << "What Would You Like To Do(Input A Spot or RUN): "; //prompt the player for a move
		//getline(cin, input);
		startBattle = true;

		while (startBattle) //loops the battle until one side wins/runs away(running away not implemented yet)
		{
			do
			{
				displayBattle(p, list[spot]); //displays the battle screen

				if (battleError)//if there is a battle error, then let the player know
				{
					setColor(12);
					cout << "That Was Not A Valid Input! Please Input A Move or BAG or RUN!\n\n";
					setColor(15);
					battleError = false;
				}

				if (inputError) //if they choose None, let them know that they cannot
				{
					setColor(12);
					cout << "You Cannot Choose A Move Slot That Has Nothing In It!\n";
					cout << "Please Input A Valid Response!\n\n";
					setColor(15);
					inputError = false;
				}

				cout << "What Would You Like To Do(Input A Move or BAG or RUN): "; //prompt the player for a move
				getline(cin, input);

				if (input == "1" || input == "2" || input == "3" || input == "4") //if 1,2,3, or 4, convert into an integer and check if it corresponsds
					//with a 'none', if it does switch 'inputError' to true
				{
					response = stoi(input);
					if (p.getMove(response - 1) == "None")
						inputError = true;
				}
			} while (inputError); //if they choose 'none' as a move, raise an error and loop back

			for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
				if (input[i] != ' ') //if the index is not a space, then capitalize it
					input[i] = toupper(input[i]);

			if (input == "1" || input == "2" || input == "3" || input == "4") //run the battle logic if they entered a 1,2,3, or 4
			{
				if (p.getAgi() >= list[spot].getAgi()) //if your pokemon has a higher agility stat, then it will attack first
				{
					//your pokemon attack
					simulateBattle(p, list[spot], input, concentrate); //simulates the battle and has the pokemon take damage

					//enemy attack
					system("Pause");
					displayBattle(p, list[spot]);
					if (list[spot].getCurrentHP() > 0) //only has the enemy attack if there health is above 0
					{
						cout << endl << "The enemy pokemon used Smack!\n";
						simulateBattle(list[spot], p, enemy, concentrate);
					}

				}
				else if ((p.getAgi() < list[spot].getAgi())) //if the enemy has a higher agility stat, then it will attack first
				{
					//enemy attack
					cout << endl << "The enemy pokemon used Smack!\n";

					simulateBattle(list[spot], p, enemy, concentrate);
					system("Pause");
					displayBattle(p, list[spot]);

					//your pokemon attack
					if (p.getCurrentHP() > 0) //only has the player attack if the pokemon has above 0 HP
						simulateBattle(p, list[spot], input, concentrate); //simulates the battle and has the pokemon take damage
				}

				system("Pause");
				displayBattle(p, list[spot]); //updates the screen


				if (list[spot].getCurrentHP() <= 0) //if the enemy faints, then break out of the loop
				{
					//gain 5 times the exp
					if (p.getLevel() != 10) //if the pokemon is not level 10(max level), then give the pokemon EXP
					{
						//gain 3 times the money
						p.gainEXP(list[spot].getLevel()); //gives the pokemon the earned EXP
						p.gainEXP(list[spot].getLevel()); //gives the pokemon the earned EXP
						p.gainEXP(list[spot].getLevel()); //gives the pokemon the earned EXP
						cout << endl << "Your Pokemon Gained " << list[spot].getLevel() * 6 << " Experience!\n\n";
					}

					p.resetSubHP();
					cout << "You Earned " << player.earnMoney(list[spot]) * 2 << " Gold From the Fight!\n\n";
					//gives 2 times the money
					player.setmoney(player.getmoney() + player.earnMoney(list[spot])); //adds the money to the players account
					player.setmoney(player.getmoney() + player.earnMoney(list[spot])); //adds the money to the players account
					//updates battles won
					concentrate = false;
					player.increaseBattles(); //increase battles
					player.checkForRankUP(); //check for a rank up
					checkForLevelUp(p); //checks if the pokemon has enough EXP to level up
					system("Pause");
					break;
				}
				else if (p.getCurrentHP() <= 0) //if your pokemon faints, thats GAME OVER
				{
					system("CLS");
					cout << "Your Pokemon Has Fainted!\n";
					cout << "Your Pokemon's HP will be restored to full HP\n\n";
					system("Pause");
					concentrate = false;
					p.fullHeal(); //full heals the pokemon
					break;
				}
			}
			else if (input == "BAG") //if they input BAG, go into the bag
				bag(player, p);
			else if (input == "RUN") //if the player decides to run, then break out of the loop
			{
				system("CLS");
				cout << "You Ran Away From The Fight . . .\n\n";
				system("Pause");
				break;
			}
			else //if they inputted something that wasnt a spot or RUN, switch on the variable for an error
				battleError = true;
		}
	}

}
void gym(POKEMON& p, trainer& player) //simulates the gym location for the game
{
	//defining variables
	string input;
	bool startBattle = false;
	bool battleError = false;
	bool concentrate = false;
	bool inputError = false;
	int response = 0;
	string enemy = "Enemy";
	POKEMON gl; //gl stands for gym leader
	gl.setStats(8, 80, 55, 50, 61); //int newLevel, int newHP, int newAtt, int newDef, int newAgi

	//gym intro
	cout << "This is the gym for the gym leader.\n\n";
	system("Pause");
	system("CLS");
	cout << "Would You Like To Fight The Gym Leader(1 = Yes, Anything Else = Leave): ";
	getline(cin, input);

	if (input == "1") //if the player inputs 1, initiate the battle
	{
		system("CLS");
		startBattle = true;

		while (startBattle) //loops the battle until one side wins/runs away(running away not implemented yet)
		{
			do
			{
				displayBattle(p, gl); //displays the battle screen

				if (battleError)//if there is a battle error, then let the player know
				{
					setColor(12);
					cout << "That Was Not A Valid Input! Please Input A Move or BAG or RUN!\n\n";
					setColor(15);
					battleError = false;
				}

				if (inputError) //if they choose None, let them know that they cannot
				{
					setColor(12);
					cout << "You Cannot Choose A Move Slot That Has Nothing In It!\n";
					cout << "Please Input A Valid Response!\n\n";
					setColor(15);
					inputError = false;
				}

				cout << "What Would You Like To Do(Input A Move or BAG or RUN): "; //prompt the player for a move
				getline(cin, input);

				if (input == "1" || input == "2" || input == "3" || input == "4") //if 1,2,3, or 4, check the input response to make sure the number is not associated with 'none'
				{
					response = stoi(input);
					if (p.getMove(response - 1) == "None")
						inputError = true;
				}
			} while (inputError); //if they choose 'none' as a move, raise an error and loop back

			for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
				if (input[i] != ' ') //if the index is not a space, then capitalize it
					input[i] = toupper(input[i]);

			if (input == "1" || input == "2" || input == "3" || input == "4")//if 1,2,3, or 4, run the battle logic
			{
				if (p.getAgi() >= gl.getAgi()) //if your pokemon has a higher agility stat, then it will attack first
				{
					//your pokemon attack
					simulateBattle(p, gl, input, concentrate); //simulates the battle and has the pokemon take damage

					//enemy attack
					system("Pause");
					displayBattle(p, gl);
					if (gl.getCurrentHP() > 0) //only has the enemy attack if there health is above 0
					{
						cout << endl << "The enemy pokemon used Smack!\n";
						simulateBattle(gl, p, enemy, concentrate);
					}

				}
				else if ((p.getAgi() < gl.getAgi())) //if the enemy has a higher agility stat, then it will attack first
				{
					//enemy attack
					cout << endl << "The enemy pokemon used Smack!\n";

					simulateBattle(gl, p, enemy, concentrate);
					system("Pause");
					displayBattle(p, gl);

					//your pokemon attack
					if (p.getCurrentHP() > 0) //only has the player attack if the pokemon has above 0 HP
						simulateBattle(p, gl, input, concentrate); //simulates the battle and has the pokemon take damage
				}

				system("Pause");
				displayBattle(p, gl); //updates the screen


				if (gl.getCurrentHP() <= 0) //if the enemy faints, then break out of the loop
				{
					if (p.getLevel() <= 10) //only give them EXP if they are not lvl 10 or above
					{
						p.gainEXP(pow(gl.getLevel(), 3)); //gives the pokemon the earned EXP
						//NOTE: winning the gym leader fight gives a stupid amount of EXP
						cout << endl << "Your Pokemon Gained " << pow(gl.getLevel() * 2, 3) << " Experience!\n\n";
					}

					p.resetSubHP();
					cout << "You Earned " << player.earnMoney(gl) << " Gold From the Fight!\n\n";
					//increases the amount of battles won and checks for a rank up
					player.increaseBattles();
					player.checkForRankUP();
					concentrate = false;
					player.setmoney(pow(player.getmoney() + player.earnMoney(gl), 2)); //adds the money to the players account
					//NOTE: winning the gym leader fight gives you a stupid amount of money
					if (p.getLevel() != 10)
						checkForLevelUp(p);
					system("Pause");
					player.beatGym();
					break;
				}
				else if (p.getCurrentHP() <= 0) //if your pokemon faints, thats GAME OVER
				{
					system("CLS");
					cout << "Your Pokemon Has Fainted!\n";
					cout << "Your Pokemon's HP will be restored to full HP\n\n";
					system("Pause");
					concentrate = false;
					p.fullHeal(); //full heals the pokemon
					break;
				}
			}
			else if (input == "BAG") //if they type bag then go into bag
				bag(player, p);
			else if (input == "RUN") //if the player decides to run, then break out of the loop
			{
				system("CLS");
				cout << "You Ran Away From The Fight . . .\n\n";
				system("Pause");
				break;
			}
			else //if they inputted something that wasnt a spot or RUN, switch on the variable for an error
				battleError = true;
		}
	}
}

void tutorial() //gives the player information on how to play the game
{
	system("CLS");
	setColor(12);
	//advice on the locations
	cout << "Move around in the game by typing the locations you want to go to!\n\n";
	setColor(10);
	//more advice on locations
	cout << "There Are A Total of 6 Locations.\n\n";
	cout << "You Can Ask Mom For Advice On Different Locations The Game and Rest to Restore the HP of Your Pokemon\n";
	cout << "Keep In Mind That Although There Are Six Locations, Each Location Has A Pokemon Level Requirement That Must Be Met\n";
	cout << "If You Are Not A High Enough Level, You Cannot Go To That Location\n\n";
	setColor(11);
	//advice on traits
	cout << "Your Pokemon Is Given A Trait That Affects The Growth of Stats, The Possible Traits Are:\n";
	cout << "Strong-Willed: Increases HP, Decreases Agility\n";
	cout << "Innocent: Increases Defense, Decreases Attack\n";
	cout << "Aggressive: Increases Attack, Decreases Defense\n";
	cout << "Care-Free: Increase In Agility, Decrease in Defense\n";
	cout << "Cheerful: Slight Increases in Every Stat. Pokemon automatically receives 20% of the EXP needed to level up\n\n";
	setColor(9);
	//advice on player rank
	cout << "As You Win More Fights, Your Player Rank Increases\n";
	cout << "As Your Rank Increases, More Items Will Become Available in the PokeMart\n\n";
	setColor(14);
	//advice on displaying stats
	cout << "Type 'display stats' if to check your pokemon's stats and moves\n";
	cout << "This feature also shows a discription of the moves your pokemon knows, their stats, and your money!\n\n";
	setColor(15);
	//advice on learning moves
	cout << "If You Fail To Learn A Move, You Will Have To Learn It The Next Time\n";
	cout << "That You Can Learn A Move\n\n";
	system("Pause");
}

void goToLocation(string location, trainer& player, POKEMON& p, int x, int y) //takes players to the various locations
{
	if (location == "HOME") //if they input HOME, return home
		home(p);
	else if (location == "TRAINING GROUNDS")//if they input TRAINING GROUNDS, return training grounds
		trainingGrounds(p, player);
	else if (location == "CASINO") //if they input CASINO, return casino
		casino(player);
	else if (location == "POKEMART") //if they input POKEMART, return pokemart
		PokeMart(player, x, y);
	else if (location == "FIGHT CLUB") //if they input FIGHT, return fight club
		fightClub(p, player);
	else if (location == "GYM")//if they input GYM, return gym
		gym(p, player);
	else if (location == "CHECK BAG") //goes to the bag
		bag(player, p);
	else if (location == "TUTORIAL")
		tutorial();
	else //displays the players stats
	{
		p.displayStats(); //displays the stats
		cout << endl << "Player Rank: " << player.getRank() << endl; //display rank
		cout << endl << "Gold: " << player.getmoney() << endl << endl; //display gold
		system("Pause");
	}

}
void displayPlayer() //displays the art of the character
{
	//defining variables
	int length = 67;
	int width = 15;
	int startLine = (length / 2) - 6;
	int lineLength = 12;
	bool hat = false;
	bool face = false;
	bool body = false;
	int defaultColor = 170;
	int playerColor = 204;
	int faceLine;
	int faceLength;
	setColor(170);
	for (int j = 0; j < width; j++) //fills in the rows
	{
		for (int i = 0; i < length; i++) //fills in the columns
		{
			if (j == 4) //if its equal to 4, change the color
			{
				if (i == 29 || i == 38)
					setColor(playerColor);
			}

			if (i == startLine) //if 'i' is equal to startline, then change the color
				setColor(playerColor);
			else if (i == startLine + lineLength) //if it is at the end of start line, change the color back to the default
				setColor(defaultColor);
			if (lineLength <= 0)
				setColor(defaultColor); //if the line length is less than 0, change it back to the default color
			if (j == 4 && i == 28) // if its equal to 4 or 28, change it to black
				setColor(0);
			else if (j == 4 && i == 37)// if its equal to 4 or 37, change it to black
				setColor(0);
			cout << " ";

		}

		if (j <= 1) //changes the startline and linelength values if j is less than 1
		{
			startLine = startLine - 2;
			lineLength = lineLength + 4;
		}
		else if (j == 2 && !hat) //if j = 2, changes the startline and linelength values
		{
			startLine = startLine + 2;
			faceLine = startLine;
			lineLength = lineLength - 4;
			faceLength = lineLength;
			hat = true;
			playerColor = 238;
		}
		else if (j == 6)//if j = 6, changes the startline and linelength values
		{
			face = true;
			startLine = (length / 2) - 2;
			lineLength = 4;
		}
		else if (j == 7)//if j = 7, changes the startline and linelength values and change the player color
		{
			startLine = faceLine + 2;
			lineLength = faceLength - 4;
			playerColor = 204;

		}


		cout << endl;
	}
	setColor(15); //sets the color back to white
}

int main() //runs the main logic of the code
{
	//defining variables
	string location;
	POKEMON p; //the player's pokemon
	string input;
	trainer player;// creating the variable for the trainer
	srand(time(NULL)); //setting the randomness for the game

	do
	{
		//defining and resetting variables when player wants to restart
		int counter = 0;
		bool gameOver = false;
		pokemonSetUp(p); //setting up the player's pokemon's stats and trait
		int x = 2; int y = 10; // specs of the size of the item bag
		int** board = boardcreate(x, y);
		player.settrainer(1, 0, 0, board); // adding the specs of a newly minted trainer

		do
		{
			do
			{
				system("CLS");
				displayPlayer();
				if (location == "INVALID") //if they gave an invalid response, give them an error message
				{
					setColor(12);
					cout << "That is an invalid response! Please Input a Valid Reponse!\n\n";
					setColor(15);
				}

				//displays the possible locations that the player can go to
				cout << "Locations:\n\n";
				cout << "Home (Level 1)\n";
				cout << "Training Grounds (Level 1)\n";
				cout << "PokeMart (Level 2)\n";
				cout << "Casino (Level 4)\n";
				cout << "Fight Club (Level 5)\n";
				cout << "Gym (Level 8)\n\n";
				cout << "Additional Commands:\n\n";
				cout << "Tutorial\n";
				cout << "Check Bag\n";
				cout << "Display Stats\n";
				cout << endl;
				cout << "Where would you like to go: ";
				getline(cin, input);
				location = playerInput(input, p); //assigns there response to the 'location' variable
			} while (location == "INVALID"); //if the player input an invalid location, loop until a valid input is set

			goToLocation(location, player, p, x, y); //sends the player to a location

		} while (player.getWin() == false); //repeat the main logic as long as the player has not received a GAME OVER

	} while (playAgain()); //repeat the code inside the loop if the player decides to play again

	system("Pause");
	return 0;
}
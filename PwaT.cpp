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
			cout << "itme not found in bag / ERROR\n";
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
void setColor(int color)// for changing color outside function
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
void pokemonSetUp(POKEMON& p) //creates everything for the initial pokemon
{
	p.setUp();
	p.createMovePool();
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

	counter++;

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
	else //if it returns invalid, that means there was an invalid response
		return "INVALID";
}
bool playAgain() //prompts the player if they want to play again, then returns true or false
{
	system("CLS");
	string tryAgain;
	cout << "Would You Like To Try Again(1 = Yes, Anything Else = No): ";
	cin >> tryAgain;
	cin.ignore();
	if (tryAgain == "1") //if input is equal to 1, return true
		return true;
	else //if it not equal to 1, return false
		return false;
}
void home(POKEMON p) //simulates the home location for the game
{
	int counter = 0;
	system("CLS");
	//defining variables
	bool stayhome = true;
	do {
		string input;
		bool error = false;
		do
		{
			if (error) //if there was an error, let the player know and set 'error' back to false
			{
				cout << "Your Response Was Invalid! Please Input a Valid Response!\n\n";
				cout << "Please enter the following inputs:\n";
				cout << "TALK TO MOM\n";
				cout << "SLEEP\n";
				cout << "LEAVE\n\n";
				error = false;
				system("pause");
				system("cls");
			}

			//tell the player they are at the house
			cout << "You Are At Your House.\n";
			cout << "Would You Like To 'Talk To Mom', 'Sleep', or 'Leave': ";
			getline(cin, input);

			for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
				input[i] = toupper(input[i]);

			if (input != "TALK TO MOM" && input != "SLEEP" && input != "LEAVE") {
				error = true;
			}

		} while (error); //as long as there is an error, keep looping the inside code

		if (input == "TALK TO MOM") {
			motherAdvice(counter);
			system("pause");
			system("cls");
		}
		else if (input == "SLEEP") {
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
	} while (stayhome);
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
			if (!alibi)
				setColor(10);
			else
				setColor(14);
		cout << "/";
	}

	setColor(15);
}
void experienceBar(float currentEXP, float totalEXPRequired)
{
	float percentageEXP = currentEXP / totalEXPRequired;
	float expBar = 20;

	expBar = ceil(expBar * percentageEXP);

	setColor(11);
	for (int i = 0; i < 20; i++)
	{
		if (i > expBar - 1)
			setColor(15);
		cout << "=";

	}

	cout << endl;
	setColor(15);
}
void displayBattle(POKEMON p, POKEMON e)
{
	system("CLS");
	cout << "Screen:\n\n";
	cout << "Enemy Level: " << e.getLevel() << endl;
	cout << "Enemy HP(" << e.getCurrentHP() << "/" << e.getTotalHP() << ") >> ";
	healthBar(e.getCurrentHP(), e.getTotalHP(), false);
	cout << endl << endl;
	setColor(207);
	cout << "		E\n\n";
	setColor(252);
	cout << "		Q\n\n";
	setColor(15);
	cout << "Your Level: " << p.getLevel() << endl;

	if (p.getSubCurrentHP() > 0) //only run if the alibi has health
	{
		cout << "Alibi HP(" << p.getSubCurrentHP() << "/" << p.getSubTotalHP() << ") >> ";
		healthBar(p.getSubCurrentHP(), p.getSubTotalHP(), true);
		cout << endl;
	}

	cout << "Your HP(" << p.getCurrentHP() << "/" << p.getTotalHP() << ") >> ";
	healthBar(p.getCurrentHP(), p.getTotalHP(), false);
	cout << endl << "EXP   	       >> ";
	experienceBar(p.getCurrentEXP(), p.getTotalEXP());
	cout << endl << endl;
	//displays the pokemon's moveset
	cout << "Moves: \n\n";
	cout << "1: " << p.getMove(0) << "		2: " << p.getMove(1) << endl;
	cout << "3: " << p.getMove(2) << "		4: " << p.getMove(3) << endl;

	setColor(9);
	cout << endl << "RUN";
	cout << endl;
	setColor(15);
	cout << endl;
}
void simulateBattle(POKEMON& AttPok, POKEMON& DefPok, string& input, bool& concentrate)
{
	int spot = -1;
	int power = 0;
	int modifier = 1;
	float damage = 0;

	if (concentrate && input != "Enemy")
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
		damage = (((((((2 * AttPok.getLevel()) / 5) + 2) * power * (AttPok.getAtt() / DefPok.getDef())) / 50) + 2) * modifier); //this is the actual formula that pokemon uses to calculate damage
	//dont ask me why its so complicated cuz tbh idk

	if (damage > 0) //if the player did damage, let them know how much damage they did
	{
		if (input == "Enemy")//if the enemy is attacking, display this message
			cout << endl << "The Attack Dealt . . . " << damage << " Damage!\n"; //tells the player how much damage they dealt
		else //else display how much damage the player did
			cout << endl << "Your Attack Dealt . . . " << damage << " Damage!\n"; //tells the player how much damage they dealt
		if (DefPok.getSubCurrentHP() > 0)
			DefPok.damageAlibi(damage);
		else
		{
			DefPok.takeDamage(damage); //has the defending pokemon take damage
			if (DefPok.getSubCurrentHP() <= 0) //if the alibi is dead, reset the stats to 0
				DefPok.resetSubHP();
		}

		if (input != "Enemy")
			concentrate = false; //switches concentrate off
	}

	if (concentrate && input != "Enemy") //lets the player know that concentrate is in effect
		cout << endl << "Your Next Attack Will Be 2.5 Times Stronger!\n\n";
}
void checkForLevelUp(POKEMON& p)
{
	string input;
	bool error = false;
	int spot;

	if (p.getCurrentEXP() >= p.getTotalEXP())
	{
		p.levelUp();
		system("CLS");
		cout << "Congratulations! Your Pokemon Just Leveled Up!\n\n";
		system("Pause");

		if (p.getLevel() % 2 == 0) //if the pokemon's level is an even number
		{
			cout << "Your Pokemon Can Learn The Move . . . " << p.getMoveFromPool(p.getSizePool() - 1) << "!\n\n";
			cout << "Would You Like Your Pokemon To Learn " << p.getMoveFromPool(p.getSizePool() - 1) << "(1 = Yes, Anything Else = No): ";
			getline(cin, input);
		}
		if (input == "1")
		{
			do
			{
				if (error)
				{
					cout << "That is an Invalid Response! Please Input A Valid Response!\n\n";
					error = false;
				}

				cout << "Which Move Slot Would You Like To Place It In(1, 2, 3, or 4)(Choosing a Slot That Has An Existing Move Will Replace It): ";
				getline(cin, input);

				if (input != "1" && input != "2" && input != "3" && input != "4")
					error = true;
				else
				{
					spot = stoi(input);
					p.learnMove(p.getMoveFromPool(p.getSizePool() - 1), spot);
					p.removeFromPool();
				}

			} while (error);
		}
		else
		{
			system("CLS");
			cout << "The Move Was Not Learned\n\n";
			system("Pause");
		}
	}


}
void trainingGrounds(POKEMON& p) //simulates the training grounds for the game
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

	for (int z = 0; z < 25; z++) //formats the spots for the training grounds
		spots.push_back(0);

	//keep in mind when the training ground is generated, the location of the player is random
	int playerLocation = rand() % 25; //determines the location of the player
	spots[playerLocation] = 1;

	do //loop the training ground logic until the player decides to leave
	{
		checkForLevelUp(p);
		p.fullHeal();
		startBattle = false;
		system("CLS");
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

		if (error)
			cout << "That was an Invalid Input! Please Input A Valid Response!\n\n";

		string input;
		cout << "What Would You Like To Do(Left, Right, Up, Down, Leave): ";
		getline(cin, input);

		for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
			if (input[i] != ' ') //if the index is not a space, then capitalize it
				input[i] = toupper(input[i]);

		//takes user input from the player that tells the program how to move the player
		if (input == "LEFT") //moves the player left on the board
		{
			spots[playerLocation] = 0;
			playerLocation = playerLocation - 1;
			spots[playerLocation] = 1;
		}
		else if (input == "RIGHT") //moves the player right on the board
		{
			spots[playerLocation] = 0;
			playerLocation = playerLocation + 1;
			spots[playerLocation] = 1;
		}
		else if (input == "UP") //moves the player up on the board
		{
			spots[playerLocation] = 0;
			playerLocation = playerLocation - 5;
			spots[playerLocation] = 1;
		}
		else if (input == "DOWN") //moves the player down on the board
		{
			spots[playerLocation] = 0;
			playerLocation = playerLocation + 5;
			spots[playerLocation] = 1;
		}
		else if (input == "LEAVE") //makes the player leave the training grounds
			leave = true;
		else
			error = true;

		if (rand() % 4 == 1 && !leave) //has a 25% chance to encounter a wild pokemon, if they role a 1, then initiate a fight
		{
			//e.setStats(10, 10, 10, 10, 10); //int newLevel, int newHP, int newAtt, int newDef, int newAgi
			e.randomizeStats(p);
			startBattle = true;
			//displayBattle(p, e);
		}
		while (startBattle) //loops the battle until one side wins/runs away(running away not implemented yet)
		{
			displayBattle(p, e); //displays the battle screen

			if (battleError)//if there is a battle error, then let the player know
			{
				setColor(12);
				cout << "That Was Not A Valid Input! Please Input A Spot or RUN!\n\n";
				setColor(15);
				battleError = false;
			}

			cout << "What Would You Like To Do(Input A Spot or RUN): "; //prompt the player for a move
			getline(cin, input);

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
					p.gainEXP(e.getLevel()); //gives the pokemon the earned EXP
					p.resetSubHP();
					cout << endl << "Your Pokemon Gained " << e.getLevel() * 2 << " Experience!\n\n";
					system("Pause");
					break;
				}
				else if (p.getCurrentHP() <= 0) //if your pokemon faints, thats GAME OVER
				{
					system("CLS");
					cout << "GAME OVER!\n\n";
					system("Pause");
					p.fullHeal(); //full heals the pokemon
					break;
				}
			}
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
		hand.push_back(v[v.size() - 1]);
		v.pop_back();
	}
	return hand;
}
bool acefound(vector<int>& v) { //checks for special case: an ace, which could count as 1 point or 11, whatever is more favorable
	for (int i = 0; i < v.size(); i++)
		if (v[i] == 1)
			return true;
	return false;
}
void casino(trainer& player) //simulates the casino location for the game
{
	cout << "You Are At The Casino!\n";
	cout << "At The Casino, You Can Irresonsibly Earn Or Lose Large Amounts of Money Here!\n";
	cout << "Mother Probably Would Not Want Me To Be At The Casino . . .\n\n";
	//blackjack

	cout << "How to play BlackJack:\n";//intro to the casio game: blackjack
	cout << "The goal of Blackjack is to beat the Dealer.\n";
	cout << "to win you must either:\n";
	cout << "1) get a blackjack (an ace card and any 10 value card) where you get a 150% of your bet as a reward\n";
	cout << "OR\n";
	cout << "2) Get closer to 21 than the dealer without going over.\n";
	cout << "You may ask for cards until your hand exceeds the 21 point bust limit, which you will loose.\n";
	cout << "the dealer shows only 1 card, and will draw cards until they exceed 17 after your turn.\n";
	cout << "If you have equal points to the dealer, you play a new round.\n";
	cout << "\n";
	cout << "all face cards = 10 points\n";
	cout << "ace cards = 1 OR 11\n";
	cout << "numbered cards = equal to the number on their card.\n";
	system("pause");
	system("cls");

	bool turnend = false;
	string bet; double betdb = 0;
	do {
		cout << "current Money: " << player.getmoney() << "$\n";
		cout << "How much do you want to bet? (Enter '0' to quit Blackjack)\n"; //ask for the bet value; make sure it doesn't exceed current money
		getline(cin, bet);
		betdb = stoi(bet);
		if (betdb > player.getmoney()) {
			cout << "You can not bet more than the amount you currently have.\n";
			system("pause");
			system("cls");
		}
		else if (betdb < 0) {
			cout << "You can not bet less than 0.\n";
			system("pause");
			system("cls");
		}
		else if (betdb == 0) { // no bet
			turnend = true;
			break;
		}
	} while (betdb > player.getmoney() || betdb < 0); // makes sure to have a valid 

	if (betdb > 0) {
		do {
			vector<int> deck = creatcarddeck();
			shuffle(deck);

			vector<int> dealerhand = dealfirst2cards(deck);//dealdealer
			vector<int> playerhand = dealfirst2cards(deck);//dealplayer

			int playerpoint = playerhand[0] + playerhand[1]; // adding the int values of both the cards together of the player's hand
			int dealerpoint = dealerhand[0] + dealerhand[1]; // add both cards up of the dealer's hand
			do {
				//ask player if they want to draw more cards or end their turn
				string str;
				do { // make sure to get a valid input of '1' or '2'
					system("cls");
					cout << "Dealer's first card: " << dealerhand[0] << endl; //show 1 card of 2, draw the card but dont show it

					cout << endl;

					cout << "Player's Hand:\n";

					for (int i = 0; i < playerhand.size(); i++)//show both cards
						cout << "Card " << i + 1 << ") " << playerhand[i] << endl;
					/*if (acefound(playerhand))
						playerpoint += playerhand[playerhand.size() - 1];*/

					cout << "Player's Total points: " << playerpoint;
					if (acefound(playerhand)) // if there is an ace, then the point value could potentially be 10 points higher, tell user that
						cout << "( + 10)";
					cout << endl << endl;

					cout << "What would you like to do?\n"; // instructions
					cout << "Enter '1' to Draw a card.\n";
					cout << "OR\n";
					cout << "Enter '2' to End your turn.\n";
					getline(cin, str);
					if (str != "1" && str != "2") {
						cout << "please Enter '1' or '2'.\n";
						system("pause");
						system("cls");
					}
				} while (str != "1" && str != "2");

				if (str == "1") {
					playerhand.push_back(deck[deck.size() - 1]); // take from deck
					deck.pop_back(); // remove the card just taken from the deck

					playerpoint += playerhand[playerhand.size() - 1];
					for (int i = 0; i < playerhand.size(); i++)//show both cards
						cout << "Card " << i + 1 << ") " << playerhand[i] << endl;

					cout << "Player's Total points: " << playerpoint;
					if (acefound(playerhand)) // if there is an ace, then the point value could potentially be 10 points higher, tell user that
						cout << "( + 10)";
					cout << endl << endl;
				}
				else { //(str == "2")
					if (acefound(playerhand) && playerpoint + 10 == 21) // if any of the cards is an ace, find best scenario to win, either ace = 1, or ace = 11
						playerpoint = 21; // if it is an ace and 1 rest sum of 10 / 10 point card, then win; if ace being 11 points wins, then ace = 11
					turnend = true;
					system("cls");
				}

			} while (!turnend && playerpoint < 21); // either until player ends turn or their hand exceeds 21 points
			int i = 0;
			cout << "Dealer's Hand:\n";
			for (i = 0; i < dealerhand.size(); i++)//show both cards
				cout << "Card " << i + 1 << ") " << dealerhand[i] << endl;

			if (playerpoint <= 21) { // wont execute if the player already lost, direct to lose text
				//reveal dealer's hand
				cout << "Dealer's Total points: " << dealerpoint << endl << endl;
				system("pause");
				if (dealerpoint <= 17) { // prevents taking from deck if already above 17
					do {// dealer draw cards until over 17
						i++;
						dealerhand.push_back(deck[deck.size() - 1]);
						deck.pop_back();
						dealerpoint += dealerhand[dealerhand.size() - 1];
						cout << "Card " << i << ") " << dealerhand[dealerhand.size() - 1] << endl;
						//cout << "Here                 |" << endl;
						if (acefound(dealerhand) && dealerpoint + 10 == 21) // if any of the cards is an ace, find best scenario to win, either ace = 1, or ace = 11
							dealerpoint = 21; // if it is an ace and 1 rest sum of 10 / 10 point card, then win; if ace being 11 points wins, then ace = 11

						cout << "Dealer's Total points: " << dealerpoint << endl << endl;
						system("pause");

					} while (dealerpoint <= 17);
				}
			}

			//win/loose communication
			if (playerpoint > 21) { //playerpint exceeds 21
				cout << "You've exceeded 21 points, You loose!\n";
				player.setmoney(player.getmoney() - betdb); // keep all valeus the same but change the money
				turnend = true; // in the case where player exceeds 21, losing but it doesnt end their turn and causes them to play again
			}
			else if (dealerpoint > 21 && playerpoint < 21) { // dealer exceeds 21 points, but since player always goes first, if theyre still <= 21 as well
				cout << "The Dealer exceeded 21 points, You Win!\n";
				turnend = true;
				player.setmoney(player.getmoney() + betdb);
			}
			else if (playerpoint == 21 && dealerpoint != 21) {
				cout << "You got exactly 21 points while the dealer didn't, You Win!\n";
				turnend = true;
				if (playerhand.size() == 2) // blackjack
					betdb = 1.5 * betdb;
				player.setmoney(player.getmoney() + betdb);
			}
			else { // other win cases
				int premainder = 21 - playerpoint; // used to see which person (player or dealer) was closest to 21 in the event that no one gets 21 exactly
				int dremainder = 21 - dealerpoint;

				if (dealerpoint != 21 && playerpoint != 21) { // if no one has 21 points exactly
					if (dremainder < premainder) {
						cout << "The dealer wins. you loose your bet.\n";
						player.setmoney(player.getmoney() - betdb);
						turnend = true;
					}
					else {
						cout << "The player wins. you won your bet.\n";
						player.setmoney(player.getmoney() + betdb);
						turnend = true;
					}
				}
				if (playerpoint <= 21 && playerpoint == dealerpoint) { //both dealer and player tie, but <= 21; replay the game
					cout << "You've tied with the dealer, You get to play again, free of charge!\n";
					turnend = false;
				}
			}
			cout << "You've lost / gained " << betdb << "$." << endl;
			cout << "current $: " << player.getmoney() << endl;
			system("pause");
			system("cls");
		} while (!turnend);
	}
	system("Pause");
}
//necessary functions for the pokemart
void buyingitem(trainer& player, int itemprice, int itemID, int x, int y) { // function for buying an item from the pokemart
	if (player.isiteminbag(0, x, y) && player.getmoney() >= itemprice) { // has enough mopney and the space for the item
		player.setmoney(player.getmoney() - itemprice); // take the amount to pay for the pruchase of the item
		cout << "Thank you for your purchase, " << itemprice << "$ has been taken from your wallet.\n"; // tell user amount to be paid
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
				cout << "Small Potion 20$ (ID: 1)\n";
				cout << "Rare Candy 2000$ (ID: 2)\n";
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

				else { // error; not a valid input of an item# or 0
					cout << "Please choose a valid item to buy from the store or enter 0 to stop shopping.\n"; // invaid input
					system("pause");
					system("cls");
				}
			} while (buying);
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
			} while (selling);
			system("cls");
		}
		else { // leave the pokemart
			stay = false;
			cout << "Thank you for shopping at PokeMart! Please come again!\n";
			system("Pause");
			system("cls");
		}
	} while (stay);
}
void fightClub(POKEMON& p) //simulates the fight club location for the game
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
	string enemy = "Enemy";

	int spot = rand() % 3; //determines which pokemon us used

	//prompts the user
	cout << "You Are At The Fight Club!\n";
	cout << "Here You Can Test Your Skills Against Other Trainors and Earn Big Rewards!\n\n";

	string input;
	cout << "Would You Like To Fight A Trainer(1 = Yes, Anything Else = Leave): "; //prompt the user for an input
	getline(cin, input);

	if (input == "1")
	{
		system("CLS");

		//cout << "What Would You Like To Do(Input A Spot or RUN): "; //prompt the player for a move
		//getline(cin, input);
		startBattle = true;

		while (startBattle) //loops the battle until one side wins/runs away(running away not implemented yet)
		{
			displayBattle(p, list[spot]); //displays the battle screen

			if (battleError) //if there is a battle error, then let the player know
			{
				setColor(12);
				cout << "That Was Not A Valid Input! Please Input A Spot or RUN!\n\n";
				setColor(15);
				battleError = false;
			}

			cout << "NOTE: You Can Run From A Gym Fight. This Counts As Forfeiting.\n";
			cout << "What Would You Like To Do(Input A Spot or RUN): "; //prompt the player for a move
			getline(cin, input);

			for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
				if (input[i] != ' ') //if the index is not a space, then capitalize it
					input[i] = toupper(input[i]);

			if (input == "1" || input == "2" || input == "3" || input == "4")
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
					//gain 2 times the exp
					p.gainEXP(list[spot].getLevel()); //gives the pokemon the earned EXP
					p.gainEXP(list[spot].getLevel()); //gives the pokemon the earned EXP
					p.resetSubHP();
					cout << endl << "Your Pokemon Gained " << list[spot].getLevel() * 2 << " Experience!\n\n";
					system("Pause");
					break;
				}
				else if (p.getCurrentHP() <= 0) //if your pokemon faints, thats GAME OVER
				{
					system("CLS");
					cout << "GAME OVER!\n\n";
					system("Pause");
					p.fullHeal(); //full heals the pokemon
					break;
				}
			}
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
void gym(POKEMON& p) //simulates the gym location for the game
{
	string input;
	bool startBattle = false;
	bool battleError = false;
	bool concentrate = false;
	string enemy = "Enemy";
	POKEMON gl; //gl stands for gym leader
	gl.setStats(8, 80, 48, 40, 60); //int newLevel, int newHP, int newAtt, int newDef, int newAgi

	cout << "This is the gym for the gym leader.\n\n";
	system("Pause");
	cout << "Would You Like To Fight The Gym Leader(1 = Yes, Anything Else = Leave): ";
	getline(cin, input);

	if (input == "1")
	{
		system("CLS");

		//cout << "What Would You Like To Do(Input A Spot or RUN): "; //prompt the player for a move
		//getline(cin, input);
		startBattle = true;

		while (startBattle) //loops the battle until one side wins/runs away(running away not implemented yet)
		{
			displayBattle(p, gl); //displays the battle screen

			if (battleError)//if there is a battle error, then let the player know
			{
				setColor(12);
				cout << "That Was Not A Valid Input! Please Input A Spot or RUN!\n\n";
				setColor(15);
				battleError = false;
			}

			cout << "NOTE: You Can Run From A Gym Fight. This Counts As Forfeiting.\n";
			cout << "What Would You Like To Do(Input A Spot or RUN): "; //prompt the player for a move
			getline(cin, input);

			for (int i = 0; i < input.size(); i++) //converts all letters to uppercase
				if (input[i] != ' ') //if the index is not a space, then capitalize it
					input[i] = toupper(input[i]);

			if (input == "1" || input == "2" || input == "3" || input == "4")
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
					p.gainEXP(gl.getLevel()); //gives the pokemon the earned EXP
					p.resetSubHP();
					cout << endl << "Your Pokemon Gained " << gl.getLevel() * 2 << " Experience!\n\n";
					system("Pause");
					break;
				}
				else if (p.getCurrentHP() <= 0) //if your pokemon faints, thats GAME OVER
				{
					system("CLS");
					cout << "GAME OVER!\n\n";
					system("Pause");
					p.fullHeal(); //full heals the pokemon
					break;
				}
			}
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
void bag(trainer player,POKEMON& p)
{
	displayBag(player.getitembag(), 2, 10); // board on console; shows the items in the bag
	cout << "what item do you want to use(0 = nothing)?\n";
	string str;
	getline(cin, str);
	int item = stoi(str);
	player.useitem(p, item);
}

void goToLocation(string location, trainer player, POKEMON& p, int** board, int x, int y)
{
	if (location == "HOME")
		home(p);
	else if (location == "TRAINING GROUNDS")
		trainingGrounds(p);
	else if (location == "CASINO")
		casino(player);
	else if (location == "POKEMART")
		PokeMart(player, x, y);
	else if (location == "FIGHT CLUB")
		fightClub(p);
	else if (location == "GYM")
		gym(p);
	else //if (location == "CHECK BAG")
		bag(player, p);
}
void displayPlayer()
{
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
	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < length; i++)
		{
			if (j == 4)
			{
				if (i == 29 || i == 38)
					setColor(playerColor);
			}

			if (i == startLine)
				setColor(playerColor);
			else if (i == startLine + lineLength)
				setColor(defaultColor);
			if (lineLength <= 0)
				setColor(defaultColor);
			if (j == 4 && i == 28)
				setColor(0);
			else if (j == 4 && i == 37)
				setColor(0);
			cout << " ";

			//setColor(playerColor);
			/*if (i == length - 1)
			{
				setColor(15);
				cout << " " << i;
				setColor(170);
			}*/

		}

		if (j <= 1)
		{
			startLine = startLine - 2;
			lineLength = lineLength + 4;
		}
		else if (j == 2 && !hat)
		{
			startLine = startLine + 2;
			faceLine = startLine;
			lineLength = lineLength - 4;
			faceLength = lineLength;
			hat = true;
			playerColor = 238;
		}
		else if (j == 6)
		{
			face = true;
			startLine = (length / 2) - 2;
			lineLength = 4;
		}
		else if (j == 7)
		{
			startLine = faceLine + 2;
			lineLength = faceLength - 4;
			playerColor = 204;

		}


		cout << endl;
	}
	setColor(15);
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
		p.fullHeal();
		p.setLevel(10); //sets the level to 10 for testing purposes
		int x = 2; int y = 10; // specs of the size of the item bag
		int** board = boardcreate(x, y);
		player.settrainer(1, 0, 10000, board); // adding the specs of a newly minted trainer
		do
		{
			do
			{
				system("CLS");
				displayPlayer();
				if (location == "INVALID") //if they gave an invalid response, give them an error message
					cout << "That is an invalid response! Please Input a Valid Reponse!\n\n";
				cout << "Locations:\n";
				cout << "Home\n";
				cout << "Training Grounds\n";
				cout << "Casino";
				cout << " (for now, no min. level to access casino)\n";
				cout << "PokeMart\n";
				cout << "Fight Club\n";
				cout << "Gym\n";
				cout << "Check Bag";
				cout << "(can not use bag at all currently)\n";
				cout << endl;
				cout << "Where would you like to go: ";
				getline(cin, input);
				location = playerInput(input, p); //assigns there response to the 'location' variable
			} while (location == "INVALID"); //if the player input an invalid location, loop until a valid input is set

			goToLocation(location, player, p, player.getitembag(), x, y);

			if (p.getTotalHP() == 0)
				gameOver = true;

		} while (!gameOver); //repeat the main logic as long as the player has not received a GAME OVER

	} while (playAgain()); //repeat the code inside the loop if the player decides to play again

	system("Pause");
	return 0;
}
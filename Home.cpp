// Donald Newandee & Jason Zhou
//Pokemon With a Twist
//DN_JZ_PwaT.cpp
//
// due june 5th

using namespace std;

#include<iostream> //libraries
#include<vector>
#include<string>
#include<time.h>
#include<cmath>
#include<windows.h>

class POKEMON //sets up the class for the player's pokemon
{
private:
	//defining variables
	int level, hp, exp, att, def, spAtt, spDef, agi; string trait, ability; vector<string> moveSet, movePool;

public:
	//functions for getting the information for their stats
	int getLevel() { return level; }
	int getHP() { return hp; }
	int getAtt() { return att; }
	int getDef() { return def; }
	int getSpAtt() { return spAtt; }
	int getSpDef() { return spDef; }
	int getAgi() { return agi; }
	int getEXP() { return exp; }
	string getAbility() { return ability; }
	string getTrait() { return trait; }

	void setHP(int health) { hp = health; }

	void setUp() //sets up the stats, traits, and initial moves for the pokemon
	{
		level = 1;
		hp = 10;
		exp = 0;
		att = 5;
		def = 5;
		spAtt = 5;
		spDef = 5;
		agi = 5;
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
		moveSet.push_back("Slap");
		moveSet.push_back("Stare");
	}

	//changes the characteristics of the pokemon after they have leveled up
	void setLevel(int newLevel) { level = newLevel; } //this is just to cheat to test things
	void levelUp()
	{
		level++;
		att = att + 2;
		def = def + 2;
		spAtt = spAtt + 2;
		spDef = spDef + 2;
		agi = agi + 2;
		hp = hp + 10;
		exp = 0;
	} //makes the pokemon level up
	void changeTrait(string newTrait) { trait = newTrait; }
	void learnMove(string newMove, int spot) { moveSet[spot - 1] = newMove; }
	void createMovePool()
	{
		movePool.push_back("Slap");
		movePool.push_back("Stare");
		movePool.push_back("Concentrate");
		movePool.push_back("Poker Face");
		movePool.push_back("Kick");
		movePool.push_back("Perfect Alibi");
		movePool.push_back("Serious Punch");
	}

	void displayStats() //displays all stats of the pokemon
	{
		cout << "Pokemon Stats:\n\n";
		cout << "Level: " << level << endl;
		cout << "Health Points: " << hp << endl;
		cout << "Attack: " << att << endl;
		cout << "Defense: " << def << endl;
		cout << "Special Attack: " << spAtt << endl;
		cout << "Special Defense: " << spDef << endl;
		cout << "Agility: " << agi << endl;
		cout << "Trait: " << trait << endl;
		cout << "Current EXP: " << exp << endl << endl;
	}
};
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
		cout << "You may be able to do things yuo were not able to do before with a higher rank.\n\n";
	}
	else if (counter == 3) //tells the player about new moves
		cout << "Your Pokemon can learn a new move every other level.\n\n";
	else if (counter == 4) //tells the player about the PokeMart
		cout << "You can go to the PokeMart to buy items like potions.\n\n";
	else if (counter == 5) //tells the player about the gym leader
		cout << "You can challenge the gym leader once your pokemon is level 7 or above.\n\n";
	else if (counter == 6) //tells the player about the fight club
	{
		cout << "I hear there's a fight club you can go to where you can battle strong trainers.\n";
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


int main() {
	srand(time(NULL)); //adds a time based randomizer
	POKEMON p; //the player's pokemon
	pokemonSetUp(p);







	system("Pause");





	system("pause");
	return 0;
}
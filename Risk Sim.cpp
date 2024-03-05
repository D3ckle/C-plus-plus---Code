//Risk Game
//Donald Alan Newandee
//Alpha test: february 24th (monday) 2020, project due 11:59 the same day 
//
//This program should simulate a battle for the classic Hasbro game Risk.
//In the game Risk, you are able to conquer an adjacent territory by
//fighting with the defending force over a series of battle rounds.
//Each “skirmish” consists of the attacker and defender rolling, at most 3
//dice for the attacker and 2 for the defender.The attacker then matches
//his / her highest roll with the defender’s higher roll and the attacker’s 2 nd
//highest roll against the defender’s 2 nd highest roll and so forth, with the
//defender winning all ties. Each skirmish could potentially eliminate 3 soldiers from 
//the board.
//This program is meant to simulate this battle and to provide the
//attacker with the odds that he / she will win the entire battle.

//lv 1 students should calculate the average remaining soldiers after the conclusion 
//battle and account for reducing number of dice if there are less 
//than 3 soldiers engaging in the skirmish on either side.
//
//Specifications / Notes:
//-Don’t use any global variables.
//- This program can only be optimized if various functions are used
//to do specific jobs, you shouldn’t have to copy paste much code.
//- All functions need to be declared in the beginning of the program
//with proper descriptions of what they’re supposed to do.
//- The attacker should see their percentage of winning the battle
//before he / she starts attacking and after each round of fighting.
//- The attacker can choose to stop the battle at any point.
//- The simulation should run 100, 000 times to reduce degree of error.

# include <iostream>
# include <time.h> // based on the specific time of running the program; imporves randomness of numbers

using namespace std;

//int* examplee(int input1, int* input2)
//{
//	int arr3[4];
//	return arr3;
//}
//
//cout << time(NULL);

// All functions and or subs
int skermishresults(int attackroll[3], int defendroll[2]); //compares the dice rolls; decides how many soldiers die / which side looses soldiers
void communicate(int* attackroll, int* defendroll); //writes out attacker/defender dice rolls
void order(int* attackroll, int* defendroll); //sorts attackers and defender rolls in order from biggest to smallest
void rolldice(int attackroll[3], int defendroll[2], int attackingarmy, int defendingarmy, int tempattackers, int tempdefenders); //function that gets attacker/defender dice rolls
double* simulation(int attackingarmy, int defendingarmy); //runs simulations of the battle


int main() //main flow of program
{
	srand(time(NULL));// based on the specific time of running the program; required for improved randomness
	int attackingarmy = 0, defendingarmy = 0; //definded variables of both armies; currently specified so user will change if their number doesnt work
	int attackroll[3]; int defendroll[2]; //defined size of how many rolls each side gets
	bool goagain = 0; bool keepattacking = 0; //switch variables for attacking and if the user wants to reset program
	int tempattackers = 0; int tempdefenders = 0; //used in simulation, but i need it defined in the main for roll dice function

	//introduction
	cout << "Welcome to Hasbro's Risk; a game of war.\n";
	cout << "You need an attacking army that will beat the defending army.\n";
	cout << "Beat the defending army, you win the battle.\n";
	cout << "Each battle will result in dice rolls that will decide the fate of up to 2 soldiers from either side.\n";
	cout << "Think you have what it takes?\n";
	system("pause");

	do { //do you want to attack again
		do {//get the army size; simple dummy proofing
			system("cls");
			// prompt user attacking army requirements
			cout << "In Risk, You must have an attacking army with atleast 2 soldiers.\n";
			cout << "(There must be 1 soldier defending your current territory and atleast 1 soldier to attack with.)\n";
			cout << "what is the attacking army size?";
			cin >> attackingarmy;
		} while (attackingarmy < 2);
		do { // prevent having an army of 0 or less
			system("cls");
			// prompt user attacking army requirements
			cout << "You must have a defending army with atleat 1 soldier.\n";
			cout << "(There must be 1 soldier to defend a territory.)\n";
			cout << "what is the defending army size?";
			cin >> defendingarmy;
		} while (defendingarmy < 1);
		system("cls");

		cout << "Your odds are nearly ";//output odds of winning
		cout << simulation(attackingarmy, defendingarmy)[0]; //run the simulation(attackarmy, defendarmy)
		cout << "% chance to win.\n";
		cout << "Average remaining attacking soldiers for wins: "; // outpput the average # of soldiers you had when u won
		cout << simulation(attackingarmy, defendingarmy)[1] << endl;

		int attack;
		cout << "Do you want to attack? (Enter 0 to attack, anything else to retreat.)";//ask if they want to attack
		cin >> attack; // variable im using to compare for dumby proofing
		if (attack != 0)
			keepattacking = 1; //any numerical inpput not 0 will be turned to 1; quit 

		while (attackingarmy > 1 && !keepattacking && defendingarmy > 0) { // keeps allowing skirmishes untill it is decided thata side wins or the attackers retreat
			rolldice(attackroll, defendroll, attackingarmy, defendingarmy, tempattackers, tempdefenders); // add in lv 1 specs here; limit atker's / defenders rolls

			communicate(attackroll, defendroll); // call to function (or is it a sub..?); tell user the odds and average # of soldiers

			int outcome = skermishresults(attackroll, defendroll); 
			if (outcome == 0) // 0 = attacker won both dice rolls
				attackingarmy -= 2; //attackers lost 2 soldiers
			else if (outcome == 1) // 1 = both sides won 1 dice roll
			{
				attackingarmy--; // take away 1 soldier from each side
				defendingarmy--;
			}
			else if (outcome == 2) //defender won both dice rolls
				defendingarmy -= 2; //defence lost 2 soldiers
			//scenarios of 1 soldier attacking on a side
			else if (outcome == 3) // 2 remaining attackers on the army; reduce by 1
				defendingarmy--; //loose 1
			else //if (outcome == 4) // 1 remaining defender beat an attacker
				attackingarmy--; //loose 1

			cout << "Soldiers in the attacking army: ";//update armies
			cout << attackingarmy << endl;
			cout << "Soldiers in the defending army: ";
			cout << defendingarmy << endl;

			if (defendingarmy <= 0) // checks status of the attack; attackers won
			{
				cout << "You have defeated the enemy. You win!\n";
				break; // leave the while loop when the victor is decided
			}
			else if (attackingarmy <= 1) // defenders won
			{
				cout << "The defending army has successfully held their territory. You lost.\n";
				break;// leave the while loop when the victor is decided
			}

			//communicate to the user
			cout << "Your odds are nearly ";//output odds of winning
			cout << simulation(attackingarmy, defendingarmy)[0]; //run the simulation(attackarmy, defendarmy)
			cout << "% chance to win.\n";
			cout << "Average remaining attacking soldiers for wins: ";
			cout << simulation(attackingarmy, defendingarmy)[1] << endl;
			int attack;
			cout << "Do you want to attack? (Enter 0 to attack, anything else to retreat.)";//ask if they want to attack
			cin >> attack; // variable im using to compare for dumby proofing
			if (attack != 0)
				keepattacking = 1;
		}
		int play;
		cout << "Do you want to go again?" << endl; //ask if they want to attack again
		cout << "Press 0 to go again, Enter anything else to end the program.\n";
		cin >> play; // variable im using to compare for dumby proofing

		if (play != 0) // convert any number not 0 to 1; quit
			goagain = 1;

	} while (!goagain);	//for each battle

	return 0; // end the program
}


int skermishresults(int attackroll[3], int defendroll[2]) //decides which side's soldier dies
{
	int killcount = 0; /// keeps track of who dies, and how many people dies on each side
	int soldiersfighting = 2; // 2 unless specified 1; 2 where 2 soldiers on both sides are fighting; tells the program that only 1 soldier fights

	if (attackroll[1] == 0 || defendroll[1] == 0) //checking if either rolls are zero, if they are, then prevent the death
	{
		soldiersfighting = 1;
	}
	if (soldiersfighting == 2) // WHEN 2 SOLDIERS FOMR EACH SIDE ARE FIGHTING
	{
		if (attackroll[0] > defendroll[0]) // if the attackers won roll 1
			killcount++;
		if (attackroll[1] > defendroll[1]) // if the attackers won roll 2
			killcount++;
	}
	else //soldiersfighting = 1; when only 1 soldier from a side is fighting
	{
		if (attackroll[0] > defendroll[0]) // attacker finishes off the defending force
			killcount = 3; // 3rd scenario, attackers wipe out defending army
		else
			killcount = 4; //defender finished off the invadind force; leaving the attacking army with 1 person on defence aka invasion force of 0
		//using previous 'outcome' since it is not being updated; why even when dicerolls say otherwise
	}

	return killcount; // = outcome
}

void communicate(int* attackroll, int* defendroll) //writes out attacker/defender dice rolls
{
	cout << "attack rolls: " << endl; // output attacker's rolls
	for (int i = 0; i < 3; i++)
		if (attackroll[i] != 0) // doesnt write the roll if it doesnt exist; aka = 0
			cout << attackroll[i] << endl;

	cout << "defend rolls: " << endl; // output defender's rolls
	for (int i = 0; i < 2; i++)
	{
		if (defendroll[i] != 0) // doesnt write the roll if it doesnt exist; aka = 0
			cout << defendroll[i] << endl;
	}

}

void order(int* attackroll, int* defendroll)
{
	//sorting attacker rolls
	int biggest, middle, small; //variables for sorting, defining the order of numbers; covers all scenarios
	if (attackroll[0] >= attackroll[1] && attackroll[0] >= attackroll[2]) //should the first roll be the biggest
	{
		biggest = attackroll[0];
		if (attackroll[1] > attackroll[2]) // decides which of the other rolls are bigger than the other
		{
			middle = attackroll[1];
			small = attackroll[2];
		}
		else
		{
			middle = attackroll[2];
			small = attackroll[1];
		}
	}
	else if (attackroll[1] >= attackroll[0] && attackroll[1] >= attackroll[2]) //should the second roll be the biggest
	{
		biggest = attackroll[1];
		if (attackroll[0] > attackroll[2])// decides which of the other rolls are bigger than the other
		{
			middle = attackroll[0];
			small = attackroll[2];
		}
		else
		{
			middle = attackroll[2];
			small = attackroll[0];
		}
	}
	else if (attackroll[2] >= attackroll[0] && attackroll[2] >= attackroll[1]) //should the last roll be the biggest
	{
		biggest = attackroll[2];
		if (attackroll[0] > attackroll[2])// decides which of the other rolls are bigger than the other
		{
			middle = attackroll[0];
			small = attackroll[2];
		}
		else
		{
			middle = attackroll[2];
			small = attackroll[0];
		}
	}
	//sorted variables; biggest to smallest
	attackroll[0] = biggest;
	attackroll[1] = middle;
	attackroll[2] = small;

	//sort defender rolls
	if (defendroll[1] > defendroll[0]) //swap the rolls if the second is bigger than the first roll; biggest to smallest
	{
		int temp1 = defendroll[0];
		defendroll[0] = defendroll[1];
		defendroll[1] = defendroll[0];
	} // if this doesnt happen, then rolls are already sorted from biggest to smallest

}

void rolldice(int attackroll[3], int defendroll[2], int attackingarmy, int defendingarmy, int tempattackers, int tempdefenders)
{
	//attacker rolls
	// if the attacking army is more or equal to 3; aka 3 rolls
	attackroll[0] = rand() % 6 + 1;
	attackroll[1] = rand() % 6 + 1;
	attackroll[2] = rand() % 6 + 1;
	if (attackingarmy == 3 || tempattackers == 3)// if the attacking army is 3; so 2 rolls; 1 soldier at defending territory
		attackroll[2] = 0;// all rolls that are zero are excluded from the comparison in skermish results
	else if (attackingarmy == 2 || tempattackers == 2)// if the attacking army is 2; so 2 rolls; any less the attack is already lost
	{
		attackroll[1] = 0;// all rolls that are zero are excluded from the comparison in skermish results
		attackroll[2] = 0;// all rolls that are zero are excluded from the comparison in skermish results
	}

	//defender rolls
	//more or equal to 2 rolls; aka 2 rolls
	defendroll[0] = rand() % 6 + 1;
	defendroll[1] = rand() % 6 + 1;
	if (defendingarmy == 1 || tempdefenders == 1) // only 1 defender, only 1 roll
		defendroll[1] = 0;// all rolls that are zero are excluded from the comparison in skermish results

	order(attackroll, defendroll);//sort the rolls
}

double* simulation(int attackingarmy, int defendingarmy)
//follows the same logic as playing normally; however, creates a simulation to produce the odds of winning currently
{
	double info[2]; // array i'll use for storing the info i'll return back

	double wins = 0; //counts the wins in the simulation
	double averageatk = 0; // tracks the average # of soldiers you have when you win
	double percentodds = 0; // variable for the percent chance to win
	int attackroll[3]; int defendroll[2]; //generate the address locations for rolls

	for (int i = 0; i < 100000; i++) //run the simulation multiple times 
	{
		int tempattackers = attackingarmy; // temp variable for the amount of soldiers currently for attackers; resets after every runthrough
		int tempdefenders = defendingarmy; // temp variable for the amount of soldiers currently for defenders; resets after every runthrough

		while (tempattackers > 1 && tempdefenders > 0) {
			rolldice(attackroll, defendroll, attackingarmy, defendingarmy, tempattackers, tempdefenders); // add in lv 1 specs here; limit atker's / defenders rolls

			int outcome = skermishresults(attackroll, defendroll); // finding out what happened in the dice roll comparison and update the armies accordingly
			if (outcome == 0) // 0 = attacker won both dice rolls
				tempattackers -= 2;
			else if (outcome == 1) // 1 = both sides won 1 dice roll
			{
				tempattackers--; //take a soldier away form each side
				tempdefenders--;
			}
			else if (outcome == 2) //defender won both dice rolls
				tempdefenders -= 2;
			//scenarios of 1 soldier attacking on a side
			else if (outcome == 3) // 2 remaining attackers on the army; reduce by 1
				tempdefenders--;
			else //if (outcome == 4) // 1 remaining defender beat an attacker
				tempattackers--;
		}

		if (tempdefenders <= 0) // checks status of the attacker wins
		{
			averageatk = averageatk + tempattackers; // adds the current amount with the amount of the newest win
			wins++;
		}
	}

	percentodds = 1.0 * wins / 1000; //calclate the percent chance to win the entire battle
	percentodds = 1.0 * round(percentodds * 100) / 100; // rounding the percent to the next 2 decimal places

	averageatk = averageatk / wins; // calcs the average

	averageatk = 1.0 * wins / 10000; // rounds the average to the next 2 decimal places
	averageatk = 1.0 * round(averageatk * 100) / 100;

	info[0] = percentodds; // address 0 away is infor regarding the odds of winning
	info[1] = averageatk; // address 1 away is info regarding the average amount of soldiers you'll have when you win

	return info; //return the percent odds and the average
}



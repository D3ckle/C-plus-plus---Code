//Project Name : Hangman
//Donald Alan Newandee
//Due: thursday 26th 2020
//
//Program Description :
//The project is meant to simulate the classic game, hangman. (Done)
//The program should generate 2 and 3 word phrases for the user (Done)
//to guess from a bank of 12 (you can do more if you want). (Done)
//Once the word is generated, the player should see either 2 or 3 rows of underscores,  (Done)
//representing the unknown word. (Done)
//Every turn the user is able to either solve the puzzle or guess a letter. (Done)
//The screen should be updated with number of turns left and the words with (Done)
//all correct letters filled in.  (Done)
//Appropriate messages should be shown with correct / incorrect guesses, and  (Done)
//game won / loss.It should be replayable.  (Done)
//There should be an appropriate animation that’s created based on the number of  (Done)
//incorrect guesses. (Done)
//
//L1 students should also check the “solve guess” to see if it (Done)
//matches the letters already guessed correctly.If not then let (Done)
//them know and have the users repick their choice.  (Done)
//if there’s only vowels left to be chosen, you need to only allow (Done)
//for the user to solve for the puzzle. (Done)
//
//Specifications / Notes:
//-The player has 6 incorrect attempts for letters. (Done)
//- Create functions for the following. (Done)
//o Display updated string with guesses  (Done)
//o Update “guess string” with “guess characters”  (Done)
//o Generate words (Done)
//
//- Guessing the word incorrectly ends the game  (Done)
//- A total score should be kept track of, which is attempts left * 10. (Done)
//- Incorrect letters should be on the screen (Done)
//- Basic dummy proofing should check for duplicate letters being guessed  (Done)
//and a guess that is not the same size as the phrase.  (Done)
//- The user should be able to enter letters as uppercase or lowercase  (Done)

#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<windows.h>

using namespace std;

//formating / adding color
void setcolor(int color) { // changes the color of the foreground and backgronud text
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}
void changewindow(int width, int height) { //resizes the window tab based on input
	HWND console = GetConsoleWindow();
	RECT r; // create a rectanlge, r
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE); //adjusts the size of the window
}

//functions
bool usinglettersguessed(string guess, string& guessword) { //makes sure the user uses their letters that they know is in the guess word
	guess[0] = toupper(guess[0]); //first letter is uppercase, change first letter to upper case if its not
	for (int i = 0; i < guess.size(); i++) { // checks the entire guess
		if (guessword[i] != '-' && guess[i] != guessword[i] && guess[i] != '-')  //compares letters that have been revealed and sees if letters guessed are used							   
			return false; // there is a non matching letter from the guess word to the guess for the secret word
	}
	return true; // letters revealed coincide with the phrase being guessed
}
void displayhangman(int incorrectguesscounter) { // displays the hang man for each time the user guess a wrong letter
	cout << "   _________________ \n";// stays the same
	cout << "   |               | \n";// stays the same
	//line 1
	if (incorrectguesscounter >= 1) // only adds a head for first error
		cout << "   |               0 \n";
	else
		cout << "   |                 \n";
	//line 2
	if (incorrectguesscounter >= 4)
		cout << "   |              -|-\n"; // adds a body and arms based on wrong guesses
	else if (incorrectguesscounter >= 3)
		cout << "   |              -| \n";
	else if (incorrectguesscounter >= 2)
		cout << "   |               | \n";
	else
		cout << "   |                 \n";
	//line 3
	if (incorrectguesscounter >= 6)
		cout << "   |              // \n";// adds legs for the final 2 wrong guesses
	else if (incorrectguesscounter >= 5)
		cout << "   |              /  \n";
	else
		cout << "   |                 \n";
	cout << "   |                 \n"; //stays the same
	cout << "___|___              \n";//stays the same
	cout << endl << endl; //line sperator
}
string generatesecretword(string& v) { // generates the secret word
	int randnum = rand() % 12; //choose a random preset phrase from the word bank below

//secret word bank
	if (randnum == 1)
		v = "Hello world!";
	else if (randnum == 2)
		v = "School is out.";
	else if (randnum == 3)
		v = "Cat and mouse.";
	else if (randnum == 4)
		v = "Wake up for school!";
	else if (randnum == 5)
		v = "We are home for two weeks.";
	else if (randnum == 6)
		v = "Do not touch anyone.";
	else if (randnum == 7)
		v = "Learning with ipads.";
	else if (randnum == 8)
		v = "Stay safe.";
	else if (randnum == 9)
		v = "We need a vaccine.";
	else if (randnum == 10)
		v = "We're in a pandemic.";
	else if (randnum == 11)
		v = "Coronavirus is dangerous.";
	else
		v = "How was your day?";
	return v; // return one of the 12 above phrases
}
string setguessword(string& secret, string& guess) { //creates a secodn string based on the secret word but with '-' instead of letters

	guess = secret; // duplicates the secret word to the soon ot be modified string

	for (int i = 0; i < secret.length() - 1; i++) { //scans entire string
		//scans the entire secret word for the characters in it
		if (secret[i] != '!' && secret[i] != '.' && secret[i] != ' ' && secret[i] != '\'') //maintains punctuation
			guess[i] = '-';
		else
			guess[i] = secret[i]; // replaces all letters with '-'
	}
	return guess; // return the modified secretword for the user to now gues what it is
}
bool updateguessword(string guess, string& guessword, string secretword) { // updates guessword but also tells if the guess is used or not used in secret word
	//you can choose to make this a bool and return false if it is something invalid
	//you can make this an integer and return how many letters are in the secret word
	bool used = false; // bool variable that tells if there is a letter guess to be right or wrong
	for (int i = 0; i < secretword.length(); i++) { // scans the entire secret word
		char temp = toupper(guess[0]);
		if (i == 0 && temp == secretword[i]) {// only appplies to the first letter: all phrases similar in that way
			guessword[i] = temp; // adds in the uppercase varient
			used = true;// function is now true that a letter has been guess right and is used in secret word
		}
		else if (secretword[i] == guess[0]) { // checks all characters; lowercase input
			guessword[i] = guess[0]; // changes the letter's location to show the revealed letter
			used = true; // function is now true that a letter has been guess right and is used in secret word
		}
	}
	if (used) // returns true or false based on parallel bool variable: used
		return true; // right guess
	else
		return false; // wrong guess
}
void usedletters(string guess, string& lettersused) { // creates a string of all the letters that have been used so far
	lettersused = lettersused + guess + ","; // adds the current guessed letter to the string lettersused
}
bool repeatingletters(string guess, string& lettersused, string& incorrectlist) { // allows user to pick again if user repeats a letter they already used before
	guess[0] = tolower(guess[0]); // convert to lowercase
	//check letters guessed that were either right or wrong
	for (int i = 0; i < incorrectlist.size(); i++) { //checks for a letter that has been used already stored in the incorrectlist string
		if (guess[0] == incorrectlist[i]) // if it is already used, it is repeated
			return true;
	}
	for (int i = 0; i < lettersused.size(); i++) { //checks for a letter that has been used already stored in the lettersused string
		if (guess[0] == lettersused[i])// if it is already used, it is repeated
			return true;
	}
	return false; // no letters are repeated, go ahead with the guess
}
void addincorrect(string guess, string& incorrectlist) { // updates the list of characters that are invalid
	incorrectlist = incorrectlist + guess + ","; // add the letter guessed to the incorreect list of characters
}
bool guessentireword(string guess, string& guessword, string secretword, string& lettersused, string& incorrectlist) { // function that will tell if the user guesses the word right or wrong
	do { // dummy proofing
		system("cls");
		//tell users important info they may need
		cout << guessword << endl << endl; // restates the guess word
		if (lettersused.size() > 0) {
			cout << "letters used:" << endl; // list of all letters guessed so far
			cout << lettersused << endl << endl;
		}
		if (incorrectlist.size() > 0) {
			cout << "Wrong guess letters:" << endl; // list of guessed letters that are wrong
			cout << incorrectlist << endl << endl;
		}

		//prompt instructions
		cout << "What do you think the entire phrase is?\n";
		cout << "Guess right, you win, but guess wrong, you lose.\n";
		cout << "(Make sure to include the spaces and the punctuation, excluding capitolization)\n";
		getline(cin, guess);
		cout << endl;

		// error communication
		if (guess.size() != secretword.size()) {
			cout << "That doesn't line up with the dashes and or punctuation of the secret word." << endl;
			system("pause");
		}
		else if (!usinglettersguessed(guess, guessword)) {
			cout << "What you guessed doesn't line up with what you know about the secret word.\n";
			cout << "Use the letters you know and fill in the dashed spots you don't know.\n";
			system("pause");
		}
	} while (guess.size() != secretword.size() || !usinglettersguessed(guess, guessword));

	for (int i = 0; i < guess.size(); i++) { // corrects the upper/lowercasing of letters
		if (i == 0) // uppercase first letter
			guess[i] = toupper(guess[i]);
		else  // lowercase for the rest of the letters
			guess[i] = tolower(guess[i]);
	}

	if (guess == secretword) // if the guess is the same with the secretword
		return true;
	else
		return false;
}
bool onlyvowelsleft(string& guessword, string secretword) { //checks if there are only vowels left
	bool vowels = true; // temp variable that dicatates whether or not there are ONLY vowels
	for (int i = 0; i < secretword.size(); i++) { //looks for the '-' spots that are left
		if (guessword[i] == '-') {//if all of the remainding address locations are vowels, return true; doesn't check puncutation
			if (secretword[i] != 'a' && secretword[i] != 'e' && secretword[i] != 'i' && secretword[i] != 'o' && secretword[i] != 'u' && secretword[i] != 'y' && secretword[i] != 'A' && secretword[i] != 'E' && secretword[i] != 'I' && secretword[i] != 'O' && secretword[i] != 'U' && secretword[i] != 'Y') {
				vowels = false;
				break; // break out at the first instance of a non-vowel letter
			}
		}
	}
	if (!vowels) {//there are letters other than vowels
		return false;
	}
	else {//only vowels are left
		system("cls");
		cout << "There are only Vowels left in the secret phrase.\n";
		cout << "You must now try and guess the rest of the phrase.\n";
		system("pause");
		return true;
	}
}


int main() { // main function

	srand(time(NULL)); // time randomizer
	//setting window perameters
	int width = 670;
	int height = 450;
	changewindow(width, height);

	int color; // defining color int for the color of the text

	//welcome screen
	cout << "Welcome to Hangman!" << endl << endl;
	cout << "The goal of Hangman is to guess the word before the man gets hanged.\n";
	cout << "You have 6 chances to guess a lettert wrong before you loose.\n";
	cout << "At any point, you can try and guess the entire phrase however,\n";
	cout << "guess wrong, you lose the entire game.\n";
	cout << "if the remaining letters are vowels, you must guess the entire phrase.\n";
	cout << "you have also have 12 turns before you must guess the entire phrase.\n";
	cout << "Think you can win?\n";
	system("pause");
	bool play = true;
	int allowednumofguesses = 6; // variable for how many times the user can guess wrong beofre they loose

	do {//loops an entire game of hangman
		string secretword; // dont show to user; string that is the word the user is trying to guess
		string guessword; //the dashes (-) that hide the secret word; same length and puntuation
		string lettersused; //string that records all the letters that have been used so far
		string incorrectlist; // string of letters user guessed but are not in the secret word
		string guess; // temp string variable that is the guess the user makes to figure out the secret word
		int turncounter = 0; // counts how many turns the user has made so far
		int maximturns = 12; // maximum # of turns allowed before user must guess the full phrase
		bool retry = false; // bool variable for if there is a problem, the user will input something different for guess
		int incorrectguesscounter = 0; // tracks the amount of time player guesses wrong;

		generatesecretword(secretword);
		setguessword(secretword, guessword);

		//game starts
		while (guessword != secretword && incorrectguesscounter < allowednumofguesses) { // play until the user wins or looses

			do {	//ask for a guess; single letter or a whole word

				system("cls");

				if (onlyvowelsleft(guessword, secretword) || turncounter == maximturns) { // forced to guess
					if (turncounter == maximturns) { // tell the user the situation
						system("cls");
						cout << "You ran out of turns.\n";
						cout << "You must now try and guess the rest of the phrase.\n";
						system("pause");
					}
					if (guessentireword(guess, guessword, secretword, lettersused, incorrectlist)) {// they guessed the word
						guessword = secretword; // instant win
						break;
					}
					else {// they guessed the word wrong
						incorrectguesscounter = allowednumofguesses; // instant loss
						break;
					}
				}
				else {
					do { // loop for dummy proofing
						system("cls");
						//communicate to user game info
						displayhangman(incorrectguesscounter);

						cout << guessword << endl << endl;	// guessword
						cout << "Turns left before you must guess the phrase:   ";
						cout << maximturns - turncounter << endl; // 
						cout << "Wrong Guesses Left:   ";
						cout << allowednumofguesses - incorrectguesscounter << endl; // # of guesses left
						if (lettersused.size() > 0) { // tell user once there is something to tell
							cout << "letters used:" << endl; // list of all letters guessed so far
							cout << lettersused << endl << endl;
						}
						if (incorrectlist.size() > 0) { // tell user once there is something to tell
							cout << "Wrong guess letters:" << endl; // list of guessed letters that are wrong
							cout << incorrectlist << endl << endl;
						}
						retry = false; // checks for an error and allows oppertunity to fix error
						cout << "What is your guess? (Enter 1 to guess the entire phrase)\n";
						getline(cin, guess);

						//dummy proofing communication
						if (guess.size() == 0) { // entered nothing / not a letter
							retry = true;
							cout << "Please enter in a letter from A to Z." << endl << endl;
						}
						if (guess.size() != 1) { // user doesnt use 1 character
							retry = true;
							cout << "Please use 1 character at a time.\n";
						}
						if (repeatingletters(guess, lettersused, incorrectlist)) {
							retry = true;
							cout << "Please use a letter you haven't guessed yet." << endl << endl;
						}
						if (retry) // allow user to ee problems before they get removed
							system("pause");
					} while (retry);

					if ((guess[0] == '1')) { // user tries to guess the entire phrase
						if (guessentireword(guess, guessword, secretword, lettersused, incorrectlist)) {// they guessed the word
							guessword = secretword; // instant win
						}
						else {// they guessed the word wrong
							incorrectguesscounter = allowednumofguesses; // instant loss
						}
					}
				}
				guess = tolower(guess[0]); // turns to the lowercase immediately if uppercase

			} while (guess.size() == 0); // || guess == '\n' or enter

			if (guessword != secretword && !updateguessword(guess, guessword, secretword)) { // a single letter guess was wrong
				addincorrect(guess, incorrectlist);
				incorrectguesscounter++;
			}
			else // single letter guess was right
				usedletters(guess, lettersused);
			turncounter++; // 1 turn has been completed
		}
		system("cls");
		// end of communication
		if (incorrectguesscounter >= allowednumofguesses) {
			color = 12; // red text
			setcolor(color);
			displayhangman(incorrectguesscounter); // display the dead man
			incorrectguesscounter = allowednumofguesses;
			cout << "Oh no! You Lose.\n";
		}
		else {
			color = 10; // green text
			setcolor(color);
			displayhangman(incorrectguesscounter); // display the dead man
			cout << "Yay! You win.\n";
		}
		color = 15; // reset color to white
		setcolor(color);
		cout << endl << endl;
		cout << "The Secret phrase was: "; //tell user the secret word
		cout << secretword << endl << endl;

		cout << "Best Possible Score:  ";
		cout << allowednumofguesses * 10 << endl;
		cout << "Your Score:    ";//communicate player's score
		cout << (allowednumofguesses - incorrectguesscounter) * 10 << endl << endl; // tells the user their score

		//replayability; ask if the user wants to play again
		cout << "Do you want to play again? Enter 1 to play again or anything else to quit.\n";
		string keeppplaying;
		getline(cin, keeppplaying);
		if (keeppplaying[0] == '1') //&& keeppplaying.size() == 1)
			play = true;
		else
			break;
		system("cls");

	} while (play); //loops an entire game of hangman
	cout << "Thank you for playing!\n";
	system("pause");
	return 0;
}
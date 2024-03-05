#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<cmath>
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
		setcolor(15); // returns the color back ot normal black bg on white text
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

int main() {

vector<setcard> puzzle(12);
puzzle[0].set(0, 3, 1, '*');
puzzle[1].set(4, 1, 1, '*');
puzzle[2].set(0, 3, 2, '*');
puzzle[3].set(4, 1, 3, '*');
puzzle[4].set(8, 3, 2, '@');
puzzle[5].set(8, 2, 1, '*');
puzzle[6].set(0, 3, 3, '*');
puzzle[7].set(4, 3, 2, '$');
puzzle[8].set(8, 1, 2, '$');
puzzle[9].set(0, 2, 1, '$');
puzzle[10].set(4, 1, 3, '$');
puzzle[11].set(0, 1, 2, '@');

for (int i = 0; i < puzzle.size(); i++) {
	cout << i;
	puzzle[i].display();
	cout << "\t";
	if (i % 4 == 3)
		cout << endl;
}
if (puzzle[0].isaset(puzzle[2], puzzle[6]))
cout << "It's a set \n";
else
cout << "It's not a set \n";

if (puzzle[0].isaset(puzzle[1], puzzle[5]))
cout << "It's a set \n";
else
cout << "It's not a set \n";

if (puzzle[2].isaset(puzzle[4], puzzle[7]))
cout << "It's a set \n";
else
cout << "It's not a set \n";
if (puzzle[6].isaset(puzzle[9], puzzle[11]))
cout << "It's a set \n";
else
cout << "It's not a set \n";
if (puzzle[2].isaset(puzzle[3], puzzle[5]))
cout << "It's a set \n";
else
cout << "It's not a set \n";
if (puzzle[3].isaset(puzzle[4], puzzle[9]))
cout << "It's a set \n";
else
cout << "It's not a set \n";

	system("pause");
	return 0;
}



//Donald Newandee




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

class quadratic {
private:
	int a, b, c;
public:
	void seta(int A) { a = A; }
	void setb(int B) { b = B; }
	void setc(int C) { c = C; }

	quadratic(int A, int B, int C) { a = A; b = B; c = C; }
	quadratic() { a = 0; b = 0; c = 0; }
	int geta() { return a; }
	int getb() { return b; }
	int getc() { return c; }

	string display() {
		string str = to_string(a) + "x^2";
		if (b >= 0)
			str += "+";
		str += to_string(b);
		str += "x";
		if (c >= 0)
			str += "+";
		str += to_string(c);
		return str;
	}
	quadratic operator+(quadratic quad2) {

		quadratic result;
		result.a = a + quad2.a;
		result.b = b + quad2.b;
		result.c = c + quad2.c;
		return result;
	}
	int operator ++ () { // the discriminant in quadratic formula
		return b * b - 4 * a * c;
	}


	vector<int> foil(quadratic quad2) { // 'foil' -ing 2 quadratics and adding the sum of their components together into a vector
		vector<int> vquartic;
		//e.g. : (2x^2 -3x + 4)*(x^2 - 0x + 3) = 2x^4 - 3x^3 + 10x^2 - 9x + 12
		int x4, x3, x2, x, constant;
		x4 = a * quad2.geta();
		x3 = (a*quad2.getb()) + (b*quad2.geta());
		x2 = a*quad2.getc() + (b*quad2.getb()) + (c* quad2.geta());
		x = (b*quad2.getc()) + (c* quad2.getb());
		constant = c * quad2.getc();

		vquartic.push_back(x4); // 4th degree
		vquartic.push_back(x3);// 3th degree
		vquartic.push_back(x2);// 2th degree
		vquartic.push_back(x);// 1st degree
		vquartic.push_back(constant);// constant
		return vquartic;
	}
};

string displayfoil(vector<int> vquartic) {
	//to_string
	string quartic;
	quartic += to_string(vquartic[0]) + "x^4";
	if (vquartic[1] >= 0)
		quartic += "+";
	quartic += to_string(vquartic[1]) + "x^3";
	if (vquartic[2] >= 0)
		quartic += "+";
	quartic += to_string(vquartic[2]) + "x^2";
	if (vquartic[3] >= 0)
		quartic += "+";
	quartic += to_string(vquartic[3]) + "x";
	if (vquartic[4] >= 0)
		quartic += "+";
	quartic += to_string(vquartic[4]);
	return quartic;
}

int main() {
	//(2x ^ 2 - 3x + 4)* (x ^ 2 - 0x + 3) = 2x ^ 4 - 3x ^ 3 + 10x ^ 2 - 9x + 12


	quadratic quad1(2, -3, 4);
	cout << quad1.display() << endl;
	quadratic quad2(1, 0, 3);
	cout << quad2.display() << endl;

	//cout << ++quad1 << endl;
 	//quadratic quad3 = ++quad1;

	vector<int> quartic = quad1.foil(quad2);
	for (int i = 0; i < quartic.size(); i++) {
		cout << i << ") " << quartic[i] << endl;
	}

	cout << displayfoil(quartic) << endl;
	system("pause");
	return 0;
}
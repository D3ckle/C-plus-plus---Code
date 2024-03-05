//perimeter function
//Donald Newandee


//Add the "addFract" and subtractFract function to the class (done)
//Add another set function that accepts a string of the form "3/5" which then  (done)
//you'll need to convert into 3 and 5 for the num and den (done)
//Add getDouble() function to the class that returns a decimal equivalent of the fraction (done)
//L1 Students
//Add a function that will return the least common multiple between the denominators of 2 fractions. (done)

using namespace std;

#include<iostream>
#include <vector>
#include<string>
#include<cmath>
#include<math.h>

class point {
private:
	double x, y; // VARIABLES FOR X AND Y COORDS
public:
	double getx() { return x; } // return only the x cord
	double gety() { return y; } // return only the y cord
	void set(double newx, double newy) { x = newx, y = newy; } // set x and y cords
	double distancefromorigin() { // function to find distance to point (0,0)
		return sqrt(x * x + y * y);
	}
};

class fraction {
private:
	int numerator; int denominator;
public:
	void set(int n, int d) { numerator = n, denominator = d; }
	int getnum() { return numerator; }
	int getden() { return denominator; }
	fraction multfrac(fraction f) {
		//fraction c = a.multfraction(b)
		int newnum = numerator * f.getnum();
		int newden = denominator * f.getden();
		fraction c;
		c.set(newnum, newden);
		return c;
	}
	string display() {
		string str = to_string(numerator) + "/" + to_string(denominator);
		return str;
	}
	fraction addfrac(fraction b) {
		//   3/5 1/2
		fraction newfrac;
		if (denominator != b.getden()) {// if the denominators don't match
			int commonden = denominator * b.getden();
			int anum = numerator * b.getden();
			int bnum = b.getnum() * denominator;
			newfrac.set(anum + bnum, commonden);
		}
		else { // denominators match
			newfrac.set(numerator + b.getnum(), denominator);
		}
		return newfrac;
	}
	fraction subtrfrac(fraction b) {
		//   3/5 1/2
		fraction newfrac;
		if (denominator != b.getden()) {// if the denominators don't match
			int commonden = denominator * b.getden();
			int anum = numerator * b.getden();
			int bnum = b.getnum() * denominator;
			newfrac.set(anum - bnum, commonden);
		}
		else { // denominators match
			newfrac.set(numerator - b.getnum(), denominator);
		}
		return newfrac;
	}
	double getdouble() { // converts our fraction to a double, decimal equivalent
		double doublequiv = (1.0 * numerator) / (1.0 * denominator);
		return doublequiv;
	}
	void stof(string str) {
		fraction f;
		int baraddress = 0;
		//cout << "size: "<< str.size() << endl;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '/') {
				baraddress = i;
				break;
			}
		}
		string numstr = str.substr(0, baraddress);
		int num = stoi(numstr);
		//cout << "num:" << numstr << endl;
		string denstr = str.substr(baraddress + 1, str.size() - baraddress);
		int den = stoi(denstr);
		//cout << "den:" << denstr << endl;
		numerator = num;
		denominator = den;
	}
};

int lcm(fraction a, fraction b) { // FUNCTION TO FIND THE LOWEST COMMON MULTIPLE OF 2 denominators
	int multiple = 0; // variable that will be the lcm
	bool found = false; // variable used to stop the do while loop

	if (a.getden() > b.getden()) // start counting at the higher denominator of the 2
		multiple = a.getden();
	else
		multiple = b.getden();

	do { // counts up until there is a number divisible by both numbers; first occurance is already the lcm
		double aremainder = multiple % a.getden();
		double bremainder = multiple % b.getden();
		if (aremainder == 0 && aremainder == bremainder) // remainder of 0 for both numbers being compared
			found = true;
		else
			multiple++; // add to the count if lcm is not found
	} while (!found);

	return multiple;
}

double distancebetweenpoints(point pt1, point pt2) { // finds distance between 2 points
	double step1 = pow((pt1.getx() - pt2.getx()), 2); // distance formula
	double step2 = pow((pt1.gety() - pt2.gety()), 2);

	return sqrt(step1 + step2);
}
double findperimeter(vector<point> plots, int& size) { // calc perimeter of a shape with all the points
	double perimeter = 0;
	for (int i = 0; i < size; i++) { // calc perimeter
		double length = 0;
		if (i == plots.size() - 1) { // compare last point to the first point; loops back to the first point to complete shape
			length = distancebetweenpoints(plots[i], plots[0]);
		}
		else {// compare the current to the next point
			length = distancebetweenpoints(plots[i], plots[i + 1]);
		}
		perimeter += length; // add together the entire sum of all the distances

	}
	return perimeter;
}

int main() {
	fraction a, b, c;

	a.set(3, 5); b.set(1, 2);
	c = a.multfrac(b);
	cout << c.getnum() << "/" << c.getden() << endl;
	cout << c.display() << endl;
	fraction d = a.addfrac(b);
	cout << a.display() << " + " << b.display() << " = " << d.getnum() << "/" << d.getden() << endl;
	fraction e = a.subtrfrac(b);
	cout << a.display() << " - " << b.display() << " = " << e.getnum() << "/" << e.getden() << endl;
	double decimal = c.getdouble();
	cout << c.display() << " = " << decimal << endl << endl;

	string str = c.display();
	fraction g;
	g.stof(str);
	cout << "the string " << str << " can be broken down into: " << endl;
	cout << "num: " << g.getnum() << endl;
	cout << "den: " << g.getden()  << endl;
	cout << "becuase i turned " << str << " into a fraction: " << g.display() << endl << endl;

	cout << "fractions used for lowest common multiple: " << endl;
	a.set(3, 4); b.set(1, 2);
	cout << a.display() << endl;
	cout << b.display() << endl << endl;
	int multiples = lcm(a, b);
	cout << "the lcm of " << a.getden() << " and " << b.getden() << " is " << multiples << endl << endl;


	system("pause");
	return 0;
}
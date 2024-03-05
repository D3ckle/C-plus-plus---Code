# include <iostream>
# include <string>
# include <vector>

using namespace std;

bool aretheyrelated(string& v1, string& v2) {// compares the 2 people's last name if they're the same


	//return false; // remove later


    // starting place of the last name
	int start1 = v1.find_last_of(" ");
	int start2 = v2.find_last_of(" ");

	if (start1 == 4294967295 || start2 == 4294967295) {
		cout << "that is only a first name. enter in a first and last name.\n";
		return false;
	}
	else {
	//getting the last names
	string last1 = v1.substr(start1, v1.size() - start1);
	string last2 = v2.substr(start2, v2.size() - start2);
	if (last1 == last2)	//compare the last names
		return true;
	else
		return false;
	}




}

int main() {
	string person1;	string person2; // string holders of the full name

	cout << "what is your name?\n"; // gets the first person
	getline(cin, person1);

	//cout << person1 << endl; // check
	//cout << person1.size() << endl;
	//cout << person1.find_last_of(" ") << endl; // tells me the address

	cout << "what is another person's name?\n"; // gets the second person
	getline(cin, person2);

	//cout << person2 << endl; //check
	//space2 = person2.find_last_of(" ");

	if (aretheyrelated(person1, person2)) // tell use if they are / arent related
		cout << "these 2 people are related.\n";
	else
		cout << "these 2 people are NOT related.\n";

	system("pause");
	return 0;
}



//lesson using strings;
//we can now use characters instead of just numbers

//int getyog(vector<string> students, int n) {
//
//	int location = students[n].find(",");
//	int endloc = students[n].find(";");
//	string yog = students[n].substr(location + 1, (endloc - location - 1));
//	return stoi(yog);
//}

//vector<string> students;
////for (int i = 0; i < 3; i++) { // 3 times
//
//cout << "what is your full name?:\n";
//string name;
////cin >> s; will only get the first name (up to the first space)
//getline(cin, name);
//cout << "What is your year of graduation?\n";
//string yog;
//getline(cin, yog); // cin for a legnth of letters AND spaces, includes the characters after it
//int yogint = stoi(yog); // stoi; string to integer; turning a string into an integer
//string student = name + "," + yog + ";";
//cout << student;
//students.push_back(student);
////cin >> student; // if you take in a string, the next line will be immedieatly 
//string x, y;
//cin >> x;
////cin.ignore();
//getline(cin, x);
//cout << x + "   " + y;



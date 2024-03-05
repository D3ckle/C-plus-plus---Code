//Project Name : Stock Analysis
//Donald Alan Newandee
//Final Project due: Monday April 20th, 2020; after spring break
//
//
//Program Description :
//This program should perform a variety of statistical analysis on a set of  (Done)
//stock data in the csv format taken from finance.yahoo.com. (Done)
//The user will provide the location of the data which the program should be able  (Done)
//to read in and analyze.  (Done)
//The program should be able to calculate :
//-the average closing price, (Done)
//-minimum and maximum stock price and the dates when they happened. (Done)
//- date range for longest streak of gains for the stock as well as the longest loss. (Done)
//- Largest trading day by Volume (Done)
//- the percentage change from Dec 31 st stock price close. (Done)
//
//The output file created will have all the details but make sure you provide  (Done)
//status updates in the console as well.  (Done)
//
//L1 programs should also include Quartiles 1, 2 and 3 (Done)
// as well as the standard deviation of the data (Done)
//total count of how many days it closed higher than it opened vs not. (Done)
//
//Specifications / Notes:
//-All variables should be local (Done)
//- The user should have the option to rerun the analysis as many (Done)
//times as they wish with different input files and outputfiles (Done)
//- You can assume the data will follow the standard finance.yahoo  (Done)
//format with a comma delimeter (Done)
//- Make sure to dummy check the user giving you a(n in?)correct file location (Done)
//- You will need to create multiple vectors to store the various parts (Done)
//of the data  (Done)
//- Ask the user to include the ticker so that you can include it in your output array (Done)
//- The output file should be very clear to the reader that answers all  (Done)
//the above criteria. (Done)

//libraries
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<math.h>

using namespace std; // i think if you place this before the libraries, it'll stop the cin / system error 


//example functions; not included in project
void alphabetize(vector<string>& v) { // rearranged lines in a string by alphabeticle order
	for (int i = 0; i < v.size() - 1; i++) {
		bool swap = false;
		for (int j = 0; j < v.size() - 1 - i; j++) {
			if (v[j].compare(v[j + 1]) > 0) { //swap
				swap = true;
				string temp;
				temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
		if (!swap) {
			break;
		}
	}
}
vector<string> readfromfile(ifstream& input, char delim) {
	string temp = "";
	vector<string> list;
	while (!input.eof()) {
		char c;
		input >> c;
		if (c != delim) {
			temp += c;
		}
		else { // == delim
			list.push_back(temp);
			temp = "";

		}
	}
	input.close();
	list.pop_back();
	return list;
}
string appearsmost(vector<string>& v) { // finds the name that apppears the most
	int mostcount = 0;
	string most = v[0];
	int tempcount = 0;

	for (int i = 1; i < v.size(); i++) { // check the entire vector of strings; already checked first name in the list
		if (v[i] == v[i - 1]) {
			tempcount++;
		}
		else { // stops appearing
			if (tempcount > mostcount) { // found a new mode
				most = v[i - 1];
				mostcount = tempcount;
			}
			tempcount = 0;
		}
	}
	return most;
}
string longestname(vector<string>& v) { // finds the longest name
	string longest = v[0];
	for (int i = 0; i < v.size(); i++) {
		if (v[i].size() > longest.size()) {
			longest = v[i];
		}
	}
	return longest;
}

//functions in project
vector<string> readfromfile(ifstream& input, char delim, int datanumber) { // reads all data and returns a piece of that data at a location
	vector<string> list; // vector of strings that holds the small peice of data to be returned
	string line; // temp string that holds 1 line in the file

	getline(input, line);
	if (datanumber == 7) { // finding the volume, just find the last comma and record what's after it
		while (!input.eof()) { // checks all the lines of the file and the last bit of info past the last comma
			getline(input, line); // gets the line
			int address = line.find_last_of(delim); // creates the address of the last comma
			string temp = line.substr(address + 1, line.length()); //record the data to the vector
			list.push_back(temp); //add to vector
		}
	}
	else {
		while (!input.eof()) { // finds the comma and records the info behind that comma

			getline(input, line); // gets a line of data from the file
			int commastart = -1;//tells the program where to start looking in the line; start
			int commaend = -1; //tells program end of info location, where to end recording the data; start
			int delimcount = 0; // how many commas seen, until hits the data number

			for (int i = 0; i < line.length(); i++) { // checks each character in the line
				if (line[i] == delim) { // counts the commas that appear
					commastart = commaend; // updates the start, the last end is the start of the next data point
					commaend = i; // updates the new end
					delimcount++; // add 1 to count
				}
				if (delimcount == datanumber) // if we found the info we are looking for
					break; // leave loop to record the data
			}
			string temp = line.substr(commastart + 1, commaend - commastart - 1); //record the data to the vector
			list.push_back(temp); //add to vector
		}
	}

	input.close(); // close input file so it can be used elsewhere
	return list; // return the vector of the data
}
double average(vector<double>& v) { //takes a vector of doubles and averages it
	double total = 0; // total sum of all the values
	double highest = v[0]; // highest close price; start
	double lowest = v[0]; // lowest close price

	for (int i = 0; i < v.size(); i++) {
		total += v[i]; // adds all close prices for the entire year up
	}
	double average = total / v.size(); //calc average
	//round
	average = average * 100;
	average = rint(average);
	average = average / 100;
	return average; // return average + highest + lowest close price
}
vector<string> longstreak(vector<double> prices, vector<string>& pricestr, vector<string> dates, bool increasing) {
	vector<string> output; // parallel vector of what the function will return: the dates and valeus of the streak
	output.push_back(dates[0]); output.push_back(dates[0]); output.push_back(dates[0]); output.push_back(dates[0]); // locatiosn of 4 info: values of streak and the dates

	int count = 0; int maxcount = 0; // counters for the streak; tracks the longest streak
	int i; // address location for the info
	for (i = 1; i < prices.size(); i++) { // checks the entire vector
		if (increasing && prices[i] >= prices[i - 1]) { // increases count if the conditions of the streak are met; value is higher than the value previous
			count++;
		}
		else if (!increasing && prices[i] <= prices[i - 1]) { // increases count if the conditions of the streak are met; value is lower than the value previous 
			count++;
		}
		else {
			if (count > maxcount) { // replace the temp longest streak for the new one if the new one is longer
				maxcount = count;
				output[0] = dates[i - count - 1]; // records the dates of the streak
				output[1] = dates[i - 1];
				output[2] = pricestr[i - count - 1]; // records the prices of the streak
				output[3] = pricestr[i - 1];
			}
			count = 0; // reset count once decided it is longer or shorter than the current longest streak
		}
	}

	if (count > maxcount) { // special case: the streak is continuously going up
		maxcount = count;
		output[0] = dates[i - count - 1];// records the dates of the streak
		output[1] = dates[i - 1];
		output[2] = pricestr[i - count - 1]; // records the prices of the streak
		output[3] = pricestr[i - 1];
	}
	return output; // return longest streak and dates of start and end of streak
}
int highest(vector<double> prices, vector<string>& pricestr, vector<string> dates) { // finds the price of the highest priced stock in the file
	double highest = 0; // temp variable: finds the highest value from the data set
	vector<string> max; // vector holding all info to be reported frpom function
	max.push_back(pricestr[0]); max.push_back(pricestr[0]); // create 2 locations, 0 = highest price, 1 = the date
	int address = 0;
	for (int i = 0; i < prices.size(); i++) { // check all the pirces from the file
		if (prices[i] > highest) { // if we found a new highest price
			highest = prices[i]; // highest temp variable update
			address = i;
			//max[0] = pricestr[i]; // update the vector
			//max[1] = dates[i];
		}
	}
	return address; // return highest value and the date of the value; address of said values
}
int lowest(vector<double> prices, vector<string>& pricestr, vector<string> dates) { // finds the price of the lowest priced stock in the file
	// same logic as 'highest' function but finding the lowest value
	double lowest = prices[0];
	vector<string> min;
	min.push_back(pricestr[0]); min.push_back(pricestr[0]); // create 2 locations, 0 = lowest price, 1 = the date
	int address = 0;
	for (int i = 0; i < prices.size(); i++) { // check all the pirces from the file
		if (prices[i] < lowest) { // if we found a new lowest price
			lowest = prices[i]; // lowest temp variable update
			address = i;
			//min[0] = pricestr[i]; // update the vector
			//min[1] = dates[i];
		}
	}
	return address; // return address of where the values are
}
vector <double> bubblesort(vector<double> v) { //bubble sort from least to greatest
	for (int i = 0; i < v.size() - 1; i++) { // filters through the entire data set
		bool swap = false; // variable that tells if a switch has been made in the inner for loop
		for (int j = 0; j < v.size() - 1 - i; j++) { // reruns through all the data to make sure all values go in order from lowest to highest
			if (v[j] > v[j + 1]) { //swap
				swap = true; // a switch has been made atleast once
				double temp = v[j]; // temporarily duplicates the value
				v[j] = v[j + 1]; // overides the old value
				v[j + 1] = temp; // re introduce the value duplicated
			}
		}
		if (!swap) { // if no switch has been made, then the data is already sorted even if there are still more rounds of the for loop to go.
			break;
		}
	}
	//for (int i = 0; i < v.size(); i++)  // write out sorted vector
	//	cout << i << ") " << v[i] << endl;

	return v; // return the sorted vector
}
vector <double> calcquartile(vector<double> prices) { // finds the quartiles values
	//quartile 1: bottom 0 - 25%
	//quartile 2: 25.0001 - 50%; up to the median
	//quartile 3: 50 - 75%; 
	// calculates the quartiles of a set fo data

	//sort the vector being used first; bubble sort
	vector <double> temp = bubblesort(prices);

	vector <double> quartiles;
	quartiles.push_back(temp[0]); // 3 addresses for each quartile
	quartiles.push_back(temp[0]);
	quartiles.push_back(temp[0]);

	//TO FIND 1 AND 3:
	//find 2, which is the median

	int number; int remainder; // 2 variables to track sizes
	number = temp.size(); // checking entire vector size
	remainder = number % 2;
	double medianaddress;
	//find 2, and take median of lowest to 2 to find 1, and highest to 2 for 3
	if (remainder == 0) { // if the size is even: ex. 10, 5 + 5
		medianaddress = number / 2;
		// find q 2
		quartiles[1] = temp[medianaddress]; // average of the 2 middle most values
	}
	else { // if the size is odd: ex. 11, 5 + 1 + 5
		medianaddress = (number / 2) - .5; // of the 2 median locations, decide to use the lower median value
		quartiles[1] = (temp[medianaddress] + temp[medianaddress + 1]) / 2; // averaging the values b/c of an odd number
	}

	//find q 1 with info of q 2
	remainder = number % 4; // if 1/4 of the size's remainder is whole

	if (remainder == 0) { // even: ex. 12, 6 + 6 = 3 + 3 | 3 + 3
		medianaddress = number / 4;
		quartiles[0] = temp[medianaddress];
		//find q 3
		medianaddress = number * (3 / 4);
		quartiles[2] = temp[medianaddress];
	}
	else { // odd: ex. 10, 5 + 5 = 2.5 + 2.5 | 2.5 + 2.5
		medianaddress = (number / 4) - .5;// of the 2 median locations, decide to use the lower median value
		quartiles[0] = ((temp[medianaddress] + temp[medianaddress + 1]) / 2);
		//find q 3
		medianaddress = (number * .75) - .5;// of the 2 median locations, decide to use the lower median value
		quartiles[2] = ((temp[medianaddress] + temp[medianaddress + 1]) / 2);// averaging the values b/c of an odd number
	}
	return quartiles; // return all info of the 3 quartiles (quartile 4 is simpple the highest number, already done in another function)
}
double stddevi(vector<double> prices, double average) { //creates the standard deviation from a vector of doubles
	double stdd = 0; // variable that will be the standard deviation
	double sum = 0; // variable taht will be the sum of all the values in the equation for standard deviation
	for (int i = 0; i < prices.size(); i++) { // for each value in the data set
		double temp = (prices[i] - average) * (prices[i] - average);
		sum += temp;
	}
	stdd = sqrt(sum / prices.size()); // final ppart of the equation
	return stdd;
}
double percentchange(vector<double> prices, vector<string>& pricestr, vector<string> dates) { // finds the percent change since the dec 31st close price
	double change = 0; // variable that will result in the final percent change since dec 31
	int address = 0; // variable that is the address of the value at dec 31
	for (int i = 0; i < prices.size(); i++) { // checks the entire data set for the line with dec 31; most recent
		string date = dates[i].substr(5, 5); // get the date of each day and find dec 31, the latest one
		//cout << date << endl;
		if (date == "12-31") {
			address = i; // records the address
		}
	}
	change = ((prices[prices.size() - 1] - prices[address]) / prices[address]) * 100; // equation for percent change
	return change; // return the percent changed since dec 31
}
vector <int> daybydaychange(vector<double> prices, vector<double> openingprice) {
	vector <int> increasedecrease;
	increasedecrease.push_back(1); increasedecrease.push_back(1); // 2 locations for info regarding days where it increased from the day before and days it decreased from the day before
	increasedecrease.push_back(1); // no change from the day before
	//0 = days increased
	//1 = days decreased
	int increase = 0; // variable tracking the days that the closed increased from the opening
	int decrease = 0;// variable tracking the days that the closed decreased from the opening
	int nochange = 0;// variable tracking the days that had no change from closed and opening
	for (int i = 0; i < prices.size(); i++) { // checks all the values in all the vectors
		if (prices[i] > openingprice[i]) // if the closing price was higher than opening
			increase++;
		else if (prices[i] < openingprice[i])// if the closing price was lower than opening
			decrease++;
		else // if the closing price  = opening price
			nochange++;
	}
	// update the vector that will be submitted 
	increasedecrease[0] = increase; // count of increasing days = address 0
	increasedecrease[1] = decrease;// count of decreasing days = address 1
	increasedecrease[2] = nochange;// count of unchanged days = address 2
	return increasedecrease;
}

int main() { // main function
	cout << "Stock Analysis Project" << endl; // introduction
	cout << "This Program will Analysis Files of stocks and provide useful information from the file." << endl;
	cout << "" << endl;
	system("pause");
	system("cls");

	bool useagain = true; // variable for dummy proofing: make sure the file can be read by the program
	do {
		bool useablefile = false; // bool variable for dummy proofing
		string stockname; // string that is the name of the file being used
		do { // dummy proofing
			//inputfile
			cout << "What is the ticker?" << endl;
			getline(cin, stockname);
			//stockname = "DIS";
			//stockname = "AMZN";
			stockname += ".csv";
			ifstream testing(stockname); // tester to make sure the name being used is valid

			if (!testing) {// error reading input file
				cout << "invalid ticker. make sure you have the correct '.csv' file." << endl;
				system("pause");
				system("cls");
			}
			else
				useablefile = true; // no error; useable file
		} while (!useablefile);

		ifstream stock(stockname); // proceed with the name the user used

		//outputfile
		string outputname; // stirng that will be the name of the output file that will be used
		bool useableoutput = false;

		cout << "What will the output file name be?" << endl;
		getline(cin, outputname);
		//outputname = "Output";
		outputname += ".txt";

		//no required dummy proofing; creates a file if it's not the same name as an existing file
	   //using txt
	   // (technically using .txt is not necessary, but will be included)

		cout << "Analysis of " << stockname << " has started." << endl << endl;
		cout << "Processing . . ." << endl << endl;

		//include the ticker to the output file name
		outputname = stockname.substr(0, stockname.size() - 4) + '_' + outputname;
		cout << outputname << endl << endl;
		cout << "Ticker complete." << endl << endl;// console update


		ofstream output(outputname); // use submitted name of the output file

		char delimcomma = ','; //delimiter used in the file to seperate chunks of info

		vector<string> dates = readfromfile(stock, delimcomma, 1); // create vector of dates

		output << "Stocks are analyzed from " << dates[0] << " to " << dates[dates.size() - 1] << endl; // date range of the data
		cout << "Dates complete." << endl << endl;// console update


		stock.open(stockname); // reopen as it was closed before from a previous function
		vector<string> closes = readfromfile(stock, delimcomma, 5); // creates a vector of the closed prices
		vector<double> closedouble; // creating a vector of doubles to compare with values and not characters ( not a string)

		for (int i = 0; i < closes.size(); i++) { //create a vector of doubles for the closing price
			//rounding
			double temp = stod(closes[i]);
			temp = temp * 100;
			temp = rint(temp);
			temp = temp / 100;
			closedouble.push_back(temp); // convert string to double
			//cout <<  i << ") "<< closedouble[i] << ";" << endl; // writes all of the close prices in the last year; price of a stock at the end of the day
		}
		output << "Most recent close price: " << closedouble[closes.size() - 1] << endl;
		cout << "close price complete." << endl << endl; // console update


		vector<string> stocksrising = longstreak(closedouble, closes, dates, true); // finds the longest increasing streak

		output << "longest increasing streak: " << stocksrising[0] << " to " << stocksrising[1] << endl;
		cout << "longest increasing streak complete." << endl << endl;// console update

		output << "price in stream rose from: " << stocksrising[2] << " to " << stocksrising[3] << endl;
		cout << "price in streak complete." << endl << endl;// console update

		vector<string> stockslowering = longstreak(closedouble, closes, dates, false); // finds the longest increasing streak

		output << "longest decreasing streak: " << stockslowering[0] << " to " << stockslowering[1] << endl;
		cout << "longest decreasing streak complete." << endl << endl;// console update

		output << "price in stream lowered from: " << stockslowering[2] << " to " << stockslowering[3] << endl;
		cout << "price in streak complete." << endl << endl;// console update

		double averageclosed = average(closedouble);
		output << "the average closed price: " << averageclosed << endl;
		cout << "average complete." << endl << endl;// console update

		//vector<string> maxprice = highest(closedouble, closes, dates);
		//output << "highest price: " << maxprice[0] << " on " << maxprice[1] << endl;

		int maxprice = highest(closedouble, closes, dates);
		output << "highest price: " << closedouble[maxprice] << " on " << dates[maxprice] << endl;

		cout << "highest price complete." << endl << endl;// console update

		//vector <string> minprice = lowest(closedouble, closes, dates);
		//output << "lowest price: " << minprice[0] << " on " << minprice[1] << endl;

		int minprice = lowest(closedouble, closes, dates);
		output << "lowest price: " << closedouble[minprice] << " on " << dates[minprice] << endl;

		cout << "lowest price complete." << endl << endl;// console update

		stock.open(stockname);
		vector<string> volume = readfromfile(stock, delimcomma, 7);
		vector<double> volumedb;


		for (int i = 0; i < volume.size(); i++) { // creating a parallel vector of doubles from the stirng vector
			volumedb.push_back(stod(volume[i]));
			//cout << volumedb[i] << ";" << endl;
		}

		//vector<string> maxvolume = highest(volumedb, volume, dates);
		//output << "Max Volume / most amount of trades: " << maxvolume[0] << " on " << maxvolume[1] << endl;

		int addhigh = highest(volumedb, volume, dates);
		output << "Max Volume / most amount of trades: " << volume[addhigh] << " on " << dates[addhigh] << endl;

		cout << "Max Volume complete." << endl << endl;// console update

		vector<double> quartiles = calcquartile(closedouble);
		output << "quartile 1: " << quartiles[0] << endl;
		output << "quartile 2: " << quartiles[1] << endl;
		output << "quartile 3: " << quartiles[2] << endl;

		cout << "Quartiles complete." << endl << endl;// console update

		double stdd = stddevi(closedouble, averageclosed);
		output << "standard deviation: " << stdd << endl;
		cout << "standard deviation complete." << endl << endl;// console update

		double change = percentchange(closedouble, closes, dates);
		output << "% change since Dec 31st: " << change << endl;
		cout << "Percent change complete." << endl << endl;// console update

		double firstvlast = ((closedouble[closedouble.size() - 1] - closedouble[0]) / closedouble[0]) * 100;

		output << "% change since beginning: " << firstvlast << endl;
		cout << "change since beginning complete." << endl << endl;// console update


		stock.open(stockname);
		vector <string> openingpricestr = readfromfile(stock, delimcomma, 2);
		vector<double> openingprice;
		for (int i = 0; i < openingpricestr.size(); i++) { // creating a parallel vector of doubles from a string
			openingprice.push_back(stod(openingpricestr[i])); // adding to the new vector of doubles
			//cout << openingprice[i] << endl;
		}
		vector <int> increasedecrease = daybydaychange(closedouble, openingprice);

		output << "days when stocks increase from previous day: " << increasedecrease[0] << endl;
		output << "days when stocks decrease from previous day: " << increasedecrease[1] << endl;
		output << "days when stocks have no change from previous day: " << increasedecrease[2] << endl;
		cout << "days increasing / decreasing complete." << endl << endl;// console update

		//all program functions are complete, prompt in console
		cout << "Processing complete." << endl << endl;
		cout << "Program is done analyzing and compiled all information onto file " << outputname << "." << endl << endl;
		stock.close(); // close the files
		output.close();

		//ask user if they want to run the program again
		cout << "do you want to run analysis again?" << endl;
		cout << "Enter 1 to run program again." << endl << endl;
		string use;
		getline(cin, use);
		if (use[0] != '1' || use.size() != 1) // if its not '1' then end program
			useagain = false;
		system("cls");
	} while (useagain); // run program again or not if the user chooses to do so

	system("pause");
	return 0; // end program
}

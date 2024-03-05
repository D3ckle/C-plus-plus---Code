# include <iostream>

using namespace std;

//Assume an array is already sorted
//Create a function which will return the array of modes(if any that exist) in the array
//Hint: You first have to scan the array and see the count of the most frequently appearing number 
//so the mode is any number that appears X number of times
//Then you have to scan down the array and see which number appears X number of times

int most = 0; // records the times a number has appeared in the array.
int mode; // records the address of the number that appeared the most
int temp = 0; //temporarily holds a number; compared to variable mode for checing if num A appears more than num B
int unique = 0; //# of unique numbers in the array; ex: (1,1,2,3) - 3 unique numbers

double calc(int arr[], int length); //array that finds the mode and the # of times that the mode appears


int main()
{
	int length = 0;

	cout << "how long is the array?\n";
	cin >> length;
	int* address = new int[length];

	for (int i = 0; i < length; i++) // asking user to assign a number to each spot in the array
	{
		cout << "Address ";
		cout << i;
		cout << ": \n";
		cin >> address[i];
	}

	calc(address, length); //call to the function

	cout << address[mode] << " apppeared the most, appearing " << most << " times." << endl;
	system("Pause");
	return 0;
}

double calc(int arr[], int length) // main logic to finding the mode of the array
{
	for (int i = 0; i < length; i++) //finding all the unique numbers
		//creating a list that is of only the unique numbers in the array so once i 
		//compare this created list to the original,i can then count how many of each number
	{
		if (arr[i] != arr[i + 1]) //comparing the next number in the list to see if it is the same number
			unique++;
		else if (i == length) 
		{
			for (int j = 0; j < length; j++)//because there is no 'next #' for the last # 
	//in the list, im comparing all previous numbers in the list to see if it is unique or not
			{
				if (arr[length] == arr[j]) 
					unique++;
			}
		}
	}

	//creating array of the unique numbers
	int* uniquearr = new int[unique];

	for (int i = 0; i < unique; i++) //unique # array list 
	{
		for (int j = 0; j < length; j++) //COMPARING Original ARRAY To THE UNIQUE # ARRAY (list)
		{
			if (arr[i] == arr[j])
			{
				temp++;
			}
		}
		if (most < temp)
		{
			mode = i; //tracks the address of the mode
			most = temp;
		}
		temp = 0;
	} //get the 

int *modearr = new int[unique];

	return (most); // output both the mode, and the amount of times the mode appears
	return (mode);
}

//getting the specific unique number in the array
//    /\
//special case (last number) see if the last number is unique it self
//compare the next number if it is the same
//all unique numbers in the list, count them
//index 1, 
// outputing all the unique numbers (testing)
// printing the mode list
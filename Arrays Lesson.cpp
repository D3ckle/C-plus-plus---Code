# include <iostream>

using namespace std;

//global variables should be use for unchanging variables; so no one will affect it;available everywhere
//const int TOTAL_DOGS = 100;

double averageDogAge(int arr[], int size);

bool swap(int arr[], int spot1[], int spot2[], int spot3[], int spot4[], int spot5[])
//bool swap(int arr[], int size)
{
	if (spot1 < 0 || spot1 >= size || spot2 < 0)
		return false;

	int temp = arr[spot1];
	int arr[spot1] = arr[spot2];
	arr[spot2] = temp;

	return true;
}
int* largestValueSpots(int arr[], int size)
{	//include a kick out if ther is only 1 element or 0 elements
	int max = arr[0];
	int maxcount = 0;
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			maxcount = 1;
		}
		else if (arr[i] == max)
			maxcount++;
	}
	int*largestSpots = new int[maxcount];
	int index2 = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == max)
			largestSpots[index2++] = i;
	}
	return largestSpots;
}

int main()
{
	int scores[5]; //5 address are created for integers
	cout << scores << endl;
	scores[0] = 3; //0; zero steps away form where youre starting
	cout << scores[1] << endl; //whatever is assigned to this spot, it can be anything, and it makes it an integer
	for (int i = 0; i < 5; i++)
		scores[i] = i;
	for (int i = 0; i < 6; i++) //extra addresses (address 6 in this case) will still run, even if there is no assigned value
		//errors like this are hard to catch; make usre to rememeber arrays
		cout << scores[i] << endl;

	int size = 0;
	cout << "how big is your array?\n";
	cin >> size; // must souce form the heap (instead of compile), instead as you cna use that at any point
	int *dogs = new int[size]; //code to use an array form the heap; works the same as any array

	for (int i = 0; i < size; i++) //showcase the heap array
	{
		cout << "enter dog age: ";
		cin >> dogs[i];
	}

	double averageAge = averageDogAge(dogs, size); // array(address, length of array)
	system("pause");
	return 0;
}

double averageDogAge(int arr[], int size)
{
	double total; //doubles with non integer values
	for (int i = 0; i < size; i++)
		total += arr[i];
	return (total / size);
}
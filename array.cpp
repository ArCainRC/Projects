#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value)
{
	if (n < 0)	// checking if n is negative
	{
		return -1;
	}

	for (int i = 0; i < n; i++)	// to append 'value' onto all the elements of the array
	{
		a[i] = a[i] + value;
	}
	return n;
}

int lookup(const string a[], int n, string target)
{
	if (n < 0)	// checking if n is negative
	{
		return -1;
	}

	for (int i = 0; i < n; i++)	// checks entire array to see find smallest position element equal to 'target'
	{
		if (a[i] == target)
		{
			return i;
		}
	}

	return -1;
}

int positionOfMax(const string a[], int n)
{
	if (n < 0) // checking if n is negative
	{
		return -1;
	}

	string bigstr = "";	// a buffer value to place the biggest string in the array
	int pos=-1;

	for (int i = 0; i < n; i++)
	{
		if (a[i] > bigstr)	
		{
			bigstr = a[i];	// replacing of the previous biggest string
			pos = i;
		}
	}

	return pos;
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0 || pos >= n || pos < 0)	// checking if n or pos is negative, and if pos is greater than or equal to number of elements in array
	{
		return -1;
	}		

	for (int i=pos; i+1<n; i++)	// to move all the other elements to one place left in the array, and putting the element at pos at the end
	{
		string move = a[i];	
		string toMove = a[i + 1];
		a[i] = toMove;
		a[i + 1] = move;
	}
	return pos;
}

int countRuns(const string a[], int n)
{
	if (n < 0)	// checking if n is negative
	{
		return -1;
	}

	int repeat = 0;	// initial value for number of unique strings in array

	for (int i = 0; i < n; i++)	// a loop where each element is checked to see if an element equal to it occurs before their position in the string, as position increments
	{
		int repeatCheck = 0;	// used to mark if an element is a repeat of a previous one
		for (int j = 0; j < i; j++)	
		{
			if (i == j)
			{
				continue;
			}
			
			if (a[i] == a[j])	// if the equality for a[i] is true, then that element was not the first occurrence of that string in the array, hence not unique
			{
				repeatCheck = 1;	// used to mark that the element is not unique
				break;
			}		

		}
		if (repeatCheck == 0)
		{
			repeat++;	// if the condition is true, then that element is unique, and the value of unique elements is incremented
		}
	}
	return repeat;
}

int flip(string a[], int n)
{
	if (n < 0)	// checking if n is negative
	{
		return -1;
	}

	int endCheck = n;	// variable used to flip the strings around, starts out at the (last position + 1)
	for (int i = 0; i < n / 2; i++)	// i < n/2 will work for both even and odd number of elements
	{
		string a1 = a[i];
		string b1 = a[endCheck - 1];
		a[i] = b1;	// swapping positions
		a[endCheck - 1] = a1;
		endCheck--;	// endCheck is reduced to the (last position + 1) -1, and so on
	}

	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0) // checking if n1 or n2 is negative
	{
		return -1;
	}

	int simiCheck = 0;	// variable used to check the first position where the corresponding elements of the arrays are not equal

	while (simiCheck < n1 && simiCheck < n2)	// if one of the arrays runs out, simiCheck will equal the value of the lesser one
	{
		if (a1[simiCheck] == a2[simiCheck])
		{
			simiCheck++;	// if they are equal, incrememnt position
			continue;
		}
		else
		{
			return simiCheck;	// returns first position where the corresponding elements of the arrays are not equal
		}
	}
	return simiCheck;	// returns either n1 or n2
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)	// checking if n1 or n2 is negative
	{
		return -1;
	}

	if (n2 == 0)	// if n2 is 0, it means the array is a subsequence of 0 elements, which will always be at the start of an array, hence return position 0
	{
		return 0;
	}

	int pos = 0;	// used to check position of the start of subsequence, if it exists
	int subCheck = 0;	// used to check if the subsequence exists in the main array
	for (; pos < n1; pos++)	// a loop used to check the entire main array for the first element of the sub-array
	{							
		if (a1[pos] == a2[0] && pos+n2 <= n1)	// checks both 1. if the first element of the sub-array was found in the main array, and 2. if there are enough elements left in the main-array for the subsequence to be present in it
		{
			for (int i = 0; i < n2; i++)
			{
				if( a1[(pos+i)] != a2[i])
				{
					subCheck=1;	// if the condition is false, then the subsequence has not been found yet, so it will go back to the main loop to search for the first element of the subsequence again
				}
			}
			if (subCheck == 0)
			{
				return pos;	// this means that the subsequence has been found, and it will return the position where it started
			}
		}
	}

	return -1;	// the subsequence wasn't found, so -1 is returned
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0) // checking if n1 or n2 is negative
	{
		return -1;
	}

	int smallestPos = n1;	// sets the variable as an value which would always be bigger than the position of an element in the array, unless changed, which it will be if two equal elements from both arrays are found
							// if an equal element is found for both arrays, it will store the position of that element from the first array
	int samePos = n1 + 1;	// sets the variable as a value which would always be bigger than smallestPos, unless changed, which it will be if two equal elements from both arrays are found

	for (int i = 0; i < n2; i++)	// used to move from one element of a2[] to another
	{
		for (int j = 0; j < n1; j++)	// used to move from one element of a1[] to another, while comparing each of them to the current element from a2[]
		{
			if (a2[i] == a1[j])
			{
				samePos = j;	// changes the value of samePos to the position in a1 of the equal element
				break;
			}
		}

		if (samePos < smallestPos)	// if the obtained samePos is smaller than the current smallest position of two equal elements from a1, which it will be for the first found position of such, as no position can be equal to or greater than the size of the array, and that value is what we have initialized smallestPos as 
		{
			smallestPos = samePos;	// assigns new smallest equal position to smallestPos
			samePos = n1 + 1;	// resets the value of samePos
		
		}
	}

	if (smallestPos == n1)	// this means the value of smallestPos was unchanged, which then means that no equal elements were found between the two arrays, hence returning -1
	{
		return -1;
	}
	else
	{
		return smallestPos;	// returns the smallest equal position
	}
}

int divide(string a[], int n, string divider)
{
	if (n < 0)	// checking if n is negative
	{
		return -1;
	}

	int midPlace = 0;	// a value to store the position of the first element greater than or equal to 'divider'
	int greatCheck = 0;	// used to check if there are any elements 'divider' is greater than
	for (int i = 0; i < n; i++)	// loop to check if each element of the array is less than 'divider'
	{
		if (a[i] < divider)	// if a string is lesser than divider, it gets moved to the start of the array
		{
			string toMove = a[i];
			for (int j = i - 1; j >= 0; j--)	// a loop used move all the elements before this element to the right, which happens to overwrite the current position of the lesser string with the element in the front(position-wise) of it in the array 
			{
				a[j + 1] = a[j];
			}
			a[0] = toMove;	// places the lesser string at the start of the array
			midPlace++;	// this will increment throughout the loop until it lists the poition of the first element greater than or equal to 'divider'
			greatCheck = 1;	// this shows at least one string is lesser than 'divider'
		}
	}

	int newMidPlace = midPlace;	// this variable will used as a position for any element equal to 'divider' to be placed at, which is, the position right afte the last element smaller than 'divider'

	for (int i = 0; i < n; i++)	// loop to check if any element in the array is equal to 'divider'
	{
		if (a[i] == divider)	// if this is true, it will move all the elements greater than 'divider'( and by proxy, greater than a[i]) one position forward in the array, which will overwrite the position of i with the value before it
		{
			string toMove = a[i];
			for (int j = i - 1; j >= newMidPlace; j--)	// by using j>= newMidPlace, we ensure that the only elements moved forward are those greater than 'divider', not those lesser than it, as those elements occupy a position smaller the newMidPlace, which will always be the position after which no element will be lesser than 'divider'
			{
				a[j + 1] = a[j];	// moving of elements
			}
			a[newMidPlace] = toMove;	// placing the value equal to 'divider' ( a[i] ), at the position in the middle of strings lesser than and greater than 'dividend'
			newMidPlace++;	// increases the position of newMidPlace, so if another value equal to dividend is found, it can be placed at the position after that of the first value equal greater than dividend, and so on 
		}
	}

	if (greatCheck == 0)	// this means no element lesser than 'dividend' was found, hence the first value greater than or equal to dividend will be at the first position, aka position 0
	{
		return 0;
	}
	
	return midPlace;	// midPlace will equal 'n' if 'divider' is greater than everything, as midPlace will be incremented for each value of a[i] lesser than it
	
}



int main()
{	
	// this is the final build
	string arr[9] = { "Jason", "Shawn", "Dio", "Richter", "Caesar","Dio", "Caesar", "Jason", "Shawn" };
	string arr1[5] = { "Alm", "Xander", "Caeda", "Xander", "Robin" };
	string subArr[3] = { "Richter", "Caesar", "Dio" };
	string simArr1[4] = {"Naruto", "Caesar", "Jason","Jekyll"};
	string simArr2[4] = {"Naruto", "Caesar", "Jason","Shawn"};
	string divArr[6] = { "John", "Zack", "Xavier","Zareidriel","Kevin", "Xavier" };
	string whyArr[1] = { " " };

	string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
	assert(lookup(h, 7, "eleni") == 5);
	assert(lookup(h, 7, "ed") == 2);
	assert(lookup(h, 2, "ed") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "greg", "gavin", "fiona", "kevin" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");

	string e[4] = { "ed", "xavier", "", "eleni" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "fiona", "ed", "john" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");

	assert(divide(h, 7, "fiona") == 3);

	cout << "All tests succeeded" << endl;
	
		
	

	
	/*
	
	cout << divide(divArr, 6, "Zz") << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << divArr[i] << endl;

	}	*/
	// cout << lookupAny(arr, 9, subArr, 3);
	
	// cout << subsequence(arr, 1, subArr, 2);
	
	// cout << differ(simArr1, -2, simArr2, 2);

	/*
	cout << flip(simArr2, 3) << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << simArr2[i] << endl;

	*/

	// cout << countRuns(arr, 0);


	/*
	cout << rotateLeft(arr1, 5, 2) << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << arr1[i] << endl;
	}
	*/

	
	/*
	string arr2[5] = { "Alm", "Xander", "Caeda", "Julius", "Robin" };
	cout << positionOfMax(arr2, 5) << endl;
	string arr3[5] = { "Alm", "Xander", "Caeda", "Julius", "Robin" };
	cout << positionOfMax(arr3, -3) << endl;
	string arr4[5] = { "Alm", "Caeda", "Xander", "Xander", "Robin" };
	cout << positionOfMax(arr4, 0) << endl; */

	/*
	cout << appendToAll(arr, 9, "!!!") << endl;
	
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << endl;
	}
	cout << "----" << endl;
	
	cout << appendToAll(arr, 5, "???") << endl;

	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << endl;
	}

	cout << "----" << endl;

	cout << appendToAll(arr, -2, "?!?!") << endl;

	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << endl;
	}
	*/

	/*
	cout << lookup(arr, 9, "Caesar")<< endl;
	cout << lookup(arr, 2, "Dio") << endl;
	cout << lookup(arr, 0, "Jason") << endl;
	cout << lookup(arr, -3, "Richter") << endl;
	cout << lookup(arr, 11, "") << endl;
	*/



	
	
	// cout << differ(simArr1, 5, simArr2, 4);
	// cout << lookupAny(simArr1, 6, simArr2, 4);

	/* cout << divide(divArr, 5, "Zephiel") << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << divArr[i] << endl;
	} */

	

}